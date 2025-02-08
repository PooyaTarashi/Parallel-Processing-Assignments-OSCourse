#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

void download_file(const char *url, const char *filename) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("error occurred!"); 
        // return 0;
        exit(0);
    }

    FILE *fp = fopen(filename, "wb");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");

    char url[1024];
    char filename[256];
    int downCnt = 0;
    while (fgets(url, sizeof(url), file))
    {
        url[strcspn(url, "\n")] = 0;
        sprintf(filename,"%d", ++downCnt);
        strcat(filename, ".jpg");

        int pid = fork();
        if (pid == 0)
        {
            download_file(url, filename);
            exit(0);
        }
    }

    fclose(file);

    while (wait(NULL) > 0) continue;

    printf("Done!\n");
    return 0;
}
