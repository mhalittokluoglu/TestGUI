#include "Widget/Widget.h"
#include "WidgetIDGenerator.h"

using namespace MTK;

Widget::Widget(Rectangle location, RGBA bgColor) :
    m_Location { location },
    m_BackgroundColor { bgColor }
{
    m_WidgetID = WidgetIDGenerator::GetNextWidgetID();
}
