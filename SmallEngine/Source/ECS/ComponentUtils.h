//
// Created by radov on 20.04.2026.
//


#pragma once
#include <atomic>

/** Type used to identify every component type by unique int ID */
using ComponentTypeID = size_t;

/** Generic utility function to help work with components*/
class ComponentUtils
{
public:
    /** Returns unique ID per Component Type */
    template<typename T>
    static ComponentTypeID GetComponentTypeID()
    {
        static ComponentTypeID id = []() {
            static std::atomic<ComponentTypeID> counter = 0;
            return counter++;
        }();
        return id;
    }
};
