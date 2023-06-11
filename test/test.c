#include "../include/typingtest.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void test_loadParagraphs() {
    TypingTest typingTest;
    memset(&typingTest, 0, sizeof(TypingTest));
    char currentPath[PATH_MAX];
    if (getcwd(currentPath, sizeof(currentPath)) == NULL) {
        fprintf(stderr, "Failed to get the current working directory.\n");
        return;
    }
    char absolutePath[PATH_MAX];
    snprintf(absolutePath, sizeof(absolutePath), "%s/data/paragraphs.txt", currentPath);
    loadParagraphs(&typingTest, absolutePath);
    assert(typingTest.numParagraphs == 10);
}

void test_getRandomParagraph() {
    TypingTest typingTest;
    memset(&typingTest, 0, sizeof(TypingTest));
    char currentPath[PATH_MAX];
    if (getcwd(currentPath, sizeof(currentPath)) == NULL) {
        fprintf(stderr, "Failed to get the current working directory.\n");
        return;
    }
    char absolutePath[PATH_MAX];
    snprintf(absolutePath, sizeof(absolutePath), "%s/data/paragraphs.txt", currentPath);
    loadParagraphs(&typingTest, absolutePath);
    char* paragraph = getRandomParagraph(&typingTest);
    assert(paragraph != NULL);
}

int main() {
    test_loadParagraphs();
    printf("All tests passed.\n");
    return 0;
}
