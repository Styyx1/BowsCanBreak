#include "formloader.h"

#include "RE/B/BGSKeywordForm.h"
#include "RE/T/TESDataHandler.h"
#include "RE/T/TESObjectMISC.h"
#include "mod-data.h"
#include "st-misc.h"

namespace NOOB
{


void FORMS::LoadForms()
{

    auto dh    = RE::TESDataHandler::GetSingleton();
    m_firewood = dh->LookupForm<RE::TESObjectMISC>(FIREWOOD_ID, SKYRIM);

    if (!m_firewood)
    {
        REX::FAIL("Can not find firewood item!");
    }
}
void FORMS::LookupKeywords()
{
    m_breakableKey        = RE::TESForm::LookupByEditorID<RE::BGSKeyword>(BREAKWORD);
    m_breakableKeyRequiem = RE::TESForm::LookupByEditorID<RE::BGSKeyword>(BREAKWORD_REQ);

    if(!m_breakableKey){
        REX::WARN("could not find {} keyword", BREAKWORD);
    }

    if (MiscUtil::IsModLoaded("Requiem.esp")){
        if(!m_breakableKeyRequiem){
            REX::WARN("Could not find requiem breakable keyword");
        }
    }
}

} // namespace NOOB