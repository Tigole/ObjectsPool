#include "Test.hpp"

ObjectsPool<int, 2> pool;

TEST(NewObject, _)
{
    ObjectRef ref = pool.CreateObject();

    EXPECT_EQ(ref.Idx, 1);
    EXPECT_EQ(ref.Gen, 1);
    EXPECT_EQ(pool.Used[1], true);

    EXPECT_EQ(&pool.GetObject(ref), &pool.Object[1]);
}
