#pragma once

#include <Actor/Actor.h>


//소코반 게임에서 wall 담당 액터클래스
class Wall : public Craft::Actor
{
	TYPE_DECLARATIONS(Wall, Actor)

public:
	Wall(const Craft::Vector2& position);

};

