#include "Enemy.h"
using namespace Craft;
Enemy::Enemy(const std::vector<Craft::Vector2>& EnemyList)
	: Actor(L"⯫", EnemyList[0], Color::RED),
	timer(0.3f),
	EnemyVector(EnemyList)
{
	
}
int Enemy::setEnemyCount()
{
	// 현재 카운트 수가 적 윛 ㅣ 로직 수보다 크거나 같다면 --
	if (EnemyCount >= EnemyVector.size() - 1) isMinus = true;
		
	// 0 이면 isMinus = true;
	if (EnemyCount <= 0) isMinus = false;

	if (isMinus) {
		return EnemyCount--;
	}
	return EnemyCount++;
}
void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	timer.Tick(deltaTime);
	if (!timer.isTimeOut())
		return;
	// EnemyList돌면서 이동 처리
	// 현재 위치 += 이동 속도* 현재시간* 다음 이동 위치
	// 다음 이동 위치: EnemyList[]
	
	SetPosition(EnemyVector[setEnemyCount()]);
	


	timer.Reset();
	
}
