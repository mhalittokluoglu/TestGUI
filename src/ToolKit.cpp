#include "ToolKit.h"
#include "SDL_Related/SDL_Include.h"
#include "SDL_Related/SDL_ttf_Include.h"
#include "SDL_Related/SDL_Structs.h"
#include "Displayer/WidgetDisplayer.h"
#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace MTK;

std::list<Window*> WindowList;
std::unordered_map<WindowID, Window*> WindowMap;

std::list<SDL_Window*> SDLWindowList;
std::list<SDL_Renderer*> SDLRendererList;

std::unordered_map<WindowID, SDL_Renderer*> SDLRendererMap;
std::unordered_map<WindowID, SDL_Window*> SDLWindowMap;
std::unordered_map<WindowID, std::list<TextureWithLocation>*> TextureWindowMap;
std::unordered_map<WindowID, std::list<SDLButton>*> SDLButtonWindowMap;
std::unordered_map<WindowID, std::list<IDisplayer*>*> DisplayerMap;
std::unordered_map<WidgetID, IDisplayer*> WidgetDisplayerMap;


ToolKit::ToolKit()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
    }
    if (TTF_Init() == -1)
    {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
        SDL_Quit();
    }
    m_CursorManager = new CursorManager();
}

ToolKit::~ToolKit()
{
}

bool ToolKit::CreateWindow(Window &window)
{
    const char *windowTitle = window.GetTitle();
    Size windowSize = window.GetSize();
    SDL_Window* sdlWindow = SDL_CreateWindow(windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowSize.W, windowSize.H,
        SDL_WINDOW_RESIZABLE);
    if (sdlWindow == nullptr)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }
    WindowID windowID = SDL_GetWindowID(sdlWindow);
    window.SetWindowID(windowID);
    

    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (sdlRenderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(sdlWindow);
        return false;
    }

    RGBA bg = window.GetBackgroundColor();
    SDL_SetRenderDrawColor(sdlRenderer, bg.R, bg.G, bg.B, bg.A);

    Window *windowInCache = new Window();
    windowInCache->Copy(window);

    WindowList.push_back(windowInCache);
    WindowMap[windowID] = windowInCache;

    SDLWindowList.push_back(sdlWindow);
    SDLRendererList.push_back(sdlRenderer);

    SDLWindowMap[windowID] = sdlWindow;
    SDLRendererMap[windowID] = sdlRenderer;

    return true;
}

bool MTK::ToolKit::CreateButton(WindowID windowID, Button &button)
{
    if (SDLRendererMap.find(windowID) == SDLRendererMap.end())
    {
        std::cout << "Unable to find Window with ID: " << windowID << std::endl;
        return false;
    }
    SDL_Renderer *sdlRenderer = SDLRendererMap.at(windowID);
    Rectangle buttonLocation = button.GetLocation();
    SDL_Rect sdlButtonLocation = {buttonLocation.X,
        buttonLocation.Y,
        buttonLocation.W,
        buttonLocation.H};


    RGBA bgColor = button.GetBackgroundColor();
    SDL_Color bg = {bgColor.R, bgColor.G, bgColor.B, bgColor.A};


    RGBA fgColor = button.GetForegroundColor();
    SDL_Color fg = {fgColor.R, fgColor.G, fgColor.B, fgColor.A};

    TTF_Font* font = TTF_OpenFont(button.GetFont(), button.GetFontSize());
    SDL_Surface* textSurface = TTF_RenderText_Shaded(font, button.GetText(), fg, bg);
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(sdlRenderer, textSurface);

    SDL_Rect textLocation;
    textLocation.x = sdlButtonLocation.x + sdlButtonLocation.w / 2;
    textLocation.y = sdlButtonLocation.y + sdlButtonLocation.h / 2 - textSurface->h / 2;
    textLocation.w = textSurface->w;
    textLocation.h = textSurface->h;

    SDL_RenderCopy(sdlRenderer, buttonTexture, nullptr, &textLocation);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDLButton sdlButton;
    sdlButton.button = &button;
    sdlButton.Texture = buttonTexture;
    sdlButton.Location = textLocation;
    sdlButton.downState = false;

    std::list<SDLButton> *buttonList;
    if (SDLButtonWindowMap.find(windowID) == SDLButtonWindowMap.end())
    {
        buttonList = new std::list<SDLButton>;
        SDLButtonWindowMap[windowID] = buttonList;
    }
    else
    {
        buttonList = SDLButtonWindowMap.at(windowID);
    }
    buttonList->push_back(sdlButton);
    
    return true;
}

bool ToolKit::CreateWidget(WindowID windowID, Widget &widget)
{
    if ( SDLRendererMap.find(windowID) == SDLRendererMap.end())
    {
        return false;
    }
    if (WidgetDisplayerMap.find(widget.GetWidgetID()) != WidgetDisplayerMap.end())
    {
        std::cout << "Widget with ID: " << widget.GetWidgetID() << " already exist!\n";
        return false;
    }
    SDL_Renderer *sdlRenderer = SDLRendererMap.at(windowID); 
    WidgetDisplayer *displayer = new WidgetDisplayer(m_CursorManager, widget, sdlRenderer);

    std::list<IDisplayer *> *displayerList;
    if (DisplayerMap.find(windowID) == DisplayerMap.end())
    {
        displayerList = new std::list<IDisplayer*>;
        DisplayerMap[windowID] = displayerList;
    }
    displayerList = DisplayerMap[windowID];
    displayerList->push_back(displayer);
    WidgetDisplayerMap[widget.GetWidgetID()] = displayer;
    
    return true;
}

