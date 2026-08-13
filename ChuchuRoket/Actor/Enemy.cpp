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
	//1 . 트리거 설정
	// 현재 카운트 수가 적 윛 ㅣ 로직 수보다 크거나 같다면 --
	if (EnemyCount >= EnemyVector.size() - 1) isMinus = true;
		
	// 0 이면 isMinus = true;
	if (EnemyCount <= 0) isMinus = false;

	// 2. 트리거에 맞게 인덱스 변경
	if (isMinus) return EnemyCount--;
	
	return EnemyCount++;
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 타이머 설정
	timer.Tick(deltaTime);
	if (!timer.isTimeOut())
		return;
	// 몬스터 움직임 ㄱㄱ
	SetPosition(EnemyVector[setEnemyCount()]);
	
	timer.Reset();
	
}
