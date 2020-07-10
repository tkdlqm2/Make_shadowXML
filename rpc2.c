/*
 *
 *  2020 07 10
 *  Created by Hong Joon
 *
 */

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <stdio.h>

void rpc_getblockchaininfo(char* IP) {
    printf("------------------------------------------- >>>>>> getblockchaininfo start \n\n");

    const char *data ="{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getblockchaininfo\", \"params\": [] }";
    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;

    if (curl) {

        headers = curl_slist_append(headers, "content-type: text/plain;");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_URL, IP);


        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(data));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_USERPWD,
                         "a:1234");

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

        curl_easy_perform(curl);
    }
}


int main(int args, char* argv[]) {

    char** IP_array;
    int row = atoi(argv[1]);
    int j = 1;

    IP_array = malloc(sizeof(char*) * row);

    for(int i=0; i<row; i++) {
        IP_array[i] = malloc(sizeof(char) * 20);
    }
    for(int i=0; i<row; i++) {
        int rport = 10000 + j;
        char lastNumber[6] = "\0";
        char IP_format[20] = "11.0.0.";
        char lastNumber_ip[2] = "\0";
        sprintf(lastNumber, "%d", rport);
        sprintf(lastNumber_ip, "%d", j);
        strcat(IP_format, lastNumber_ip);
        strcat(IP_format,":");
        strcat(IP_format, lastNumber);
        strcpy(IP_array[i], IP_format);
        j ++;
    }
    for(int i=0; i<row; i++){
        rpc_getblockchaininfo(IP_array[i]);
    }
}