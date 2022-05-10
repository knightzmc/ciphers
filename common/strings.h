//
// Created by alex on 7/8/21.
//

#include <stdbool.h>

#ifndef CIPHERS_STRINGS_H
#define CIPHERS_STRINGS_H

#endif //CIPHERS_STRINGS_H

// String type that isn't null character terminated
typedef struct
{
    unsigned long length;
    char *data;
} string;

string empty_string();

void print(string s);

string get_input(void);

bool is_empty(string s);