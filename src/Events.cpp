#include "Events.h"

namespace Events
{

void OnHitBow::Register()
{
    RE::ScriptEventSourceHolder *eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
    eventHolder->AddEventSink(this);
    REX::INFO("Registered for {}", typeid(RE::TESHitEvent).name());
}

bool OnHitBow::IsInMassRange(RE::Actor *a_attacker) const
{
    return !set::use_actor_mass.GetValue() ||
           a_attacker->GetActorValue(RE::ActorValue::kMass) >= set::mass_threshold.GetValue();
}

bool OnHitBow::UseOrIsPowerAttack(RE::Actor *aggressor) const
{

    if (!set::only_power_attacks.GetValue())
    {
        return true;
    }

    return ActorUtil::IsPowerAttacking(aggressor);
}

bool OnHitBow::CanDefenderWeaponBreak(RE::Actor *defender, RE::TESObjectWEAP *weapon) const
{
    bool hasBreakableKeyword =
        weapon->HasKeywordString("REQ_BowBreakable") ||
        weapon->HasKeywordString("BowBreakable");
    if (!hasBreakableKeyword) {
    
        return false;
    }
       

    auto st = defender->GetAttackState();
    uint32_t state = static_cast<uint32_t>(st);
    //REX::INFO("Defender attack state: {}", MiscUtil::AttackStateToString(st));

    bool isBowAction = (state > 8 && state <= 14);
    return isBowAction;

    return (weapon->HasKeywordString("REQ_BowBreakable") || weapon->HasKeywordString("BowBreakable")) &&
           (defender->GetAttackState() == RE::ATTACK_STATE_ENUM::kBowDraw ||
            defender->GetAttackState() == RE::ATTACK_STATE_ENUM::kBowDrawn);
}

bool OnHitBow::IsDefenderProtected(RE::Actor *defender) const
{
    return ActorUtil::HasEffectWithKeywordActive(defender, "UnbreakableBow");
}

bool OnHitBow::IsInHealthRange(RE::Actor *defender) const
{
    return !Config::Settings::use_health_percentage.GetValue() ||
           ActorUtil::GetActorValuePercentage(defender, RE::ActorValue::kHealth) <=
               Config::Settings::health_percentage_threshold.GetValue() / 100.0;
}

bool OnHitBow::IsHighSkill(RE::Actor *defender) const
{
    return Config::Settings::prevent_with_skill.GetValue() &&
           defender->GetBaseActorValue(RE::ActorValue::kArchery) >= Config::Settings::skill_level_threshold.GetValue();
}

event_result OnHitBow::ProcessEvent(const RE::TESHitEvent *event, RE::BSTEventSource<RE::TESHitEvent> *)
{
    using HFlag = RE::TESHitEvent::Flag;
    if (!event || !event->target || !event->cause || event->projectile || !event->source)
    {
        return event_result::kContinue;
    }

    auto defender = event->target ? event->target->As<RE::Actor>() : nullptr;
    if (!defender || !defender->currentProcess || !defender->currentProcess->high || !defender->Get3D())
    {
        return event_result::kContinue;
    }

    auto aggressor = event->cause ? event->cause->As<RE::Actor>() : nullptr;
    if (!aggressor || !aggressor->currentProcess || !aggressor->currentProcess->high || !aggressor->Get3D())
    {
        return event_result::kContinue;
    }

    if (!IsInMassRange(aggressor))
    {
        //REX::INFO("{} not in mass range", aggressor->GetName());
        return event_result::kContinue;
    }

    if (!UseOrIsPowerAttack(aggressor))
    {
        //REX::INFO("power attack for {} is false", aggressor->GetName());
        return event_result::kContinue;
    }

    if (IsDefenderProtected(defender))
    {
        //REX::INFO("{} is protected", defender->GetName());
        return event_result::kContinue;
    }

    if (!IsInHealthRange(defender))
    {
        //REX::INFO("{} is not in health range", defender->GetName());
        return event_result::kContinue;
    }

    if (IsHighSkill(defender))
    {
        //REX::INFO("{} has high skill", defender->GetName());
        return event_result::kContinue;
    }

    RE::TESObjectWEAP *attack_weapon = ActorUtil::getWieldingWeapon(aggressor);
    if (!attack_weapon || !attack_weapon->IsMelee() || attack_weapon->IsHandToHandMelee())
    {
        //REX::INFO("attacker weapon is not melee");
        return event_result::kContinue;
    }

    RE::TESObjectWEAP *defender_weapon = ActorUtil::getWieldingWeapon(defender);
    if (!defender_weapon || !(defender_weapon->IsBow() || defender_weapon->IsCrossbow()))
    {
        //REX::INFO("defender weapon is not bow or crossbow");
        return event_result::kContinue;
    }

    if (CanDefenderWeaponBreak(defender, defender_weapon))
    {
        //REX::INFO("processing weapon loss");
        Utility::ProcessWeaponLoss(defender, defender_weapon);
    }

    return event_result::kContinue;
}

} // namespace Events
