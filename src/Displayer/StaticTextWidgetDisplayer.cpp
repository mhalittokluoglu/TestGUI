#include "StaticTextWidgetDisplayer.h"
#include "SDL_Related/SDL_ttf_Include.h"

using namespace MTK;

StaticTextWidgetDisplayer::StaticTextWidgetDisplayer(
    CursorManager *cursorManager,
    const StaticTextWidget &staticTextWidget,
    SDL_Renderer *renderer) : 
        WidgetDisplayer(cursorManager, staticTextWidget, renderer),
        m_StaticTextWidget { staticTextWidget }
{
    const Rectangle &location = m_Widget.GetLocation();

    RGBA bgColor = m_StaticTextWidget.GetBackgroundColor();
    SDL_Color bg = {bgColor.R, bgColor.G, bgColor.B, bgColor.A};

    RGBA fgColor = m_StaticTextWidget.GetForegroundColor();
    SDL_Color fg = {fgColor.R, fgColor.G, fgColor.B, fgColor.A};

    TTF_Font* font = TTF_OpenFont(m_StaticTextWidget.GetFont(), m_StaticTextWidget.GetFontSize());
    SDL_Surface* textSurface = TTF_RenderUTF8_Shaded(font, m_StaticTextWidget.GetText(), fg, bg);
    if (bg.a == 0)
        textSurface = TTF_RenderUTF8_Blended(font, m_StaticTextWidget.GetText(), fg);
    m_Texture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);

    m_TextLocation.x = location.X;
    m_TextLocation.y = location.Y;
    m_TextLocation.w = textSurface->w;
    m_TextLocation.h = textSurface->h;

    SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &m_TextLocation);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void StaticTextWidgetDisplayer::Handle(const SDL_Event &event, const Position &mousePosition)
{
    WidgetDisplayer::Handle(event, mousePosition);
}

void StaticTextWidgetDisplayer::Render()
{
    const Rectangle &location = m_StaticTextWidget.GetLocation();
    SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &m_TextLocation);
    if (bMousePressedState && m_ClickHandler != nullptr && m_ClickHandler->GetClickEffectAvailable())
    {
        SDL_Rect rectBorder { location.X, location.Y, location.W, location.H };
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0xFF);
        SDL_RenderDrawRect(m_Renderer, &rectBorder);
    }
    else if (bMouseHover && m_HoverHandler != nullptr && m_HoverHandler->GetHoverEffectAvailable())
    {
        SDL_Rect rectBorder { location.X, location.Y, location.W, location.H };
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawRect(m_Renderer, &rectBorder);
    }
}

Rectangle StaticTextWidgetDisplayer::GetTextSize(const StaticTextWidget &staticTextWidget)
{
    TTF_Font* font = TTF_OpenFont(staticTextWidget.GetFont(), staticTextWidget.GetFontSize());
    int w, h;
    TTF_SizeText(font, staticTextWidget.GetText(), &w, &h);
    const Rectangle location = staticTextWidget.GetLocation();
    return Rectangle(location.X, location.Y, w, h); 
}
