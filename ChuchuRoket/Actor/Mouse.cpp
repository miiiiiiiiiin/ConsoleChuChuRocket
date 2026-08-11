#include "Mouse.h"
#include <Actor/Wall.h>

using namespace Craft;
Mouse::Mouse(const Craft::Vector2& position)
	: Actor(L"⯈", position, Color::BRIGHTWHITE)
{
	sortingOrder = 5;
}

void Mouse::OnCollision(const std::shared_ptr<Actor>& other)
{
	// 벽 부딪히면 시계방향 90 회전
	if (other->IsTypeOf<Wall>())
	{
		switch (direction)
		{
		case Right:
			direction = Down;
			break;
		case Left:
			direction = Up;
			break;
		case Up:
			direction = Right;
			break;
		case Down:
			direction = Left;
			break;
		}
	}
}

void Mouse::Tick(float deltaTime)
{

}

