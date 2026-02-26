#include "Test.hpp"

class A
{
    int a;
    int b;
    virtual void toto() {}
};

ObjectsPool<A, 2> poolA;
