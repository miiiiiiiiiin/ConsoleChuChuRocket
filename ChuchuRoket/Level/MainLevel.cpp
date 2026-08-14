#include "MainLevel.h"
#include <Render/Renderer.h>
#include <Input/Input.h>
#include <Game/Game.h>
#include <string>
#include <cstdio>
#include <cassert>
using namespace Craft;
MainLevel::MainLevel()
{
}

void MainLevel::Tick(float deltaTime)
{
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.GoToGameLevel();
	}
}

void MainLevel::Draw()
{
	std::string TitleText = "mainAsciiART.txt";
	std::string PressText = "PressEnterArt.txt";
	TitleTextLoad(TitleText, Vector2(3, 1));
	TitleTextLoad(PressText, Vector2(6, 8));


}

void MainLevel::TitleTextLoad(std::string fileName, Craft::Vector2 position)
{	
	char* Titlearr[300][300] = {};
	//Renderer::Get().Submit(
	//	Vector2(0, 0));

	FILE* file = nullptr;
	std::string fileFullName = "../LevelResources/" + fileName;
	fopen_s(&file, fileFullName.c_str(), "rt");
	// 한줄씩 읽어오다가 개행문자 만나면 멈추고 submit  출력
	if (!file) return;

	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	// 새 버퍼에 fread로 file 읽어오기
	char* buffer = new char[fileSize];
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	buffer[readSize] = '\0';

	int index = 0;
	std::wstring text = {};
	//Vector2 position = Vector2(3,1);
	while (index < (int)readSize)
	{
		if (buffer[index] == '\n')
		{
			for (int i = 0; i< text.length(); i++)
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

			Renderer::Get().Submit(text, position);
			position.y++;
			++index;
			text.clear();
			continue;
			//position.x;
		}
		text += buffer[index++];
	}

	delete buffer;
	buffer = nullptr;
	fclose(file);
	file = nullptr;
}
