#ifndef _MTK_DYNAMICTEXTWIDGETDISPLAYER_H_
#define _MTK_DYNAMICTEXTWIDGETDISPLAYER_H_
#include "WidgetDisplayer.h"
#include "Widget/CursorManager.h"
#include "Widget/DynamicTextWidget.h"
#include "SDL_Related/SDL_ttf_Include.h"
namespace MTK
{
    class DynamicTextWidgetDisplayer : public WidgetDisplayer
    {
    public:
        DynamicTextWidgetDisplayer(CursorManager *cursorManager,
            const DynamicTextWidget &dynamicTextWidget,
            SDL_Renderer *renderer);
        virtual ~DynamicTextWidgetDisplayer ();

        virtual void Handle(const SDL_Event &event,
            const Position &mousePosition) override;
        virtual void Render() override;

        inline void SetFocus(bool focused) { m_bFocused = focused; }
        static int GetTextHeight(const DynamicTextWidget &widget);
        static int GetCharTextWidth(const DynamicTextWidget &widget);

    protected:
        const DynamicTextWidget &m_DynamicTextWidget;
        TTF_Font *m_Font;
        Position m_TextPosition;
        int32_t m_CharWidth;
    };
} // namespace MTK

#endif // _MTK_DYNAMICTEXTWIDGETDISPLAYER_H_