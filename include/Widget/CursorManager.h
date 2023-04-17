#ifndef _MTK_CURSORMANAGER_H_
#define _MTK_CURSORMANAGER_H_
namespace MTK
{
    enum EnumCursor
    {
        CURSOR_ARROW,
        CURSOR_IBEAM,    
        CURSOR_WAIT,
        CURSOR_CROSSHAIR,
        CURSOR_WAITARROW,
        CURSOR_SIZENWSE,
        CURSOR_SIZENESW, 
        CURSOR_SIZEWE,
        CURSOR_SIZENS,
        CURSOR_SIZEALL,
        CURSOR_NO,
        CURSOR_HAND,
        NUM_SYSTEM_CURSORS
    };

    class CursorManager
    {
    public:
        CursorManager();
        ~CursorManager();
        void *GetCursor() const;
        void SetCursor(EnumCursor cursorType);

    private:
        void *m_Cursor;
    };
} // namespace MTK

#endif // _MTK_CURSORMANAGER_H_