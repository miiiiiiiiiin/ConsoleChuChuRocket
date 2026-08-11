#include "Ground.h"

using namespace Craft;
Ground::Ground(const Vector2& position)
	: Actor(L" ", position) // super:상위계층가리킴
{
	//우선순위 설정
	//바닥 액터는 다른 액터랑 겹쳤을때 덮어쓰기되어야함
	sortingOrder = 0;

}
