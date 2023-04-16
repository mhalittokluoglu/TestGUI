#include "DisplayerService.h"

using namespace MTK;

bool DisplayerService::IsOverlapped(const Rectangle &rect, const Position &pos)
{
    bool bResult = false;
    if (rect.X < pos.X &&
        rect.Y < pos.Y &&
        rect.X + rect.W > pos.X &&
        rect.Y + rect.H > pos.Y)
    {
        bResult = true;
    }
    return bResult;
}
