#include "../include/typingtest.h"

void loadParagraph(TypingTest* typing_test, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    char line[1024];
    int num_lines = 0;
    int num_paragraphs = 0;

    // Count the number of lines and paragraphs in the file
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n') {
            // Increment the number of paragraphs when encountering an empty line
            num_paragraphs++;
        }
        num_lines++;
    }

    // Set the number of paragraphs in the TypingTest object
    typing_test->num_paragraphs = num_paragraphs;

    // Allocate memory for the array of paragraphs
    typing_test->paragraphs = (char**)malloc(num_paragraphs * sizeof(char*));
    if (typing_test->paragraphs == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // Reset the file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    int paragraph_index = 0;
    int line_index = 0;

    // Load the paragraphs into the TypingTest object
    while (fgets(line, sizeof(line), file)) {
        size_t line_length = strlen(line);

        // Skip empty lines
        if (line[0] == '\n') {
            continue;
        }

        // Remove the newline character from the end of the line
        if (line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
        }

        // Allocate memory for the current line and copy the content
        char* new_line = strdup(line);
        if (new_line == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            fclose(file);
            return;
        }

        // append the line to the current paragraph
        typing_test->paragraphs[paragraph_index] = (char*)realloc(typing_test->paragraphs[paragraph_index], (line_index + 1) * sizeof(char));
        if (typing_test->paragraphs[paragraph_index] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            fclose(file);
            return;
        }
        strcpy(typing_test->paragraphs[paragraph_index] + line_index, new_line);

        line_index++;

        // Check if the current line is the end of a paragraph
        if (line[0] == '\n') {
            paragraph_index++;
            line_index = 0;
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
