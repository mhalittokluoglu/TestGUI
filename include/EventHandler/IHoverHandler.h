#ifndef _MTK_IHOVERHANDLER_H_
#define _MTK_IHOVERHANDLER_H_
namespace MTK
{
    class IHoverHandler
    {
    public:
        virtual ~IHoverHandler() { }
        virtual void OnHover() = 0;
    };
} // namespace MTK

#endif // _MTK_IHOVERHANDLER_H_