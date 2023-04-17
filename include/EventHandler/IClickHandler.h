#ifndef _MTK_ICLICKHANDLER_H_
#define _MTK_ICLICKHANDLER_H_
namespace MTK
{
    class IClickHandler
    {
    public:
        IClickHandler(bool clickEffect = true):
            m_bClickEffect { clickEffect } { }
        virtual ~IClickHandler() { }
        virtual void OnClicked() = 0;
        inline bool GetClickEffectAvailable() const { return m_bClickEffect; }

    protected:
        bool m_bClickEffect;
    };
} // namespace MTK

#endif // _MTK_ICLICKHANDLER_H_