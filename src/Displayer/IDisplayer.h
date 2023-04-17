#ifndef _MTK_IDISPLAYER_H_
#define _MTK_IDISPLAYER_H_
#include "SDL_Related/SDL_Include.h"
#include "Shapes.h"
#include "EventHandler/IClickHandler.h"
#include "EventHandler/IHoverHandler.h"
namespace MTK
{
    class IDisplayer
    {
    public:
        IDisplayer() :
            m_ClickHandler { nullptr },
            m_HoverHandler { nullptr } { }
        virtual ~IDisplayer() { }
        virtual void Handle(const SDL_Event &event,
            const Position &mousePosition) = 0;
        virtual void Render() = 0;
        void RegisterClickHandler(IClickHandler *handler) { m_ClickHandler = handler; }
        void RegisterHoverHandler(IHoverHandler *handler) { m_HoverHandler = handler; }

    protected:
        IClickHandler* m_ClickHandler;
        IHoverHandler* m_HoverHandler;
    };
} // namespace MTK

#endif // _MTK_IDISPLAYER_H_