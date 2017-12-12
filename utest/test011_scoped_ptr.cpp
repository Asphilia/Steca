#include "def/special_pointers.h"
#include "gtest/gtest.h"

TEST(ScopedPtr, NotNull) {
    int i = 0;
    auto p1 = not_null<int*>::from(&i), p2(p1);
    EXPECT_EQ(p1, p2);

    ++(*p1);
    EXPECT_EQ(1, *p2);
}

struct Counter {
    static int cnt;

    Counter() { ++cnt; }
    ~Counter() { --cnt; }
};

int Counter::cnt = 0;

TEST(ScopedPtr, Scoped) {
    {
        Counter* c;
        scoped<Counter*> p((c = new Counter()));
        EXPECT_FALSE(p.isNull());
        EXPECT_TRUE(c == p.ptr());
        EXPECT_TRUE(c == static_cast<Counter*>(p));
        EXPECT_EQ(1, p->cnt);
    }
    EXPECT_EQ(0, Counter::cnt);

    Counter* raw;

    {
        scoped<Counter*> p(new Counter());
        EXPECT_FALSE(p.isNull());
        EXPECT_EQ(1, Counter::cnt);
        raw = p.take();
        EXPECT_TRUE(p.isNull());
        EXPECT_EQ(1, Counter::cnt);
    }

    EXPECT_EQ(1, Counter::cnt);

    {
        scoped<Counter*> p(raw);
        EXPECT_FALSE(p.isNull());
        EXPECT_EQ(1, Counter::cnt);
    }

    EXPECT_EQ(0, Counter::cnt);
}