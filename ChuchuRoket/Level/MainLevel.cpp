#include "MainLevel.h"
#include <Render/Renderer.h>
#include <Input/Input.h>
#include <Game/Game.h>
#include <string>
#include <cstdio>
#include <cassert>

using namespace Craft;

MainLevel::MainLevel()
	: blinkTimer(0.5f)
{
	mascotX = 6.0f;
}

void MainLevel::Tick(float deltaTime)
{
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.GoToGameLevel();
	}

	// 애니메이션 연출용 누적 시간.
	totalTime += deltaTime;

	// PRESS ENTER 깜빡임 처리 (0.5초마다 토글).
	blinkTimer.Tick(deltaTime);
	if (blinkTimer.isTimeOut())
	{
		blinkVisible = !blinkVisible;
		blinkTimer.Reset();
	}

	// 마스코트 쥐 좌우 왕복 이동.
	const float mascotSpeed = 12.0f;
	const float mascotMinX = 18.0f;
	const float mascotMaxX = 62.0f;

	mascotX += mascotSpeed * deltaTime * mascotDir;
	if (mascotX >= mascotMaxX)
	{
		mascotX = mascotMaxX;
		mascotDir = -1;
	}
	else if (mascotX <= mascotMinX)
	{
		mascotX = mascotMinX;
		mascotDir = 1;
	}
}

void MainLevel::Draw()
{
	// ---- 타이틀: 줄마다 다른 색으로 무지개처럼 ----
	std::vector<Color> rainbow =
	{
		Color::RED,
		Color::YELLOW,
		Color::GREEN,
		Color::CYAN,
		Color::BLUE,
		Color::PURPLE
	};

	TitleTextLoad("mainAsciiART.txt", Vector2(3, 1), Color::WHITE, &rainbow);

	// ---- 반짝이는 별 장식 ----
	DrawSparkles();

	// ---- PRESS ENTER: 깜빡이게 (0.5초 주기로 보였다 안 보였다) ----
	if (blinkVisible)
	{
		std::vector<Color> pressColor = { Color::BRIGHTWHITE };
		TitleTextLoad("PressEnterArt.txt", Vector2(6, 8), Color::BRIGHTWHITE, &pressColor);
	}

	// ---- 화면 아래를 오가는 쥐 마스코트 ----
	DrawMascot();
}

void MainLevel::DrawSparkles()
{
	// 타이틀 주변에 흩뿌린 별들. 각자 다른 위상(phase)으로 반짝이게 함.
	struct Sparkle { int x; int y; float phase; };

	static const Sparkle sparkles[] =
	{
		{ 1,  0, 0.0f },
		{ 88, 0, 0.6f },
		{ 2,  6, 1.2f },
		{ 90, 6, 0.3f },
		{ 45, 0, 0.9f },
		{ 20, 6, 1.6f },
		{ 70, 6, 0.4f },
	};

	static const wchar_t* sparkleChars[] = { L"✦", L"·", L"✧"};

	for (const Sparkle& s : sparkles)
	{
		// 위상마다 다른 타이밍에 반짝이도록 사인파 기반 패턴 사용.
		float wave = totalTime * 2.0f + s.phase * 6.0f;
		int frame = ((int)(wave)) % 6;

		if (frame == 0 || frame == 1)
		{
			continue; // 안 보이는 구간 (반짝임의 "꺼짐" 상태).
		}

		const wchar_t* ch = sparkleChars[frame % 3];
		Renderer::Get().Submit(ch, Vector2(s.x, s.y), Color::YELLOW);
	}
}

void MainLevel::DrawMascot()
{
	// 마스코트가 지나가는 바닥 트랙(점선). mascotMinX~mascotMaxX 범위와 길이를 맞춤.
	std::wstring track = L".............................................";
	Renderer::Get().Submit(track, Vector2(18, 14), Color::WHITE);

	// 좌우로 왕복하는 쥐. 방향에 따라 좌우 반전 느낌의 문자로 교체.
	const wchar_t* mouseChar = (mascotDir > 0) ? L"⯈" : L"⯇";
	Renderer::Get().Submit(mouseChar, Vector2((int)mascotX, 14), Color::BRIGHTWHITE);
}

void MainLevel::TitleTextLoad(
	std::string fileName,
	Craft::Vector2 position,
	Color color,
	const std::vector<Color>* lineColors)
{
	FILE* file = nullptr;
	std::string fileFullName = "../LevelResources/" + fileName;
	fopen_s(&file, fileFullName.c_str(), "rt");
	if (!file) return;

	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	// +1: 널 종단 문자를 위한 여유 공간 (원래 코드엔 없어서 버퍼 오버런 위험이 있었음).
	char* buffer = new char[fileSize + 1];
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	buffer[readSize] = '\0';

	int index = 0;
	int lineIndex = 0;
	std::wstring text = {};

	auto replaceAndSubmit = [&]()
	{
		for (int i = 0; i < (int)text.length(); i++)
		{
			switch (text[i])
			{
			case L'#':
				text[i] = L'█';
				break;
			case L'-':
				text[i] = L'▄';
				break;
			case L'+':
				text[i] = L'▀';
				break;
			}
		}

		Color lineColor = color;
		if (lineColors && !lineColors->empty())
		{
			lineColor = (*lineColors)[lineIndex % lineColors->size()];
		}

		Renderer::Get().Submit(text, position, lineColor);
	};

	while (index < (int)readSize)
	{
		if (buffer[index] == '\n')
		{
			replaceAndSubmit();
			position.y++;
			++lineIndex;
			++index;
			text.clear();
			continue;
		}
		text += buffer[index++];
	}

	// 파일이 개행 문자 없이 끝나는 경우, 마지막 줄을 놓치지 않게 처리.
	if (!text.empty())
	{
		replaceAndSubmit();
	}

	delete[] buffer;
	buffer = nullptr;
	fclose(file);
	file = nullptr;
}
