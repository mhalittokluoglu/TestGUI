#ifndef _MTK_StaticTextWidgetDISPLAYER_H_
#define _MTK_StaticTextWidgetDISPLAYER_H_
#include "WidgetDisplayer.h"
#include "Widget/StaticTextWidget.h"

namespace MTK
{
    class StaticTextWidgetDisplayer : public WidgetDisplayer
    {
    public:
        StaticTextWidgetDisplayer(CursorManager *cursorManager,
            const StaticTextWidget &staticTextWidget,
            SDL_Renderer *renderer);
        virtual ~StaticTextWidgetDisplayer() { }
        virtual void Handle(const SDL_Event &event,
            const Position &mousePosition) override;
        virtual void Render() override;

        static Rectangle GetTextSize(const StaticTextWidget &staticTextWidget);
        static Rectangle GetTextSize(const char* text, const char *font, uint8_t fontSize);

    protected:
        SDL_Texture *m_Texture;
        SDL_Rect m_TextLocation;
        const StaticTextWidget &m_StaticTextWidget;

    };
} // namespace MTK

#endif // _MTK_StaticTextWidgetDISPLAYER_H_