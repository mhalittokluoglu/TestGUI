#ifndef _MTK_LABEL_H_
#define _MTK_LABEL_H_
#include "TextableWidget.h"
namespace MTK
{
    class Label : public TextableWidget
    {
    public:
        Label(Rectangle location,
            const char *text = "Label",
            const char *font = "Fira Code",
            RGBA bgColor = RGBA(0xFF, 0xFF, 0xFF, 0x00),
            RGBA fgColor = RGBA(0x00, 0x00, 0x00, 0xFF),
            uint8_t fontSize = 12):
                TextableWidget(location, bgColor,
                fgColor, text, font, fontSize) { }
        virtual ~Label() { }
    };
} // namespace MTK

#endif // _MTK_LABEL_H_