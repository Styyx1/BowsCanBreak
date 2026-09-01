#include "config/config.h"
#include "events/hit-event.h"
#include "forms/formloader.h"
#include "menu/sksemenu.h"
#include "modevent.h"

void BackupLoadKeys()
{

    if (!NOOB::FORMS::m_breakableKey)
    {
        NOOB::FORMS::LookupKeywords();
    }
}

void Listener(SKSE::MessagingInterface::Message* a_msg)
{
    switch (a_msg->type)
    {
        case SKSE::MessagingInterface::kDataLoaded:
            NOOB::HitEvList::RegisterHit();
            NOOB::SKSEMenu::RegisterBCB();
            break;
        default:
            break;
    }
}

SKSE_PLUGIN_LOAD(const SKSE::LoadInterface* a_skse)
{
    SKSE::Init(a_skse);
    NOOB::CONF::UpdateSettings();
    if (!SKSE::GetMessagingInterface()->RegisterListener(Listener))
    {
        return false;
    }
    SKSE::GetModCallbackEventSource()->AddEventSink(&NOOB::g_modEventListener);
    return true;
}
