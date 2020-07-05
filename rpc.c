/*
 *
 *  2020 06 30
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

void getWalletaddress(char* wallet, char* string_info) {
    for (int i = 11; i < 46; i++) { // 46
        wallet[i - 11] = string_info[i];
    }
}

void rpc_generatetoaddress(char* IP, char* ID, char* wallet) {

    printf("------------------------------------------------------------- start generatetoaddress \n\n");
    char first[100] = "{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"generatetoaddress\", ";
    char input[250];
    char second[30] = "\"params\": [1, ";
    char last[50];
    strcpy(input, first);
    strcat(input, second);
    sprintf(last, "\"%s\"", wallet);
    strcat(input, last);
    strcat(input, "]}");
    printf("%s \n", input);

    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;


    if (curl) {

        headers = curl_slist_append(headers, "content-type: text/plain;");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_URL, IP);


        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(input));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, input);

        curl_easy_setopt(curl, CURLOPT_USERPWD,
                         ID);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

        curl_easy_perform(curl);
    }
}

void rpc_getblockchaininfo(char* IP, char* ID){

    printf("----------------- start getblockchaininfo \n\n");
    printf("%s \n", IP);
    printf("%s \n", ID);

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
                         ID);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

        curl_easy_perform(curl);
    }
}

char* rpc_getnewaddress(char* IP, char* ID, char* wallet){

    printf("------------------------------------------------------------- start getnewaddress \n\n");
    printf("IP : %s \n", IP);
    printf("ID : %s \n", ID);
    printf("wallet : %s \n", wallet);
    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;

    if (curl) {
        struct string s;
        init_string(&s);
        const char *getnewaddress =
                "{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getnewaddress\", \"params\": [] }";

        headers = curl_slist_append(headers, "content-type: text/plain;");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_URL, IP);


        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(getnewaddress));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, getnewaddress);

        curl_easy_setopt(curl, CURLOPT_USERPWD,
                         ID);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

        curl_easy_perform(curl);
        getWalletaddress(wallet, s.ptr);
        free(s.ptr);
    }
}
void rpc_getpeerinfo(char* IP, char* ID){

    const char *data ="{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getpeerinfo\", \"params\": [] }";
    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;

    if (curl) {

        headers = curl_slist_append(headers, "content-type: text/plain;");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_URL, IP);


        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(data));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_USERPWD,
                         ID);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

        curl_easy_perform(curl);
    }
}

void rpc_addnode(char* IP, char* ID, char* neigborNode) {

    char first[100] = "{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"addnode\", ";
    char input[250];
    char second[30] = "\"params\": [";

    char last[50];
    char onetry[10] = "\0";

    strcpy(input, first);
    strcat(input, second);
    sprintf(last, "\"%s\"", neigborNode);
    strcat(input, last);
    sprintf(onetry,"\"%s\"", "onetry");
    strcat(input, ", ");
    strcat(input, onetry);
    strcat(input, "]}");

    printf("%s \n", input);

    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;

    if (curl) {

        headers = curl_slist_append(headers, "content-type: text/plain;");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_URL, IP);


        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(input));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, input);

        curl_easy_setopt(curl, CURLOPT_USERPWD,
                         ID);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

        curl_easy_perform(curl);
    }
}

int main(int args, char* argv[] )
{
    char wallet_address[100]="\0";
    char port_number[5] = "1111";
    // -rpcport = 1000 + i
    // -port = 111 + i

    int col = 5;
    int row = atoi(argv[1]);
    char rport[5] = "1000";
    char IP_format[15] = "11.0.0.1:";
    char admin[10] = "a:1234";


    int** rpc_array = malloc(sizeof(int *) * row);
    int** port_array = malloc(sizeof(int *) * row);
    char** wallet_array = malloc(sizeof(char *) * row);

    for(int i=0; i<row; i++){
        rpc_array[i] = malloc(sizeof(int *) * col);
        port_array[i] = malloc(sizeof(int *) * col);
        wallet_array[i] = malloc(sizeof(char *) * 100);
    }
    printf("%s \n", port_number);
    for(int i=0; i<row; i++) {
        strcpy(rpc_array[i], rport);
        strcpy(port_array[i], port_number);
    }

    // ------------------------------------------------------
    // TODO : add atoi logic  (rpc port, port number, IP 4class setting)
    // 나중에 피어 맵핑 설정 하기.
    // ------------------------------------------------------

    for(int i=0; i<row; i++) {
        printf("---------------------------------------------------------------------------------------------------- bleep%d rpc start\n\n",i);
        char target_address[15];
        strcpy(target_address,strcat(IP_format,rpc_array[i]));

        rpc_getnewaddress(target_address, admin, wallet_array[i]);
        rpc_addnode(target_address, admin, strcat(IP_format,rpc_array[i+1]));
        rpc_generatetoaddress(target_address, admin, wallet_array[i]);
    }

    // for(int i=0; i<row; i++){
    //     strcpy(rpc_array[i], strcat("1000",itoa(j)));
    //     printf("%s \n", rpc_array[i]);
    //     j ++;
    // }

//    rpc_addnode(IP, rpc_ID, node);
//    rpc_generatetoaddress(wallet_address, _IP, rpc_ID);

    // get wallet address
    // rpc_getnewaddress(argv[1], argv[2], wallet_address);

    // start mining
    // rpc_generatetoaddress(argv[1], argv[2], wallet_address);


    // check result
    // rpc_getblockchaininfo(argv[1], argv[2]);

//    rpc_getpeerinfo(IP, rpc_ID);
}