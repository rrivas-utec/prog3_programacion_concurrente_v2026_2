#pragma once
#include "catch.hpp"
#include "clasificacion_numeros.h"
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;
static std::vector<int> leer_q1(const fs::path& archivo) {
    std::ifstream entrada(archivo);
    std::vector<int> numeros;
    for (int n; entrada >> n;) numeros.push_back(n);
    return numeros;
}
static fs::path preparar_q1(int indice, const std::vector<int>& numeros) {
    auto dir = fs::temp_directory_path() / ("prog3_concurrente_q1_" + std::to_string(indice));
    fs::remove_all(dir);
    fs::create_directories(dir);
    std::ofstream salida(dir / "numeros.txt");
    for (int n : numeros) salida << n << '\n';
    return dir;
}
#if TEST_CASE_INDEX == 1
TEST_CASE("Q1 clasifica 10 valores") {
    std::vector<int> numeros{2, 3, 5, 7, 30, 6, 10, 15, 11, 13};
    auto dir = preparar_q1(1, numeros);
    clasificar_numeros((dir / "numeros.txt").string(), dir.string());
    REQUIRE((leer_q1(dir / "pares.txt") == std::vector<int>{2, 30, 6, 10}));
    REQUIRE((leer_q1(dir / "mult3.txt") == std::vector<int>{3, 30, 6, 15}));
    REQUIRE((leer_q1(dir / "mult5.txt") == std::vector<int>{5, 30, 10, 15}));
    REQUIRE((leer_q1(dir / "otros.txt") == std::vector<int>{7, 11, 13}));
    fs::remove_all(dir);
}
TEST_CASE("Q1 crea los cuatro archivos cuando la entrada esta vacia") {
    auto dir = preparar_q1(11, {});
    clasificar_numeros((dir / "numeros.txt").string(), dir.string());
    for (auto nombre : {"pares.txt", "mult3.txt", "mult5.txt", "otros.txt"}) {
        REQUIRE((fs::exists(dir / nombre)));
        REQUIRE((leer_q1(dir / nombre).empty()));
    }
    fs::remove_all(dir);
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q1 clasifica 100 valores con categorias superpuestas") {
    std::vector<int> numeros;
    for (int n = 1; n <= 100; ++n) numeros.push_back(n);
    auto dir = preparar_q1(2, numeros);
    clasificar_numeros((dir / "numeros.txt").string(), dir.string());
    std::vector<int> pares, mult3, mult5, otros;
    for (int n : numeros) {
        if (n % 2 == 0) pares.push_back(n);
        if (n % 3 == 0) mult3.push_back(n);
        if (n % 5 == 0) mult5.push_back(n);
        if (n % 2 && n % 3 && n % 5) otros.push_back(n);
    }
    REQUIRE((leer_q1(dir / "pares.txt") == pares));
    REQUIRE((leer_q1(dir / "mult3.txt") == mult3));
    REQUIRE((leer_q1(dir / "mult5.txt") == mult5));
    REQUIRE((leer_q1(dir / "otros.txt") == otros));
    fs::remove_all(dir);
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q1 clasifica 1000 valores repetidos") {
    std::vector<int> numeros;
    for (int i = 0; i < 1000; ++i) numeros.push_back(i % 30 + 1);
    auto dir = preparar_q1(3, numeros);
    clasificar_numeros((dir / "numeros.txt").string(), dir.string());
    std::vector<int> pares, mult3, mult5, otros;
    for (int n : numeros) {
        if (n % 2 == 0) pares.push_back(n);
        if (n % 3 == 0) mult3.push_back(n);
        if (n % 5 == 0) mult5.push_back(n);
        if (n % 2 && n % 3 && n % 5) otros.push_back(n);
    }
    REQUIRE((leer_q1(dir / "pares.txt") == pares));
    REQUIRE((leer_q1(dir / "mult3.txt") == mult3));
    REQUIRE((leer_q1(dir / "mult5.txt") == mult5));
    REQUIRE((leer_q1(dir / "otros.txt") == otros));
    fs::remove_all(dir);
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q1 clasifica 10000 valores sin perder elementos") {
    std::vector<int> numeros;
    for (int n = 1; n <= 10000; ++n) numeros.push_back(n);
    auto dir = preparar_q1(4, numeros);
    clasificar_numeros((dir / "numeros.txt").string(), dir.string());
    std::vector<int> pares, mult3, mult5, otros;
    for (int n : numeros) {
        if (n % 2 == 0) pares.push_back(n);
        if (n % 3 == 0) mult3.push_back(n);
        if (n % 5 == 0) mult5.push_back(n);
        if (n % 2 && n % 3 && n % 5) otros.push_back(n);
    }
    REQUIRE((leer_q1(dir / "pares.txt") == pares));
    REQUIRE((leer_q1(dir / "mult3.txt") == mult3));
    REQUIRE((leer_q1(dir / "mult5.txt") == mult5));
    REQUIRE((leer_q1(dir / "otros.txt") == otros));
    fs::remove_all(dir);
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
