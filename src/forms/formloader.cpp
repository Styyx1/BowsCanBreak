#include "formloader.h"

#include "mod-data.h"

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

    auto dh = RE::TESDataHandler::GetSingleton();

    auto& keyarray = dh->GetFormArray(RE::FormType::Keyword);

    bool found     = false;
    bool found_req = false;

    for (auto* key : keyarray)
    {

        auto keyw = key->As<RE::BGSKeyword>();
        if (!keyw)
        {
            continue;
        }
        if (!REX::STR::IEQUALS(keyw->GetFormEditorID(), BREAKWORD) &&
            !REX::STR::IEQUALS(keyw->GetFormEditorID(), BREAKWORD_REQ))
        {
            continue;
        }

        if (REX::STR::IEQUALS(keyw->GetFormEditorID(), BREAKWORD))
        {
            m_breakableKey = keyw;
            found          = true;
        }
        if (MiscUtil::IsModLoaded("Requiem.esp"))
        {
            if (REX::STR::IEQUALS(keyw->GetFormEditorID(), BREAKWORD_REQ))
            {
                m_breakableKeyRequiem = keyw;
                found_req             = true;
            }
        }
        else
        {
            found_req = true;
        }
        if (found && found_req)
        {
            return;
        }
    }
}

} // namespace NOOB