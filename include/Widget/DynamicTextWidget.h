#ifndef _MTK_DYNAMICTEXTWIDGET_H_
#define _MTK_DYNAMICTEXTWIDGET_H_
#include "Widget.h"
#include "Constants.h"
#include <string>
namespace MTK
{
    class DynamicTextWidget : public Widget
    {
    public:
        DynamicTextWidget(Rectangle location,
            RGBA bgColor,
            RGBA fgColor,
            const char *font,
            uint8_t fontSize);
        virtual ~DynamicTextWidget() { }

    // Setters
        inline void SetForegroundColor(RGBA fgColor) { m_ForegroundColor = fgColor; }
        void SetFont(const char *font);
        inline void SetFontSize(uint8_t fontSize) { m_FontSize = fontSize; }

    // Getters
        inline RGBA GetForegroundColor() const { return m_ForegroundColor; }
        inline const char* GetFont() const { return m_Font; }
        inline uint8_t GetFontSize() const { return m_FontSize; }
        inline const char* GetText() const { return m_Text.c_str(); }
        inline const int32_t GetTextSize() const { return (int32_t)m_Text.size(); }
        inline std::string GetTextString() const { return m_Text; }
        
        inline void AddString(const char* str) const { m_Text += str; }
        void AddString(const char* str, int index) const;
        inline void ClearString() const { m_Text.clear(); }
        void DeleteChar(int index) const;
        size_t GetUTF8Size() const;

        static size_t GetIndexFromUTF8Index(const char * text, size_t utf8Index);

    protected:
        char m_Font[MAX_FONT_SIZE];
        RGBA m_ForegroundColor;
        uint8_t m_FontSize;
        mutable std::string m_Text;

    };
} // namespace MTK

#endif // _MTK_DYNAMICTEXTWIDGET_H_