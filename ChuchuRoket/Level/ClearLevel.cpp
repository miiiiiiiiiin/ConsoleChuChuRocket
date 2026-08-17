#include "ClearLevel.h"

#include <Render/Renderer.h>
using namespace Craft;

ClearLevel::ClearLevel()
	: timer(2.0f)
{
}
void ClearLevel::OnInitialized()
{
	Level::OnInitialized();
	//timer.Reset();   // ClearLevel에 진입할 때마다 타이머 새로 시작
}

void ClearLevel::Tick(float deltaTime)
{	// 엔진은 참조로받아야돼서 Cast ㄴㄴ
	Level::Tick(deltaTime);

	Game& game = dynamic_cast<Game&>(Engine::Get());
	//game.ResetTime();
	//game.SetTimer(1.6f);
	//game.ToggleGameToClear();

	if (game.GetisClear())
	{

		// 계싼 시작
		game.SetTick(deltaTime);

		// 타이머로 한 3초 뒤 게임 부르기
		if (game.GetisTimeOut())
		{
			game.SetisClear(false);
			// Todo: dd
			if (game.GetStageNum() > 5)
			{
				// 스테이지 5 넘으면 불러오기 중지
				return;
			}
			//game.ResetTime();
			game.GoToGameLevel();
		}
	}
}

void ClearLevel::Draw()
{
	//Renderer::Get().Submit(L"Stage Clear!", Vector2(5, 5));
	TitleTextLoad("GameClearAsciiArt.txt", Vector2(7, 5));

}

void ClearLevel::TitleTextLoad(
	std::string fileName,
	Craft::Vector2 position)
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
				}
			}

			Renderer::Get().Submit(text, position);
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