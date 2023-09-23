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
/// @brief Text�� ScreenBuffer�� ����Ѵ�.
//-----------------------------------------------------------------------------
void TextBox::Render()
{
	ScreenBuffer::Instance()->DrawString(_y, _x, _text);
}

void TextBox::OnCollision(BaseObject* other)
{
}

//-----------------------------------------------------------------------------
/// @brief ����� ��Ʈ���� �����Ѵ�.
//-----------------------------------------------------------------------------
void TextBox::ChangeText(const char* text)
{
	strcpy_s(_text, text);
}

