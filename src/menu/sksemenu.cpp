#include "sksemenu.h"

#include "API/SKSEMenuFramework.h"
#include "config/config.h"
#include "menu-defines.h"
#include "st-ui.h"

namespace NOOB
{

using namespace IGMenu;

void SKSEMenu::RegisterBCB()
{
    if (!SKSEMenuFramework::IsInstalled())
    {
        return;
    }
    SKSEMenuFramework::SetSection(TIT::MOD_TITLE);
    SKSEMenuFramework::AddSectionItem(TIT::SETTINGS_SECTION, RenderMenu);
    RegisterMenuOpenCloseEvent();
}
void SKSEMenu::OnMenuClose()
{
    CONF::UpdateSettings(true);
}
void SKSEMenu::OnMenuOpen()
{
    FUN::LoadFromConfig();
}

void __stdcall MenuEventListener(SKSEMenuFramework::Model::EventType a_eventType)
{
    switch (a_eventType)
    {
        case SKSEMenuFramework::Model::kOpenMenu:
            SKSEMenu::OnMenuOpen();
            break;
        case SKSEMenuFramework::Model::kCloseMenu:
            SKSEMenu::OnMenuClose();
            break;
        default:
            break;
    }
}

void SKSEMenu::RegisterMenuOpenCloseEvent()
{
    static SKSEMenuFramework::Model::Event event(MenuEventListener, 1.5);
}
void SKSEMenu::DrawBowsCanBreak()
{

    using ux = SKSEMenuUtil;

    ux::GreenTitleText(TIT::MOD_TITLE);

    ux::SetCheckbox(LAB::destroy_bow, VAR::destroy_bow, CONF::destroy_bow, HEL::destroy_bow);
    SameLine();
    ux::SetCheckbox(LAB::spawn_wood, VAR::spawn_wood, CONF::spawn_wood, HEL::spawn_wood);

    ux::SetSliderFloat(LAB::wood_chance, VAR::wood_chance, CONF::wood_chance, 0.0f, 100.0f, HEL::wood_chance);

    ux::SetCheckbox(LAB::only_power_attacks, VAR::only_power_attacks, CONF::only_power_attacks,
                    HEL::only_power_attacks);
    SameLine();
    ux::SetCheckbox(LAB::use_actor_mass, VAR::use_actor_mass, CONF::use_actor_mass, HEL::use_actor_mass);

    ux::SetSliderFloat(LAB::mass_threshold, VAR::mass_threshold, CONF::mass_threshold, 0.0f, 20.0f,
                       HEL::mass_threshold);

    ux::SetCheckbox(LAB::use_health_percentage, VAR::use_health_percentage, CONF::use_health_percent,
                    HEL::use_health_percentage);
    ux::SetSliderFloat(LAB::health_percent_threshold, VAR::health_percentage_threshold, CONF::health_percent_threshold,
                       0.0f, 100.0f, HEL::health_percent_threshold);

    ux::SetCheckbox(LAB::prevent_with_skill, VAR::prevent_with_skill, CONF::prevent_with_skill,
                    HEL::prevent_with_skill);
    ux::SetSliderInt<uint32_t>(LAB::skill_level_threshold, VAR::skill_level_threshold, CONF::skill_level_threshold, uint32_t(0), uint32_t(100),
                       HEL::skill_level_threshold);
}
void SKSEMenu::DrawSystem()
{
    if (Button("Reset Defaults"))
    {
        FUN::RestoreDefaults();
    }
}

void __stdcall SKSEMenu::RenderMenu()
{
    if (CollapsingHeader(TIT::SETTINGS_SECTION, ImGuiTreeNodeFlags_DefaultOpen))
    {
        DrawBowsCanBreak();
    }
    if (CollapsingHeader(TIT::SYSTEM_SECTION, ImGuiTreeNodeFlags_DefaultOpen))
    {
        DrawSystem();
    }
}


} // namespace NOOB