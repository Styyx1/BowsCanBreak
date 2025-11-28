#pragma once
#include "Settings.h"

struct Utility 
{    
    inline static void ProcessWeaponLoss(RE::Actor* defender,  RE::TESObjectWEAP* defender_weap) {
        auto eqman = RE::ActorEquipManager::GetSingleton();
        if (Config::Settings::destroy_bow.GetValue()) {
            eqman->UnequipObject(defender, defender_weap, nullptr, 1, nullptr, false, true, true, true);
            defender->RemoveItem(defender_weap, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr);
            REX::DEBUG("destroyed {}", defender_weap->GetName());
            if (Config::Settings::spawn_wood.GetValue()) {
                defender->PlaceObjectAtMe(Config::Formloader::firewood, false);
            }
        }
        else {
            eqman->UnequipObject(defender, defender_weap, nullptr, 1, nullptr, false, true, true, true);
            defender->RemoveItem(defender_weap, 1, RE::ITEM_REMOVE_REASON::kDropping, nullptr, nullptr, nullptr);
            REX::DEBUG("dropped {}", defender_weap->GetName());
        }        
    }
};
