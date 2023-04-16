#include "WidgetDisplayer.h"
#include "DisplayerService.h"
#include <iostream>

using namespace MTK;

extern SDL_Cursor* sdlCursor;
extern SDL_Cursor* sdlArrowCursor;
extern SDL_Cursor* sdlHandCursor;

WidgetDisplayer::WidgetDisplayer(const Widget &widget,
        SDL_Renderer *renderer) :
    m_Widget { widget },
    m_Renderer { renderer }
{
}

void WidgetDisplayer::Handle(const SDL_Event &event,
    const Position &mousePosition)
{
    const Rectangle &widgetLocation = m_Widget.GetLocation();
    if (DisplayerService::IsOverlapped(widgetLocation, mousePosition))
    {
        sdlCursor = sdlHandCursor;
    }
}

void WidgetDisplayer::Render()
{
    const RGBA bg = m_Widget.GetBackgroundColor();
    SDL_SetRenderDrawColor(m_Renderer, bg.R, bg.G, bg.B, bg.A);
    const Rectangle &location = m_Widget.GetLocation();
    SDL_Rect rect { location.X, location.Y, location.W, location.H };
    SDL_RenderFillRect(m_Renderer, &rect);
}
