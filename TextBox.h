#pragma once
#include "BaseObject.h"
class TextBox : public BaseObject
{
public:
	TextBox(int32 y, int32 x, const char* text);
	~TextBox() override;

	bool Update() override;
	void Render() override;
	void OnCollision(BaseObject* other) override;

	void ChangeText(const char* text);

private:
	char _text[100] = "";
};

