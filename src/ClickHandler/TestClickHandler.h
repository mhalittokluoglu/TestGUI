#ifndef _MTK_TESTCLICKHANDLER_H_
#define _MTK_TESTCLICKHANDLER_H_
#include "EventHandler/IClickHandler.h"
#include "Widget/Widget.h"
namespace MTK
{
    class TestClickHandler : public IClickHandler
    {
    public:
        TestClickHandler(const Widget &widget);
        virtual ~TestClickHandler() { }
        virtual void OnClicked() override;
        
    protected:
        const Widget &m_Widget;
    };
} // namespace MTK

#endif // _MTK_TESTCLICKHANDLER_H_