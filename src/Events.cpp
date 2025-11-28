#include "Events.h"

namespace Events
{ 

    void OnHitBow::Register()
    {
        RE::ScriptEventSourceHolder* eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
        eventHolder->AddEventSink(this);
        REX::INFO("Registered for {}", typeid(RE::TESHitEvent).name());
    }

    bool OnHitBow::IsInMassRange(RE::Actor* a_attacker) const
    {
        return !set::use_actor_mass.GetValue() || a_attacker->GetActorValue(RE::ActorValue::kMass) >= set::mass_threshold.GetValue();
    }

    bool OnHitBow::UseOrIsPowerAttack(bool p_atk) const
    {
        return !set::only_power_attacks.GetValue() || p_atk;
    }

    bool OnHitBow::CanDefenderWeaponBreak(RE::Actor* defender, RE::TESObjectWEAP* weapon) const
    {
        return (weapon->HasKeywordString("REQ_BowBreakable") || weapon->HasKeywordString("BowBreakable")) && (defender->GetAttackState() == RE::ATTACK_STATE_ENUM::kBowDraw || defender->GetAttackState() == RE::ATTACK_STATE_ENUM::kBowDrawn);
    }

    bool OnHitBow::IsDefenderProtected(RE::Actor* defender) const
    {
        return ActorUtil::HasEffectWithKeywordActive(defender, "UnbreakableBow");
    }

    event_result OnHitBow::ProcessEvent(const RE::TESHitEvent* event, RE::BSTEventSource<RE::TESHitEvent>*)
    {
        using HFlag = RE::TESHitEvent::Flag;
        if (!event || !event->target || !event->cause || event->projectile || !event->source) {
            return event_result::kContinue;
        }

        auto defender = event->target ? event->target->As<RE::Actor>() : nullptr;
        if (!defender || !defender->currentProcess || !defender->currentProcess->high || !defender->Get3D() ) {
            return event_result::kContinue;
        }

        auto aggressor = event->cause ? event->cause->As<RE::Actor>() : nullptr;
        if (!aggressor || !aggressor->currentProcess || !aggressor->currentProcess->high || !aggressor->Get3D()) {
            return event_result::kContinue;
        }

        if (!IsInMassRange(aggressor)) {
            return event_result::kContinue;
        }
        bool p_atk = event->flags.any(HFlag::kPowerAttack);
        if (!UseOrIsPowerAttack(p_atk)) {
            return event_result::kContinue;
        }

        if (IsDefenderProtected(defender)) {
            return event_result::kContinue;
        }

        RE::TESObjectWEAP* attack_weapon  = ActorUtil::getWieldingWeapon(aggressor); 
        if (!attack_weapon || !attack_weapon->IsMelee() || attack_weapon->IsHandToHandMelee()) {
            return event_result::kContinue;
        }

        RE::TESObjectWEAP* defender_weapon = ActorUtil::getWieldingWeapon(defender);
        if (!defender_weapon || !(defender_weapon->IsBow() || defender_weapon->IsCrossbow())) {
            return event_result::kContinue;
        }

        if (CanDefenderWeaponBreak(defender, defender_weapon)) {
            Utility::ProcessWeaponLoss(defender, defender_weapon);
        }

        return event_result::kContinue;
    }

} // namespace Events
