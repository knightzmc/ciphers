#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/strings.h"
#include "../common/base64.h"


string vernam(const string plain_text, const string key)
{
    unsigned long len = plain_text.length;
    if (len > key.length)
    {
        return empty_string();
    }
    char *cipher_text = malloc(len);
    for (int i = 0; i < len; i++)
    {
        int plain_char = (int) plain_text.data[i];
        int key_char = (int) key.data[i];
        int cipher = plain_char ^ key_char;
        cipher_text[i] = (char) cipher;
    }
    string result;
    result.length = len;
    result.data = cipher_text;
    return result;
}

int main()
{
    while (1)
    {
        printf("Input Mode:\n1. Encrypt\n2. Decrypt\n3. Quit\n");

        string input = get_input();
        char c = input.data[0];
        free(input.data);

        string key;
        string res;
        if (c == '1')
        {
            printf("Input Plain Text:\n");
            string plain_text = get_input();
            printf("Input Key Text:\n");
            key = get_input();

            res = vernam(plain_text, key);
            if (is_empty(res))
            {
                printf("Error: Password too short.");
            } else
            {
                printf("Your encrypted text is: ");
                char *enc = b64_encode((const unsigned char *) res.data, res.length);
                printf("%s", enc);
                free(enc);
            }
            printf("\n");
            free(plain_text.data);
        } else if (c == '2')
        {
            printf("Input Cipher Text:\n");
            string cipher_text = get_input();
            size_t out_len = cipher_text.length;
            printf("%ul", out_len);
            char *out = malloc(out_len);
            if (!b64_decode(cipher_text.data, (unsigned char *) out, out_len))
            {
                printf("Could not decode base64 string.\n");
                return 1;
            }
            string decoded_cipher_text = from_std_string(out);
            free(out);
            printf("Input Key Text:\n");
            key = get_input();
            res = vernam(decoded_cipher_text, key);
            if (is_empty(res))
            {
                printf("Error: Password too short.");
            } else
            {
                printf("Decrypted text as: ");
                print(res);
            }
            printf("\n");
            free(cipher_text.data);
            free(decoded_cipher_text.data);

        } else if (c == '3')
        {
            return 0;
        } else
        {
            printf("Invalid input.\n");
            return 1;
        }

        free(key.data);
        free(res.data);
    }
}

