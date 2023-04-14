#include "Button.h"
#include <cstring>
#include <iostream>
#include "FontMapper/FontMapper.h"

using namespace MTK;

Button::Button(Rectangle location,
    const char *text,
    const char *font ,
    RGBA background,
    RGBA foreground,
    uint8_t fontSize):
    m_Location { location },
    m_BackgroundColor { background },
    m_ForegroundColor { foreground },
    m_FontSize { fontSize },
    m_ClickedEvent { nullptr }
{
    SetText(text);
    if (!FontMapper::Instance()->GetFontWithPath(font, m_Font))
    {
        std::cout << "DEBUG: Using Custom Font: " << font << std::endl;
        SetFont(font);
    }
}

void Button::SetText(const char *text)
{
    memset(m_Text, 0 , sizeof(m_Text));
    size_t textLength = strlen(text);
    if (textLength > MAX_BUTTON_TEXT_SIZE - 1)
    {
        std::cout << "WARNING: Font Length is too long!: " 
            << text << " truncated to 512" << std::endl;
        textLength = MAX_FONT_SIZE - 1;
    }
    memcpy(m_Text, text, textLength);
}

void Button::SetFont(const char *font)
{
    memset(m_Font, 0 , sizeof(m_Font));
    size_t fontLength = strlen(font);
    if (fontLength > MAX_FONT_SIZE - 1)
    {
        std::cout << "WARNING: Font Length is too long!: " 
            << font << " truncated to 512" << std::endl;
        fontLength = MAX_FONT_SIZE - 1;
    }
    memcpy(m_Font, font, fontLength);
}

void Button::OnClicked()
{
    if (m_ClickedEvent != nullptr)
    {
        m_ClickedEvent->OnClicked(this);
    }
}
