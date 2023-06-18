#include "../include/typingtest.h"
#include "../include/fetch_data.h"

int main() {
    srand((unsigned)time(NULL));

    TypingTest typing_test;
    memset(&typing_test, 0, sizeof(typing_test));
    char current_path[PATH_MAX];
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        fprintf(stderr, "Failed to get the current working directory.\n");
        return 1;
    }
    
    printf("Do you want to fetch new typing paragraph? (y/n): ");
    char choice;
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        // retrieve the API key from the environment variable
        char* api_key = getenv("API_KEY");
        if (api_key == NULL) {
            fprintf(stderr, "API_KEY environment variable is not set.\n");
            fprintf(stderr, "Please set the API_KEY environment variable and run the program again.\n");
            return 1;
        }

        printf("Fetching new data...\n");
        if (fetch_data() != 0) {
            fprintf(stderr, "Failed to fetch new data. Falling back to the previous default_paragraph.txt file.\n");
        }
    }
    
    char absolute_path[PATH_MAX];
    snprintf(absolute_path, sizeof(absolute_path), "%s/data/paragraph.txt", current_path);
    load_paragraph(&typing_test, absolute_path);

    printf("Welcome to the Typing Test!\n");
    printf("Press Enter to start the test...\n");
    getchar();

    run_typingtest(&typing_test);
    for (int i = 0; i < typing_test.num_paragraphs; i++)
        free(typing_test.paragraphs[i]);

    free(typing_test.paragraphs);
    printf("Thank you for using the Typing Test! Goodbye.\n");
    return 0;
}
