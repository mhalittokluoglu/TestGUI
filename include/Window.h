#ifndef _MTK_WINDOW_H_
#define _MTK_WINDOW_H_
#include "Shapes.h"
#include "Constants.h"
#include "Types.h"
namespace MTK
{
    class Window
    {
    public:
        Window(WindowID windowID = 0,
            const char *title = "MTK",
            RGBA background = RGBA(0xFF, 0xFF, 0xFF, 0xFF),
            Size size = Size(640, 480));
        virtual ~Window() { }
        Window(const Window &other);
        void Copy(const Window &other);
        

        // Setters
        inline void SetWindowID(WindowID windowID) { m_WindowID = windowID; }
        void SetTitle(const char *title);
        inline void SetBackgroundColor(RGBA background) { m_BackgroundColor = background; }
        inline void SetSize(Size size) { m_Size = size; }

        // Getters
        inline WindowID GetWindowID() const { return m_WindowID; }
        inline const char* GetTitle() const { return m_Title; }
        inline RGBA GetBackgroundColor() const { return m_BackgroundColor; }
        inline Size GetSize() const {return m_Size; }

    private:
        RGBA m_BackgroundColor;
        char m_Title[MAX_TITLE_SIZE];
        WindowID m_WindowID;
        Size m_Size;
    };
} // namespace MTK

#endif // _MTK_WINDOW_H_