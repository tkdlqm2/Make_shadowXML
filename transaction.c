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


struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}

void getTxHash(char* tx, char* string_info) {
    for (int i = 11; i < 46; i++) { // 46
        wallet[i - 11] = string_info[i];
    }
}

void rpc_sendtoaddress_doubleSpending(char* IP, char* wallet) {

    printf("------------------------------------------------------------- start sendtoaddress \n\n");
    char first[100] = "{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"sendtoaddress\", ";
    char input[250];
    char second[30] = "\"params\": [";
    char last[50];
    char tx[50] = "\0";

    strcpy(input, first);
    strcat(input, second);
    sprintf(last, "\"%s\"", wallet);
    strcat(input, last);
    strcat(input, "50 ]}");
    printf("%s \n", input);

    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;

    if (curl) {
        struct string s;
        init_string(&s);
        
        headers = curl_slist_append(headers, "content-type: text/plain;");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_URL, IP);


        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(input));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, input);

        curl_easy_setopt(curl, CURLOPT_USERPWD,
                         "a:1234");

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

        curl_easy_perform(curl);
        getTxHash(tx, s.ptr);
        free(s.ptr);
    }

    printf("------------------------------------------------------------- start createrawtransaction \n\n");

    char first[100] = "{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"createrawtransaction\", ";
    char input[250];
    char second[30] = "\"params\": [";
    char last[50];
    char tx[50] = "\0";
}



void rpc_sendtoaddress(char* IP, char* wallet) {

    printf("------------------------------------------------------------- start sendtoaddress \n\n");
    char first[100] = "{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"sendtoaddress\", ";
    char input[250];
    char second[30] = "\"params\": [";
    char last[50];
    strcpy(input, first);
    strcat(input, second);
    sprintf(last, "\"%s\"", wallet);
    strcat(input, last);
    strcat(input, "0.001 ]}");
    printf("%s \n", input);

    // CURL *curl = curl_easy_init();
    // struct curl_slist *headers = NULL;


    // if (curl) {

    //     headers = curl_slist_append(headers, "content-type: text/plain;");
    //     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //     curl_easy_setopt(curl, CURLOPT_URL, IP);


    //     curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(input));
    //     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, input);

    //     curl_easy_setopt(curl, CURLOPT_USERPWD,
    //                      "a:1234");

    //     curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

    //     curl_easy_perform(curl);
    // }
}

void rpc_getwalletinfo(char* IP, char* wallet) {

    printf("------------------------------------------------------------- start getwalletinfo \n\n");

    printf("%s \n", IP);
    printf("%s \n", wallet);

    // CURL *curl = curl_easy_init();
    // struct curl_slist *headers = NULL;

    // if (curl) {
    //     struct string s;
    //     init_string(&s);
    //     const char *getwalletinfo =
    //             "{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getwalletinfo\", \"params\": [] }";

    //     headers = curl_slist_append(headers, "content-type: text/plain;");
    //     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    //     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    //     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //     curl_easy_setopt(curl, CURLOPT_URL, IP);


    //     curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(getwalletinfo));
    //     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, getwalletinfo);

    //     curl_easy_setopt(curl, CURLOPT_USERPWD,
    //                      ID);

    //     curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

    //     curl_easy_perform(curl);
    //     // getWalletaddress(wallet, s.ptr);
    //     free(s.ptr);
    // }
}

int main(int args, char* argv[]) {

    char** IP_array;
    char** target_IP_array;
    char** target_wallet_array;

    int row = atoi(argv[1]);
    int total_count = atoi(argv[2]);
    int target_count = total_count - row;
    int j = 1;

    IP_array = malloc(sizeof(char*) * row);
    target_wallet_array = malloc(sizeof(char *) * row);
    target_IP_array = malloc(sizeof(char *) * target_count);

    for(int i=0; i<row; i++) {
        IP_array[i] = malloc(sizeof(char) * 20);
        wallet_array[i] = malloc(sizeof(char) * 50);
    }

    for(int i=0; i<target_count; i++) {
        target_IP_array[i] = malloc(sizeof(char) * 20);
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
    j = 0;

    for(int i=target_count; i<total_count; i++) {
        int rport = 10000 + i;
        char lastNumber[6] = "\0";
        char IP_format[20] = "11.0.0.";
        char lastNumber_ip[2] = "\0";
        sprintf(lastNumber, "%d", rport);
        sprintf(lastNumber_ip, "%d", i);
        strcat(IP_format, lastNumber_ip);
        strcat(IP_format,":");
        strcat(IP_format, lastNumber);
        strcpy(target_IP_array[j], IP_format);
        j ++;
    }

    for(int i=0; i<target_count; i++){
        rpc_getwalletinfo(target_IP_array[i], target_wallet_array[i]);
    }

    while(1){
        rpc_sendtoaddress(IP_array[i], target_wallet_array[j]);
        j++;
        i++;
        // 번갈아 가면서 비트코인 송금
        if(j == target_count) {
            j = 0;
        }
    }
}