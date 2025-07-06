// realm_util.c
#include "realm_util.h"
#include <stdio.h>

char *get_kerberos_realm(krb5_context ctx) {
    char *realm = NULL;

    if (!ctx) {
        fprintf(stderr, "Error: krb5_context is NULL in get_kerberos_realm().\n");
        return NULL;
    }

    krb5_error_code ret = krb5_get_default_realm(ctx, &realm);
    if (ret != 0) {
        const char *err_msg = krb5_get_error_message(ctx, ret);
        fprintf(stderr, "Error fetching default realm: %s\n", err_msg);
        krb5_free_error_message(ctx, err_msg);
        return NULL;
    }

    return realm;
}