#include "../include/typingtest.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void test_loadParagraph() {
    TypingTest typing_test;
    memset(&typing_test, 0, sizeof(TypingTest));
    char current_path[PATH_MAX];
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        fprintf(stderr, "Failed to get the current working directory.\n");
        return;
    }
    char absolute_path[PATH_MAX];
    snprintf(absolute_path, sizeof(absolute_path), "%s/data/paragraph.txt", current_path);
    printf("Loading paragraph from: %s\n", absolute_path);
    loadParagraph(&typing_test, absolute_path);
    printf("Number of paragraphs loaded: %d\n", typing_test.num_paragraphs);
    printf("Current paragraph: %s\n", typing_test.paragraphs[0]); // Print the current paragraph
    assert(typing_test.num_paragraphs == 1);
}

int main() {
    test_loadParagraph();
    printf("All tests passed.\n");
    return 0;
}

