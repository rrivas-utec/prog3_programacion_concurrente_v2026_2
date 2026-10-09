#pragma once
#include "catch.hpp"
#include "logger.h"
#include <filesystem>
#include <fstream>
#include <set>
#include <string>
#include <thread>
#include <vector>

namespace fs = std::filesystem;
static std::vector<std::string> leer_lineas_q6(const fs::path& archivo) {
    std::ifstream entrada(archivo);
    std::vector<std::string> lineas;
    for (std::string linea; std::getline(entrada, linea);) lineas.push_back(linea);
    return lineas;
}
#if TEST_CASE_INDEX == 1
TEST_CASE("Q6 escribe 10 mensajes por linea") {
    auto archivo = fs::temp_directory_path() / "prog3_concurrente_q6_1.txt";
    fs::remove(archivo);
    Logger logger(archivo.string());
    for (int i = 0; i < 10; ++i) logger.log("mensaje_" + std::to_string(i));
    auto lineas = leer_lineas_q6(archivo);
    REQUIRE((lineas.size() == 10));
    for (int i = 0; i < 10; ++i) REQUIRE((lineas[i] == "mensaje_" + std::to_string(i)));
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q6 conserva 100 mensajes en modo append") {
    auto archivo = fs::temp_directory_path() / "prog3_concurrente_q6_2.txt";
    { std::ofstream salida(archivo); for (int i = 0; i < 50; ++i) salida << "anterior_" << i << '\n'; }
    Logger logger(archivo.string());
    for (int i = 0; i < 50; ++i) logger.log("nuevo_" + std::to_string(i));
    auto lineas = leer_lineas_q6(archivo);
    REQUIRE((lineas.size() == 100));
    for (int i = 0; i < 50; ++i) {
        REQUIRE((lineas[i] == "anterior_" + std::to_string(i)));
        REQUIRE((lineas[i + 50] == "nuevo_" + std::to_string(i)));
    }
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q6 evita intercalar 1000 mensajes entre hilos") {
    auto archivo = fs::temp_directory_path() / "prog3_concurrente_q6_3.txt";
    fs::remove(archivo);
    Logger logger(archivo.string());
    std::vector<std::thread> hilos;
    for (int i = 0; i < 10; ++i)
        hilos.emplace_back([&logger, i] {
            for (int j = 0; j < 100; ++j)
                logger.log("mensaje_" + std::to_string(i * 100 + j));
        });
    for (auto& hilo : hilos) hilo.join();
    auto lineas = leer_lineas_q6(archivo);
    REQUIRE((lineas.size() == 1000));
    std::set<std::string> esperados;
    for (int i = 0; i < 1000; ++i) esperados.insert("mensaje_" + std::to_string(i));
    REQUIRE((std::set<std::string>(lineas.begin(), lineas.end()) == esperados));
    fs::remove(archivo);
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q6 registra la clasificacion de 10000 numeros") {
    auto dir = fs::temp_directory_path() / "prog3_concurrente_q6_4";
    fs::remove_all(dir);
    fs::create_directories(dir);
    { std::ofstream salida(dir / "numeros.txt"); for (int n = 1; n <= 10000; ++n) salida << n << '\n'; }
    Logger logger((dir / "log.txt").string());
    clasificar_y_registrar(logger, (dir / "numeros.txt").string(), dir.string());
    auto lineas = leer_lineas_q6(dir / "log.txt");
    REQUIRE((lineas.size() == 4));
    REQUIRE((std::set<std::string>(lineas.begin(), lineas.end()) ==
        std::set<std::string>{"pares.txt: 5000", "mult3.txt: 3333", "mult5.txt: 2000", "otros.txt: 2666"}));
    fs::remove_all(dir);
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
