#ifndef _MTK_TESTHOVERHANDLER_H_
#define _MTK_TESTHOVERHANDLER_H_
#include "EventHandler/IHoverHandler.h"
#include "Widget/Widget.h"
namespace MTK
{
    class TestHoverHandler : public IHoverHandler
    {
    public:
        TestHoverHandler(const Widget & widget) :
            m_Widget { widget } { }
        virtual ~TestHoverHandler() { }
        virtual void OnHover() override;
        
    protected:
        const Widget &m_Widget;
    };
} // namespace MTK

#endif // _MTK_TESTHOVERHANDLER_H_