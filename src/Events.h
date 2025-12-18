#pragma once
#include "Utility.h"
#include "Settings.h"

namespace Events
{
    using event_result = RE::BSEventNotifyControl;
    using set = Config::Settings;
    using fload = Config::Formloader;

    struct OnHitBow : REX::Singleton<OnHitBow>, RE::BSTEventSink<RE::TESHitEvent>
    {
        event_result ProcessEvent(const RE::TESHitEvent* event, RE::BSTEventSource<RE::TESHitEvent>*) override;
        void         Register();

    private:
        bool IsInMassRange(RE::Actor* a_attacker) const;
        bool UseOrIsPowerAttack(RE::Actor* aggressor) const;
        bool CanDefenderWeaponBreak(RE::Actor* defender, RE::TESObjectWEAP* weapon) const;
        bool IsDefenderProtected(RE::Actor* defender) const;
        bool IsInHealthRange(RE::Actor* defender) const;
        bool IsHighSkill(RE::Actor* defender) const;    
    };

} // namespace Events
