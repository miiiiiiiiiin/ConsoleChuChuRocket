#include "Player.h"
#include <Input/Input.h>

using namespace Craft;
Player::Player(const Vector2& position)
	: Actor("P", position, Color::GREEN)
{
	// 우선순위 설정
	// 액터 중 가장 높은 값
	sortingOrder = 10;

}

void Player::Tick(float deltaTime)
{
	// 상위 계층의 tick 호출
	super::Tick(deltaTime);

	//esc 종료 처리
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 게임 종료
		QuitGame();
		return;
	}

	// 이동 처리
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		// 이동하려는 위치 값 만들기
		Vector2 newPosition = GetPosition();
		newPosition.x += 1;

		// 새로운 위치 설정
		SetPosition(newPosition);
	}
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		// 이동하려는 위치 값 만들기
		Vector2 newPosition = GetPosition();
		newPosition.x -= 1;

		// 새로운 위치 설정
		SetPosition(newPosition);
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		// 이동하려는 위치 값 만들기
		Vector2 newPosition = GetPosition();
		newPosition.y -= 1;

		// 새로운 위치 설정
		SetPosition(newPosition);
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		// 이동하려는 위치 값 만들기
		Vector2 newPosition = GetPosition();
		newPosition.y += 1;

		// 새로운 위치 설정
		SetPosition(newPosition);
	}
}
