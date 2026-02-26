# ObjectsPool
Objects container implementation based on Wookash &amp; Anton Mikhailov discussion https://www.youtube.com/watch?v=-m7lhJ_Mzdg

# How to use
Add the files in the include/ folder in your project (copy or link to them).

Create your own type/struct/class to be contained.
Your type has to be trivially copiable.

Instanciate in the global scope an object of op::ObjectsPool<YourType, HowManyYouWantToHold>: as discussed in the video, it relies on zero initialisation.
Keep in mind that HowManyYouWantToHold has to be greater than 1 (as [0] is a sentinel and should not be used by user).

```c++
#include "ObjectsPool.hpp"

struct YourStruct
{
    uint32_t someId;
    float someFload;
    ...
};


op::ObjectsPool<YourStruct, 5000> YourStructPool;

int main()
{
    /// Object creation
    op::ObjectRef someObject = YourStructPool.CreateObject();

    /// Object modification (Consider newly created object to be filled with garbage so initialize it)
    YourStructPool.GetObject(someObject).someId = 42;
    YourStructPool.GetObject(someObject).someFload = 4.2f;

    /// Object deletion
    YourStructPool.DeleteObject(someObject);

    /// Reuse of deleted object will "fail" (not override newly created object)
    op::ObjectRef newObjectAtTheSamePlaceOfThePreviousOne = YourStructPool.CreateObject();

    YourStructPool.GetObject(newObjectAtTheSamePlaceOfThePreviousOne).someId = 1992;
    YourStructPool.GetObject(someObject).someId = 0;    /// will not override 1992 (will write into object at [0] the sentinel)

    /// Iterate over created objects
    for (auto& obj: YourStructPool)
    {
        obj.someFloat = 44.44f;
    }

    return 0;
}
```