#pragma once
#include "catch.hpp"
#include "cliente_bancario.h"
#include <sstream>
#include <thread>
#include <vector>

#if TEST_CASE_INDEX == 1
TEST_CASE("Q5 constructores e impresion despues de 10 operaciones") {
    Client vacio;
    REQUIRE((vacio.getBalance() == 0.0));
    Client cliente(100.0);
    simular_operaciones(cliente, 5, 3.0, 5, 2.0);
    REQUIRE((cliente.getBalance() == 105.0));
    std::ostringstream salida;
    salida << cliente;
    REQUIRE((salida.str() == "105"));
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q5 protege el saldo en 100 operaciones simultaneas") {
    Client cliente(1000.0);
    std::vector<std::thread> hilos;
    for (int i = 0; i < 10; ++i)
        hilos.emplace_back([&cliente] {
            for (int j = 0; j < 5; ++j) {
                cliente.deposit(3.0);
                cliente.withdraw(2.0);
            }
        });
    for (auto& hilo : hilos) hilo.join();
    REQUIRE((cliente.getBalance() == 1050.0));
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q5 protege el saldo en 1000 operaciones") {
    Client cliente(75.0);
    std::vector<std::thread> hilos;
    for (int i = 0; i < 10; ++i)
        hilos.emplace_back([&cliente] {
            for (int j = 0; j < 50; ++j) {
                cliente.deposit(4.0);
                cliente.withdraw(3.0);
            }
        });
    for (auto& hilo : hilos) hilo.join();
    REQUIRE((cliente.getBalance() == 575.0));
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q5 procesa 10000 operaciones en varios clientes") {
    auto saldos = simular_clientes(10, 100.0, 5, 2.0, 5, 1.0);
    REQUIRE((saldos.size() == 10));
    for (double saldo : saldos) REQUIRE((saldo == 105.0));
    Client cliente(100.0);
    std::vector<std::thread> hilos;
    for (int i = 0; i < 10; ++i)
        hilos.emplace_back([&cliente] {
            for (int j = 0; j < 500; ++j) {
                cliente.deposit(2.0);
                cliente.withdraw(1.0);
            }
        });
    for (auto& hilo : hilos) hilo.join();
    REQUIRE((cliente.getBalance() == 5100.0));
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
