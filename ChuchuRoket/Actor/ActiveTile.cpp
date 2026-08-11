#include "ActiveTile.h"
using namespace Craft;

ActiveTile::ActiveTile(const Craft::Vector2& position, ArrowTile::TileDir dir)
	: Actor(L"@", position, Color::BLUE)
{
}
