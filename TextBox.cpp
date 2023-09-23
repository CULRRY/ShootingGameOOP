#include "stdafx.h"
#include "TextBox.h"

#include "ObjectType.h"
#include "ScreenBuffer.h"

TextBox::TextBox(int32 y, int32 x, const char* text) : BaseObject(y, x, ObjectType::TEXT_BOX)
{
	strcpy_s(_text, text);
}

TextBox::~TextBox()
{
}

bool TextBox::Update()
{
	return true;
}

//-----------------------------------------------------------------------------
/// @brief Text를 ScreenBuffer에 출력한다.
//-----------------------------------------------------------------------------
void TextBox::Render()
{
	ScreenBuffer::Instance()->DrawString(_y, _x, _text);
}

void TextBox::OnCollision(BaseObject* other)
{
}

//-----------------------------------------------------------------------------
/// @brief 출력할 스트링을 변경한다.
//-----------------------------------------------------------------------------
void TextBox::ChangeText(const char* text)
{
	strcpy_s(_text, text);
}

