#pragma once
#include "catch.hpp"
#include "suma_archivos.h"
#include <array>
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;
static fs::path preparar_q3(int indice, const std::array<std::vector<int>, 4>& valores) {
    auto dir = fs::temp_directory_path() / ("prog3_concurrente_q3_" + std::to_string(indice));
    fs::remove_all(dir);
    fs::create_directories(dir);
    const std::array<const char*, 4> nombres{"pares.txt", "mult3.txt", "mult5.txt", "otros.txt"};
    for (std::size_t i = 0; i < 4; ++i) {
        std::ofstream salida(dir / nombres[i]);
        for (int n : valores[i]) salida << n << '\n';
    }
    return dir;
}
#if TEST_CASE_INDEX == 1
TEST_CASE("Q3 suma 10 valores repartidos entre archivos") {
    auto dir = preparar_q3(1, {{{2, 4, 6}, {3, 6, 9}, {5, 10}, {7, 11}}});
    REQUIRE((sumar_archivos_clasificados(dir.string()) == std::array<long long, 4>{12, 18, 15, 18}));
    fs::remove_all(dir);
}
TEST_CASE("Q3 informa cuando falta un archivo") {
    auto dir = preparar_q3(11, {{{2}, {3}, {5}, {7}}});
    fs::remove(dir / "mult5.txt");
    REQUIRE_THROWS(sumar_archivos_clasificados(dir.string()));
    fs::remove_all(dir);
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q3 suma 100 valores con archivos de tamaños distintos") {
    std::array<std::vector<int>, 4> datos;
    std::array<long long, 4> esperado{};
    for (int i = 0; i < 100; ++i) {
        int indice = i % 4;
        int valor = i + 1;
        datos[indice].push_back(valor);
        esperado[indice] += valor;
    }
    auto dir = preparar_q3(2, datos);
    REQUIRE((sumar_archivos_clasificados(dir.string()) == esperado));
    fs::remove_all(dir);
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q3 suma 1000 valores repetidos") {
    std::array<std::vector<int>, 4> datos;
    std::array<long long, 4> esperado{};
    for (int i = 0; i < 1000; ++i) {
        int indice = i % 4;
        int valor = i % 17 + 1;
        datos[indice].push_back(valor);
        esperado[indice] += valor;
    }
    auto dir = preparar_q3(3, datos);
    REQUIRE((sumar_archivos_clasificados(dir.string()) == esperado));
    fs::remove_all(dir);
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q3 suma 10000 valores en cuatro archivos") {
    std::array<std::vector<int>, 4> datos;
    std::array<long long, 4> esperado{};
    for (int i = 0; i < 10000; ++i) {
        int indice = i % 4;
        int valor = i + 1;
        datos[indice].push_back(valor);
        esperado[indice] += valor;
    }
    auto dir = preparar_q3(4, datos);
    REQUIRE((sumar_archivos_clasificados(dir.string()) == esperado));
    fs::remove_all(dir);
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
