#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <fcntl.h>

#ifndef TYPINGTEST_H
#define TYPINGTEST_H

#define ANSI_CLEAR_LINE "\033[2K"
#define ANSI_RESET_CURSOR "\033[1G"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_RESET "\033[0m"

#define MAX_PARAGRAPH_LENGTH 4096
#define MAX_USER_INPUT_LENGTH 4096
#define TIME_LIMIT_SECONDS 60
#define MAX_WORDS 350
#define MAX_LENGTH 50

typedef struct {
    char** paragraphs;
    int num_paragraphs;
} TypingTest;

void load_paragraph(TypingTest* typing_test, const char* filename);
void run_typingtest(TypingTest* typing_test);
void print_paragraph(const char* paragraph);

#endif
