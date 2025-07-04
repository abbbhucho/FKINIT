#ifndef FIDOJWT_TOKEN_H
#define FIDOJWT_TOKEN_H

#define MAX_ID_LEN 256
#define MAX_STR_LEN 128
#define MAX_JSON_SIZE 1024

typedef struct {
    char sub[MAX_STR_LEN];             // client@REALM
    char pubkey_id[MAX_ID_LEN];       // Base64url-encoded cred ID
    char timestamp[MAX_STR_LEN];      // ISO-8601 string
    char challenge[MAX_ID_LEN];       // Base64url-encoded nonce
} fido_jwt_payload;


#endif //FIDOJWT_TOKEN_H
