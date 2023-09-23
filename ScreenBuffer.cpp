 #include "stdafx.h"
#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer() : _buffer{0, }
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	// ȭ���� Ŀ���� �Ⱥ��̰Բ� �����Ѵ�.
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;			// Ŀ�� ũ��.

	// �ܼ�ȭ�� (���ٴٵ� �ƿ�ǲ) �ڵ��� ���Ѵ�.
	_hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleCursorInfo(_hConsole, &stConsoleCursor);
}

ScreenBuffer::~ScreenBuffer()
{
	::CloseHandle(_hConsole);
}

//--------------------------------------------------------------------
/// @brief ������ ������ ȭ������ ����ش�.
///	@details ����,�Ʊ�,�Ѿ� ���� szScreenBuffer �� �־��ְ�,
///			 1 �������� ������ �������� �� �Լ��� ȣ���Ͽ� ���� -> ȭ�� ���� �׸���.
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
/// @brief ȭ�� ���۸� �����.
/// @details �� ������ �׸��� �׸��� ������ ���۸� ���� �ش�. 
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
/// @brief ������ Ư�� ��ġ�� ���ϴ� ���ڸ� ����Ѵ�.
///
/// @param y y��ǥ
/// @param x x��ǥ
/// @param sprite ����� ����
//--------------------------------------------------------------------
void ScreenBuffer::DrawSprite(int32 y, int32 x, char sprite)
{
	if (x < 0 || y < 0 || x >= BUFFER_WIDTH - 1 || y >= BUFFER_HEIGHT)
		return;

	_buffer[y][x] = sprite;
}

//--------------------------------------------------------------------
/// @brief ������ Ư�� ��ġ�� ���ϴ� ���ڿ��� ����Ѵ�.
///
/// @param y y��ǥ
/// @param x x��ǥ
/// @param string ����� ���ڿ�
//--------------------------------------------------------------------
void ScreenBuffer::DrawString(int32 y, int32 x, const char* string)
{
	if (x + strlen(string) >= BUFFER_WIDTH)
		return;

	::memcpy(&_buffer[y][x], string, strlen(string));
}

//--------------------------------------------------------------------
/// @brief �ܼ� ȭ���� Ŀ���� y, x��ǥ�� �̵���Ų��.
///
/// @param y y��ǥ
/// @param x x��ǥ
//--------------------------------------------------------------------
void ScreenBuffer::MoveCursor(int32 y, int32 x)
{
	COORD stCoord;
	stCoord.Y = y;
	stCoord.X = x;

	// ���ϴ� ��ġ�� Ŀ���� �̵���Ų��.
	::SetConsoleCursorPosition(_hConsole, stCoord);
}

//--------------------------------------------------------------------
/// @brief �ܼ� ȭ���� ����ȭ �Ѵ�.
//--------------------------------------------------------------------
void ScreenBuffer::ClearScreen()
{
	//-------------------------------------------------------------
	// ȭ�� ũ�⸸ŭ ����, ���� ���� for ���� ����Ͽ�
	// ������ ��ǥ���� printf(" ");  ������ ���� ��� ���ش�.
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
