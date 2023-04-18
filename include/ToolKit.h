#ifndef _MTK_TOOLKIT_H_
#define _MTK_TOOLKIT_H_
#include "Window.h"
#include "Widget/Button.h"
#include "Widget/Label.h"
#include "EventHandler/IClickHandler.h"
#include "EventHandler/IHoverHandler.h"
#include "Widget/CursorManager.h"
namespace MTK
{
    class ToolKit
    {
    public:
        ToolKit();
        ~ToolKit();
        bool CreateWindow(Window &window);
        bool CreateButton(WindowID windowID, Button &button);
        bool CreateLabel(WindowID windowID, Label &label);
        bool CreateWidget(WindowID windowID, Widget &widget);
        bool CreateStaticTextWidget(WindowID windowID, StaticTextWidget &StaticTextWidget);
        bool RegisterClickEventHandler(WidgetID widgetID, IClickHandler *handler);
        bool RegisterHoverEventHandler(WidgetID widgetID, IHoverHandler *handler);

        void MainLoop();
        void Update(const Window &window);

    private:
        CursorManager *m_CursorManager;

    };
} // namespace MTK

#endif // _MTK_TOOLKIT_H_