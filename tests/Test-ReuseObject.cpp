#include "Test.hpp"

ObjectsPool<int, 2> pool;

TEST(ReuseObject, _)
{
    ObjectRef ref1 = pool.CreateObject();
    ObjectRef ref2;

    pool.DeleteObject(ref1);

    EXPECT_EQ(ref1.Idx, 1);
    EXPECT_EQ(ref1.Gen, 1);
    EXPECT_EQ(pool.Used[1], false);
    EXPECT_EQ(&pool.GetObject(ref1), &pool.Object[0]);

    ref2 = pool.CreateObject();
    EXPECT_EQ(ref2.Idx, 1);
    EXPECT_EQ(ref2.Gen, 2);
    EXPECT_EQ(pool.Used[1], true);

    EXPECT_EQ(&pool.GetObject(ref1), &pool.Object[0]);
    EXPECT_EQ(&pool.GetObject(ref2), &pool.Object[1]);
}
