#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define TARGET_WORD_COUNT 350

typedef struct {
    char* data;
    size_t size;
} ResponseData;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    ResponseData* response = (ResponseData*)userdata;

    size_t data_size = size * nmemb;
    char* new_data = realloc(response->data, response->size + data_size + 1);
    if (new_data == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    response->data = new_data;
    memcpy(&(response->data[response->size]), ptr, data_size);
    response->size += data_size;
    response->data[response->size] = '\0';

    return data_size;
}

int main() {
    CURL *curl = curl_easy_init();
    CURLcode res = CURLE_OK;
    char *url = "https://random-word-by-api-ninjas.p.rapidapi.com/v1/randomword?type=verb";
    FILE *file = fopen("../data/paragraph.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Failed to open the file.\n");
        return 1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // set the request URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // set the custom headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-RapidAPI-Key: 5df4435f4dmsh807f019b58e885cp193981jsn2e05fa26930f");
        headers = curl_slist_append(headers, "X-RapidAPI-Host: random-word-by-api-ninjas.p.rapidapi.com");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // set the write callback function to receive the data
        ResponseData response;
        response.data = NULL;
        response.size = 0;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // make the request and fetch the data
        int word_count = 0;
        while (word_count < TARGET_WORD_COUNT) {
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                break;
            }

            // extract the word from the response
            char* word = strstr(response.data, "\"word\": ");
            if (word != NULL) {
                word += 9; // skip the initial characters
                char* end_quote = strchr(word, '\"');
                if (end_quote != NULL) {
                    *end_quote = '\0'; // replace the closing quote with a null character
                    fprintf(file, "%s ", word);
                    word_count++;
                }
            }

            free(response.data);
            response.data = NULL;
            response.size = 0;
        }
    }

    fclose(file);

    // check if fetch_data was successful
    if (res != CURLE_OK) {
        fprintf(stderr, "Fetch data failed. Falling back to the previous default_paragraph.txt file.\n");
        FILE *default_file = fopen("../data/default_paragraph.txt", "r");
        if (default_file == NULL) {
            fprintf(stderr, "Failed to open the default_paragraph.txt file.\n");
            return 1;
        }

        int ch;
        while ((ch = fgetc(default_file)) != EOF) {
            fputc(ch, file);
        }

        fclose(default_file);
    }

    fclose(file);

    // cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
