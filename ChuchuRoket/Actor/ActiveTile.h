#pragma once
#include <Actor/Actor.h>
#include "TileDir.h"

class ActiveTile : public Craft::Actor
{
	TYPE_DECLARATIONS(ActiveTile, Actor)

public:
	ActiveTile(const std::wstring& image, const Craft::Vector2& position, TileDir dir);
	inline TileDir GetDir() const { return tileDir; }
private:
	// 타일의 방향 정보 저장
	TileDir tileDir;
};

