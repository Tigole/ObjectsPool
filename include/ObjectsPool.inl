#include "ObjectsPool.hpp"

template<typename T, uint16_t MAX_OBJECT_COUNT>
ObjectRef ObjectsPool<T, MAX_OBJECT_COUNT>::CreateObject(void)
{
    if (FirstFreeObject == MAX_OBJECT_COUNT)
    {
        return Nil;
    }
    const uint16_t idx = FirstFreeObject;

    Generation[idx]++;
    Used[idx] = true;

    while (FirstFreeObject < MAX_OBJECT_COUNT && Used[FirstFreeObject])
    {
        FirstFreeObject++;
    }

    return { idx, Generation[idx] };
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
T& ObjectsPool<T, MAX_OBJECT_COUNT>::GetObject(ObjectRef ref)
{
    return Object[GetIndex(ref)];
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
void ObjectsPool<T, MAX_OBJECT_COUNT>::DeleteObject(ObjectRef ref)
{
    Used[GetIndex(ref)] = false;
    if (ref.Idx < FirstFreeObject)
    {
        FirstFreeObject = ref.Idx;
    }
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
uint16_t ObjectsPool<T, MAX_OBJECT_COUNT>::GetIndex(ObjectRef ref) const
{
    if (ref.Idx < MAX_OBJECT_COUNT && Used[ref.Idx] && ref.Gen == Generation[ref.Idx])
    {
        return ref.Idx;
    }
    return 0;
}

/////////////////////////////////////////
// Iterators
/////////////////////////////////////////

template<typename T, uint16_t MAX_OBJECT_COUNT>
ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator::Iterator(ObjectsPool<T, MAX_OBJECT_COUNT>& owner, ObjectRef ref) : Pool(owner), Ref(ref)
{}

template<typename T, uint16_t MAX_OBJECT_COUNT>
T& ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator::operator*(void)
{
    return Pool.GetObject(Ref);
}

/*template<typename T, uint16_t MAX_OBJECT_COUNT>
T& ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator::operator->(void)
{
    return Pool.GetObject(Ref);
}*/

template<typename T, uint16_t MAX_OBJECT_COUNT>
bool ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator::operator!=(const Iterator& other)
{
    return !operator==(other);
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
bool ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator::operator==(const Iterator& other)
{
    return Ref.Idx == other.Ref.Idx && Ref.Gen == other.Ref.Gen;
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator& ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator::operator++()
{
    Ref = Pool.NextUsed(Ref);
    return *this;
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator ObjectsPool<T, MAX_OBJECT_COUNT>::Begin()
{
    return Iterator(*this, BeginUsed());
}
template<typename T, uint16_t MAX_OBJECT_COUNT>
ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator ObjectsPool<T, MAX_OBJECT_COUNT>::End()
{
    return Iterator(*this, EndUsed());
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
ObjectRef ObjectsPool<T, MAX_OBJECT_COUNT>::BeginUsed(void) const
{
    return NextUsed(Nil);
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
ObjectRef ObjectsPool<T, MAX_OBJECT_COUNT>::EndUsed(void) const
{
    return { MAX_OBJECT_COUNT, 0 };
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
ObjectRef ObjectsPool<T, MAX_OBJECT_COUNT>::NextUsed(ObjectRef ref) const
{
    for (uint16_t ii = ref.Idx + 1; ii < MAX_OBJECT_COUNT; ii++)
    {
        if (Used[ii] == true)
        {
            return { ii, Generation[ii] };
        }
    }
    return EndUsed();
}
