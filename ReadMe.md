# FixedCache Container

## Description

A fixed-size container for caching objects.

- Non-blocking
- FIFO

## Build
- Build **cache** library
```bash
cmake -B build -S .
cmake --build build --target all -j8
```
- Build With Test
```bash
cmake -B build -S . -DBUILD_TEST=ON
cmake --build build --target all -j8
```
- Build With Example
```bash
cmake -B build -S . -DBUILD_EXAMPLE=ON
cmake --build build --target all -j8
```


## Usage
```cpp
    // @Foo: Foo is the type of object to cache
    // @3: the fixed-size of the cache
    cache::Cache<Foo, 3> cachePool;

    // update new cache
    cachePool.Update(Foo("a"));

    // get latest cache
    bool ok = false;
    auto foo = cachePool.Peek(ok);
```

## Cache simply preview
```c++
    foo::User foo1;
    foo1.set_id(1);
    foo1.set_name("foo1");

    foo::User foo2;
    foo2.set_id(2);
    foo2.set_name("foo2");

    foo::User foo3;
    foo3.set_id(3);
    foo3.set_name("foo3");


    cache::Cache<foo::User, 3> UserCache;

    UserCache.Update(foo1);
    bool exist = false;

    auto bar1 = UserCache.Peek(&exist);
    EXPECT_EQ(exist, true);
    EXPECT_EQ(bar1.id(), 1);
    EXPECT_EQ(bar1.name(), "foo1");

    UserCache.Update(foo2);
    auto bar2 = UserCache.Peek(&exist);
    EXPECT_EQ(exist, true);
    EXPECT_EQ(bar2.id(), 2);
    EXPECT_EQ(bar2.name(), "foo2");

    UserCache.Update(foo3);
    auto bar3 = UserCache.Peek(&exist);
    EXPECT_EQ(exist, true);
    EXPECT_EQ(bar3.id(), 3);
    EXPECT_EQ(bar3.name(), "foo3");

    // overwrite
    UserCache.Update(foo1);
    auto bar4 = UserCache.Peek(&exist);
    EXPECT_EQ(exist, true);
    EXPECT_EQ(bar4.id(), 1);
    EXPECT_EQ(bar4.name(), "foo1");

    // update
    UserCache.Update(foo2);
    auto bar5 = UserCache.Peek(&exist);
    EXPECT_EQ(exist, true);
    EXPECT_EQ(bar5.id(), 2);
    EXPECT_EQ(bar5.name(), "foo2");

```

## Benchmark
[cache_benchmark](./test/cache_benchmark.cc)
```bash
Running ./cache_benchmark
Run on (8 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x8)
Load Average: 2.84, 2.64, 2.27
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
Cache_BenchmarkUpdate/1024      44849 ns        44848 ns        15619
Cache_BenchmarkUpdate/2048      76114 ns        76114 ns         9151
Cache_BenchmarkUpdate/4096     138877 ns       138877 ns         5031
Cache_BenchmarkUpdate/8192     264576 ns       264565 ns         2648
Cache_BenchmarkPeek/1024         16.7 ns         16.7 ns     41818758
Cache_BenchmarkPeek/2048         16.7 ns         16.7 ns     41803024
Cache_BenchmarkPeek/4096         16.8 ns         16.8 ns     41817758
Cache_BenchmarkPeek/8192         16.7 ns         16.7 ns     41749918
Cache_BenchmarkSyncWR/1024      49815 ns        49815 ns        13994
Cache_BenchmarkSyncWR/2048      98358 ns        98358 ns         7116
Cache_BenchmarkSyncWR/4096     195586 ns       195582 ns         3595
Cache_BenchmarkSyncWR/8192     388107 ns       388092 ns         1803
```

## Graph

