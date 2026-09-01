#pragma once

#include <cstdint>
namespace NOOB
{

namespace IGMenu
{

namespace TIT
{
inline constexpr auto MOD_TITLE        = "Bows Can Break";
inline constexpr auto SETTINGS_SECTION = "Settings";
inline constexpr auto SYSTEM_SECTION   = "System";
} // namespace TIT
namespace LAB
{
inline constexpr auto destroy_bow              = "Destroy Bows";
inline constexpr auto spawn_wood               = "Spawn Firewood";
inline constexpr auto only_power_attacks       = "Requires Power Attack";
inline constexpr auto use_actor_mass           = "Use Actor Mass";
inline constexpr auto mass_threshold           = "Min Mass required";
inline constexpr auto use_health_percentage    = "Use Health Percent";
inline constexpr auto health_percent_threshold = "Health Percent Threshold";
inline constexpr auto wood_chance              = "Firewood Spawn Chance";
inline constexpr auto prevent_with_skill       = "Prevent with hight Skill";
inline constexpr auto skill_level_threshold    = "Skill level threshold";
} // namespace LAB
namespace VAR
{
inline bool destroy_bow;
inline bool spawn_wood;
inline bool only_power_attacks;
inline bool use_actor_mass;
inline float mass_threshold;
inline bool use_health_percentage;
inline float health_percentage_threshold;
inline float wood_chance;
inline bool prevent_with_skill;
inline uint32_t skill_level_threshold;
} // namespace VAR
namespace HEL
{
inline constexpr auto destroy_bow = "Destroy the Bow, if you untick it, it will just drop it!\n Note, there is nothing "
                                    "this mod does to prevent skyrim's physics to eat the bow";
inline constexpr auto spawn_wood  = "If you destroy the bow, you can have it spawn a piece of firewood";
inline constexpr auto only_power_attacks = "Only power attacks can break bows";
inline constexpr auto use_actor_mass =
    "If enabled, you need a mod that makes NPCs actually use the mass Actor Value (Requiem is one of those mods)";
inline constexpr auto mass_threshold = "Minimum mass required for an actor to be able to break a bow";
inline constexpr auto use_health_percentage =
    "Bows can only break if the health of the archer is below a certain percentage";
inline constexpr auto health_percent_threshold = "Health percent threshold below which bows can break";
inline constexpr auto wood_chance              = "Chance (in percent) to spawn firewood when a bow breaks";
inline constexpr auto prevent_with_skill       = "Prevent bow breaking if the archer has high Archery skill";
inline constexpr auto skill_level_threshold    = "Archery skill level threshold above which bow breaking is prevented";
} // namespace HEL
namespace FUN
{
void RestoreDefaults();
void LoadFromConfig();
} // namespace FUN

} // namespace IGMenu

} // namespace NOOB