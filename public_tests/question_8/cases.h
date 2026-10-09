#pragma once
#include "catch.hpp"
#include "lectura_ciclica.h"
#include <array>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;
static std::array<std::string, 3> preparar_q8(
    int indice, const std::array<std::vector<int>, 3>& valores) {
    const auto dir = fs::temp_directory_path() / ("prog3_concurrente_q8_" + std::to_string(indice));
    fs::remove_all(dir);
    fs::create_directories(dir);
    std::array<std::string, 3> rutas;
    for (std::size_t i = 0; i < 3; ++i) {
        auto ruta = dir / (std::string(1, static_cast<char>('A' + i)) + ".txt");
        rutas[i] = ruta.string();
        std::ofstream salida(ruta);
        for (int n : valores[i]) salida << n << '\n';
    }
    return rutas;
}
static std::vector<int> salida_q8(const std::string& texto) {
    std::istringstream entrada(texto);
    std::vector<int> valores;
    for (int n; entrada >> n;) valores.push_back(n);
    return valores;
}
#if TEST_CASE_INDEX == 1
TEST_CASE("Q8 intercala 10 numeros de A B C") {
    auto rutas = preparar_q8(1, {{{1, 4, 7, 10}, {2, 5, 8}, {3, 6, 9}}});
    std::ostringstream salida;
    leer_archivos_en_turnos(rutas, salida);
    REQUIRE((salida_q8(salida.str()) == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
    fs::remove_all(fs::path(rutas[0]).parent_path());
}
TEST_CASE("Q8 acepta archivos vacios") {
    auto rutas = preparar_q8(11, {{{}, {}, {}}});
    std::ostringstream salida;
    leer_archivos_en_turnos(rutas, salida);
    REQUIRE((salida.str().empty()));
    fs::remove_all(fs::path(rutas[0]).parent_path());
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q8 termina con 100 numeros en archivos desiguales") {
    std::array<std::vector<int>, 3> valores;
    for (int n = 1; n <= 100; ++n) valores[(n - 1) % 3].push_back(n);
    auto rutas = preparar_q8(2, valores);
    std::ostringstream salida;
    leer_archivos_en_turnos(rutas, salida);
    auto numeros = salida_q8(salida.str());
    REQUIRE((numeros.size() == 100));
    for (int i = 0; i < 100; ++i) REQUIRE((numeros[i] == i + 1));
    fs::remove_all(fs::path(rutas[0]).parent_path());
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q8 intercala 1000 numeros") {
    std::array<std::vector<int>, 3> valores;
    for (int n = 1; n <= 1000; ++n) valores[(n - 1) % 3].push_back(n);
    auto rutas = preparar_q8(3, valores);
    std::ostringstream salida;
    leer_archivos_en_turnos(rutas, salida);
    auto numeros = salida_q8(salida.str());
    REQUIRE((numeros.size() == 1000));
    for (int i = 0; i < 1000; ++i) REQUIRE((numeros[i] == i + 1));
    fs::remove_all(fs::path(rutas[0]).parent_path());
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q8 intercala 10000 numeros sin perdidas") {
    std::array<std::vector<int>, 3> valores;
    for (int n = 1; n <= 10000; ++n) valores[(n - 1) % 3].push_back(n);
    auto rutas = preparar_q8(4, valores);
    std::ostringstream salida;
    leer_archivos_en_turnos(rutas, salida);
    auto numeros = salida_q8(salida.str());
    REQUIRE((numeros.size() == 10000));
    for (int i = 0; i < 10000; ++i) REQUIRE((numeros[i] == i + 1));
    fs::remove_all(fs::path(rutas[0]).parent_path());
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
