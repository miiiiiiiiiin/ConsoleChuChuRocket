#include "MenuLevel.h"
#include <Game/Game.h>
#include <Input/Input.h>
#include <Render/Renderer.h>

#include<cassert>
using namespace Craft;
MenuLevel::MenuLevel()
{
	// 메뉴 아이템 생성
	itemList.emplace_back(
		std::make_unique<MenuItem>(
			L"Resume Game",
			[]()
			{
				// 메뉴 토글 함수 호출
				Game& game = dynamic_cast<Game&>(Engine::Get());
				game.ToggleMenu();
			}
		)
	);
	// 메뉴 아이템 생성
	itemList.emplace_back(
		std::make_unique<MenuItem>(
			L"Quit Game",
			[]()
			{
				// 게임 종료 호출
				Engine::Get().Quit();
			}
		)
	);

}

void MenuLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);

	// 입력 처리(위아래 방향키, 엔터, esc키)
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu();

		// 인덱스 초기화
		currentIndex = 0;
	}
	// 배열의 요소 개수
	const int length = static_cast<int>(itemList.size());
	if (Input::Get().GetKeyDown(VK_UP))
	{
		// 인덱스 돌리기(+ 방향) 나머지연산으로..
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		// 인덱스 돌리기(+ 방향) 나머지연산으로..
		currentIndex = (currentIndex + 1) % length;
	}

	// 엔터 입력 처리 -> 현재 선택된 메뉴의 로직 실행
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 어서트
		assert(currentIndex >= 0
			&& currentIndex < (int)itemList.size()
			&& itemList[currentIndex]->onSelected
		);
		
		// 메뉴 아이템에 저장된 로직 실행
		itemList[currentIndex]->onSelected();
	}

}

void MenuLevel::Draw()
{
	//제목 그리기
	Renderer::Get().Submit(L"Sokoban Game", Vector2::Zero);

	// 메뉴 아이템 그리기
	const int count = static_cast<int>(itemList.size());
	for (int i = 0; i < count; i++)
	{
		// 선택/ 미선택된 아이템 색상 처리
		Color textColor = (i == currentIndex) ? selectedColor : unselectedColor;

		// 아이템 그리기
		Renderer::Get().Submit(
			itemList[i]->text,
			Vector2(0, 2 + i),
			textColor
		);
	}
}
