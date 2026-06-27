#include "epch.h"
#include "Timer.h"

Engine::Timer::Timer()
{
	prevTime = high_res_clock::now();
}

void Engine::Timer::Start()
{
	
}

void Engine::Timer::Stop()
{
	
}

void Engine::Timer::Reset()
{
	
}

void Engine::Timer::Tick()
{
	currTime = high_res_clock::now();
	deltaTime = std::chrono::duration<double>(currTime - prevTime);
	prevTime = currTime;
}

float Engine::Timer::DeltaTime()
{
	return deltaTime.count();
}

std::chrono::duration<double> Engine::Timer::deltaTime;

