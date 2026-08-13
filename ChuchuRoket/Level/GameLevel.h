#pragma once
#include <Level/Level.h>
#include <string>
#include <Engine/Engine.h>
#include <Game/Game.h>
class GameLevel : public Craft::Level
{
	TYPE_DECLARATIONS(GameLevel, Level)
public:
	// 이동 가능한지 확인
	// 타일맵 이동시 호출하여 이동가능한지 확인하게한다
	bool CanMove(const Craft::Vector2& playerPosition, const Craft::Vector2& nextPosition);

	// 타일맵 밟았는지 확인(포지션 같은지 확인)
	bool isSamePosition(const Craft::Vector2& playerPosition,
		const Craft::Vector2& nextPosition);


	// ArrowCOunt 게터
	// 외부(ArrowTile 등)에서 부를 수 있는 public 인터페이스.
	void DecreaseArrowCount() { remainingArrowCount--; }
	int GetRemainingArrowCount() const { return remainingArrowCount; }

	bool GetisCanMove() const { return isCanMove; }
	void SetisCanMove(bool ismove) { isCanMove = ismove; }

	void SetisClear(bool isclear) { isGameClear = isclear; }


private:
	//레벨 초기화 함수
	virtual void OnInitialized() override;

	//Draw 이벤트 함수
	virtual void Draw() override;

	virtual void Tick(float deltaTime) override;

	//맵 로드 함수
	void LoadMap(const std::string& filename);


private:
	//목표 점수 - 클리어 조건
	int targetScore = 0;

	// 화살표 움직이게하는 플래그. false 되면 화살표못움직이고 쥐돌이가움직인다
	bool isCanMove = true;

	// 게임 클리어되었느닞 확인하는 플래그.
	bool isGameClear = false;

	// 게임 스테이지 번호

	// 남은 화살표 개수
	int remainingArrowCount = 0;

	// 몬스터 경로 넣는 리스트
	std::vector<Craft::Vector2> EnemyList;
};

