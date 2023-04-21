#include "DynamicTextWidgetDisplayer.h"
#include "SDL_Related/SDL_ttf_Include.h"
#include <iostream>
#include <chrono>

using namespace MTK;

bool keyPressing = false;
DynamicTextWidgetDisplayer::DynamicTextWidgetDisplayer(
    CursorManager *cursorManager,
    const DynamicTextWidget &dynamicTextWidget,
    SDL_Renderer *renderer):
        WidgetDisplayer(cursorManager,
        dynamicTextWidget,
        renderer),
        m_DynamicTextWidget { dynamicTextWidget },
        m_Font { nullptr },
        m_TextPosition {0,0},
        m_BlinkingOn { false },
        m_CursorIndex { 0 },
        m_DisplayCursorIndex { 0 },
        m_DisplayStartIndex { 0 }
{
    m_Font = TTF_OpenFont(m_DynamicTextWidget.GetFont(), m_DynamicTextWidget.GetFontSize());
    m_CharWidth = GetCharTextWidth(m_DynamicTextWidget);
    m_TextHeight = GetTextHeight(m_DynamicTextWidget);
    m_PrevTime = GetTimeInMillisecond();
    m_DisplayTextSize = m_DynamicTextWidget.GetLocation().W / m_CharWidth;
    m_TextToDisplay = new char[(m_DisplayTextSize * 4) + 1];
    memset(m_TextToDisplay, 0, (m_DisplayTextSize * 4) + 1);
}

DynamicTextWidgetDisplayer::~DynamicTextWidgetDisplayer()
{
    TTF_CloseFont(m_Font);
}

void DynamicTextWidgetDisplayer::Handle(
    const SDL_Event &event,
    const Position &mousePosition)
{
    bool bStrngAvailable;
    WidgetDisplayer::Handle(event, mousePosition);
    if (m_bMouseHover)
    {
        m_CursorManager->SetCursor(CURSOR_IBEAM);
    }
    if (m_bClicked)
    {
        m_DisplayCursorIndex = (mousePosition.X - m_DynamicTextWidget.GetLocation().X) / m_CharWidth;
        if (m_DisplayCursorIndex > m_DynamicTextWidget.GetTextSize())
        {
            m_DisplayCursorIndex = m_DynamicTextWidget.GetTextSize();
        }
    }
    if (m_bFocused)
    {
        if (event.type == SDL_KEYDOWN)
        {
            if ( event.key.keysym.sym == SDLK_LEFT)
            {
                DecrementDisplayIndexes(m_DisplayCursorIndex, m_DisplayStartIndex);
            }
            else if ( event.key.keysym.sym == SDLK_RIGHT)
            {
                IncrementDisplayIndexes(m_DisplayCursorIndex, m_DisplayStartIndex);
            }
            keyPressing = true;
            if (event.key.keysym.sym == SDLK_BACKSPACE)
            {
                m_DynamicTextWidget.DeleteChar(m_DisplayCursorIndex + m_DisplayStartIndex);
                DecrementDisplayIndexes(m_DisplayCursorIndex, m_DisplayStartIndex);
            }
        }
        else
        {
            keyPressing = false;
        }
        if (event.type == SDL_TEXTINPUT)
        {
            m_DynamicTextWidget.AddString(event.text.text, m_DisplayCursorIndex + m_DisplayStartIndex);
            IncrementDisplayIndexes(m_DisplayCursorIndex, m_DisplayStartIndex);
            keyPressing = true;
        }
        const char* text = m_DynamicTextWidget.GetText();
        int startIndex = m_DynamicTextWidget.GetIndexFromUTF8Index(text, m_DisplayStartIndex);
        int32_t textSize = strlen(text);
        int32_t utf8Size = m_DynamicTextWidget.GetUTF8Size();
        memset(m_TextToDisplay, 0, (m_DisplayTextSize * 4) + 1);
        if (m_DisplayTextSize < utf8Size)
            textSize = m_DynamicTextWidget.GetIndexFromUTF8Index(text, m_DisplayTextSize);
        memcpy(m_TextToDisplay, &text[startIndex], textSize);
        int a = 3;
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

    SDL_Surface* textSurface = TTF_RenderUTF8_Shaded(m_Font, m_TextToDisplay, fg, bg);

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);

    SDL_Rect textLocation;
    textLocation.x = location.X;
    textLocation.y = location.Y;
    if (textSurface == nullptr)
    {
        textLocation.w = 0;
        textLocation.h = m_TextHeight;
    }
    else
    {
        textLocation.w = textSurface->w;
        textLocation.h = textSurface->h;
    }
    if (textLocation.w > location.W)
    {
        textLocation.w = location.W;
    }
    SDL_RenderCopy(m_Renderer, textTexture, nullptr, &textLocation);
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0xFF);
    uint64_t currentTime = GetTimeInMillisecond();
    bool bTimeValid = currentTime - m_PrevTime > 500;

    if (m_bFocused && keyPressing)
    {
        m_BlinkingOn = true;
        m_PrevTime = currentTime;
    }
    else if (m_bFocused && bTimeValid)
    {
        m_BlinkingOn = !m_BlinkingOn;
        m_PrevTime = currentTime;
    }
    if (m_BlinkingOn && m_bFocused)
    {
        int x = location.X + m_DisplayCursorIndex * m_CharWidth;
        int y = textLocation.y;
        SDL_RenderDrawLine(m_Renderer, x, y, x, y + textLocation.h);
    }
}

int DynamicTextWidgetDisplayer::GetTextHeight(const DynamicTextWidget &widget)
{
    TTF_Font* font = TTF_OpenFont(widget.GetFont(), widget.GetFontSize());
    int w, h;
    TTF_SizeText(font,"Test|", &w, &h);
    return h;
}

int DynamicTextWidgetDisplayer::GetCharTextWidth(const DynamicTextWidget &widget)
{
    int w, h;
    TTF_Font* font = TTF_OpenFont(widget.GetFont(), widget.GetFontSize());
    TTF_SizeText(font,"i", &w, &h);
    return w;
}

uint64_t DynamicTextWidgetDisplayer::GetTimeInMillisecond() const
{
    using namespace std;
    using namespace std::chrono;
    time_point<system_clock> now = system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return (uint64_t) millis;
}

void DynamicTextWidgetDisplayer::IncrementDisplayIndexes(
    int32_t &displayCursorIndex,
    int32_t &displayStartIndex)
{
    if (displayCursorIndex + displayStartIndex < m_DynamicTextWidget.GetUTF8Size())
    {
        if (displayCursorIndex < m_DisplayTextSize)
            displayCursorIndex++;
        else
            displayStartIndex++;
    }
}

void DynamicTextWidgetDisplayer::DecrementDisplayIndexes(
    int32_t &displayCursorIndex,
    int32_t &displayStartIndex)
{
    if (displayCursorIndex > 0 )
        displayCursorIndex--;
    else if (displayStartIndex > 0 )
            displayStartIndex--;
}
