#include "hit-event.h"

#include "config/config.h"
#include "forms/formloader.h"
#include "mod-data.h"

namespace NOOB
{


void HitEvList::RegisterHit()
{
    if (auto scr = RE::ScriptEventSourceHolder::GetSingleton(); scr)
    {
        scr->AddEventSink(GetSingleton());
        REX::INFO("Registered for HitEvent");
    }
}

bool HitEvList::IsInMassRange(RE::Actor* a_attacker) const
{
    if (CONF::use_actor_mass.GetValue())
    {
        return a_attacker->GetActorValue(RE::ActorValue::kMass) >= CONF::mass_threshold.GetValue();
    }
    return true;
}

bool HitEvList::UseOrIsPowerAttack(RE::Actor* a_attacker) const
{
    if (CONF::only_power_attacks.GetValue())
    {
        return ActorUtil::IsPowerAttacking(a_attacker);
    }
    return true;
}
bool HitEvList::CanDefenderWeaponBreak(RE::Actor* a_victim, RE::TESObjectWEAP* a_weapon) const
{

    bool breakable = a_weapon->HasKeyword(FORMS::m_breakableKey) || a_weapon->HasKeyword(FORMS::m_breakableKeyRequiem);

    // fallback if KID is not installed or fails for whatever reason.
    //  Shouldn't actually happen
    if (!FORMS::m_breakableKey)
    {
        breakable = a_weapon->HasKeywordString(BREAKWORD) || a_weapon->HasKeywordString(BREAKWORD_REQ);
    }

    if (!breakable)
    {
        return false;
    }

    auto state = a_victim->GetAttackState();

    bool bowState = false;

    switch (state)
    {

        case RE::ATTACK_STATE_ENUM::kBowNextAttack:
        case RE::ATTACK_STATE_ENUM::kBowAttached:
        case RE::ATTACK_STATE_ENUM::kBowDraw:
        case RE::ATTACK_STATE_ENUM::kBowDrawn:
        case RE::ATTACK_STATE_ENUM::kBowFollowThrough:
        case RE::ATTACK_STATE_ENUM::kBowReleased:
        case RE::ATTACK_STATE_ENUM::kBowReleasing:
            bowState = true;
            break;
        default:
            break;
    }
    return bowState;
}


bool HitEvList::IsDefenderProtected(RE::Actor* a_victim) const
{
    return ActorUtil::HasEffectWithKeywordActive(a_victim, "UnbreakableBow");
}
bool HitEvList::IsInHealthRange(RE::Actor* a_victim) const
{

    if (CONF::use_health_percent.GetValue())
    {
        return ActorUtil::GetActorValuePercentage(a_victim, RE::ActorValue::kHealth) <=
               CONF::GetFloatFromPerc(CONF::health_percent_threshold.GetValue());
    }
    return true;
}
bool HitEvList::IsHighSkill(RE::Actor* a_victim) const
{

    if (CONF::prevent_with_skill.GetValue())
    {
        return a_victim->GetBaseActorValue(RE::ActorValue::kArchery) >= CONF::skill_level_threshold.GetValue();
    }
    return false;
}
void HitEvList::ProcessWeaponLoss(RE::Actor* a_victim, RE::TESObjectWEAP* a_weapon)
{
    auto em = RE::ActorEquipManager::GetSingleton();
    if (CONF::destroy_bow.GetValue())
    {
        em->UnequipObject(a_victim, a_weapon, nullptr, 1, nullptr, false, true, true, true);
        a_victim->RemoveItem(a_weapon, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr);
        if (CONF::spawn_wood.GetValue())
        {
            if (GetRandSpawn(0.0f, 100.0f) <= CONF::wood_chance.GetValue())
            {
                a_victim->PlaceObjectAtMe(FORMS::m_firewood, false);
            }
        }
    }
    else
    {
        em->UnequipObject(a_victim, a_weapon, nullptr, 1, nullptr, false, true, true, true);
        a_victim->RemoveItem(a_weapon, 1, RE::ITEM_REMOVE_REASON::kDropping, nullptr, nullptr, nullptr);
    }
}
float HitEvList::GetRandSpawn(float a_min, float a_max)
{
    static REX::RNG::F32 rng;
    return rng.Generate(a_min, a_max);
}

RES HitEvList::ProcessEvent(const RE::TESHitEvent* a_event, RE::BSTEventSource<RE::TESHitEvent>*)
{

    using hit = RE::TESHitEvent::Flag;
    if (!a_event || !a_event->target || !a_event->cause || !a_event->source || a_event->projectile)
    {
        return RES::kContinue;
    }
    RE::Actor* archer = a_event->target ? a_event->target->As<RE::Actor>() : nullptr;

    if (!archer || !archer->currentProcess || !archer->GetHighProcess() || !archer->Get3D())
    {
        return RES::kContinue;
    }

    RE::Actor* attacker = a_event->cause ? a_event->cause->As<RE::Actor>() : nullptr;

    if (!attacker || !attacker->currentProcess || !attacker->GetHighProcess() || !attacker->Get3D())
    {
        return RES::kContinue;
    }

    if (!IsInMassRange(attacker) || !UseOrIsPowerAttack(attacker) || IsDefenderProtected(archer) ||
        !IsInHealthRange(archer) || IsHighSkill(archer))
    {
        return RES::kContinue;
    }

    RE::TESObjectWEAP* attacker_weap = ActorUtil::GetWieldingWeapon(attacker);

    if (!attacker_weap || !attacker_weap->IsMelee() || attacker_weap->IsHandToHandMelee())
    {
        return RES::kContinue;
    }

    RE::TESObjectWEAP* archer_weap = ActorUtil::GetWieldingWeapon(archer);

    if (!archer_weap || !(archer_weap->IsBow() || archer_weap->IsCrossbow()) || archer_weap->IsBound())
    {
        return RES::kContinue;
    }

    if (CanDefenderWeaponBreak(archer, archer_weap))
    {
        ProcessWeaponLoss(archer, archer_weap);
    }
    return RES::kContinue;
}

} // namespace NOOB