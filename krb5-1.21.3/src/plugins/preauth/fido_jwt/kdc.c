/* Minimal FIDO JWT KDC preauth plugin skeleton */
#include "k5-int.h"
#include <krb5/kdcpreauth_plugin.h>

#define FIDO_JWT_PA_TYPE 145

static krb5_preauthtype pa_types[] = { FIDO_JWT_PA_TYPE, 0 };

static krb5_error_code
fido_jwt_init(krb5_context context, krb5_kdcpreauth_moddata *moddata_out,
              const char **realmnames)
{
    *moddata_out = NULL;
    return 0;
}

static void
fido_jwt_fini(krb5_context context, krb5_kdcpreauth_moddata moddata)
{
}

static void
fido_jwt_edata(krb5_context context, krb5_kdc_req *req, krb5_kdcpreauth_data *rock,
               krb5_kdcpreauth_callbacks cb, krb5_preauthtype pa_type,
               krb5_kdcpreauth_edata_respond_fn respond, void *arg)
{
    respond(arg, 0, NULL, NULL, NULL);
}

static void
fido_jwt_verify(krb5_context context, krb5_data *req_pkt, krb5_kdc_req *request,
                krb5_kdcpreauth_data *rock, krb5_kdcpreauth_callbacks cb,
                krb5_kdcpreauth_moddata moddata, krb5_preauthtype pa_type,
                krb5_pa_data *pa_data, krb5_kdcpreauth_verify_respond_fn respond,
                void *arg)
{
    /* TODO: verify signed JWT token here */
    respond(arg, 0, NULL, NULL, NULL);
}

krb5_error_code
kdcpreauth_fido_jwt_initvt(krb5_context context, int maj_ver, int min_ver,
                           krb5_plugin_vtable vtable)
{
    krb5_kdcpreauth_vtable vt;

    if (maj_ver != 1)
        return KRB5_PLUGIN_VER_NOTSUPP;
    vt = (krb5_kdcpreauth_vtable)vtable;
    vt->name = "fido_jwt";
    vt->pa_type_list = pa_types;
    vt->init = fido_jwt_init;
    vt->fini = fido_jwt_fini;
    vt->edata = fido_jwt_edata;
    vt->verify = fido_jwt_verify;
    return 0;
}