
#include <krb5.h>
#include <krb5/clpreauth_plugin.h>
#include <stdio.h>
#include "k5-int.h"
#include "fidojwt.h"

#define PA_FIDO_JWT 145

#define FIDO_JWT_PA_TYPE 145

static krb5_preauthtype pa_types[] = { FIDO_JWT_PA_TYPE, 0 };

static krb5_error_code
fido_jwt_init(krb5_context context, krb5_clpreauth_moddata *moddata_out)
{
    *moddata_out = NULL;
    return 0;
}

static void
fido_jwt_fini(krb5_context context, krb5_clpreauth_moddata moddata)
{
}

static krb5_error_code
fido_jwt_process(krb5_context context, krb5_clpreauth_moddata moddata,
                 krb5_clpreauth_modreq modreq, krb5_get_init_creds_opt *opt,
                 krb5_clpreauth_callbacks cb, krb5_clpreauth_rock rock,
                 krb5_kdc_req *req, krb5_data *pa_data,
                 krb5_data *req_body, krb5_data *prev_req,
                 krb5_pa_data **out_pa_data)
{
    /* TODO: build and sign JWT token here */
    *out_pa_data = NULL;
    return 0;
}

krb5_error_code
clpreauth_fido_jwt_initvt(krb5_context context, int maj_ver, int min_ver,
                          krb5_plugin_vtable vtable)
{
    krb5_clpreauth_vtable vt;

    if (maj_ver != 1)
        return KRB5_PLUGIN_VER_NOTSUPP;
    vt = (krb5_clpreauth_vtable)vtable;
    vt->name = "fido_jwt";
    vt->pa_type_list = pa_types;
    vt->init = fido_jwt_init;
    vt->fini = fido_jwt_fini;
    vt->process = fido_jwt_process;
    return 0;
}

/*
static krb5_error_code
fidojwt_client_process(krb5_context context,
                       krb5_clpreauth_moddata moddata,
                       krb5_clpreauth_modreq modreq,
                       krb5_get_init_creds_opt *opt,
                       krb5_clpreauth_callbacks cb,
                       krb5_clpreauth_rock rock,
                       krb5_kdc_req *request,
                       krb5_data *encoded_request_body,
                       krb5_data *encoded_previous_reply,
                       krb5_pa_data *pa_data,
                       krb5_prompter_fct prompter,
                       void *prompter_data,
                       krb5_pa_data ***out_pa_data)
{
    printf("[FIDOJWT-Client] fidojwt_client_process() called\n");
    return KRB5KDC_ERR_PREAUTH_FAILED; // Just a stub, fails intentionally
}

krb5_error_code
clpreauth_fidojwt_initvt(krb5_context context, int maj_ver, int min_ver,
                         krb5_plugin_vtable vtable)
{
    krb5_clpreauth_vtable vt;

    if (maj_ver != 1)
        return KRB5_PLUGIN_VER_NOTSUPP;

    vt = (krb5_clpreauth_vtable)vtable;
    vt->name = "fidojwt";
    vt->pa_type_list = (krb5_preauthtype[]){ PA_FIDO_JWT, 0 };
    vt->client_process = fidojwt_client_process;

    printf("[FIDOJWT-Client] clpreauth_fidojwt_initvt() loaded\n");

    return 0;
}
*/