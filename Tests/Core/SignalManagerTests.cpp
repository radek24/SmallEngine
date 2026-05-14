//
// Created by radov on 12.05.2026.
//

#include <doctest/doctest.h>

#include "Engine/SignalManager.h"


TEST_CASE("SignalManager - Subscribe and call with empty payload") {
    SignalManager sm;
    bool Called = false;
    sm.Subscribe("TestTopic",[&Called](SignalPayload p){Called = true;});
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    REQUIRE(Called);
}

struct IntPayload : public SignalPayload
{
    int Data;
};

TEST_CASE("SignalManager - Subscribe and call with simple payload") {
    SignalManager sm;
    int CallbackData = 0;
    sm.Subscribe("TestTopic", [&CallbackData](SignalPayload& p) {CallbackData = static_cast<IntPayload&>(p).Data;});
    IntPayload payload{};
    payload.Data = 10;
    sm.Dispatch("TestTopic", payload);
    REQUIRE(CallbackData == 10);
}

TEST_CASE("SignalManager - Multiple calls to multiple subscribers from single topic") {
    SignalManager sm;
    int sub1=0,sub2=0,sub3=0;
    sm.Subscribe("TestTopic", [&sub1](SignalPayload& p){sub1++;});
    sm.Subscribe("TestTopic", [&sub2](SignalPayload& p){sub2--;});
    sm.Subscribe("NoTopic", [&sub3](SignalPayload& p){sub3--;});

    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    REQUIRE(sub1 == 4);
    REQUIRE(sub2 == -4);
    REQUIRE(sub3 == 0);
}

TEST_CASE("SignalManager - Unsubscribing")
{
    SignalManager sm;
    int sub1=0,sub2=0,sub3=0;
    auto subscription1 = sm.Subscribe("TestTopic", [&sub1](SignalPayload& p){sub1++;});
    auto subscription2 =  sm.Subscribe("TestTopic", [&sub2](SignalPayload& p){sub2--;});
    sm.Subscribe("NoTopic", [&sub3](SignalPayload& p){sub3--;});

    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Unsubscribe(subscription2);
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Unsubscribe(subscription1);
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    REQUIRE(sub1 == 3);
    REQUIRE(sub2 == -1);
    REQUIRE(sub3 == 0);
}
TEST_CASE("SignalManager - Cleanup")
{
    SignalManager sm;
    int sub1=0,sub2=0,sub3=0;
    sm.Subscribe("TestTopic", [&sub1](SignalPayload& p){sub1++;});
    sm.Subscribe("TestTopic", [&sub2](SignalPayload& p){sub2--;});
    sm.Subscribe("NoTopic", [&sub3](SignalPayload& p){sub3--;});

    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    REQUIRE(sub1 == 4);
    REQUIRE(sub2 == -4);
    REQUIRE(sub3 == 0);
    sm.CleanUpAll();
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    sm.Dispatch("TestTopic",SignalPayload::GetEmpty());
    REQUIRE(sub1 == 4);
    REQUIRE(sub2 == -4);
    REQUIRE(sub3 == 0);

}