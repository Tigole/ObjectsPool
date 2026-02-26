#include "Test.hpp"

class A
{
public:
    int a;

    int GetA(void) const
    {
        return a;
    }
    int GetB(void) const
    {
        return b;
    }
    int GetC(void) const
    {
        return c;
    }

protected:
    int b;

private:
    int c;
};

#define MAX_OBJECT_COUNT 16

ObjectsPool<A, MAX_OBJECT_COUNT> poolComplexType;

TEST(GlobalZeroInitialization, _)
{
    for (uint16_t ii = 0; ii < MAX_OBJECT_COUNT; ii++)
    {
        ASSERT_EQ(poolComplexType.GetObject({ ii, 1 }).GetA(), 0);
        ASSERT_EQ(poolComplexType.GetObject({ ii, 1 }).GetB(), 0);
        ASSERT_EQ(poolComplexType.GetObject({ ii, 1 }).GetC(), 0);
    }
}
