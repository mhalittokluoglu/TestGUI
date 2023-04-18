#include "ToolKit.h"
#include <iostream>
#include "TestHandler/TestClickHandler.h"
#include "TestHandler/TestHoverHandler.h"
#include "Widget/Label.h"

class TestEvent : public MTK::IButtonClickedEvent
{
public:
    TestEvent () { }
    ~TestEvent() { }
    void OnClicked(MTK::Button *button) override
    {
        std::cout << "Clicked on " << button->GetText() << std::endl;
    }
    
};

int main(int argc, char *argv[])
{
    MTK::ToolKit mtk;

    MTK::Window mainWindow;
    mainWindow.SetBackgroundColor(MTK::RGBA(0x77, 0x77, 0x77));
    mainWindow.SetSize(MTK::Size(800, 600));
    mtk.CreateWindow(mainWindow);
    
    mainWindow.SetTitle("Test Application");
    mtk.Update(mainWindow);

    TestEvent testClickEvent;
    MTK::Button button(MTK::Rectangle(300, 300, 50, 20));
    button.SetFontSize(20);
    button.SetClickedEvent(&testClickEvent);
    mtk.CreateButton(mainWindow.GetWindowID(), button);

    MTK::Button button2(MTK::Rectangle(100,50, 20, 10));
    button2.SetText("Click Me");
    button2.SetFontSize(17);
    button2.SetBackgroundColor(MTK::RGBA(0xFF, 0xFF, 0xDD, 0xDD));
    button2.SetClickedEvent(&testClickEvent);
    mtk.CreateButton(mainWindow.GetWindowID(), button2);

    MTK::Widget widget(MTK::Rectangle(200,200,40,20), MTK::RGBA(0xFF, 0xFF, 0xAA, 0xFF));
    mtk.CreateWidget(mainWindow.GetWindowID(), widget);
    MTK::TestClickHandler testclickHandler(widget);
    mtk.RegisterClickEventHandler(widget.GetWidgetID(), &testclickHandler);

    MTK::TestHoverHandler testhoverHandler(widget);
    mtk.RegisterHoverEventHandler(widget.GetWidgetID(), &testhoverHandler);

    MTK::TextableWidget textableWidget(MTK::Rectangle(250, 400, 150, 50),
        MTK::RGBA(0xAA, 0xAA, 0xAA, 0xFF), MTK::RGBA(0, 0, 0, 0xFF), "Test Widget",
        "Fira Code", 11);
    mtk.CreateTextableWidget(mainWindow.GetWindowID(), textableWidget);
    MTK::TestClickHandler testClickHandler2(textableWidget);
    mtk.RegisterClickEventHandler(textableWidget.GetWidgetID(), &testClickHandler2);


    MTK::Label label1(MTK::Rectangle(50, 50),"Merhaba");
    mtk.CreateLabel(mainWindow.GetWindowID(), label1);

    mtk.MainLoop();
    return 0;
}