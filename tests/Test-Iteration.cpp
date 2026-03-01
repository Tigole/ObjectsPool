#include <bitset>

#include "Test.hpp"

ObjectsPool<int, 16> pool;

TEST(Iteration, _)
{
    std::array<ObjectRef, 4> refs;
    std::bitset<4> loop     = 0;
    std::size_t loopCounter = 0;

    for (ObjectRef& r: refs)
    {
        r = pool.CreateObject();
    }

    for (auto it = pool.Begin(); it != pool.End(); ++it)
    {
        *it               = 4;
        loop[loopCounter] = true;
        loopCounter++;
        EXPECT_EQ(it.GetRef().Idx , loopCounter);
        EXPECT_EQ(it.GetRef().Gen , 1);
    }

    EXPECT_EQ(loopCounter, refs.size());
    for (std::size_t ii = 0; ii < loopCounter; ii++)
    {
        EXPECT_TRUE(loop[ii]);
    }

    for (ObjectRef& r: refs)
    {
        EXPECT_EQ(pool.GetObject(r), 4);
    }

    for (auto& data: pool)
    {
        data = 44;
    }

    for (ObjectRef& r: refs)
    {
        EXPECT_EQ(pool.GetObject(r), 44);
    }
}
