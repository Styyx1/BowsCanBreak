#pragma once

#include <forms/formloader.h>
namespace NOOB
{

struct ModEventListener : REX::TSingleton<ModEventListener>, RE::BSTEventSink<SKSE::ModCallbackEvent>
{

    RE::BSEventNotifyControl ProcessEvent(const SKSE::ModCallbackEvent* a_event,
                                          RE::BSTEventSource<SKSE::ModCallbackEvent>*) override;
};

inline RE::BSEventNotifyControl ModEventListener::ProcessEvent(const SKSE::ModCallbackEvent* a_event,
                                                               RE::BSTEventSource<SKSE::ModCallbackEvent>*)
{

    if (!a_event)
    {
        return RE::BSEventNotifyControl::kContinue;
    }

    if(a_event->eventName == "KID_KeywordDistributionDone"){

        REX::INFO("KID is done, lookup keywords");
        FORMS::LookupKeywords();
    }
    return RE::BSEventNotifyControl::kContinue;

}

inline ModEventListener g_modEventListener;

} // namespace NOOB