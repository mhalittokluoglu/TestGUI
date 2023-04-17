#ifndef _MTK_CURSORMANAGER_H_
#define _MTK_CURSORMANAGER_H_
#include "SDL_Related/SDL_Include.h"
namespace MTK
{
    class CursorManager
    {
    public:
        CursorManager();
        ~CursorManager();
        SDL_Cursor *GetCursor() const;
        void SetCursor(SDL_SystemCursor cursorType);

    private:
        void *m_Cursor;
    };
} // namespace MTK

#endif // _MTK_CURSORMANAGER_H_