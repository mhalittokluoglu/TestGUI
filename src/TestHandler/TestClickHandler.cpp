#include "TestClickHandler.h"
#include <iostream>

using namespace MTK;

TestClickHandler::TestClickHandler(const Widget &widget):
    m_Widget { widget }
{
}

void TestClickHandler::OnClicked()
{
    WidgetID widgetID = m_Widget.GetWidgetID();
    std::cout << "Widget with ID " << widgetID << " is clicked\n";
}
