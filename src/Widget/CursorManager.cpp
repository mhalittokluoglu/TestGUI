#include "Widget/CursorManager.h"
#include "SDL_Related/SDL_Include.h"
#include <unordered_map>

using namespace MTK;

static std::unordered_map<EnumCursor, SDL_Cursor*> CursorMap;
static SDL_Cursor *CurrentCursor = nullptr;

CursorManager::CursorManager()
{
    SDL_Cursor *cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    CursorMap[CURSOR_ARROW] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    CursorMap[CURSOR_IBEAM] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
    CursorMap[CURSOR_WAIT] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    CursorMap[CURSOR_CROSSHAIR] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW);
    CursorMap[CURSOR_WAITARROW] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    CursorMap[CURSOR_SIZENWSE] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    CursorMap[CURSOR_SIZENESW] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    CursorMap[CURSOR_SIZEWE] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    CursorMap[CURSOR_SIZENS] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    CursorMap[CURSOR_SIZEALL] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
    CursorMap[CURSOR_NO] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    CursorMap[CURSOR_HAND] = cursor;
    cursor = SDL_CreateSystemCursor(SDL_NUM_SYSTEM_CURSORS);
    CursorMap[NUM_SYSTEM_CURSORS] = cursor;

    CurrentCursor = CursorMap[CURSOR_ARROW];
}

CursorManager::~CursorManager()
{
}

void *CursorManager::GetCursor() const
{
    return CurrentCursor;
}

void CursorManager::SetCursor(EnumCursor cursorType)
{
    CurrentCursor = CursorMap[cursorType];
}
