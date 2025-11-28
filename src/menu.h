#pragma once

namespace Menu
{
    using ux = StyyxUtil::UIUtil;

    namespace Titles
    {
        inline std::string MOD_TITLE    = "Bows Can Break";
        inline std::string SETTINGS_SEC = "Settings";
    } // namespace Titles

    namespace Label
    {
        inline std::string system           = FontAwesome::UnicodeToUtf8(0xf390) + " System";
        inline std::string save_settings    = FontAwesome::UnicodeToUtf8(0xf0c7) + " Save Settings";
        inline std::string restore_defaults = FontAwesome::UnicodeToUtf8(0xf0e2) + " Reset Settings";
    } // namespace Label

    void RegisterMenu();
    void RestoreFromSettings();
    void ResetDefaults();
    void RenderSystem();
    

    namespace Settings
    {
        namespace Titles
        {
            inline std::string BOWS_BREAK = "Bows Can Break";
        } // namespace Titles

        namespace Label
        {
            inline std::string destroy_bow               = "Destroy Bows";
            inline std::string spawn_wood                = "Spawn Firewood";
            inline std::string only_power_attacks        = "Require Power Attack";
            inline std::string use_actor_mass            = "Use Actor Mass";
            inline std::string mass_threshold            = "Mass Threshold";
            inline std::string use_health_percentage     = "Use Health Percentage";
            inline std::string health_percentage_threshold = "Health Percentage Threshold";
            inline std::string wood_chance                 = "Wood Spawn Chance";
        } // namespace Label

        namespace Tool
        {
            inline std::string destroy_bow        = "Destroy the Bow, if you untick it, it will just drop it!\n Note, there is nothing this mod does to prevent skyrim's physics to eat the bow";
            inline std::string spawn_wood         = "If you destroy the bow, you can have it spawn a piece of firewood";
            inline std::string only_power_attacks = "Only power attacks can break bows";
            inline std::string use_actor_mass     = "If enabled, you need a mod that makes NPCs actually use the mass Actor Value (Requiem is one of those mods)";
            inline std::string mass_threshold     = "Minimum mass required for an actor to be able to break a bow";
            inline std::string use_health_percentage = "Bows can only break if the health of the archer is below a certain percentage";
            inline std::string health_percentage_threshold = "Health percentage threshold below which bows can break";
            inline std::string wood_chance                 = "Chance (in percentage) to spawn firewood when a bow breaks";
        } // namespace Tool

        namespace Var
        {
            inline bool destroy_bow;
            inline bool spawn_wood;
            inline bool only_power_attacks;
            inline bool use_actor_mass;
            inline float mass_threshold;
            inline bool  use_health_percentage;
            inline float health_percentage_threshold;
            inline float wood_chance;
        } // namespace Var

        void __stdcall RenderSettings();
    } // namespace Settings
}

