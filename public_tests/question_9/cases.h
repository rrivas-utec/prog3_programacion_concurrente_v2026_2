#pragma once
#include "catch.hpp"
#include "sala.h"
#include <chrono>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

static std::vector<std::string> lineas_q9(const std::string& texto) {
    std::istringstream entrada(texto);
    std::vector<std::string> lineas;
    for (std::string linea; std::getline(entrada, linea);) lineas.push_back(linea);
    return lineas;
}
#if TEST_CASE_INDEX == 1
TEST_CASE("Q9 registra 10 visitas secuenciales") {
    std::ostringstream salida;
    for (int i = 0; i < 10; ++i)
        ingresar_a_la_sala("P" + std::to_string(i), salida, std::chrono::milliseconds(0));
    auto lineas = lineas_q9(salida.str());
    REQUIRE((lineas.size() == 20));
    for (int i = 0; i < 10; ++i) {
        auto nombre = "P" + std::to_string(i);
        REQUIRE((lineas[2 * i] == nombre + " ha entrado a la sala"));
        REQUIRE((lineas[2 * i + 1] == nombre + " ha salido de la sala"));
    }
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q9 impide entradas simultaneas en 100 visitas") {
    std::ostringstream salida;
    std::vector<std::thread> hilos;
    for (int i = 0; i < 10; ++i)
        hilos.emplace_back([&, i] {
            for (int j = 0; j < 10; ++j)
                ingresar_a_la_sala("P" + std::to_string(i * 10 + j), salida, std::chrono::milliseconds(0));
        });
    for (auto& hilo : hilos) hilo.join();
    auto lineas = lineas_q9(salida.str());
    REQUIRE((lineas.size() == 200));
    for (std::size_t i = 0; i < lineas.size(); i += 2) {
        auto nombre = lineas[i].substr(0, lineas[i].find(" ha entrado"));
        REQUIRE((lineas[i] == nombre + " ha entrado a la sala"));
        REQUIRE((lineas[i + 1] == nombre + " ha salido de la sala"));
    }
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q9 reutiliza la sala durante 1000 visitas") {
    std::ostringstream salida;
    std::vector<std::thread> hilos;
    for (int i = 0; i < 10; ++i)
        hilos.emplace_back([&, i] {
            for (int j = 0; j < 100; ++j)
                ingresar_a_la_sala("P" + std::to_string(i * 100 + j), salida, std::chrono::milliseconds(0));
        });
    for (auto& hilo : hilos) hilo.join();
    auto lineas = lineas_q9(salida.str());
    REQUIRE((lineas.size() == 2000));
    for (std::size_t i = 0; i < lineas.size(); i += 2) {
        auto nombre = lineas[i].substr(0, lineas[i].find(" ha entrado"));
        REQUIRE((lineas[i + 1] == nombre + " ha salido de la sala"));
    }
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q9 conserva los mensajes de 10000 visitas") {
    std::ostringstream salida;
    std::vector<std::thread> hilos;
    for (int i = 0; i < 20; ++i)
        hilos.emplace_back([&, i] {
            for (int j = 0; j < 500; ++j)
                ingresar_a_la_sala("P" + std::to_string(i * 500 + j), salida, std::chrono::milliseconds(0));
        });
    for (auto& hilo : hilos) hilo.join();
    auto lineas = lineas_q9(salida.str());
    REQUIRE((lineas.size() == 20000));
    std::set<std::string> nombres;
    for (std::size_t i = 0; i < lineas.size(); i += 2) {
        auto nombre = lineas[i].substr(0, lineas[i].find(" ha entrado"));
        nombres.insert(nombre);
        REQUIRE((lineas[i] == nombre + " ha entrado a la sala"));
        REQUIRE((lineas[i + 1] == nombre + " ha salido de la sala"));
    }
    REQUIRE((nombres.size() == 10000));
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
