#include "PlayerBullet.h"
using namespace Craft;

PlayerBullet::PlayerBullet(const Craft::Vector2& position)
	: Actor("@", position, Color::BLUE), 
	yPosition(static_cast<float>(position.y))
{
	
}

void PlayerBullet::Tick(float deltaTime)
{
	//상위 틱 로직 호출
	super::Tick(deltaTime);

	// 아래 -> 위 이동 처리
	yPosition -= moveSpeed * deltaTime;
	// 좌표 검사(화면 이탈 검사)
	if (yPosition < 0.0f)
	{
		// 삭제 
		Destroy();
		return;
	}

	// 위치 값 설정 및 갱신
	Vector2 newPosition = GetPosition();
	newPosition.y = static_cast<int>(yPosition);
	SetPosition(newPosition);


}
