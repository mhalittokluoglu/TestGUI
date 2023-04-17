#ifndef _MTK_TEXTABLEWIDGETDISPLAYER_H_
#define _MTK_TEXTABLEWIDGETDISPLAYER_H_
#include "WidgetDisplayer.h"
#include "Widget/TextableWidget.h"

namespace MTK
{
    class TextableWidgetDisplayer : public WidgetDisplayer
    {
    public:
        TextableWidgetDisplayer(CursorManager *cursorManager,
            const TextableWidget &textableWidget,
            SDL_Renderer *renderer);
        virtual ~TextableWidgetDisplayer() { }
        virtual void Handle(const SDL_Event &event,
            const Position &mousePosition) override;
        virtual void Render() override;

        static Rectangle GetTextSize(const TextableWidget &textableWidget);

    protected:
        SDL_Texture *m_Texture;
        SDL_Rect m_TextLocation;
        const TextableWidget &m_TextableWidget;

    };
} // namespace MTK

#endif // _MTK_TEXTABLEWIDGETDISPLAYER_H_