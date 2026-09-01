#include "menu-defines.h"

#include "config/config.h"

namespace NOOB
{

void IGMenu::FUN::RestoreDefaults()
{
    VAR::destroy_bow                 = true;
    VAR::spawn_wood                  = true;
    VAR::only_power_attacks          = true;
    VAR::use_actor_mass              = true;
    VAR::mass_threshold              = 2.0f;
    VAR::use_health_percentage       = false;
    VAR::health_percentage_threshold = 25.0f;
    VAR::wood_chance                 = 75.0f;
    VAR::prevent_with_skill          = false;
    VAR::skill_level_threshold       = 50;

    CONF::destroy_bow.SetValue(VAR::destroy_bow);
    CONF::spawn_wood.SetValue(VAR::spawn_wood);
    CONF::only_power_attacks.SetValue(VAR::only_power_attacks);
    CONF::use_actor_mass.SetValue(VAR::use_actor_mass);
    CONF::mass_threshold.SetValue(VAR::mass_threshold);
    CONF::use_health_percent.SetValue(VAR::use_health_percentage);
    CONF::health_percent_threshold.SetValue(VAR::health_percentage_threshold);
    CONF::wood_chance.SetValue(VAR::wood_chance);
    CONF::prevent_with_skill.SetValue(VAR::prevent_with_skill);
    CONF::skill_level_threshold.SetValue(VAR::skill_level_threshold);

    CONF::UpdateSettings(true);
}
void IGMenu::FUN::LoadFromConfig()
{
    VAR::destroy_bow                 = CONF::destroy_bow.GetValue();
    VAR::spawn_wood                  = CONF::spawn_wood.GetValue();
    VAR::only_power_attacks          = CONF::only_power_attacks.GetValue();
    VAR::use_actor_mass              = CONF::use_actor_mass.GetValue();
    VAR::mass_threshold              = CONF::mass_threshold.GetValue();
    VAR::use_health_percentage       = CONF::use_health_percent.GetValue();
    VAR::health_percentage_threshold = CONF::health_percent_threshold.GetValue();
    VAR::wood_chance                 = CONF::wood_chance.GetValue();
    VAR::prevent_with_skill          = CONF::prevent_with_skill.GetValue();
    VAR::skill_level_threshold       = CONF::skill_level_threshold.GetValue();
}

} // namespace NOOB