#pragma once
#include <Level/Level.h>
#include <setTimer/Timer.h>
#include <vector>

class MainLevel : public Craft::Level
{
public:
	MainLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	// 타이틀 파일 불러와서 쓰기. lineColors를 넘기면 줄마다 다른 색으로 그려짐(무지개 효과용).
	void TitleTextLoad(
		std::string fileName,
		Craft::Vector2 position,
		Craft::Color color,
		const std::vector<Craft::Color>* lineColors = nullptr);

private:
	// PRESS ENTER 깜빡임 연출.
	Timer blinkTimer;
	bool blinkVisible = true;

	// 반짝이는 별 장식 & 마스코트 이동에 쓰는 누적 시간.
	float totalTime = 0.0f;

	// 화면 하단을 좌우로 오가는 쥐 마스코트 위치.
	float mascotX = 0.0f;
	int mascotDir = 1;

	void DrawSparkles();
	void DrawMascot();
};

