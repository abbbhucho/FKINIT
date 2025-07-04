#ifndef FIDO_JWT_H
#define FIDO_JWT_H

#include <stddef.h>
#include <stdint.h>

#define MAX_ID_LEN 256
#define MAX_STR_LEN 128
#define MAX_JSON_SIZE 1024

typedef struct {
    char sub[MAX_STR_LEN];             // client@REALM
    char pubkey_id[MAX_ID_LEN];       // Base64url-encoded cred ID
    char timestamp[MAX_STR_LEN];      // ISO-8601 string
    char challenge[MAX_ID_LEN];       // Base64url-encoded nonce
} fido_jwt_payload;

void get_iso8601_timestamp(char *buf, size_t len);

void base64url_encode(const uint8_t *in, size_t in_len,
                      char *out, size_t out_max);

// Builds a JSON object string and returns 0 on success
int build_jwt_payload(char *out_json, size_t out_len,
                      const char *principal,
                      const uint8_t *cred_id, size_t cred_len,
                      const uint8_t *challenge, size_t chal_len);

// declared to SHA-256 hash the JSON before signing
int sha256_hash_json(const char *json, uint8_t out_digest[32]);

#endif