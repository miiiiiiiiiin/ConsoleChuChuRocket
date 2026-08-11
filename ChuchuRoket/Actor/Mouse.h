#pragma once
#include<Actor/Actor.h>
class Mouse : public Craft::Actor
{
	TYPE_DECLARATIONS(Mouse, Actor)

	//현재 쥐가 바라보는 방향
	enum MouseDir
	{
		Left,
		Right,
		Up,
		Down
	};

public:
	Mouse(const Craft::Vector2& position);

private:
	// 플래그 뜨면 쥐 이동
	// 기호 방향에 맞춰서 직진 이동 함수
	// Dir: 
	virtual void Tick(float deltaTime) override;

	//쥐가 바라보고 있는 방향 설정. 
	//벽 부딪히면 90회전
	void MousePrsp();

	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;

private:
	//현재 위치
	Craft::Vector2 position;
	MouseDir direction = MouseDir::Left;

	



};

