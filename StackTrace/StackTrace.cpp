#include <iostream>
#include <windows.h>
#include <DbgHelp.h>
#include <stdio.h>

void printStack(void)
{
	unsigned int   i;
	void         * stack[100];
	unsigned short frames;
	SYMBOL_INFO  * symbol;
	HANDLE         process;

	process = GetCurrentProcess();
	SymInitialize(process, NULL, TRUE);
	frames = CaptureStackBackTrace(0, 100, stack, NULL);
	symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	IMAGEHLP_LINE64 *line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
	line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);
	DWORD displacement;

	for (i = 0; i < frames; i++)
	{
		SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
		SymGetLineFromAddr64(process, (DWORD64)stack[i], &displacement, line);

		printf("%s %s:%i\n", symbol->Name, line->FileName, line->LineNumber);
	}

	free(symbol);
}

void test2()
{
	printStack();
}

void test()
{
	test2();
}

int main()
{
	test();
    return 0;
}

