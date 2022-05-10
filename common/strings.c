//
// Created by alex on 7/8/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

void print(const string s)
{
    for (int i = 0; i < s.length; i++)
    {
        putc(s.data[i], stdout);
    }
}


string get_input(void)
{
    int max_length = 500;
    char *line = malloc(max_length);
    string res;
    if (fgets(line, max_length, stdin) != NULL)
    {
        line[strcspn(line, "\n")] = 0; // trim \n
        res.length = strlen(line);
        res.data = line;
        return res;
    }
    return empty_string();
}

string empty_string()
{
    return (string) {0, NULL};
}

bool is_empty(string s) {
    return s.data == NULL || s.length == 0;
}