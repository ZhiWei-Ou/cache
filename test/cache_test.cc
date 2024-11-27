#include <gtest/gtest.h>
#include <string>

#include "foo.pb.h"
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

TEST(Cache, ProtoBufCacheTest) {
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
}
