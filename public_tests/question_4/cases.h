#pragma once
#include "catch.hpp"
#include "frecuencia_numeros.h"
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;
static fs::path preparar_q4(int indice, const std::vector<int>& numeros) {
    auto archivo = fs::temp_directory_path() / ("prog3_concurrente_q4_" + std::to_string(indice) + ".txt");
    std::ofstream salida(archivo);
    for (int n : numeros) salida << n << '\n';
    return archivo;
}
#if TEST_CASE_INDEX == 1
TEST_CASE("Q4 cuenta 10 valores repetidos") {
    auto archivo = preparar_q4(1, {1, 2, 1, 3, 2, 1, 4, 4, 4, 4});
    auto frecuencias = contar_frecuencias(archivo.string(), 3);
    REQUIRE((frecuencias.size() == 4));
    REQUIRE((frecuencias.at(1) == 3));
    REQUIRE((frecuencias.at(2) == 2));
    REQUIRE((frecuencias.at(3) == 1));
    REQUIRE((frecuencias.at(4) == 4));
    fs::remove(archivo);
}
TEST_CASE("Q4 acepta archivo vacio y mas hilos que datos") {
    auto archivo = preparar_q4(11, {});
    REQUIRE((contar_frecuencias(archivo.string(), 4).empty()));
    fs::remove(archivo);
    archivo = preparar_q4(12, {9, 9});
    REQUIRE((contar_frecuencias(archivo.string(), 10).at(9) == 2));
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q4 cuenta 100 valores con varios hilos") {
    std::vector<int> numeros;
    for (int i = 0; i < 100; ++i) numeros.push_back(i % 10);
    auto archivo = preparar_q4(2, numeros);
    auto frecuencias = contar_frecuencias(archivo.string(), 10);
    REQUIRE((frecuencias.size() == 10));
    for (int n = 0; n < 10; ++n) REQUIRE((frecuencias.at(n) == 10));
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q4 cuenta 1000 valores con repeticiones") {
    std::vector<int> numeros;
    for (int i = 0; i < 1000; ++i) numeros.push_back(i % 7);
    auto archivo = preparar_q4(3, numeros);
    auto frecuencias = contar_frecuencias(archivo.string(), 8);
    REQUIRE((frecuencias.size() == 7));
    for (int n = 0; n < 7; ++n) REQUIRE((frecuencias.at(n) == 1000 / 7 + (n < 1000 % 7)));
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q4 conserva 10000 valores bajo contencion") {
    std::vector<int> numeros;
    for (int i = 0; i < 10000; ++i) numeros.push_back(i % 5 + 1);
    auto archivo = preparar_q4(4, numeros);
    auto frecuencias = contar_frecuencias(archivo.string(), 16);
    REQUIRE((frecuencias.size() == 5));
    for (int n = 1; n <= 5; ++n) REQUIRE((frecuencias.at(n) == 2000));
    fs::remove(archivo);
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
