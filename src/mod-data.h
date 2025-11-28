#pragma once

namespace MOD
{
struct DATA
{
    static inline constexpr std::string_view TOML_PATH_DEFAULT = "Data/SKSE/Plugins/breaking-bows.toml";
    inline static constexpr std::string_view TOML_PATH_CUSTOM = "Data/SKSE/Plugins/breaking-bows_custom.toml";

    inline static constexpr std::string_view SETTINGS = "Settings";
    inline static constexpr std::string_view TOGGLES  = "Toggles";

    inline static constexpr std::string_view SKYRIM = "Skyrim.esm";
    inline static constexpr RE::FormID       FIREWOOD_ID = 0x6f993;



};
} // namespace MOD
