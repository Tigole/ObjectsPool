#include "Test.hpp"

ObjectsPool<int, 3> pool;

TEST(Full, _)
{
    ObjectRef ref1 = pool.CreateObject();
    ObjectRef ref2 = pool.CreateObject();
    ObjectRef ref3 = pool.CreateObject();

    EXPECT_EQ(ref1.Idx, 1);
    EXPECT_EQ(ref1.Gen, 1);
    EXPECT_EQ(pool.Used[1], true);

    EXPECT_EQ(ref2.Idx, 2);
    EXPECT_EQ(ref2.Gen, 1);
    EXPECT_EQ(pool.Used[2], true);

    EXPECT_EQ(ref3.Idx, 0);
    EXPECT_EQ(ref3.Gen, 0);
    EXPECT_EQ(pool.Used[0], false);
}
