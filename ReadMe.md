# FixedCache Container

## Description

A fixed-size container for caching objects.

- Non-blocking
- FIFO

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

## Graph
![graph](./assets/Graph.png)

