#pragma once
#include "Types.h"

enum class ConsoleColor
{
	BLACK = 0,
	PURPLE = 0x0005,
	SKYBLUE = 0x0003,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	YELLOW = 0x0006,
	WHITE = 0x0007
};

class ConsoleHelper
{
public:
	static void SetCursorPosition(int32 x, int32 y);
	static void SetCursorColor(ConsoleColor color);
	static void ShowConsoleCursor(bool flag);
};

