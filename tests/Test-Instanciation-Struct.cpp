#include "Test.hpp"

struct ComplexType
{
    int a;
    int b;
};

#define MAX_OBJECT_COUNT 16

ObjectsPool<ComplexType, MAX_OBJECT_COUNT> poolComplexType;

TEST(GlobalZeroInitialization, _)
{
    for (uint16_t ii = 0; ii < MAX_OBJECT_COUNT; ii++)
    {
        ASSERT_EQ(poolComplexType.GetObject({ ii, 1 }).a, 0);
        ASSERT_EQ(poolComplexType.GetObject({ ii, 1 }).b, 0);
    }
}
