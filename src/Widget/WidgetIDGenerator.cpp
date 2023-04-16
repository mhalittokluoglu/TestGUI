#include "WidgetIDGenerator.h"

using namespace MTK;

WidgetID currentID = 0;

WidgetID WidgetIDGenerator::GetNextWidgetID()
{
    currentID++;
    return currentID;
}
