#include "samples/prototypes.h"
#include <string.h>

#include <stdio.h>


const char *get_env_value(const char *envp[], const char *key) {
    int keyLength;    //this will hold the length of any given string

    for (int i = 0; envp[i] != NULL; i++) {
        //create a string to hold just the key value
        keyLength = strcspn(envp[i], "=");
        char chars[keyLength + 1];
        strncpy(chars, envp[i], keyLength);
        char *keyName = chars;
        keyName[keyLength] = '\0';

        //if key and keyName have the same value
        if (!strcmp(key, keyName)) {
            //return a pointer to the first character after the "="
            return strstr(envp[i], "=") + 1;
        }
    }
    return NULL;
}


bool scan_token(const char **p_input, const char *delimiters, char buf[], size_t buflen) {
    *p_input += strspn(*p_input, delimiters);    //advance past any leading delimiters

    //if we haven't reached the null terminator we can do stuff
    if (**p_input != '\0') {
        int toklen = strcspn(*p_input, delimiters);    //represents the length of the token
        toklen = (toklen < buflen - 1) ? toklen : buflen - 1;    //if the token is too long, cut it to just buflen - 1

        //copy in the string to buf and then cap it off with a null terminator
        strncpy(buf, *p_input, toklen);
        buf[toklen] = '\0';
        
        *p_input += toklen;    //advance the pointer to the next delimiter
        return true;
        
    //if we have reached the null terminator we can't tokenize anything
    } else {
        return false;
    }
}
