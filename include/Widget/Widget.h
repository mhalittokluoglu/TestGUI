#ifndef _MTK_WIDGET_H_
#define _MTK_WIDGET_H_
#include "Shapes.h"
#include "Types.h"
namespace MTK
{
    class Widget
    {
    public:
        Widget(Rectangle location,
                RGBA bgColor);
        virtual ~Widget() { }

    // Setters
        inline void SetLocation(Rectangle location) { m_Location = location; }
        inline void SetBackgroundColor(RGBA bgColor) { m_BackgroundColor = bgColor; }
        inline void SetWindowID(WindowID windowID) { m_WindowID = windowID; }

    // Getters
        inline Rectangle GetLocation() const { return m_Location; }
        inline RGBA GetBackgroundColor() const { return m_BackgroundColor; }
        inline WindowID GetWindowID() const { return m_WindowID; }
        inline WidgetID GetWidgetID() const { return m_WidgetID; }


    protected:
        RGBA m_BackgroundColor;
        Rectangle m_Location;
        WindowID m_WindowID;
        WidgetID m_WidgetID;
    };
} // namespace MTK

#endif // _MTK_WIDGET_H_