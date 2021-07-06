#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <stdlib.h>

// String type that isn't null character terminated
typedef struct
{
    unsigned long length;
    char *data;
} string;

void print(string s)
{
    for (int i = 0; i < s.length; i++)
    {
        putc(s.data[i], stdout);
    }
}

string get_input(void)
{
    char *line = malloc(sizeof(char) * 500);
    string res;
    if (fgets(line, 500, stdin) != NULL)
    {
        line[strcspn(line, "\n")] = 0; // trim \n
        res.length = strlen(line);
        res.data = line;
        return res;
    }
    res.length = 0;
    res.data = NULL;
    return res;
}

string vernam(string plain_text, string key)
{
    unsigned long len = plain_text.length;
    if (len > key.length)
    {
        return (string) {0, NULL};
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

void print_hex(const string string)
{
    unsigned char *p = (unsigned char *) string.data;

    for (int i = 0; i < string.length; ++i)
    {
        if (!(i % 16) && i)
        {
            printf("\n");
        }


        printf("%02x", p[i]);
        if (i != string.length - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}


string read_hex_string(const string s)
{
    unsigned long len = s.length;
    unsigned long number_of_bytes = len / 2;
    char *data = malloc(number_of_bytes);
    int bytes_written = 0;

    for (int i = 0; i < len;)
    {
        char a = s.data[i];
        if (a == ' ' || a == 0)
        {
            break;
        }
        char b = s.data[++i];

        char decoded = (char) strtol((char[]) {a, b}, NULL, 16);
        data[bytes_written] = decoded;
        if (i >= len)
        {
            break;
        }
        if (s.data[i + 1] == ' ')
        {
            i += 2; // skip the space
        }

        bytes_written++;
    }
    char *real_data = malloc(bytes_written);
    for (int i = 0; i < bytes_written; i++)
    {
        real_data[i] = data[i];
    }
    free(data);
    string result;
    result.length = bytes_written;
    result.data = real_data;
    return result;
}


int main()
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
        printf("Your encrypted text is: ");
        print_hex(res);
        free(plain_text.data);
    } else if (c == '2')
    {
        printf("Input Cipher Text:\n");
        string cipher_text = get_input();
        string decoded_cipher_text = read_hex_string(cipher_text);
        printf("Input Key Text:\n");
        key = get_input();
        res = vernam(decoded_cipher_text, key);
        printf("Decrypted text as: ");
        print(res);
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
    free(key.data);

    return main();
}

