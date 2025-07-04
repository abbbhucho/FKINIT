#include "fidojwt.h"
#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>
#include <time.h>

static const char b64url_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

/**
produces RFC 7515-compliant base64url strings, safe for JWT or CBOR headers.
*/
void base64url_encode(const uint8_t *in, size_t in_len, char *out, size_t out_max) {
    size_t i, j;
    uint32_t val;
    char *p = out;

    for (i = 0; i < in_len;) {
        val = in[i++] << 16;
        if (i < in_len) val |= in[i++] << 8;
        if (i < in_len) val |= in[i++];

        for (j = 0; j < 4 && (p - out) < out_max - 1; j++) {
            if ((j * 6) > (in_len * 8)) break;
            *p++ = b64url_table[(val >> (18 - 6 * j)) & 0x3F];
        }
    }

    *p = '\0';  // Null-terminate

    // Remove any trailing '=' padding (not used in base64url)
    while (p > out && *(p - 1) == '=') *(--p) = '\0';
}

void get_iso8601_timestamp(char *buf, size_t len) {
    time_t now = time(NULL);
    struct tm *tm_info = gmtime(&now);
    strftime(buf, len, "%Y-%m-%dT%H:%M:%SZ", tm_info);
}

/*
void base64url_encode(const uint8_t *in, size_t in_len,
                      char *out, size_t out_max) {
    // ❗#TODO: Replace with real base64url logic later
    // # TODO OVER: DONE ABOVE
    for (size_t i = 0; i < in_len && (i * 2 + 1) < out_max; i++)
        sprintf(out + i * 2, "%02x", in[i]);
    out[out_max - 1] = '\0';
}
*/

/**
to sign your JWT-style JSON payload using a FIDO2 device,
you first need to compute its SHA-256 hash (the challenge passed into libfido2's assertion).

# Done here using only standard C and OpenSSL(is there in most linux envs)
*/

int sha256_hash_json(const char *json, uint8_t out_digest[32]) {
    if (!json || !out_digest)
        return -1;

    SHA256_CTX ctx;
    if (SHA256_Init(&ctx) != 1)
        return -1;

    if (SHA256_Update(&ctx, json, strlen(json)) != 1)
        return -1;

    if (SHA256_Final(out_digest, &ctx) != 1)
        return -1;

    return 0;
}


int build_jwt_payload(char *out_json, size_t out_len,
                      const char *principal,
                      const uint8_t *cred_id, size_t cred_len,
                      const uint8_t *challenge, size_t chal_len) {
    fido_jwt_payload token;
    strncpy(token.sub, principal, sizeof(token.sub));
    base64url_encode(cred_id, cred_len, token.pubkey_id, sizeof(token.pubkey_id));
    base64url_encode(challenge, chal_len, token.challenge, sizeof(token.challenge));
    get_iso8601_timestamp(token.timestamp, sizeof(token.timestamp));

    int written = snprintf(out_json, out_len,
        "{ \"sub\": \"%s\", \"pubkey_id\": \"%s\", \"timestamp\": \"%s\", \"challenge\": \"%s\" }",
        token.sub, token.pubkey_id, token.timestamp, token.challenge);

    return (written > 0 && written < out_len) ? 0 : -1;
}