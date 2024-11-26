#include "spdlog/spdlog.h"

struct A {
    int i;
    A(int i) : i(i) {}

    A(const A& other) {
        spdlog::debug("const A&");
        i = other.i;
    }

    A(A&& other) {
        spdlog::debug("A&&");
        i = other.i;
        other.i = 0;
    }
};

void funcB(A&& a) {
    auto a1 = std::move(a);
    spdlog::info("{} a: {}",__FUNCTION__, a.i);
}

void funcA(const A& a) {
    auto a1 = a;
    funcB(std::move(a1));
    // auto a1 = std::move(a);
    // spdlog::info("a1: {}", a1.i);
    // spdlog::info("a: {}", a.i);
}


int main(int argc, char **argv) {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Hello, Cache!");

    A a(10);
    funcA(a);
    // funcB(std::move(a));

    spdlog::info("a: {}", a.i);

    return 0;
}
