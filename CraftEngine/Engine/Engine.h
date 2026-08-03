#pragma once
#include<memory> // 스마트 포인터 사용

namespace Craft
{
	//전방 선언
	class Level;
	class Input;

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

		//레벨 추가 요청 함수
		// 1. std::is_base_of 하는일이 무엇인지
		// 2. std::enable_if_t 하는일이 무엇인지
		// 3. typename = std::enable_if_t<std::is_base_of<Level, T>::value>>
		template<typename T, 
			typename = std::enable_if_t<std::is_base_of<Level, T>::value>>
		void AddNewLevel()
		{
			//추가 요청 레벨 객체 생성
			nextLevel = std::make_shared<T>();
		}

		//전역 접근 함수
		static Engine& Get();

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

		//전역 접근이 가능하도록 변수 선언
		static Engine* instance;

		//메인 레벨
		std::shared_ptr<Level> mainLevel;

		//추가 요청된 레벨
		std::shared_ptr<Level> nextLevel;
		
		//입력 시스템 변수
		std::unique_ptr<Input> input;
	};
}



