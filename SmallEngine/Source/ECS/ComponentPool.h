//
// Created by radov on 17.04.2026.
//

#pragma once
#include <vector>
#include <Engine/DebugBreaks.h>

#include "Entity.h"

#define PAGE_SIZE 256

static constexpr size_t INVALID_INDEX = std::numeric_limits<size_t>::max();

/** Interface with virtual methods so we can use it with types*/
struct IComponentPool
{
    virtual ~IComponentPool() = default;
    virtual void Remove(Entity E) = 0;
};

/** Sparse set implementation with pages */
template<typename T>
class ComponentPool : public IComponentPool
{
    std::vector<T> DenseData;
    std::vector<Entity> DenseEntity;
    std::vector<std::vector<size_t>> SparseData;

public:
    /** Adds an entity and component to this pool */
    T& Add(Entity E, T Component);
    /** Returns the dense entity array for iteration */
    [[nodiscard]] const std::vector<Entity>& GetEntities() const { return DenseEntity; }
    /** Removes an entity from this list (will swap removed element with last and then pop, so this will keep cache continuity) */
    void Remove(Entity E) override;
    /** Gets an entity from this set, if this entity doesn't exist will crash. */
    T& Get(Entity E);
    /** Returns true if entity E has a component in this pool*/
    [[nodiscard]] bool Contains(Entity E) const;
    /** Returns number of components in this pool*/
    [[nodiscard]] size_t Size() const { return DenseData.size(); }
    /** Pre-allocates dense storage and sparse pages to avoid reallocation spikes */
    void Reserve(size_t Count)
    {
        DenseData.reserve(Count);
        DenseEntity.reserve(Count);
        size_t PagesNeeded = (Count / PAGE_SIZE) + 1;
        if (SparseData.size() < PagesNeeded)
            SparseData.resize(PagesNeeded);
        for (size_t i = 0; i < PagesNeeded; ++i)
            if (SparseData[i].empty())
                SparseData[i].assign(PAGE_SIZE, INVALID_INDEX);
    }


    struct Entry
    {
        Entity E;
        T&     Component;
    };

    struct Iterator
    {
        ComponentPool* Pool;
        size_t         Index;

        Entry operator*() const
        {
            return { Pool->DenseEntity[Index], Pool->DenseData[Index] };
        }

        Iterator& operator++() { ++Index; return *this; }

        bool operator!=(const Iterator& Other) const { return Index != Other.Index; }
        bool operator==(const Iterator& Other) const { return Index == Other.Index; }
    };
    Iterator begin() { return { this, 0 }; }
    Iterator end()   { return { this, DenseData.size() }; }

private:
    static std::pair<size_t,size_t> GetPageAndIndexFromEntity(Entity E);
};

template<typename T>
T& ComponentPool<T>::Add(Entity E, T Component)
{
    auto [Page, Idx] = GetPageAndIndexFromEntity(E);

    if (Page >= SparseData.size())
        SparseData.resize(Page + 1);

    if (SparseData[Page].empty())
        SparseData[Page].assign(PAGE_SIZE, INVALID_INDEX);

    SparseData[Page][Idx] = DenseData.size();
    DenseData.push_back(std::move(Component));
    DenseEntity.push_back(E);
    return DenseData.back();
}

template<typename T>
void ComponentPool<T>::Remove(Entity E)
{
    if (!Contains(E)) return;
    auto [Page, Idx] = GetPageAndIndexFromEntity(E);
    size_t RemovedDenseIdx = SparseData[Page][Idx];
    size_t LastDenseIdx    = DenseData.size() - 1;

    DenseData[RemovedDenseIdx]   = std::move(DenseData[LastDenseIdx]);
    DenseEntity[RemovedDenseIdx] = DenseEntity[LastDenseIdx];

    Entity MovedEntity = DenseEntity[RemovedDenseIdx];
    auto [MovedPage, MovedIdx] = GetPageAndIndexFromEntity(MovedEntity);
    SparseData[MovedPage][MovedIdx] = RemovedDenseIdx;

    SparseData[Page][Idx] = INVALID_INDEX;

    DenseData.pop_back();
    DenseEntity.pop_back();
}

template<typename T>
T & ComponentPool<T>::Get(Entity E)
{
    auto [Page, Idx] = GetPageAndIndexFromEntity(E);
    size_t Index = SparseData[Page][Idx];
    Assert(Index != INVALID_INDEX && "Get() called on entity without component");
    return DenseData[Index];
}

template<typename T>
bool ComponentPool<T>::Contains(Entity E) const
{
    auto [Page, Idx] = GetPageAndIndexFromEntity(E);
    if (Page >= SparseData.size() || SparseData[Page].empty())
        return false;
    return SparseData[Page][Idx] != INVALID_INDEX;
}

template<typename T>
std::pair<size_t, size_t> ComponentPool<T>::GetPageAndIndexFromEntity(Entity E)
{
    size_t PageNumber = E.GetId() / PAGE_SIZE;
    size_t Index = E.GetId() % PAGE_SIZE;
    return std::make_pair(PageNumber,Index);
}
