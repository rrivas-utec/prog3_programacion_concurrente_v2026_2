#pragma once
#include "catch.hpp"
#include "productor_consumidor.h"
#include <sstream>
#include <vector>

static std::vector<int> impresos_q7(const std::string& texto) {
    std::istringstream entrada(texto);
    std::vector<int> valores;
    for (int n; entrada >> n;) valores.push_back(n);
    return valores;
}
#if TEST_CASE_INDEX == 1
TEST_CASE("Q7 produce e imprime 10 elementos") {
    std::ostringstream salida;
    auto valores = productor_consumidor(10, 123, salida);
    REQUIRE((valores.size() == 10));
    REQUIRE((impresos_q7(salida.str()) == valores));
}
TEST_CASE("Q7 acepta cero elementos") {
    std::ostringstream salida;
    REQUIRE((productor_consumidor(0, 5, salida).empty()));
    REQUIRE((salida.str().empty()));
}
#elif TEST_CASE_INDEX == 2
TEST_CASE("Q7 produce 100 numeros dentro del rango") {
    std::ostringstream salida;
    auto valores = productor_consumidor(100, 7, salida);
    REQUIRE((valores.size() == 100));
    REQUIRE((impresos_q7(salida.str()) == valores));
    for (int n : valores) REQUIRE((n >= 1 && n <= 1000));
}
#elif TEST_CASE_INDEX == 3
TEST_CASE("Q7 reproduce 1000 numeros con la misma semilla") {
    std::ostringstream primera, segunda;
    auto a = productor_consumidor(1000, 42, primera);
    auto b = productor_consumidor(1000, 42, segunda);
    REQUIRE((a.size() == 1000));
    REQUIRE((a == b));
    REQUIRE((primera.str() == segunda.str()));
}
#elif TEST_CASE_INDEX == 4
TEST_CASE("Q7 consume 10000 elementos sin perder salidas") {
    std::ostringstream salida;
    auto valores = productor_consumidor(10000, 99, salida);
    REQUIRE((valores.size() == 10000));
    REQUIRE((impresos_q7(salida.str()) == valores));
    for (int n : valores) REQUIRE((n >= 1 && n <= 1000));
}
#else
#error "TEST_CASE_INDEX must select an existing case"
#endif
