#include "menu.h"
#include "Settings.h"

namespace Menu
{
void RegisterMenu()
{
    if (!SKSEMenuFramework::IsInstalled())
    {
        return;
    }
    SKSEMenuFramework::SetSection(Titles::MOD_TITLE);
    SKSEMenuFramework::AddSectionItem(Titles::SETTINGS_SEC, Settings::RenderSettings);
    RestoreFromSettings();
}

void RestoreFromSettings()
{
    using set = Config::Settings;
    using namespace Settings::Var;

    destroy_bow = set::destroy_bow.GetValue();
    spawn_wood = set::spawn_wood.GetValue();
    only_power_attacks = set::only_power_attacks.GetValue();
    use_actor_mass = set::use_actor_mass.GetValue();
    mass_threshold = set::mass_threshold.GetValue();
}

void ResetDefaults()
{
    using set = Config::Settings;
    using namespace Settings::Var;
    destroy_bow = true;
    spawn_wood = true;
    only_power_attacks = true;
    use_actor_mass = true;
    mass_threshold = 2.0f;

    set::destroy_bow.SetValue(destroy_bow);
    set::spawn_wood.SetValue(spawn_wood);
    set::only_power_attacks.SetValue(only_power_attacks);
    set::use_actor_mass.SetValue(use_actor_mass);
    set::mass_threshold.SetValue(mass_threshold);
}

void RenderSystem()
{
    ImGui::NewLine();
    ImGui::SeparatorText(Label::system.c_str());

    if (ImGui::Button(Label::save_settings.c_str()))
    {
        Config::Settings::GetSingleton()->UpdateSettings(true);
    }

    ImGui::SameLine();
    if (ImGui::Button(Label::restore_defaults.c_str()))
    {
        ResetDefaults();
    }
}

template <class T>
bool SettingSlider(const char *label, T &slider_var, const T min, const T max, const char *fmt,
                   REX::TOML::Setting<T> &setting, const char *help)
{
    ImGui::SetNextItemWidth(200.f);
    bool changed = ImGui::SliderScalar(label, ImGuiDataType_::ImGuiDataType_Float, &slider_var, &min, &max, fmt);
    if (changed)
    {
        setting.SetValue(slider_var);
    }
    ImGui::SameLine();
    ux::HelpMarker(help);
    return changed;
}

inline bool SettingCheckbox(const char *label, bool &value_var, REX::TOML::Setting<bool> &setting, const char *help)
{
    bool changed = ImGui::Checkbox(label, &value_var);
    if (changed)
    {
        setting.SetValue(value_var);
    }
    ImGui::SameLine();
    ux::HelpMarker(help);
    return changed;
}

namespace Settings
{
void __stdcall RenderSettings()
{
    using set = Config::Settings;
    FontAwesome::PushSolid();
    ImGui::Text(Titles::BOWS_BREAK.c_str());
    ImGui::NewLine();

    SettingCheckbox(Label::destroy_bow.c_str(), Var::destroy_bow, set::destroy_bow, Tool::destroy_bow.c_str());
    ImGui::SameLine();
    SettingCheckbox(Label::spawn_wood.c_str(), Var::spawn_wood, set::spawn_wood, Tool::spawn_wood.c_str());

    SettingCheckbox(Label::only_power_attacks.c_str(), Var::only_power_attacks, set::only_power_attacks,
                    Tool::only_power_attacks.c_str());
    ImGui::SameLine();
    SettingCheckbox(Label::use_actor_mass.c_str(), Var::use_actor_mass, set::use_actor_mass,
                    Tool::use_actor_mass.c_str());

    SettingSlider(Label::mass_threshold.c_str(), Var::mass_threshold, 0.0f, 50.0f, "%.2f", set::mass_threshold,
                  Tool::mass_threshold.c_str());

    RenderSystem();

    FontAwesome::Pop();
}
} // namespace Settings
} // namespace Menu
