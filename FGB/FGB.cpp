// FGB.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <windows.h>
#include "Buffer.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const float FRAME_RATE = 60.0;

void ClearScreen()
{
	system("CLS");
	std::cout << std::flush;
}

void GetKeyboardInputs(Buffer & buffer, std::vector<EnumInput> & UserInputs, std::mutex & UserInputsMutex)
{
	while (1)
	{
		bool UpKeyDown = GetAsyncKeyState(VK_UP) & 0x8000;
		bool DownKeyDown = GetAsyncKeyState(VK_DOWN) & 0x8000;
		bool LeftKeyDown = GetAsyncKeyState(VK_LEFT) & 0x8000;
		bool RightKeyDown = GetAsyncKeyState(VK_RIGHT) & 0x8000;

		UserInputsMutex.lock();
		if (UpKeyDown) {
			UserInputs.push_back(EnumInput::UP);
		}
		if (DownKeyDown) {
			UserInputs.push_back(EnumInput::DOWN);
		}
		if (LeftKeyDown) {
			UserInputs.push_back(EnumInput::LEFT);
		}
		if (RightKeyDown) {
			UserInputs.push_back(EnumInput::RIGHT);
		}
		if (!UpKeyDown && !DownKeyDown && !LeftKeyDown && !RightKeyDown) {
			UserInputs.push_back(EnumInput::NEUTRAL);
		}
		UserInputsMutex.unlock();
	}
}

void AddUserInputsInBuffer(Buffer & buffer, const std::vector<EnumInput> & UserInputs, int FrameCounter)
{
	for (int i = 0; i < UserInputs.size(); ++i)
	{
		buffer.AddInput(Input(FrameCounter, UserInputs[i]));
	}
}

int main()
{
	Buffer buffer;
	int FrameCounter = 0;
	std::vector<EnumInput> UserInputs;
	std::mutex UserInputsMutex;
	std::thread UserInputsThread(GetKeyboardInputs, std::ref(buffer), std::ref(UserInputs), std::ref(UserInputsMutex));

	while (1)
	{
		FrameCounter++;

		UserInputsMutex.lock();
		AddUserInputsInBuffer(buffer, UserInputs, FrameCounter);
		UserInputs.clear();
		UserInputsMutex.unlock();

		buffer.CutInputs();

		buffer.PrintBuffer();

		std::this_thread::sleep_for(std::chrono::duration<float>(1.0 / FRAME_RATE));
	}

	return (0);
}

