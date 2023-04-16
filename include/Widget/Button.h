#ifndef _MTK_BUTTON_H_
#define _MTK_BUTTON_H_
#include "TextableWidget.h"
#include "IButtonClickedEvent.h"
namespace MTK
{
    class ToolKit;
    class Button : public TextableWidget
    {
    public:
        Button(Rectangle location,
            const char *text = "Button",
            const char *font = "Fira Code",
            RGBA bgColor = RGBA(0xAA, 0xAA, 0xAA, 0xFF),
            RGBA fgColor = RGBA(0x00, 0x00, 0x00, 0xFF),
            uint8_t fontSize = 12) :
                TextableWidget(location, bgColor,
                fgColor, text, font, fontSize),
                m_ClickedEvent { nullptr } { }
        virtual ~Button() { }

    // Setters
        inline void SetClickedEvent(IButtonClickedEvent *event) { m_ClickedEvent = event; }

    private:
        IButtonClickedEvent *m_ClickedEvent;

    private:
        void OnClicked();
        friend class ToolKit;

    };
} // namespace MTK

#endif // _MTK_BUTTON_H_