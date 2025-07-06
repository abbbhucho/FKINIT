#ifndef REALM_UTIL_H
#define REALM_UTIL_H

#include <krb5.h>

// Retrieves the default Kerberos realm from the krb5 context.
// Returns a heap-allocated string which must be freed using
// krb5_free_default_realm(ctx, realm).
// Returns NULL on failure.
char *get_kerberos_realm(krb5_context ctx);

#endif // REALM_UTIL_H