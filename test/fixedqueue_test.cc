#include <gtest/gtest.h>
#include <string>

#include "../cache.h"
#include "spdlog/spdlog.h"

struct Foo {
    std::string name;

    Foo() = default;
    Foo(std::string name) : name(name) {}
    Foo(const Foo& other) : name(other.name) {
    }
    Foo(Foo&& other) : name(std::move(other.name)) {
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

std::ostream& operator<<(std::ostream& os, const Foo& person)
{
    return os << person.name;
}


TEST(FixedQueue, BasicEnqueueTest) {
    const int fixedSize = 3;
    std::array<Foo, fixedSize> bars = {Foo("a"), Foo("b"), Foo("c")};

    cache::FixedQueue<Foo, fixedSize> q;
    EXPECT_EQ(q.Len(), 0);
    EXPECT_EQ(q.Cap(), 3);

    for (auto&& bar : bars) {
        q.Enqueue(bar);
    } 

    EXPECT_EQ(q.Len(), 3);
    EXPECT_EQ(q.Cap(), 3);

    for (auto&& bar : bars) {
        EXPECT_EQ(q.TakeDequeue().name, bar.name);
    }
    EXPECT_EQ(q.Len(), 0);
}

TEST(FixedQueue, OverflowTest) {
    const int fixedSize = 5;
    std::array<Foo, fixedSize> bars = {Foo("a"), Foo("b"), Foo("c"), Foo("d"), Foo("e")};

    cache::FixedQueue<Foo, fixedSize> q;

    // Full
    for (auto&& bar : bars) {
        q.Enqueue(bar);
    }
    EXPECT_EQ(q.Len(), q.Cap());

    // Overflow
    q.Enqueue(Foo("1"));
    q.Enqueue(Foo("2"));
    q.Enqueue(Foo("3"));
    q.Enqueue(Foo("4"));
    q.Enqueue(Foo("5"));

    EXPECT_EQ(q.TakeDequeue().name, "1");
    EXPECT_EQ(q.TakeDequeue().name, "2");
    EXPECT_EQ(q.TakeDequeue().name, "3");
    EXPECT_EQ(q.TakeDequeue().name, "4");
    EXPECT_EQ(q.TakeDequeue().name, "5");

    EXPECT_EQ(q.Len(), 0);
}

TEST(FixedQueue, DebugTest) {
    cache::FixedQueue<Foo, 10> q;

    q.Enqueue(Foo("a"));
    q.Enqueue(Foo("b"));
    q.Enqueue(Foo("c"));
    q.Enqueue(Foo("d"));
    q.Enqueue(Foo("e"));
    q.Enqueue(Foo("f"));
    q.Enqueue(Foo("g"));
    q.Enqueue(Foo("h"));
    q.Enqueue(Foo("i"));
    q.Enqueue(Foo("j"));

    q.Debug([](const Foo& foo) {
        spdlog::info("{}", foo.name);
    });
}

TEST(FixedQueue, PeekTest) {
    cache::FixedQueue<Foo, 10> q;
    q.Enqueue(Foo("a"));
    q.Enqueue(Foo("b"));
    q.Enqueue(Foo("c"));
    q.Enqueue(Foo("d"));
    q.Enqueue(Foo("e"));
    q.Enqueue(Foo("f"));
    q.Enqueue(Foo("g"));
    q.Enqueue(Foo("h"));
    q.Enqueue(Foo("i"));
    q.Enqueue(Foo("j"));

    EXPECT_EQ(q.PeekNew().name, "j");
    EXPECT_EQ(q.PeekOld().name, "a");

    q.Enqueue(Foo("1"));
    EXPECT_EQ(q.PeekNew().name, "1");
    EXPECT_EQ(q.PeekOld().name, "b");

    q.Enqueue(Foo("2"));
    EXPECT_EQ(q.PeekNew().name, "2");
    EXPECT_EQ(q.PeekOld().name, "c");

    q.Enqueue(Foo("3"));
    EXPECT_EQ(q.PeekNew().name, "3");
    EXPECT_EQ(q.PeekOld().name, "d");

    q.Enqueue(Foo("4"));
    EXPECT_EQ(q.PeekNew().name, "4");
    EXPECT_EQ(q.PeekOld().name, "e");

    q.Enqueue(Foo("5"));
    EXPECT_EQ(q.PeekNew().name, "5");
    EXPECT_EQ(q.PeekOld().name, "f");

    q.Enqueue(Foo("6"));
    EXPECT_EQ(q.PeekNew().name, "6");
    EXPECT_EQ(q.PeekOld().name, "g");

    q.Enqueue(Foo("7"));
    EXPECT_EQ(q.PeekNew().name, "7");
    EXPECT_EQ(q.PeekOld().name, "h");

    q.Enqueue(Foo("8"));
    EXPECT_EQ(q.PeekNew().name, "8");
    EXPECT_EQ(q.PeekOld().name, "i");

    q.Enqueue(Foo("9"));
    EXPECT_EQ(q.PeekNew().name, "9");
    EXPECT_EQ(q.PeekOld().name, "j");

    q.Enqueue(Foo("!"));
    EXPECT_EQ(q.PeekNew().name, "!");
    EXPECT_EQ(q.PeekOld().name, "1");
}

TEST(FixedQueue, IteratorTest) {
}
