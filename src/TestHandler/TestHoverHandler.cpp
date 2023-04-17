#include "TestHoverHandler.h"
#include <iostream>

using namespace MTK;

void TestHoverHandler::OnHover()
{
    static int counter = 0;
    if (counter == 100)
    {
        std::cout << "Hover!\n";
        counter = 0;
    }
    counter++;
}
