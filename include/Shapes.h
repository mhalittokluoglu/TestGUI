#ifndef _MTK_SHAPES_H_
#define _MTK_SHAPES_H_
#include <inttypes.h>
namespace MTK
{
    struct Rectangle
    {
        int32_t X;
        int32_t Y;
        int32_t W;
        int32_t H;
        Rectangle(int32_t x = 0,
            int32_t y = 0,
            int32_t w = 0,
            int32_t h = 0) : 
            X { x }, Y { y },
            W { w }, H { h } { }
        ~Rectangle() { }
    };

    struct Position
    {
        int32_t X;
        int32_t Y;
        Position(int32_t x = 0,
            int32_t y = 0) : 
            X { x }, Y { y } { }
        ~Position() { }
    };

    struct Size
    {
        int32_t W;
        int32_t H;
        Size(int32_t w = 0,
            int32_t h = 0) :
            W { w }, H { h } { }
        ~Size() { }
    };

    struct RGBA
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;
        RGBA(uint8_t r = 0,
            uint8_t g = 0,
            uint8_t b = 0,
            uint8_t a = 0xFF) : 
            R { r }, G { g },
            B { b }, A { a } { }
        ~RGBA() { }
    };
    
} // namespace MTK

#endif // _MTK_SHAPES_H_