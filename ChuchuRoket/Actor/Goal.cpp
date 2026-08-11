#include "Goal.h"
using namespace Craft;
Goal::Goal(const Vector2& position)
	: Actor(L"▣", position, Color::MAGENTA)
{
	sortingOrder = 0;
}
