#include "ToolKit.h"
#include "SDL_Related/SDL_Include.h"
#include "SDL_Related/SDL_ttf_Include.h"
#include "SDL_Related/SDL_Structs.h"
#include "Displayer/WidgetDisplayer.h"
#include "Displayer/TextableWidgetDisplayer.h"
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
std::unordered_map<WindowID, std::list<IDisplayer*>*> DisplayerMap;
std::unordered_map<WidgetID, IDisplayer*> WidgetDisplayerMap;


static bool IsWidgetValidToCreate(WindowID windowID, WidgetID widgetID)
{
    if ( SDLRendererMap.find(windowID) == SDLRendererMap.end())
    {
        return false;
    }
    if (WidgetDisplayerMap.find(widgetID) != WidgetDisplayerMap.end())
    {
        std::cout << "Widget with ID: " << widgetID << " already exist!\n";
        return false;
    }
    return true;
}


static void AddToWidgetDisplayerList(WindowID windowID, WidgetID widgetID, IDisplayer *displayer)
{
    std::list<IDisplayer *> *displayerList;
    if (DisplayerMap.find(windowID) == DisplayerMap.end())
    {
        displayerList = new std::list<IDisplayer*>;
        DisplayerMap[windowID] = displayerList;
    }
    displayerList = DisplayerMap[windowID];
    displayerList->push_back(displayer);
    WidgetDisplayerMap[widgetID] = displayer;
}

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
    SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);

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
    if (!CreateTextableWidget(windowID, button))
    {
        return false;
    }
    if (!RegisterClickEventHandler(button.GetWidgetID(), button.GetClickHandler()))
    {
        return false;
    }
    return true;
}

bool MTK::ToolKit::CreateLabel(WindowID windowID, Label &label)
{
    bool bResult = false;
    if (CreateTextableWidget(windowID, label))
    {
        bResult = true;;
    }
    return bResult;
}

bool ToolKit::CreateWidget(WindowID windowID, Widget &widget)
{
    const WidgetID widgetID = widget.GetWidgetID();
    if (!IsWidgetValidToCreate(windowID, widgetID))
    {
        return false;
    }
    widget.SetWindowID(windowID);
    SDL_Renderer *sdlRenderer = SDLRendererMap.at(windowID); 
    WidgetDisplayer *displayer = new WidgetDisplayer(m_CursorManager, widget, sdlRenderer);
    AddToWidgetDisplayerList(windowID, widgetID, displayer);
    return true;
}

bool ToolKit::CreateTextableWidget(WindowID windowID, TextableWidget &textableWidget)
{
    const WidgetID widgetID = textableWidget.GetWidgetID();
    if (!IsWidgetValidToCreate(windowID, widgetID))
    {
        return false;
    }
    textableWidget.SetWindowID(windowID);
    SDL_Renderer *sdlRenderer = SDLRendererMap.at(windowID); 
    textableWidget.SetLocation(TextableWidgetDisplayer::GetTextSize(textableWidget));
    TextableWidgetDisplayer *displayer = new TextableWidgetDisplayer(m_CursorManager, textableWidget, sdlRenderer);
    AddToWidgetDisplayerList(windowID, widgetID, displayer);
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
            m_CursorManager->SetCursor(SDL_SYSTEM_CURSOR_ARROW);
            WindowID windowID = event.window.windowID;

            if (DisplayerMap.find(windowID)!= DisplayerMap.end())
            {
                std::list<IDisplayer*>* displayerList = DisplayerMap.at(windowID);
                std::for_each(displayerList->begin(), displayerList->end(), [&](IDisplayer* displayer)
                {
                    displayer->Handle(event, mousePosition);
                });
            }
            SDL_Cursor* sdlCursor = m_CursorManager->GetCursor();
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

