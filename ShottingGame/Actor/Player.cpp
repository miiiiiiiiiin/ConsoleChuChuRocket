#include "Player.h"
#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Level/Level.h>
#include <Actor/PlayerBullet.h>
#include <Actor/EnemyBullet.h>
#include <Actor/DestroyEffect.h>

using namespace Craft;
Player::Player()
	: Actor(L"<=A=>", Vector2::Zero, Color::GREEN)
	, firemode(FireMode::OneShot)
{
	//  생성 위치 설정
	int x = (Engine::Get().GetWidth() / 2) - (width / 2);
	int y = (Engine::Get().GetHeight() - 2);
	SetPosition(Vector2(x, y));

	// x위치 저장
	xPosition = static_cast<float>(x);

	// 연사 타이머 시간 설정
	timer.SetTargetTime(fireInterval);
}

	// 이벤트 함수 오버라이드
void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//esc 키 종료 처리
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}

	// 방향키 입력에 따른 이동 방향 설정
	// 오른쪽: 1 왼쪽: -1
	float direction = 0.0f;
	if (Input::Get().GetKey(VK_RIGHT))
	{
		direction = 1.0f;
	}
	if (Input::Get().GetKey(VK_LEFT))
	{
		direction = -1.0f;
	}

	// 이동 함수 호출
	Move(direction, deltaTime);

	// 발사 타이머 업데이트
	timer.Tick(deltaTime);

	if (firemode == FireMode::OneShot)
	{
		// 탄약 발사 처리
		if (Input::Get().GetKeyDown(VK_SPACE))
		{
			Fire();
		}
	}
	else if (firemode == FireMode::Repeat)
	{
		if (Input::Get().GetKey(VK_SPACE))
		{
			// 연사 발사 함수 호출
			FireInterval();
		}
	}
	// 발사 모드 전환 처리
	if (Input::Get().GetKeyDown('R'))
	{
		if (firemode == FireMode::OneShot)
		{
			firemode = FireMode::Repeat;
		}
		else if (firemode == FireMode::Repeat)
		{
			firemode = FireMode::OneShot;
		}
	}

}

void Player::OnCollision(const std::shared_ptr<Actor>& other)
{
	super::OnCollision(other);

	// 부딪힌 액터가 적 탄약이면 처리
	if (other->IsTypeOf<EnemyBullet>())
	{
		// 플레이어 제거
		Destroy();

		// 적 탄약 제거
		other->Destroy();

		// 파괴 이펙트 생성
		if (GetOwner())
		{
			GetOwner()->SpawnActor<DestroyEffect>(GetPosition());

			// 게임 오버 
			QuitGame();
		}
	}
}

	// 이동 처리 함수
void Player::Move(float direction, float deltaTime)
{
	// x위치 업데이트
	// 이동 처리 -> 이동 방향과 빠르기를 적용해서 새로운 위치를 구하는 것
	// 이동 방향(direction) / 빠르기(moveSpeed) | 시간
	// 동속도 운동: 이동거리 = 기존의 위치 + 이동방향*빠르기*시간
	xPosition += direction * moveSpeed * deltaTime;

	// 왼쪽 화면 벗어나지 않도록 처리
	if (xPosition < 0)
	{
		xPosition = 0.0f;
	}

	// 화면 오른쪽 벗어나지 않도록 처리
	if (xPosition + width >= Engine::Get().GetWidth())
	{
		xPosition = static_cast<float>(Engine::Get().GetWidth() - width);
	}

	// 위치 업데이트
	Vector2 newPosition = GetPosition();

	//float 값을 int로 형변환할때 소수점은 버림처리됨
	newPosition.x = static_cast<int>(xPosition);
	SetPosition(newPosition);
}

void Player::Fire()
{
	// 탄약 생성 위치 구하기
	//플레이어의 가운데 위치 
	//< = A = >
	//^ ->^ 현재위치 + 플래이어/2
	Vector2 bulletPosition(GetPosition().x + (width / 2), GetPosition().y);
	
	// 탄약 생성
	std::shared_ptr<Level> owner = GetOwner();
	if (owner) // null아닌경우만 생성
	{
		owner->SpawnActor<PlayerBullet>(bulletPosition);
	}
}

void Player::FireInterval()
{
	// 발사 가능 여부 확인
	if (!CanShoot()) return;

	// 발사 처리
	Fire();

	// 경과 시간 초기화
	timer.Reset();

}
