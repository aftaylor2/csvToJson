#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csvToJSON.h"
#include <curl/curl.h>

#define AUTH_HEADER_SIZE 512

// Function to make an HTTPS POST request with JSON data
void post_json(const char *url, const char *json_data, const char *token) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        
        if (token != NULL) {
            char auth_header[AUTH_HEADER_SIZE];
            snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", token);
            headers = curl_slist_append(headers, auth_header);
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Usage: %s <csv_file_path> [<api_endpoint>] [<bearer_token>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *csv_file_path = argv[1];
    const char *api_endpoint = (argc >= 3) ? argv[2] : NULL;
    const char *bearer_token = (argc == 4) ? argv[3] : NULL;

    char *json_data = csv_to_json(csv_file_path);
    printf("JSON Data: %s\n", json_data);

    if (api_endpoint != NULL && strlen(api_endpoint) > 0) {
        post_json(api_endpoint, json_data, bearer_token);
    }

    free(json_data);

    return EXIT_SUCCESS;
}
