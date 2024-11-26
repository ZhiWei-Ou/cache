#include <gtest/gtest.h>
#include <string>

#include "../cache.h"
#include "spdlog/spdlog.h"

struct Foo {
    std::string name;

    Foo() = default;
    Foo(int flag) : name(std::to_string(flag)) {}
    Foo(std::string name) : name(name) {}
    Foo(const Foo& other) : name(other.name) {
        // spdlog::info("copy {}", name);
    }
    Foo(Foo&& other) : name(other.name) {
        // spdlog::info("move {}", name);
    }

    Foo &operator=(const Foo& other) {
        if (this == &other) {
            return *this;
        }
        name = other.name;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Foo& person);
};

TEST(Cache, BasicTest) {
    cache::Cache<Foo, 3> cachePool;

    bool ok = false;
    cachePool.Peek(&ok);
    EXPECT_EQ(ok, false);

    cachePool.Update(Foo("a"));
    auto c1 = cachePool.Peek(&ok);
    EXPECT_EQ(ok, true);
    EXPECT_EQ(c1.name, "a"); 

    cachePool.Update(Foo("b"));
    cachePool.Update(Foo("c"));
    cachePool.Update(Foo("d"));
    auto c2 = cachePool.Peek(&ok);
    EXPECT_EQ(ok, true);
    EXPECT_EQ(c2.name, "d"); 

    cachePool.Update(Foo("e"));
    cachePool.Update(Foo("f"));
    cachePool.Update(Foo("g"));
    cachePool.Update(Foo("h"));
    auto c3 = cachePool.Peek(&ok);
    EXPECT_EQ(ok, true);
    EXPECT_EQ(c3.name, "h"); 
}
