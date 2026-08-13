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
	Renderer::Get().Submit(L"Stage Clear!", Vector2(5, 5));

}
