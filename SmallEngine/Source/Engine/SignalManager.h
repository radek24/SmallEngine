//
// Created by radov on 12.05.2026.
//


#pragma once
#include "Engine/Core.h"

/** Class used to transfer arbitrary data between dispatcher and subscriber*/
struct SE_API SignalPayload
{
public:
    static SignalPayload &GetEmpty(){return Empty;}
private:
    static SignalPayload Empty;
};

using SubscriptionId = std::uint64_t;

struct Subscription
{
    SubscriptionId Id;
    std::function<void(SignalPayload&)> Callback;
};

class SE_API SignalManager
{
public:
    /** Subscribes to a event, returns handle to that subscription. Currently you need to manually unsubscribe when no longer using*/
    SubscriptionId Subscribe(const std::string& Topic, const std::function<void(SignalPayload&)>& Callback);
    /** Unsubscribe a specified handle. Kinda expensive as it does liar lookup of all current subscriptions. */
    void Unsubscribe(SubscriptionId Handle);
    /** Dispatches event to all subscribers*/
    void Dispatch(const std::string& Topic, SignalPayload& Payload);
    /** Checks if anyone is subscribed to Topic*/
    bool IsAnyoneSubscribed(const std::string& Topic);
    /** Will clear all subscription and will reset Next id to 1*/
    void CleanUpAll();
private:
    std::unordered_map<std::string,std::vector< Subscription>> CallMap;
    SubscriptionId NextId = 1;
};
