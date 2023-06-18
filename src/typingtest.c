#include "../include/typingtest.h"

void loadParagraph(TypingTest* typing_test, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    char paragraph[1024];
    char line[256];

    typing_test->paragraphs = NULL;
    typing_test->num_paragraphs = 0;

    for (int i = 0; i < 1; i++) {  // Load only one paragraph
        if (fgets(line, sizeof(line), file) == NULL) {
            break;  // Break if no more lines are available
        }

        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0') {
            if (paragraph[strlen(paragraph) - 1] == ' ')
                paragraph[strlen(paragraph) - 1] = '\0';

            // Allocate memory for the new paragraph and copy the content
            char* new_paragraph = strdup(paragraph);
            if (new_paragraph == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                fclose(file);
                return;
            }

            // Resize the array of paragraphs and add the new paragraph
            typing_test->paragraphs = realloc(typing_test->paragraphs, (typing_test->num_paragraphs + 1) * sizeof(char*));
            if (typing_test->paragraphs == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                fclose(file);
                return;
            }

            // Add the new paragraph to the array
            typing_test->paragraphs[typing_test->num_paragraphs++] = new_paragraph;
        } else {
            strcat(paragraph, line);
            strcat(paragraph, " ");
        }
    }

    fclose(file);
}

void printParagraph(const char* paragraph) {
    printf(ANSI_CLEAR_LINE);
    printf(ANSI_RESET_CURSOR);

    for (size_t i = 0; i < strlen(paragraph); i++) {
        printf("%c", paragraph[i]);
    }
}

void runTypingTest(TypingTest* typing_test) {
    srand(time(NULL));
    while (1) {
        char* target_paragraph = typing_test->paragraphs[0];
        printParagraph(target_paragraph);

        printf("\n\nType the paragraph above within %d seconds:\n", TIME_LIMIT_SECONDS);
        printf("Time start now!!!\n");

        fd_set input_set;
        struct timeval timeout;
        int ready_for_reading = 0;
        int read_bytes = 0;

        FD_ZERO(&input_set);
        FD_SET(STDIN_FILENO, &input_set);

        timeout.tv_sec = TIME_LIMIT_SECONDS;
        timeout.tv_usec = 0;

        ready_for_reading = select(1, &input_set, NULL, NULL, &timeout);

        if (ready_for_reading == -1) {
            printf("Unable to read your input\n");
            continue;
        }

    
        char user_input[MAX_USER_INPUT_LENGTH];
        if (ready_for_reading) {
            read_bytes = read(STDIN_FILENO, user_input, MAX_USER_INPUT_LENGTH);
            if (user_input[read_bytes - 1] == '\n') {
                --read_bytes;
                user_input[read_bytes] = '\0';
            }
        } 
        printf("%s\n", user_input);
        printf("%d seconds are over", TIME_LIMIT_SECONDS);
        sleep(2);
        size_t characters_typed = 0;
        size_t words_typed = 0;
        characters_typed = strlen(user_input);
        for (size_t i = 0; i < characters_typed; i++) {
            if (user_input[i] == ' ') {
                words_typed++;
            }
        }
        size_t typing_speed = (size_t)(words_typed / (double)(TIME_LIMIT_SECONDS / 60.0));
        size_t accuracy = 0;
        size_t target_length = strlen(target_paragraph);

        size_t correct_characters = 0;
        for (size_t i = 0; i < target_length; i++) {
            if (i < characters_typed && target_paragraph[i] == user_input[i])
                correct_characters++;
        }
        accuracy = (size_t)((correct_characters / (double)target_length) * 100);
        printf(ANSI_CLEAR_LINE);
        printf("\nTyping speed: %zu WPM\n", typing_speed);
        printf("Accuracy: ");
        if (accuracy == 100)
            printf(ANSI_COLOR_GREEN "%zu%%" ANSI_COLOR_RESET, accuracy);
        else
            printf(ANSI_COLOR_RED "%zu%%" ANSI_COLOR_RESET, accuracy);
        printf("\n");
        printf("Press Enter to continue or 'q' to quit...\n");
        char input[10];
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "q\n") == 0 || strcmp(input, "Q\n") == 0)
            break;
    }
}
