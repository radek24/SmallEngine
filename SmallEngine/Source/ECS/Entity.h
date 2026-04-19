//
// Created by radov on 08.03.2026.
//


#pragma once
#include <cstdint>


/** Class that represents Entity in our game engine, it only has a ID and all other methods are private. Use registry to create this class */
class Entity
{
public:
    using IdType = std::uint32_t;
    static IdType InvalidEntity;
    constexpr Entity() = delete;

    [[nodiscard]] constexpr IdType GetId() const
    {
        return m_Id;
    }

    [[nodiscard]] constexpr bool IsValid() const
    {
        return m_Id != 0;
    }
    constexpr bool operator==(const Entity& other) const
    {
        return m_Id == other.m_Id;
    }

    constexpr bool operator!=(const Entity& other) const
    {
        return m_Id != other.m_Id;
    }

private:
    explicit constexpr Entity(const IdType ID): m_Id(ID) {}
    IdType m_Id = 0;
    friend class Registry;
};

Entity::IdType Entity::InvalidEntity = 0;