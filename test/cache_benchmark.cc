#include <random>
#include <benchmark/benchmark.h>

#include "../cache.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> key_dis(1, 1000000);

static void DoSetup(const benchmark::State& state) {
}

static void DoTeardown(const benchmark::State& state) {
}

static void Cache_BenchmarkUpdate(benchmark::State& state) {
    for (auto _ : state) {
        cache::Cache<int, 1024> cache;
        for (int i = 0; i < state.range(0); i++) {
            cache.Update(key_dis(gen));
        }
    }
}
BENCHMARK(Cache_BenchmarkUpdate)->Args({1024})->Args({2048})->Args({4096})->Args({8192});

static void Cache_BenchmarkPeek(benchmark::State& state) {
    cache::Cache<int, 104> cache;
    for (int i = 0; i < state.range(0); i++) {
        cache.Update(key_dis(gen));
    }

    bool ok;
    for (auto _ : state) {
        cache.Peek(&ok);
    }
}
BENCHMARK(Cache_BenchmarkPeek)->Args({1024})->Args({2048})->Args({4096})->Args({8192});

static void Cache_BenchmarkSyncWR(benchmark::State& state) {
    for (auto _ : state) {
        cache::Cache<int, 104> cache;
        bool ok;
        for (int i = 0; i < state.range(0); i++) {
            cache.Update(key_dis(gen));
            cache.Peek(&ok);
        }
    }
}
BENCHMARK(Cache_BenchmarkSyncWR)->Args({1024})->Args({2048})->Args({4096})->Args({8192});
