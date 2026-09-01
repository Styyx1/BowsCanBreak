#pragma once

#include "RE/A/Actor.h"
#include "RE/B/BSTEvent.h"
#include "RE/T/TESHitEvent.h"
#include "REX/TSingleton.h"
namespace NOOB
{

using RES = RE::BSEventNotifyControl;

struct HitEvList : REX::TSingleton<HitEvList>, RE::BSTEventSink<RE::TESHitEvent>
{

    static void RegisterHit();

  private:
    bool IsInMassRange(RE::Actor* a_attacker) const;
    bool UseOrIsPowerAttack(RE::Actor* a_attacker) const;
    bool CanDefenderWeaponBreak(RE::Actor* a_victim, RE::TESObjectWEAP* a_weapon) const;
    bool IsDefenderProtected(RE::Actor* a_victim) const;
    bool IsInHealthRange(RE::Actor* a_victim) const;
    bool IsHighSkill(RE::Actor* a_victim) const;
    void ProcessWeaponLoss(RE::Actor* a_victim, RE::TESObjectWEAP* a_weapon);
    static float GetRandSpawn(float min, float max);

  protected:
    RES ProcessEvent(const RE::TESHitEvent* a_event, RE::BSTEventSource<RE::TESHitEvent>*) override;
};

} // namespace NOOB