#pragma once
#include <Actor/Actor.h>
class Ground : public Craft::Actor
{
	TYPE_DECLARATIONS(Ground, Actor)
public:
	Ground(Craft::Vector2& position);
};

