#include "Test.hpp"

#define MAX_OBJECT_COUNT 16

ObjectsPool<int, MAX_OBJECT_COUNT> poolInt;

TEST(GlobalZeroInitialization, _)
{
    for (uint16_t ii = 0; ii < MAX_OBJECT_COUNT; ii++)
    {
        ASSERT_EQ(poolInt.GetObject({ ii, 1 }), 0);
    }
}
