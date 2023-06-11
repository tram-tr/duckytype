#include "../include/typingtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void loadParagraphs(TypingTest* typingTest, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    char paragraph[1024];
    char line[256];

    typingTest->paragraphs = NULL;
    typingTest->numParagraphs = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0') {
            if (paragraph[strlen(paragraph) - 1] == ' ') 
                paragraph[strlen(paragraph) - 1] = '\0';
            
            // allocate memory for the new paragraph and copy the content
            char* newParagraph = strdup(paragraph);
            if (newParagraph == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                fclose(file);
                return;
            }

            // resize the array of paragraphs and add the new paragraph
            typingTest->paragraphs = realloc(typingTest->paragraphs, (typingTest->numParagraphs + 1) * sizeof(char*));
            if (typingTest->paragraphs == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                fclose(file);
                return;
            }

            // add the new paragraph to the array
            typingTest->paragraphs[typingTest->numParagraphs++] = newParagraph;
            paragraph[0] = '\0';
        } else {
            strcat(paragraph, line);
            strcat(paragraph, " "); 
        }
    }
    fclose(file);
}

char* getRandomParagraph(const TypingTest* typingTest) {
    int index = rand() % typingTest->numParagraphs;
    return typingTest->paragraphs[index];
}

void printParagraph(const char* paragraph, int currentPosition) {
    printf(ANSI_CLEAR_LINE);
    printf(ANSI_RESET_CURSOR);
    for (int i = 0; i < strlen(paragraph); i++) {
        if (i < currentPosition) {
            printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, paragraph[i]);
        } else if (i == currentPosition) {
            printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, paragraph[i]);
        } else {
            printf("%c", paragraph[i]);
        }
    }
}

void run(TypingTest* typingTest) {
    srand(time(NULL));
    while (1) {
        char* targetParagraph = getRandomParagraph(typingTest);
        int currentPosition = 0;
        printParagraph(targetParagraph, currentPosition);
    }
}
