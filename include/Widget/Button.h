#ifndef _MTK_BUTTON_H_
#define _MTK_BUTTON_H_
#include "StaticTextWidget.h"
#include "IButtonClickedEvent.h"
#include "EventHandler/IClickHandler.h"
namespace MTK
{
    class ButtonClickHandler;
    class Button : public StaticTextWidget
    {
    public:
        Button(Rectangle location,
            const char *text = "Button",
            const char *font = "Fira Code",
            RGBA bgColor = RGBA(0xAA, 0xAA, 0xAA, 0xFF),
            RGBA fgColor = RGBA(0x00, 0x00, 0x00, 0xFF),
            uint8_t fontSize = 12);
        virtual ~Button() { }

    // Setters
        void SetClickedEvent(IButtonClickedEvent *event);

    // Getters
        IClickHandler* GetClickHandler() const;

    private:
        ButtonClickHandler *m_ClickedHandler;
    };
    
    class ButtonClickHandler : public IClickHandler
    {
    public:
        ButtonClickHandler(Button *button, IButtonClickedEvent *clickedEvent) :
            m_Button { button },
            m_ClickedEvent { clickedEvent } { }
        virtual ~ButtonClickHandler () { }
        void SetClickedEvent(IButtonClickedEvent *clickedEvent)
        {
            m_ClickedEvent = clickedEvent;
        }
        virtual void OnClicked() override
        {
            if (m_ClickedEvent != nullptr)
            {
                m_ClickedEvent->OnClicked(m_Button);
            }
        }
    private:
        Button *m_Button;
        IButtonClickedEvent *m_ClickedEvent;
    };
} // namespace MTK

#endif // _MTK_BUTTON_H_