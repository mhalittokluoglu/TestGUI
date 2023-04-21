#include "Widget/DynamicTextWidget.h"
#include "FontMapper/FontMapper.h"
#include <iostream>
#include <cstring>
#include <vector>

namespace MTK
{
std::vector<bool> out8ByteVector(1024, false);
} // namespace MTK 

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

void DynamicTextWidget::AddString(const char* str, int index) const
{
    int utf8Index = GetIndexFromUTF8Index(m_Text.c_str(), index);
    if (m_Text.size() < utf8Index)
    {
        AddString(str);
    }
    else
    {
        std::string rightSide = m_Text.substr(utf8Index, m_Text.size() - utf8Index);
        std::string leftSide = m_Text.substr(0, utf8Index);
        m_Text = leftSide;
        m_Text += str;
        m_Text += rightSide;
    }
}

void DynamicTextWidget::DeleteChar(int index) const
{
    int lastIndex = GetIndexFromUTF8Index(m_Text.c_str(), index);
    int firstIndex = GetIndexFromUTF8Index(m_Text.c_str(), index - 1);
    if (m_Text.size() > 0 && lastIndex <= m_Text.size())
    {
        if (firstIndex >= 0 && lastIndex > 0 )
        {
            m_Text.erase(m_Text.begin() + firstIndex, m_Text.begin() + lastIndex);
        }
    }
}

size_t DynamicTextWidget::GetIndexFromUTF8Index(const char * text, size_t utf8Index)
{
    size_t resultIndex = 0;
    size_t textSize = strlen(text);
    for (size_t index = 0; index < utf8Index && index < textSize; index++)
    {
        const unsigned char c = text[resultIndex];
        if (c > 0 && c < 127)
            resultIndex+=1;
        else if ((c & 0xE0) == 0xC0)
            resultIndex+=2;
        else if ((c & 0xF0) == 0xE0)
            resultIndex+=3;
        else if ((c & 0xF8) == 0xF0)
            resultIndex+=4;
    }
    return resultIndex;
}

size_t DynamicTextWidget::GetUTF8Size() const
{
    size_t utf8Size = 0;
    for (size_t index = 0; index < m_Text.size(); utf8Size++)
    {
        const unsigned char c = m_Text[index];
        if (c > 0 && c < 127)
            index+=1;
        else if ((c & 0xE0) == 0xC0)
            index+=2;
        else if ((c & 0xF0) == 0xE0)
            index+=3;
        else if ((c & 0xF8) == 0xF0)
            index+=4;
    }
    return utf8Size;
}
