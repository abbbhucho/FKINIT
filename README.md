## 🔐 FIDO2-Kerberos Pre-Authentication Plugin (fido_jwt)

### Overview

This project implements a Kerberos pre-authentication plugin that uses FIDO2 security keys (e.g., YubiKey, SoloKey) as a replacement for PKINIT certificates.

Instead of relying on a traditional X.509 PKI infrastructure, this plugin introduces a JWT/CBOR-based token, signed by the client’s FIDO2 private key, to authenticate with the Kerberos Key Distribution Center (KDC).

This enables a passwordless authentication flow while maintaining Kerberos’ strong session-based authentication model.

###  Features

-  FIDO2 integration using libfido2
-  JWT/CBOR-like tokens as lightweight certificate alternatives
-  Kerberos Preauth Plugin (fido_jwt) in src/plugins/preauth/
-  Secure challenge–response authentication with YubiKey/other FIDO2 devices

###  Compatible with standard Kerberos 5 setup (tested with MIT Kerberos)

###  Project Structure
```
src/plugins/preauth/fido_jwt/
│── clnt.c            # Client-side plugin logic
│── kdc.c             # KDC-side plugin logic
│── fidojwt.h         # Shared header definitions
│── fido_jwt.exports  # Export symbols
│── deps              # Dependency includes
│── Makefile.in       # Build rules
```

###  Authentication Flow

1. Client runs kinit → plugin prompts for FIDO2 key insertion, PIN, and touch.
2. Client plugin generates a JSON/CBOR payload (principal, challenge, timestamp, rp_id).
3. Payload is signed by FIDO2 private key → produces ECDSA signature.
4. Client sends {payload, signature, cred_id} inside AS-REQ.
5. KDC plugin (kdc.c) verifies signature using the stored public key.
6. If valid → TGT issued (AS-REP).
7. Client uses TGT to request service tickets (normal Kerberos flow).

###  Installation & Build

> Prerequisites

 - MIT Kerberos (built from source with plugin support)
 - libfido2
 - C compiler + GNU make

### Build Steps
```bash
cd src/plugins/preauth/fido_jwt
make
make install
```

Enable the plugin in your krb5.conf:

```ini
[plugins]
    preauth = {
        module = fido_jwt:/usr/local/lib/krb5/plugins/preauth/fido_jwt.so
    }
```

###  Registration Flow

Before a client can authenticate, its FIDO2 public key + credential ID must be registered with the KDC.

Example:
```bash
./register_fido_user --principal alice@KERBEROS.LOCAL \
    --cred-id AbCdEf123... \
    --pubkey pubkey.pem
```

###  Roadmap

- Basic plugin skeleton (clnt.c, kdc.c)
- JWT payload signing & verification
- CBOR token support
- GUI for PIN/touch prompt (GTK+4)
- Database-backed credential storage

###  References

1. RFC 4120 - Kerberos V5
2. RFC 4556 - PKINIT
3. FIDO2: WebAuthn & CTAP
4. MIT Kerberos Plugin Docs

----

👨‍💻 Author

Developed by Anirban Bhattacharya under the guidance of Dr Divyashikha Sethia as part of a research-driven project on modern passwordless Kerberos authentication.
