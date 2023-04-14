#ifndef _MTK_IBUTTONCLICKEDEVENT_H_
#define _MTK_IBUTTONCLICKEDEVENT_H_
namespace MTK
{
    class Button;
    class IButtonClickedEvent
    {
    public:
        virtual ~IButtonClickedEvent() { }
        virtual void OnClicked(Button *button) = 0;
    };
} // namespace MTK

#endif // _MTK_IBUTTONCLICKEDEVENT_H_