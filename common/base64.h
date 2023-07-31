//
// Created by Alexander Wood on 10/05/2022.
//

#include <stddef.h>

#ifndef CIPHERS_BASE64_H
#define CIPHERS_BASE64_H

#endif //CIPHERS_BASE64_H

// Source: https://nachtimwald.com/2017/11/18/base64-encode-and-decode-in-c/


char *b64_encode(const unsigned char *in, size_t len);

int b64_decode(const char *in, unsigned char *out, size_t outlen);