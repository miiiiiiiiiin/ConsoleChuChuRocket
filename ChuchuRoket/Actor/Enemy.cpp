#include "Enemy.h"
using namespace Craft;
Enemy::Enemy(const Vector2& position)
	: Actor(L"⯍", position, Color::GREEN),
	timer(0.3f)
{
}
void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 타이머 설정
	timer.Tick(deltaTime);
	if (!timer.isTimeOut())
		return;

	// 몬스터 움직임 ㄱㄱ
	image = isReturn ? L"⯌" : L"⯍";
	timer.Reset();
	isReturn = !isReturn; // isReturn 상태 반전시키기
	
}
