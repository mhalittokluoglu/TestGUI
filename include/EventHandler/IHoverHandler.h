#ifndef _MTK_IHOVERHANDLER_H_
#define _MTK_IHOVERHANDLER_H_
namespace MTK
{
    class IHoverHandler
    {
    public:
        IHoverHandler(bool hoverEffect = true) :
            m_bHoverEffect { hoverEffect } { }
        virtual ~IHoverHandler() { }
        virtual void OnHover() = 0;
        inline bool GetHoverEffectAvailable() const { return m_bHoverEffect; }

    protected:
        bool m_bHoverEffect;
    };
} // namespace MTK

#endif // _MTK_IHOVERHANDLER_H_