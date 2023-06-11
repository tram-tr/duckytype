#include "../include/typingtest.h"

int main() {
    srand((unsigned)time(NULL));

    TypingTest typing_test;
    memset(&typing_test, 0, sizeof(typing_test));
    char current_path[PATH_MAX];
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        fprintf(stderr, "Failed to get the current working directory.\n");
        return 1;
    }
    char absolute_path[PATH_MAX];
    snprintf(absolute_path, sizeof(absolute_path), "%s/data/paragraphs.txt", current_path);
    loadParagraphs(&typing_test, absolute_path);

    printf("Welcome to the Typing Test!\n");
    printf("Press Enter to start the test...\n");
    getchar();

    runTypingTest(&typing_test);
    for (int i = 0; i < typing_test.num_paragraphs; i++)
        free(typing_test.paragraphs[i]);

    free(typing_test.paragraphs);
    printf("Thank you for using the Typing Test! Goodbye.\n");
    return 0;
}