bool ToolKit::RegisterClickEventHandler(WidgetID widgetID, IClickHandler *handler)
{
    bool bResult = false;
    if (WidgetDisplayerMap.find(widgetID) != WidgetDisplayerMap.end())
    {
        IDisplayer *displayer = WidgetDisplayerMap.at(widgetID);
        displayer->RegisterClickHandler(handler);
        bResult = true;
    }
    return bResult;
}

bool ToolKit::RegisterHoverEventHandler(WidgetID widgetID, IHoverHandler *handler)
{
    bool bResult = false;
    if (WidgetDisplayerMap.find(widgetID) != WidgetDisplayerMap.end())
    {
        IDisplayer *displayer = WidgetDisplayerMap.at(widgetID);
        displayer->RegisterHoverHandler(handler);
        bResult = true;
    }
    return bResult;
}

void ToolKit::MainLoop()
{
    SDL_Event event;
    bool bIsRunning = true;
    while (bIsRunning)
    {
        while (SDL_WaitEventTimeout(&event, 50))
        {
            if (event.type == SDL_QUIT)
            {
                bIsRunning = false;
            }

            Position mousePosition;
            SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);
            WindowID windowID = event.window.windowID;
            if (SDLButtonWindowMap.find(windowID) != SDLButtonWindowMap.end())
            {
                std::list<SDLButton>* sdlButtonList = SDLButtonWindowMap.at(windowID);
                m_CursorManager->SetCursor(CURSOR_ARROW);
                std::for_each(sdlButtonList->begin(), sdlButtonList->end(), [&](SDLButton &sdlButton){
                    if (sdlButton.Location.x < mousePosition.X &&
                        sdlButton.Location.y < mousePosition.Y &&
                        sdlButton.Location.x + sdlButton.Location.w > mousePosition.X &&
                        sdlButton.Location.y + sdlButton.Location.h > mousePosition.Y)
                        {
                            m_CursorManager->SetCursor(CURSOR_HAND);
                            if (event.type == SDL_MOUSEBUTTONUP)
                            {
                                if (sdlButton.downState)
                                    sdlButton.button->OnClicked();
                                sdlButton.downState = false;
                            }
                            if (event.type == SDL_MOUSEBUTTONDOWN)
                            {
                                sdlButton.downState = true;
                            }
                        }
                });
            }

            if (DisplayerMap.find(windowID)!= DisplayerMap.end())
            {
                std::list<IDisplayer*>* displayerList = DisplayerMap.at(windowID);
                std::for_each(displayerList->begin(), displayerList->end(), [&](IDisplayer* displayer)
                {
                    displayer->Handle(event, mousePosition);
                });
            }
            SDL_Cursor* sdlCursor = static_cast<SDL_Cursor*>(m_CursorManager->GetCursor());
            SDL_SetCursor(sdlCursor);
        }

        std::for_each(WindowList.begin(), WindowList.end(), [&](Window* window)
        {
            WindowID windowID = window->GetWindowID();
            RGBA bg = window->GetBackgroundColor();
            SDL_Renderer *sdlRenderer = SDLRendererMap.at(windowID);
            SDL_SetRenderDrawColor(sdlRenderer, bg.R, bg.G, bg.B, bg.A);
            SDL_RenderClear(sdlRenderer);

            Position mousePosition;
            SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);
            

            if (TextureWindowMap.find(windowID) != TextureWindowMap.end())
            {
                std::list<TextureWithLocation>* textureList = TextureWindowMap.at(windowID);
                std::for_each(textureList->begin(), textureList->end(), [&](TextureWithLocation &textureLocation){
                    SDL_RenderCopy(sdlRenderer, textureLocation.Texture, nullptr, &textureLocation.Location);
                });
            }
            if (SDLButtonWindowMap.find(windowID) != SDLButtonWindowMap.end())
            {
                std::list<SDLButton>* sdlButtonList = SDLButtonWindowMap.at(windowID);
                std::for_each(sdlButtonList->begin(), sdlButtonList->end(), [&](SDLButton &sdlButton){
                    SDL_RenderCopy(sdlRenderer, sdlButton.Texture, nullptr, &sdlButton.Location);
                });
            }

            if (DisplayerMap.find(windowID)!= DisplayerMap.end())
            {
                std::list<IDisplayer*>* displayerList = DisplayerMap.at(windowID);
                std::for_each(displayerList->begin(), displayerList->end(), [&](IDisplayer* displayer)
                {
                    displayer->Render();
                });
            }

            SDL_RenderPresent(sdlRenderer);
        });

    }
}

void ToolKit::Update(const Window &window)
{
    WindowID windowID = window.GetWindowID(); 

    Window *windowInCache = WindowMap.at(windowID);
    windowInCache->Copy(window);

    SDL_Window *sdlWindow = SDLWindowMap.at(windowID);
    SDL_SetWindowTitle(sdlWindow, windowInCache->GetTitle());
    Size windowSize = windowInCache->GetSize();
    SDL_SetWindowSize(sdlWindow, windowSize.W, windowSize.H);

    SDL_Renderer *sdlRenderer = SDLRendererMap.at(windowID);
    RGBA bg = windowInCache->GetBackgroundColor();
    SDL_SetRenderDrawColor(sdlRenderer, bg.R, bg.G, bg.B, bg.A);
}

