#include "DynamicTextWidgetDisplayer.h"
#include "SDL_Related/SDL_ttf_Include.h"

using namespace MTK;

DynamicTextWidgetDisplayer::DynamicTextWidgetDisplayer(
    CursorManager *cursorManager,
    const DynamicTextWidget &dynamicTextWidget,
    SDL_Renderer *renderer):
        WidgetDisplayer(cursorManager,
        dynamicTextWidget,
        renderer),
        m_DynamicTextWidget { dynamicTextWidget },
        m_Font { nullptr },
        m_TextPosition {0,0}
{
    m_Font = TTF_OpenFont(m_DynamicTextWidget.GetFont(), m_DynamicTextWidget.GetFontSize());
}

DynamicTextWidgetDisplayer::~DynamicTextWidgetDisplayer()
{
    TTF_CloseFont(m_Font);
}

void DynamicTextWidgetDisplayer::Handle(
    const SDL_Event &event,
    const Position &mousePosition)
{
    WidgetDisplayer::Handle(event, mousePosition);
    if (bMouseHover)
    {
        m_CursorManager->SetCursor(CURSOR_IBEAM);
    }
    if (m_bFocused && event.type == SDL_TEXTINPUT)
    {
        m_DynamicTextWidget.AddString(event.text.text);
    }
}

void DynamicTextWidgetDisplayer::Render()
{
    const RGBA bgColor = m_DynamicTextWidget.GetBackgroundColor();
    SDL_Color bg = {bgColor.R, bgColor.G, bgColor.B, bgColor.A};

    RGBA fgColor = m_DynamicTextWidget.GetForegroundColor();
    SDL_Color fg = {fgColor.R, fgColor.G, fgColor.B, fgColor.A};

    SDL_SetRenderDrawColor(m_Renderer, bg.r, bg.g, bg.b, bg.a);
    const Rectangle &location = m_Widget.GetLocation();
    SDL_Rect rect { location.X, location.Y, location.W, location.H };
    SDL_RenderFillRect(m_Renderer, &rect);


    SDL_Surface* textSurface = TTF_RenderUTF8_Shaded_Wrapped(m_Font, m_DynamicTextWidget.GetText(), fg, bg, location.W);

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);

    SDL_Rect textLocation;
    textLocation.x = location.X;
    textLocation.y = location.Y;
    if (textSurface == nullptr)
    {
        textLocation.w = 0;
        textLocation.h = 0;
    }
    else
    {
        textLocation.w = textSurface->w;
        textLocation.h = textSurface->h;
    }
    
    SDL_RenderCopy(m_Renderer, textTexture, nullptr, &textLocation);
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0xFF);
    if (textLocation.w != 0 && textLocation.h != 0)
    {
        int x = textLocation.w + textLocation.x;
        int y = textLocation.h + textLocation.y;
        SDL_RenderDrawLine(m_Renderer, x, y - m_DynamicTextWidget.GetFontSize() , x, y);
    }
}
