#include "FontMapper.h"
#include <cstring>
#include <array>
#include "Constants.h"

using namespace MTK;

const std::array<const char*, 1> FontArray =  {
    "Fira Code"
};

const std::array<const char*, 1> FontPathArray = {
    "fonts/Fira_Code/FiraCode-VariableFont_wght.ttf"
};

FontMapper *FontMapper::m_Instance = nullptr;

FontMapper::FontMapper()
{
}


FontMapper *FontMapper::Instance()
{
    if (m_Instance == nullptr)
        m_Instance = new FontMapper();

    return m_Instance;
}

bool FontMapper::GetFontWithPath(const char *font, char *fontWithFullPath)
{
    bool bResult = false;
    int index = 0;
    for (index = 0; index < FontArray.size(); index++)
    {
        const char *fontName = FontArray[index];
        if (!strcmp(fontName, font))
        {
            bResult = true;
            break;
        }
    }

    if (bResult)
    {
        strcpy(fontWithFullPath, FontPathArray[index]);
    }

    return bResult;
}
