#pragma once
#include "mod-data.h"




namespace Config
{
    struct Settings : REX::Singleton<Settings>, MOD::DATA
    {
        inline static REX::TOML::Bool destroy_bow{ TOGGLES, "bDestroyBow", true };
        inline static REX::TOML::Bool spawn_wood{ TOGGLES, "bSpawnWood", true };
        inline static REX::TOML::Bool only_power_attacks{ TOGGLES, "bOnlyUsePowerAttacks", true };
        inline static REX::TOML::Bool use_actor_mass{ TOGGLES, "bUseActorMass", true };
        inline static REX::TOML::F32  mass_threshold{ SETTINGS, "fMassThreshold", 2.0f };
        inline static REX::TOML::Bool use_health_percentage{ TOGGLES, "bUseHealthPercentage", false };
        inline static REX::TOML::F32  health_percentage_threshold{ SETTINGS, "fHealthPercentageThreshold", 25.f };
        inline static REX::TOML::F32  wood_chance{ SETTINGS, "fWoodSpawnChance", 75.0f };

        void UpdateSettings(bool a_save);

    };

    struct Formloader : REX::Singleton<Formloader>, MOD::DATA
    {
        inline static RE::TESObjectMISC* firewood;
        void                             LoadForms();
    };

}
