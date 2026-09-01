#pragma once

#include "RE/B/BGSKeyword.h"
#include "RE/B/BGSKeywordForm.h"
namespace NOOB
{

namespace FORMS
{

inline RE::TESObjectMISC* m_firewood{nullptr};
inline RE::BGSKeyword* m_breakableKey{nullptr};
inline RE::BGSKeyword* m_breakableKeyRequiem{nullptr};

void LoadForms();
void LookupKeywords();
} // namespace FORMS

} // namespace NOOB