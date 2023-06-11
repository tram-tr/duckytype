#ifndef TYPINGTEST_H
#define TYPINGTEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_CLEAR_LINE "\033[2K"
#define ANSI_RESET_CURSOR "\033[1G"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_RESET "\033[0m"

typedef struct {
    char** paragraphs;
    int numParagraphs;
} TypingTest;

void loadParagraphs(TypingTest* typingTest, const char* filename);
void runTypingTest(TypingTest* typingTest);
char* getRandomParagraph(TypingTest* typingTest);
void printParagraph(const char* paragraph, size_t currentPosition);

#endif
