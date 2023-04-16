#include "Widget/Button.h"
#include <cstring>
#include <iostream>
#include "FontMapper/FontMapper.h"

using namespace MTK;

void Button::OnClicked()
{
    if (m_ClickedEvent != nullptr)
    {
        m_ClickedEvent->OnClicked(this);
    }
}
