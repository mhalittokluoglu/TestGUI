#include "Widget/CursorManager.h"
#include "SDL_Related/SDL_Include.h"
#include <unordered_map>

using namespace MTK;

static std::unordered_map<SDL_SystemCursor, SDL_Cursor*> CursorMap;
static SDL_Cursor *CurrentCursor = nullptr;

CursorManager::CursorManager()
{
    SDL_Cursor *cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    CursorMap[SDL_SYSTEM_CURSOR_ARROW] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    CursorMap[SDL_SYSTEM_CURSOR_IBEAM] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
    CursorMap[SDL_SYSTEM_CURSOR_WAIT] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    CursorMap[SDL_SYSTEM_CURSOR_CROSSHAIR] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW);
    CursorMap[SDL_SYSTEM_CURSOR_WAITARROW] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    CursorMap[SDL_SYSTEM_CURSOR_SIZENWSE] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    CursorMap[SDL_SYSTEM_CURSOR_SIZENESW] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    CursorMap[SDL_SYSTEM_CURSOR_SIZEWE] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    CursorMap[SDL_SYSTEM_CURSOR_SIZENS] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    CursorMap[SDL_SYSTEM_CURSOR_SIZEALL] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
    CursorMap[SDL_SYSTEM_CURSOR_NO] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    CursorMap[SDL_SYSTEM_CURSOR_HAND] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_NUM_SYSTEM_CURSORS);
    CursorMap[SDL_NUM_SYSTEM_CURSORS] = cursor;

    CurrentCursor = CursorMap[SDL_SYSTEM_CURSOR_ARROW];
}

CursorManager::~CursorManager()
{
}

SDL_Cursor *CursorManager::GetCursor() const
{
    return CurrentCursor;
}

void CursorManager::SetCursor(SDL_SystemCursor cursorType)
{
    CurrentCursor = CursorMap[cursorType];
}
