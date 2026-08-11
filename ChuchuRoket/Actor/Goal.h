#pragma once
#include <Actor/Actor.h>

class Goal : public Craft::Actor
{
	TYPE_DECLARATIONS(Goal, Actor)

public:
	Goal(const Craft::Vector2& position);
};

