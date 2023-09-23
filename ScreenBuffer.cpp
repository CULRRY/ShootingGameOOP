 #include "stdafx.h"
#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer() : _buffer{0, }
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	// 화면의 커서를 안보이게끔 설정한다.
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;			// 커서 크기.

	// 콘솔화면 (스텐다드 아웃풋) 핸들을 구한다.
	_hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleCursorInfo(_hConsole, &stConsoleCursor);
}

ScreenBuffer::~ScreenBuffer()
{
	::CloseHandle(_hConsole);
}

//--------------------------------------------------------------------
/// @brief 버퍼의 내용을 화면으로 찍어준다.
///	@details 적군,아군,총알 등을 szScreenBuffer 에 넣어주고,
///			 1 프레임이 끝나는 마지막에 본 함수를 호출하여 버퍼 -> 화면 으로 그린다.
//--------------------------------------------------------------------
void ScreenBuffer::Flip()
{
	for (uint32 y = 0; y < BUFFER_HEIGHT; y++)
	{
		MoveCursor(y, 0);
		printf(_buffer[y]);
	}
}

//--------------------------------------------------------------------
/// @brief 화면 버퍼를 지운다.
/// @details 매 프레임 그림을 그리기 직전에 버퍼를 지워 준다. 
//--------------------------------------------------------------------
void ScreenBuffer::Clear()
{
	for (uint32 y = 0; y < BUFFER_HEIGHT; y++)
	{
		memset(_buffer[y], ' ', BUFFER_WIDTH);
		_buffer[y][BUFFER_WIDTH - 1] = (char)NULL;
	}
}

//--------------------------------------------------------------------
/// @brief 버퍼의 특정 위치에 원하는 문자를 출력한다.
///
/// @param y y좌표
/// @param x x좌표
/// @param sprite 출력할 문자
//--------------------------------------------------------------------
void ScreenBuffer::DrawSprite(int32 y, int32 x, char sprite)
{
	if (x < 0 || y < 0 || x >= BUFFER_WIDTH - 1 || y >= BUFFER_HEIGHT)
		return;

	_buffer[y][x] = sprite;
}

//--------------------------------------------------------------------
/// @brief 버퍼의 특정 위치에 원하는 문자열을 출력한다.
///
/// @param y y좌표
/// @param x x좌표
/// @param string 출력할 문자열
//--------------------------------------------------------------------
void ScreenBuffer::DrawString(int32 y, int32 x, const char* string)
{
	if (x + strlen(string) >= BUFFER_WIDTH)
		return;

	::memcpy(&_buffer[y][x], string, strlen(string));
}

//--------------------------------------------------------------------
/// @brief 콘솔 화면의 커서를 y, x좌표로 이동시킨다.
///
/// @param y y좌표
/// @param x x좌표
//--------------------------------------------------------------------
void ScreenBuffer::MoveCursor(int32 y, int32 x)
{
	COORD stCoord;
	stCoord.Y = y;
	stCoord.X = x;

	// 원하는 위치로 커서를 이동시킨다.
	::SetConsoleCursorPosition(_hConsole, stCoord);
}

//--------------------------------------------------------------------
/// @brief 콘솔 화면을 조기화 한다.
//--------------------------------------------------------------------
void ScreenBuffer::ClearScreen()
{
	//-------------------------------------------------------------
	// 화면 크기만큼 세로, 가로 이중 for 문을 사용하여
	// 각각의 좌표마다 printf(" ");  공백을 전부 출력 해준다.
	//-------------------------------------------------------------
	for (int32 y = 0; y < BUFFER_HEIGHT + 3; y++)
	{
		for (int32 x = 0; x < BUFFER_WIDTH; x++)
		{
			MoveCursor(y, x);
			printf(" ");
		}
	}
}
