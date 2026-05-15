//
// Created by radov on 12.05.2026.
//

#include "SignalManager.h"
#include <vector>
#include "Engine/DebugBreaks.h"

SignalPayload SignalPayload::Empty;

SubscriptionId SignalManager::Subscribe(const std::string &Topic, const std::function<void(SignalPayload &)>& Callback)
{
    SubscriptionId id = NextId++;
    CallMap[Topic].push_back({id, Callback});
    return id;
}

void SignalManager::Unsubscribe(SubscriptionId id)
{
    for(auto& Topic : CallMap)
    {
        int i =0;
        for (const auto& Subscription: Topic.second)
        {
            if(Subscription.Id == id)
            {
                Topic.second.erase(Topic.second.begin() + i);
                return;
            }
            i++;
        }
    }
}

void SignalManager::Dispatch(const std::string &Topic, SignalPayload& Payload)
{
    if(!IsAnyoneSubscribed(Topic))
        return;

    auto Callbacks = CallMap.find(Topic);
    for(const auto& Callback : Callbacks->second)
       Callback.Callback(Payload);
}

bool SignalManager::IsAnyoneSubscribed(const std::string &Topic)
{
    auto Callbacks = CallMap.find(Topic);

    if(Callbacks == CallMap.end())
        return false;
    if(Callbacks->second.empty())
        return false;

    return true;
}

void SignalManager::CleanUpAll()
{
    CallMap.clear();
    NextId = 1;
}
