#ifndef _MTK_TOOLKIT_H_
#define _MTK_TOOLKIT_H_
#include "Window.h"
#include "Widget/Button.h"
#include "EventHandler/IClickHandler.h"
namespace MTK
{
    class ToolKit
    {
    public:
        ToolKit();
        ~ToolKit();
        bool CreateWindow(Window &window);
        bool CreateButton(WindowID windowID, Button &button);
        bool CreateWidget(WindowID windowID, Widget &widget);
        bool RegisterClickEventHandler(WidgetID widgetID, IClickHandler *handler);

        void MainLoop();
        void Update(const Window &window);

    };
} // namespace MTK

#endif // _MTK_TOOLKIT_H_