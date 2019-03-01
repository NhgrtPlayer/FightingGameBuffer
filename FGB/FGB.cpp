// FGB.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include "Buffer.h"
#include "Move.h"

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

void GetKeyboardInputs(Buffer & buffer, std::vector<EnumInput> & UserInputs)
{
	bool UpKeyDown = GetAsyncKeyState(VK_UP) & 0x8000;
	bool DownKeyDown = GetAsyncKeyState(VK_DOWN) & 0x8000;
	bool LeftKeyDown = GetAsyncKeyState(VK_LEFT) & 0x8000;
	bool RightKeyDown = GetAsyncKeyState(VK_RIGHT) & 0x8000;
	bool A_KeyDown = GetAsyncKeyState('A') & 0x8000;
	bool B_KeyDown = GetAsyncKeyState('B') & 0x8000;
	bool C_KeyDown = GetAsyncKeyState('C') & 0x8000;
	bool D_KeyDown = GetAsyncKeyState('D') & 0x8000;

	if (UpKeyDown && LeftKeyDown) {
		return (UserInputs.push_back(EnumInput::UP_LEFT));
	}
	if (UpKeyDown && RightKeyDown) {
		return (UserInputs.push_back(EnumInput::UP_RIGHT));
	}
	if (UpKeyDown) {
		UserInputs.push_back(EnumInput::UP);
	}
	if (DownKeyDown && LeftKeyDown) {
		return (UserInputs.push_back(EnumInput::DOWN_LEFT));
	}
	if (DownKeyDown && RightKeyDown) {
		return (UserInputs.push_back(EnumInput::DOWN_RIGHT));
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
	if (A_KeyDown) {
		UserInputs.push_back(EnumInput::A_BUTTON);
	}
	if (B_KeyDown) {
		UserInputs.push_back(EnumInput::B_BUTTON);
	}
	if (C_KeyDown) {
		UserInputs.push_back(EnumInput::C_BUTTON);
	}
	if (D_KeyDown) {
		UserInputs.push_back(EnumInput::D_BUTTON);
	}
}

void AddUserInputsInBuffer(Buffer & buffer, const std::vector<EnumInput> & UserInputs, int FrameCounter)
{
	for (int i = 0; i < UserInputs.size(); ++i)
	{
		buffer.AddInput(Input(FrameCounter, UserInputs[i]));
	}
}

void CheckMoves(const std::vector<Move> & UserMoves, const Buffer & buffer)
{
	for (auto const &Move : UserMoves)
	{
		if (Move.CheckMove(buffer.GetInputs()))
		{
			std::cout << "MOVE EXECUTED : " << Move.ToString() << '\n';
			// FLUSH BUFFER SI LE MOVE DOIT LE FAIRE
		}
	}
}

int main()
{
	Buffer buffer;
	int FrameCounter = 0;
	std::vector<EnumInput> UserInputs;
	//std::mutex UserInputsMutex;
	//std::thread UserInputsThread(GetKeyboardInputs, std::ref(buffer), std::ref(UserInputs), std::ref(UserInputsMutex));

	std::vector<Move> UserMoves;
	UserMoves.push_back(Move("MoveRight", Input(EnumInput::RIGHT), EnumMovePriority::MOVEMENT));
	UserMoves.push_back(Move("DashRight", { Input(EnumInput::RIGHT), Input(EnumInput::RIGHT) }, EnumMovePriority::DASH));
	UserMoves.push_back(Move("Hadoken", { Input(EnumInput::DOWN), Input(EnumInput::DOWN_RIGHT), Input(EnumInput::RIGHT), Input(EnumInput::A_BUTTON) }, EnumMovePriority::SPECIAL_MOVE, true));

	std::sort(UserMoves.begin(), UserMoves.end(), [](const auto& lhs, const auto& rhs)
	{
		return (lhs.GetPriority() > rhs.GetPriority());
	});
	while (1)
	{
		FrameCounter++;
		ClearScreen();

		GetKeyboardInputs(buffer, UserInputs);
		AddUserInputsInBuffer(buffer, UserInputs, FrameCounter);
		UserInputs.clear();

		buffer.CutInputs(FrameCounter);

		buffer.PrintBuffer();

		std::this_thread::sleep_for(std::chrono::duration<float>(1.0 / FRAME_RATE));
	}

	return (0);
}

