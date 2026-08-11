#pragma once
#include <Actor/Actor.h>
#include <Actor/ArrowTile.h>
class ActiveTile : public Craft::Actor
{
	TYPE_DECLARATIONS(ActiveTile, Actor)
public:
	ActiveTile(const std::wstring& image, const Craft::Vector2& position, ArrowTile::TileDir dir);

private:
	ArrowTile::TileDir tileDir;
};

