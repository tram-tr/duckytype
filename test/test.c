#include "../include/typingtest.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void test_loadParagraphs() {
    TypingTest typing_test;
    memset(&typing_test, 0, sizeof(TypingTest));
    char current_path[PATH_MAX];
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        fprintf(stderr, "Failed to get the current working directory.\n");
        return;
    }
    char absolute_path[PATH_MAX];
    snprintf(absolute_path, sizeof(absolute_path), "%s/data/paragraphs.txt", current_path);
    loadParagraphs(&typing_test, absolute_path);
    assert(typing_test.num_paragraphs == 10);
}

void test_getRandomParagraph() {
    TypingTest typing_test;
    memset(&typing_test, 0, sizeof(TypingTest));
    char current_path[PATH_MAX];
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        fprintf(stderr, "Failed to get the current working directory.\n");
        return;
    }
    char absolute_path[PATH_MAX];
    snprintf(absolute_path, sizeof(absolute_path), "%s/data/paragraphs.txt", current_path);
    loadParagraphs(&typing_test, absolute_path);
    char* paragraph = getRandomParagraph(&typing_test);
    assert(paragraph != NULL);
}

int main() {
    test_loadParagraphs();
    printf("All tests passed.\n");
    return 0;
}
