#ifndef _OBJECTS_POOL_HPP
#define _OBJECTS_POOL_HPP 1

#include <cstdint>
#include <type_traits>

namespace op
{

struct ObjectRef
{
    uint16_t Idx;
    uint16_t Gen;
};

template<typename T, uint16_t MAX_OBJECT_COUNT>
class ObjectsPool
{
    static_assert(std::is_trivially_copyable_v<T>);
    static_assert(MAX_OBJECT_COUNT > 1);

public:
    bool Used[MAX_OBJECT_COUNT];
    T Object[MAX_OBJECT_COUNT];
    uint16_t Generation[MAX_OBJECT_COUNT];
    // uint16_t NextFreeObject[MAX_OBJECT_COUNT];
    uint16_t FirstFreeObject = 1;

public:
    ObjectRef CreateObject(void);
    T& GetObject(ObjectRef ref);
    void DeleteObject(ObjectRef ref);

    class Iterator
    {
    public:
        Iterator(ObjectsPool& owner, ObjectRef ref);
        T& operator*(void);
        // T& operator->(void);
        bool operator!=(const Iterator& other);
        bool operator==(const Iterator& other);
        Iterator& operator++();

        ObjectRef GetRef(void) const;

    private:
        ObjectsPool& Pool;
        ObjectRef Ref;
    };

    Iterator Begin();
    Iterator End();

private:
    uint16_t GetIndex(ObjectRef ref) const;
    ObjectRef BeginUsed(void) const;
    ObjectRef EndUsed(void) const;
    ObjectRef NextUsed(ObjectRef ref) const;
    const ObjectRef Nil = { 0, 0 };
};

#include "ObjectsPool.inl"

#if 1
template<typename T, uint16_t MAX_OBJECT_COUNT>
auto begin(op::ObjectsPool<T, MAX_OBJECT_COUNT>& c) noexcept -> op::ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator
{
    return c.Begin();
}

template<typename T, uint16_t MAX_OBJECT_COUNT>
auto end(op::ObjectsPool<T, MAX_OBJECT_COUNT>& c) noexcept -> op::ObjectsPool<T, MAX_OBJECT_COUNT>::Iterator
{
    return c.End();
}
#endif  // 0

}  // namespace op

#endif  // _OBJECTS_POOL_HPP
