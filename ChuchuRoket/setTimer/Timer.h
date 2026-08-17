#pragma once
class Timer
{
public:
	Timer(float targetTime);

	void Tick(float deltaTime = 1.0f);

	// 누적 시간 리셋
	void Reset();

	// 타겟 타임 재설정 함수
	void SetTargetTime(float targetTime);

	//  설정한 시간이 지났는지 확인하는 함수
	inline bool isTimeOut() const { return elapsedTime >= targetTime; }


	//Getter
	int GetElapsedTime() { return (int)elapsedTime; }
	int GetTargetTime() { return (int)targetTime; }

private:
	float elapsedTime = 0.0f;
	float targetTime = 0.0f;
};

