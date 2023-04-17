#ifndef _MTK_ICLICKHANDLER_H_
#define _MTK_ICLICKHANDLER_H_
namespace MTK
{
    class IClickHandler
    {
    public:
        virtual ~IClickHandler() { }
        virtual void OnClicked() = 0;
    };
} // namespace MTK

#endif // _MTK_ICLICKHANDLER_H_