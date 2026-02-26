#include "Test.hpp"

class A
{
public:
    int a;

protected:
    int b;

private:
    int c;
};

class B: public A
{
private:
    int d;
};

ObjectsPool<D, 2> poolA;
