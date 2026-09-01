#pragma once 

#include "mod-data.h"

namespace NOOB{

    namespace CONF{

        inline REX::TOML::Bool destroy_bow {TOG_CON, "bDestroyBow", true};
        inline REX::TOML::Bool spawn_wood {TOG_CON, "bSpawnWood", true};
        inline REX::TOML::Bool only_power_attacks{TOG_CON, "bOnlyUsePowerAttacks", true};
        inline REX::TOML::Bool use_actor_mass {TOG_CON, "bUseActorMass", true};
        inline REX::TOML::Bool use_health_percent {TOG_CON, "bUseHealthPercentage", true};
        inline REX::TOML::Bool prevent_with_skill {TOG_CON, "bPreventWithSkill", false};

        inline REX::TOML::F32 mass_threshold {SET_CON, "fMassThreshold", 2.0f};
        inline REX::TOML::F32 health_percent_threshold {SET_CON, "fHealthPercentThreshold", 25.0f};
        inline REX::TOML::F32 wood_chance {SET_CON, "fWoodSpawnChance", 75.0f};
        inline REX::TOML::I32 skill_level_threshold {SET_CON, "iSkillLevelThreshold", 50};

        void UpdateSettings(const bool a_save = false);

        float GetFloatFromPerc(float a_percentageValue);
    }

}