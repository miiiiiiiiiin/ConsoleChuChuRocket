#pragma once
#include<Level/Level.h>
#include <string>
class GameLevel : public Craft::Level
{
	TYPE_DECLARATIONS(GameLevel, Level)
public:
	// 이동 가능한지 확인
	// 타일맵 이동시 호출하여 이동가능한지 확인하게한다
	bool CanMove(const Craft::Vector2& playerPosition, const Craft::Vector2& nextPosition);

private:
	//레벨 초기화 함수
	virtual void OnInitialized() override;

	//Draw 이벤트 함수
	virtual void Draw() override;

	//맵 로드 함수
	void LoadMap(const std::string& filename);

private:
	//목표 점수 - 클리어 조건
	int targetScore = 0;

	//게임 클리어 여부 플래그
	bool isGameClear = false;
};

