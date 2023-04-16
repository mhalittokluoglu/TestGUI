#ifndef _MTK_IDISPLAYER_H_
#define _MTK_IDISPLAYER_H_
#include "SDL_Related/SDL_Include.h"
#include "Shapes.h"
namespace MTK
{
    class IDisplayer
    {
    public:
        virtual ~IDisplayer() { }
        virtual void Handle(const SDL_Event &event,
            const Position &mousePosition) = 0;
        virtual void Render() = 0;
    };
} // namespace MTK

#endif // _MTK_IDISPLAYER_H_