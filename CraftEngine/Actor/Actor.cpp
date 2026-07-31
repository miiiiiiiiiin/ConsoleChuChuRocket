#include "Actor/Actor.h"
#include <Engine/Engine.h>
namespace Craft
{
	Craft::Actor::~Actor()
	{
	}

	void Craft::Actor::BeginPlay()
	{
		//이벤트 처리했다고 설정
		hasBeganPlay = true;

	}

	void Craft::Actor::Tick(float deltaTime)
	{
	}

	void Craft::Actor::Draw()
	{
	}

	void Craft::Actor::Destroy()
	{
		//삭제 예약 설정
		hasExpired = true;
	}

	void Craft::Actor::QuitGame()
	{
		//엔진 종료 요청
		Engine::Get().Quit();

	}

}
