#ifndef _MTK_SDL_STRUCTS_H_
#define _MTK_SDL_STRUCTS_H_
#include "SDL_Include.h"
#include "Button.h"
namespace MTK
{
    struct TextureWithLocation
    {
        SDL_Texture *Texture;
        SDL_Rect Location;
    };

    struct SDLButton
    {
        SDL_Texture *Texture;
        SDL_Texture *HoverTexture;
        SDL_Texture *ClickedTexture;
        SDL_Rect Location;
        Button *button;
        bool downState;
    };
} // namespace MTK

#endif // _MTK_SDL_STRUCTS_H_