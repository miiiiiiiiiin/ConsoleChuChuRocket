#pragma once
#include <Level/Level.h>
class MainLevel : public Craft::Level
{
public:
	MainLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
	// 타이틀 파일 불러와서 쓰기
	void TitleTextLoad(std::string fileName, Craft::Vector2 position, Craft::Color color);
private:

};

