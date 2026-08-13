#include "Ground.h"
using namespace Craft;

Ground::Ground(Craft::Vector2& position)
	: Actor(L"⬚", position, Color::WHITE)
{
	sortingOrder = 0;
}
