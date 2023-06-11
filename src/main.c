#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/typingtest.h"

int main() {
    srand((unsigned)time(NULL));

    TypingTest typingTest;
    loadParagraphs(&typingTest, "../data/paragraphs.txt");

    printf("Welcome to the Typing Test!\n");
    printf("Press Enter to start the test...\n");
    getchar();

    runTypingTest(&typingTest);

    printf("Thank you for using the Typing Test! Goodbye.\n");

    return 0;
}
