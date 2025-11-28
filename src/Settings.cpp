#include "Settings.h"

namespace Config
{
    void Settings::UpdateSettings(bool a_save) {
        const auto toml = REX::TOML::SettingStore::GetSingleton();
        toml->Init(TOML_PATH_DEFAULT.data(), TOML_PATH_CUSTOM.data());
        if (!a_save)
            toml->Load();
        else
            toml->Save();
    }
    
    void Formloader::LoadForms() {
        auto dataHandler = RE::TESDataHandler::GetSingleton();
        firewood         = dataHandler->LookupForm<RE::TESObjectMISC>(FIREWOOD_ID, SKYRIM.data());
    }
} // namespace Config
