#include "ActiveTile.h"
using namespace Craft;

ActiveTile::ActiveTile(const std::wstring& image, const Craft::Vector2& position, TileDir dir)
	: Actor(image, position, Color::CYAN), tileDir(dir)
{

}
