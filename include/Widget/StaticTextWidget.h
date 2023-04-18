#ifndef _MTK_StaticTextWidget_H_
#define _MTK_StaticTextWidget_H_
#include "Widget.h"
#include "Constants.h"
namespace MTK
{
    class StaticTextWidget : public Widget
    {
    public:
        StaticTextWidget(Rectangle location,
                        RGBA bgColor,
                        RGBA fgColor,
                        const char *text,
                        const char *font,
                        uint8_t fontSize);
        virtual ~StaticTextWidget() { }

    // Setters
        void SetText(const char *text);
        inline void SetForegroundColor(RGBA fgColor) { m_ForegroundColor = fgColor; }
        void SetFont(const char *font);
        inline void SetFontSize(uint8_t fontSize) { m_FontSize = fontSize; }

    // Getters
        inline const char *GetText() const { return m_Text; }
        inline RGBA GetForegroundColor() const { return m_ForegroundColor; }
        inline const char* GetFont() const { return m_Font; }
        inline uint8_t GetFontSize() const { return m_FontSize; }

    protected:
        char m_Font[MAX_FONT_SIZE];
        char m_Text[MAX_BUTTON_TEXT_SIZE];
        RGBA m_ForegroundColor;
        uint8_t m_FontSize;
    };
} // namespace MTK

#endif // _MTK_StaticTextWidget_H_