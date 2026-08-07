#include "Box.h"
using namespace Craft;

Box::Box(const Craft::Vector2& position)
	: Actor("B", position,Color::RED)
{
	// 박스는 이동이 가능하기 때문에 땅과 겹칠 수 있음
	//땅보다 높은 우선순위로 설정.
	//박스는 타겟(목표 지점) 위에 배치될 수 있어야 함 
	//따라서 타겟보다 높은 우선순위로 설정
	sortingOrder = 5;

}
