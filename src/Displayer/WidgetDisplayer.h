#ifndef _MTK_WIDGETDISPLAYER_H_
#define _MTK_WIDGETDISPLAYER_H_
#include "Widget/Widget.h"
#include "IDisplayer.h"
namespace MTK
{
    class WidgetDisplayer : public IDisplayer
    {
    public:
        WidgetDisplayer(const Widget &widget,
            SDL_Renderer *renderer);
        virtual ~WidgetDisplayer() { }
        virtual void Handle(const SDL_Event &event,
            const Position &mousePosition) override;
        virtual void Render() override;

    private:
        const Widget &m_Widget;
        SDL_Renderer *m_Renderer;
        bool bMousePressedState;
    };
} // namespace MTK

#endif // _MTK_WIDGETDISPLAYER_H_