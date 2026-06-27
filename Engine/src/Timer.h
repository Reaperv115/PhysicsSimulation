#pragma once
#include <iostream>
#include <chrono>

using high_res_clock = std::chrono::high_resolution_clock;

namespace Engine
{
	class Timer
	{
	public:
		Timer();
		void Start();
		void Stop();
		void Reset();
		void Tick();
		static float DeltaTime();
	private:
		static std::chrono::duration<double> deltaTime;
		double secondsperCount;

		high_res_clock::time_point baseTime;
		high_res_clock::duration pausedTime;
		high_res_clock::time_point stopTime;
		high_res_clock::time_point prevTime;
		high_res_clock::time_point currTime;

		bool isStopped;
		
	};
}

