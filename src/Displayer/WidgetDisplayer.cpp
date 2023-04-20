#include "WidgetDisplayer.h"
#include "DisplayerService.h"
#include <iostream>

using namespace MTK;


WidgetDisplayer::WidgetDisplayer(CursorManager* cursorManager, const Widget &widget,
        SDL_Renderer *renderer) :
    m_CursorManager { cursorManager },
    m_Widget { widget },
    m_Renderer { renderer },
    m_bMousePressedState { false },
    m_bMouseHover { false },
    m_bClicked { false },
    m_bFocused { false }
{
}

void WidgetDisplayer::Handle(const SDL_Event &event,
    const Position &mousePosition)
{
    const Rectangle &widgetLocation = m_Widget.GetLocation();
    m_bMouseHover = false;
    m_bClicked = false;
    if (DisplayerService::IsOverlapped(widgetLocation, mousePosition))
    {
        m_bMouseHover = true;
        if (m_ClickHandler != nullptr)
        {
            m_CursorManager->SetCursor(CURSOR_HAND);
        }

        if (m_HoverHandler != nullptr)
        {
            m_HoverHandler->OnHover();
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            m_bMousePressedState = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (m_bMousePressedState)
            {
                m_bClicked = true;
                if (m_ClickHandler != nullptr)
                {
                    m_ClickHandler->OnClicked();
                }
                m_bFocused = true;
            }
        }
    }
    else
    {
        if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
        {
                m_bFocused = false;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        m_bMousePressedState = false;
    }
}

void WidgetDisplayer::Render()
{
    const RGBA bg = m_Widget.GetBackgroundColor();
    SDL_SetRenderDrawColor(m_Renderer, bg.R, bg.G, bg.B, bg.A);
    const Rectangle &location = m_Widget.GetLocation();
    SDL_Rect rect { location.X, location.Y, location.W, location.H };
    SDL_RenderFillRect(m_Renderer, &rect);
    if (m_bMousePressedState && m_ClickHandler != nullptr && m_ClickHandler->GetClickEffectAvailable())
    {
        SDL_Rect rectBorder { location.X, location.Y, location.W, location.H };
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0xFF);
        SDL_RenderDrawRect(m_Renderer, &rectBorder);
    }
    else if (m_bMouseHover && m_HoverHandler != nullptr && m_HoverHandler->GetHoverEffectAvailable())
    {
        SDL_Rect rectBorder { location.X, location.Y, location.W, location.H };
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawRect(m_Renderer, &rectBorder);
    }
}
