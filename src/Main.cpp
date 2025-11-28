#include "Events.h"
#include "Settings.h"
#include "menu.h"

void Listener(SKSE::MessagingInterface::Message* message) noexcept
{
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        
        Config::Formloader::GetSingleton()->LoadForms();
        Events::OnHitBow::GetSingleton()->Register();
        Config::Settings::destroy_bow.SetValue(true);
        Config::Settings::GetSingleton()->UpdateSettings(true);

    }    
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    Init(skse);
    Config::Settings::GetSingleton()->UpdateSettings(false);
    Menu::RegisterMenu();
    SKSE::GetMessagingInterface()->RegisterListener(Listener);


    return true;
}
