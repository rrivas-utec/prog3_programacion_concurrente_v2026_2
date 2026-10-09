#pragma once
#include "catch.hpp"
#include "suma_rangos.h"
#include <array>
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;
static fs::path preparar_q2(int indice, const std::vector<int>& numeros) {
    auto archivo = fs::temp_directory_path() / ("prog3_concurrente_q2_" + std::to_string(indice) + ".txt");
    std::ofstream salida(archivo);
    for (int n : numeros) salida << n << '\n';
    return archivo;
}
#if TEST_CASE_INDEX == 1
TEST_CASE("Q2 suma 10 valores en los extremos de los rangos") {
    auto archivo = preparar_q2(1, {1, 10, 11, 20, 21, 30, 91, 100, 0, 101});
    auto sumas = sumar_rangos(archivo.string());
    REQUIRE((sumas[0] == 11));
    REQUIRE((sumas[1] == 31));
    REQUIRE((sumas[2] == 51));
    REQUIRE((sumas[9] == 191));
    for (int i = 3; i < 9; ++i) REQUIRE((sumas[i] == 0));
    fs::remove(archivo);
}
TEST_CASE("Q2 ignora extremos invalidos y conserva repeticiones") {
    auto archivo = preparar_q2(11, {0, 1, 1, 10, 101, 200});
    auto sumas = sumar_rangos(archivo.string());
    REQUIRE((sumas[0] == 12));
    for (int i = 1; i < 10; ++i) REQUIRE((sumas[i] == 0));
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q2 suma 100 valores de todos los rangos") {
    std::vector<int> numeros;
    for (int n = 1; n <= 100; ++n) numeros.push_back(n);
    auto archivo = preparar_q2(2, numeros);
    auto sumas = sumar_rangos(archivo.string());
    for (int i = 0; i < 10; ++i) REQUIRE((sumas[i] == 100 * i + 55));
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q2 suma 1000 valores repetidos") {
    std::vector<int> numeros;
    for (int i = 0; i < 1000; ++i) numeros.push_back(i % 100 + 1);
    auto archivo = preparar_q2(3, numeros);
    auto sumas = sumar_rangos(archivo.string());
    for (int i = 0; i < 10; ++i) REQUIRE((sumas[i] == 10 * (100 * i + 55)));
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q2 suma 10000 valores con datos fuera de rango") {
    std::vector<int> numeros;
    for (int i = 0; i < 10000; ++i) numeros.push_back(i % 102);
    auto archivo = preparar_q2(4, numeros);
    auto sumas = sumar_rangos(archivo.string());
    std::array<long long, 10> esperado{};
    for (int n : numeros) if (n >= 1 && n <= 100) esperado[(n - 1) / 10] += n;
    REQUIRE((sumas == esperado));
    fs::remove(archivo);
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
