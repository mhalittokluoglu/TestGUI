#include "TextableWidgetDisplayer.h"
#include "SDL_Related/SDL_ttf_Include.h"

using namespace MTK;

TextableWidgetDisplayer::TextableWidgetDisplayer(
    CursorManager *cursorManager,
    const TextableWidget &textableWidget,
    SDL_Renderer *renderer) : 
        WidgetDisplayer(cursorManager, textableWidget, renderer),
        m_TextableWidget { textableWidget }
{
    const Rectangle &location = m_Widget.GetLocation();

    RGBA bgColor = m_TextableWidget.GetBackgroundColor();
    SDL_Color bg = {bgColor.R, bgColor.G, bgColor.B, bgColor.A};

    RGBA fgColor = m_TextableWidget.GetForegroundColor();
    SDL_Color fg = {fgColor.R, fgColor.G, fgColor.B, fgColor.A};

    TTF_Font* font = TTF_OpenFont(m_TextableWidget.GetFont(), m_TextableWidget.GetFontSize());
    SDL_Surface* textSurface = TTF_RenderText_Shaded(font, m_TextableWidget.GetText(), fg, bg);
    if (bg.a == 0)
        textSurface = TTF_RenderText_Blended(font, m_TextableWidget.GetText(), fg);
    m_Texture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);

    m_TextLocation.x = location.X;
    m_TextLocation.y = location.Y;
    m_TextLocation.w = textSurface->w;
    m_TextLocation.h = textSurface->h;

    SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &m_TextLocation);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void TextableWidgetDisplayer::Handle(const SDL_Event &event, const Position &mousePosition)
{
    WidgetDisplayer::Handle(event, mousePosition);
}

void TextableWidgetDisplayer::Render()
{
    const Rectangle &location = m_TextableWidget.GetLocation();
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

Rectangle TextableWidgetDisplayer::GetTextSize(const TextableWidget &textableWidget)
{
    TTF_Font* font = TTF_OpenFont(textableWidget.GetFont(), textableWidget.GetFontSize());
    int w, h;
    TTF_SizeText(font, textableWidget.GetText(), &w, &h);
    const Rectangle location = textableWidget.GetLocation();
    return Rectangle(location.X, location.Y, w, h); 
}
