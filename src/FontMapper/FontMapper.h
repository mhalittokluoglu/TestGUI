#ifndef _MTK_FONTMAPPER_H_
#define _MTK_FONTMAPPER_H_
#include <inttypes.h>
namespace MTK
{
    class FontMapper
    {
    public:
        static FontMapper* Instance();
        static bool GetFontWithPath(const char *font, char *fontWithFullPath);

    private:
        static FontMapper *m_Instance;
        FontMapper();
    };
} // namespace MTK

#endif // _MTK_FONTMAPPER_H_