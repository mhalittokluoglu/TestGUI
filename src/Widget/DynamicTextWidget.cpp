#include "Widget/DynamicTextWidget.h"
#include "FontMapper/FontMapper.h"
#include <iostream>
#include <cstring>

using namespace MTK;

MTK::DynamicTextWidget::DynamicTextWidget(Rectangle location,
    RGBA bgColor,
    RGBA fgColor,
    const char *font,
    uint8_t fontSize):
    Widget(location, bgColor),
    m_ForegroundColor { fgColor },
    m_FontSize { fontSize }
{
    m_Text.reserve(1024);
    if (!FontMapper::Instance()->GetFontWithPath(font, m_Font))
    {
        std::cout << "DEBUG: Using Custom Font: " << font << std::endl;
        SetFont(font);
    }
}

void DynamicTextWidget::SetFont(const char *font)
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

void DynamicTextWidget::DeleteChar() const
{
    if (m_Text.size() > 0)
        m_Text.erase(m_Text.size() - 1);
}
