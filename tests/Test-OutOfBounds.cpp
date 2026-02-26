#include "Test.hpp"

ObjectsPool<int, 2> pool;

TEST(OutOfBounds, _)
{
    ObjectRef ref1 = pool.CreateObject();

    EXPECT_EQ(ref1.Idx, 1);
    EXPECT_EQ(ref1.Gen, 1);
    EXPECT_EQ(pool.Used[1], true);

    EXPECT_EQ(&pool.GetObject({ 2, 1 }), &pool.Object[0]);
}
