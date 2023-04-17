#include "Widget/Button.h"
#include <cstring>
#include <iostream>
#include "FontMapper/FontMapper.h"
#include "Widget/Button.h"

using namespace MTK;

Button::Button(Rectangle location,
    const char *text,
    const char *font,
    RGBA bgColor, RGBA fgColor,
    uint8_t fontSize):
        TextableWidget(location, bgColor,
                fgColor, text, font, fontSize)
{
    m_ClickedHandler = new ButtonClickHandler(this, nullptr);
}

void Button::SetClickedEvent(IButtonClickedEvent * event)
{
    m_ClickedHandler->SetClickedEvent(event);
}

IClickHandler* Button::GetClickHandler() const
{
    return m_ClickedHandler;
}
