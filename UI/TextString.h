#ifndef __TEXT_INPUT_H__
#define __TEXT_INPUT_H__

#include <string.h>
#include <stdio.h>
#include <time.h>

#include "fssimplewindow.h"
#include "ysglfontdata.h"


class GenericCharArray
{
private:
	int lng;
	char *str;

	GenericCharArray(const GenericCharArray &);
	GenericCharArray &operator=(const GenericCharArray &);
public:
	GenericCharArray();
	~GenericCharArray();
	void CleanUp(void);

	int GetSize(void) const;
protected:
	void Resize(int newLng);
	char *GetPointer(void);
	const char *GetPointer(void) const;
};

class TextString : public GenericCharArray
{
public:
	TextString();
	TextString(const TextString &incoming);
	~TextString();
	void CleanUp(void);

	TextString &operator=(const TextString &incoming);

	void CopyFrom(const TextString &incoming);

	void Add(char c);
	void Add(const char str[]);
	void BackSpace(void);

	void Set(const char incoming[]);
	const char *GetPointer(void) const;

	int Strlen(void) const;

	const char *Fgets(FILE *fp);
	void Print(void) const;
};



#endif