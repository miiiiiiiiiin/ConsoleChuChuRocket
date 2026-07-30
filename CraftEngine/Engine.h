#pragma once

namespace Craft
{
	//메인 엔진 클래스
	//엔진 루프 제공, 게임 엔진 핵심기능 제공
	class Engine
	{
		//엔진설정(데이터)
		struct Setting
		{
			//목표 프레임 수(초당프레임)
			float framerate = 120.0f;
		};
	public:
		Engine();
		virtual ~Engine();
		//엔진실행함수
		void Run();
		//엔진종료함수
		void Quit();
	protected:
		//입력 처리 함수(입력 폴링)
		void ProcessInput();

		//프레임 시간 계산
		
		//초기화함수
		void OnInitialized();

		//게임 플레이 이벤트 함수
		//게임 초기화함수
		void BeginPlay();

		//게임 플레이 업데이트 함수
		void Tick(float deltaTime);

		//레벨 그리기 함수
		void Draw();

		//프레임 간 입력 값 저장을 위한 함수
		void SavePriviousInputStates();

		//엔진 종료시 정리 함수
		void ShutDown();

	protected:
		//엔진 종료 요청 여부 플래그
		bool isQuit = false;

		//엔진 설정 함수
		Setting setting;
	};
}



