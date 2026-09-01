#include "config.h"

#include "mod-data.h"

namespace NOOB
{


void CONF::UpdateSettings(const bool a_save)
{

    auto s = REX::TSingleton<REX::FTomlSettingStore>::GetSingleton();
    s->Init(TOML_P_D, TOML_P_C);

    a_save ? s->Save() : s->Load();
}
float CONF::GetFloatFromPerc(float a_percentageValue)
{
    return a_percentageValue / 100.f;
}

} // namespace NOOB