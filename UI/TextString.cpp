#include <string.h>
#include <stdio.h>

#include"TextString.h"

GenericCharArray::GenericCharArray()
{
	str = nullptr;
	CleanUp();
}
GenericCharArray::~GenericCharArray()
{
	CleanUp();
}
void GenericCharArray::CleanUp(void)
{
	if (nullptr != str)
	{
		delete[] str;
	}
	str = nullptr;
	lng = 0;
}

int GenericCharArray::GetSize(void) const
{
	return lng;
}
void GenericCharArray::Resize(int newLng)
{
	// Allocate
	char *newStr = new char[newLng];

	// Make a copy
	for (int i = 0; i<lng && i<newLng; ++i)
	{
		newStr[i] = str[i];
	}

	// CleanUp
	CleanUp();

	// Re-point
	str = newStr;
	lng = newLng;
}
char *GenericCharArray::GetPointer(void)
{
	return str;
}
const char *GenericCharArray::GetPointer(void) const
{
	return str;
}




TextString::TextString()
{
}
TextString::TextString(const TextString &incoming)
{
	CopyFrom(incoming);
}
TextString::~TextString()
{
	CleanUp();
}

TextString &TextString::operator=(const TextString &incoming)
{
	CopyFrom(incoming);
	return *this;
}

void TextString::CopyFrom(const TextString &incoming)
{
	Set(incoming.GetPointer());
}

void TextString::CleanUp(void)
{
	GenericCharArray::CleanUp();
}

void TextString::Add(char c)
{
	if (0 == GetSize())
	{
		const char newStr[2] = { c,0 };
		Set(newStr);
	}
	else
	{
		Resize(GetSize() + 1);

		char *str = GenericCharArray::GetPointer();
		auto l = strlen(str);
		str[l] = c;
		str[l + 1] = 0;
	}
}

void TextString::Add(const char str[])
{
	for (int i = 0; str[i] != 0; ++i)
	{
		Add(str[i]);
	}
}

void TextString::Set(const char incoming[])
{
	if (incoming != GetPointer())
	{
		auto l = strlen(incoming);

		Resize(l + 1);
		auto str = GenericCharArray::GetPointer();
		strcpy(str, incoming);
	}
}

void TextString::BackSpace(void)
{
	if (nullptr != GetPointer())
	{
		auto l = strlen(GetPointer());
		// Quick version
		// if(0<l)
		// {
		// 	str[l-1]=0;
		// }

		if (0<l)
		{
			Resize(l);
			auto str = GenericCharArray::GetPointer();
			str[l - 1] = 0;
		}
	}
}

const char *TextString::GetPointer(void) const
{
	auto str = GenericCharArray::GetPointer();
	if (nullptr != str)
	{
		return str;
	}
	else
	{
		return "";
	}
}

int TextString::Strlen(void) const
{
	return strlen(GetPointer());
}

const char *TextString::Fgets(FILE *fp)
{
	CleanUp();

	char str[16];
	for (;;)
	{
		if (nullptr != fgets(str, 15, fp))
		{
			for (int i = 0; str[i] != 0; ++i)
			{
				if (str[i] == '\n')
				{
					return GetPointer();
				}
				Add(str[i]);
			}
		}
		else
		{
			if (0<Strlen())
			{
				return GetPointer();
			}
			else
			{
				return nullptr;
			}
		}
	}
}





