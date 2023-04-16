#ifndef _MTK_DISPLAYERSERVICE_H_
#define _MTK_DISPLAYERSERVICE_H_
#include "Shapes.h"
namespace MTK
{
    class DisplayerService
    {
    public:
        static bool IsOverlapped(const Rectangle &rect,
            const Position &pos);
    };
} // namespace MTK

#endif // _MTK_DISPLAYERSERVICE_H_