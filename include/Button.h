#ifndef _MTK_BUTTON_H_
#define _MTK_BUTTON_H_
#include "Shapes.h"
#include "Constants.h"
#include "Types.h"
#include "IButtonClickedEvent.h"
namespace MTK
{
    class ToolKit;
    class Button
    {
    public:
        Button(Rectangle location,
            const char *text = "Button",
            const char *font = "Fira Code",
            RGBA background = RGBA(0xAA, 0xAA, 0xAA, 0xFF),
            RGBA foreground = RGBA(0x00, 0x00, 0x00, 0xFF),
            uint8_t fontSize = 12);
        virtual ~Button() { }

    // Setters
        inline void SetLocation(Rectangle location) { m_Location = location; }
        void SetText(const char *text);
        inline void SetBackgroundColor(RGBA bgColor) { m_BackgroundColor = bgColor; }
        inline void SetForegroundColor(RGBA fgColor) { m_ForegroundColor = fgColor; }
        void SetFont(const char *font);
        inline void SetFontSize(uint8_t fontSize) { m_FontSize = fontSize; }
        inline void SetWindowID(WindowID windowID) { m_WindowID = windowID; }
        inline void SetClickedEvent(IButtonClickedEvent *event) { m_ClickedEvent = event; }

    // Getters
        inline Rectangle GetLocation() const { return m_Location; }
        inline const char *GetText() const { return m_Text; }
        inline RGBA GetBackgroundColor() const { return m_BackgroundColor; }
        inline RGBA GetForegroundColor() const { return m_ForegroundColor; }
        inline const char* GetFont() const { return m_Font; }
        inline uint8_t GetFontSize() const { return m_FontSize; }
        inline WindowID GetWindowID() const { return m_WindowID; }

    private:
        char m_Font[MAX_FONT_SIZE];
        char m_Text[MAX_BUTTON_TEXT_SIZE];
        RGBA m_BackgroundColor;
        RGBA m_ForegroundColor;
        Rectangle m_Location;
        uint8_t m_FontSize;
        WindowID m_WindowID;
        IButtonClickedEvent *m_ClickedEvent;

    private:
        void OnClicked();
        friend class ToolKit;

    };
} // namespace MTK

#endif // _MTK_BUTTON_H_