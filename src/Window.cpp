#include "Window.h"
#include <cstring>
#include <iostream>

using namespace MTK;

MTK::Window::Window(WindowID windowID,
    const char *title, RGBA background,
    Size size):
    m_WindowID { windowID },
    m_BackgroundColor { background },
    m_Size { size }
{
    SetTitle(title);
}

Window::Window(const Window &other)
{
    this->Copy(other);
}

void Window::Copy(const Window &other)
{
    this->m_WindowID = other.m_WindowID;
    this->SetBackgroundColor(other.GetBackgroundColor());
    this->SetTitle(other.GetTitle());
    this->SetSize(other.GetSize());
}

void Window::SetTitle(const char *title)
{
    memset(m_Title, 0, sizeof(m_Title));
    size_t titleLength = strlen(title);
    if (titleLength > MAX_TITLE_SIZE - 1)
    {
        titleLength = MAX_TITLE_SIZE - 1;
        std::cout << "WARNING: Title: " << title << 
            " length is too long, it will be truncated!" << std::endl;
    }
    memcpy(m_Title, title, titleLength);
}
