#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "CString.h"

struct CString *CString_New(size_t length) {
    struct CString *string;
    string = malloc(sizeof(struct CString));
    if (string == NULL) return NULL;
    string->bytes = malloc(sizeof(char) * length + 1);
    if (string->bytes == NULL) {
        free(string);
        return NULL;
    }
    string->length = 0;
    string->bytes[0] = '\0';
    return string;
}

struct CString *CString_From(char *str) {
    size_t length = strlen(str);
    struct CString *string = CString_New(length);
    if (string == NULL) return NULL;
    string->length = length;
    memcpy(string->bytes, str, length + 1);
    return string;
}

struct CString *CString_clone(struct CString *this) {
    return CString_From(this->bytes);
}

struct CString *CString_concat(struct CString *this, struct CString *string) {
    struct CString *concatenated = CString_New(this->length + string->length);
    if (concatenated == NULL) return NULL;
    strcat(concatenated->bytes, this->bytes);
    strcat(concatenated->bytes, string->bytes);
    concatenated->length = this->length + string->length;
    return concatenated;
}

struct CString *CString_substring(struct CString *this, size_t start, size_t end) {
    struct CString *substring;
    if (start > end) return NULL;
    if (end > this->length) return NULL;
    substring = CString_New(end - start);
    if (substring == NULL) return NULL;
    strncpy(substring->bytes, &this->bytes[start], end - start);
    substring->length = end - start;
    substring->bytes[substring->length] = '\0';
    return substring;
}

struct CString *CString_replaceAll(struct CString *this, struct CString *pattern, struct CString *replacement) {
    struct CString *replaced;
    size_t replacementsCount = 0;
    size_t thisIndex = 0;
    size_t patternIndex = 0;
    size_t replacedIndex = 0;
    size_t replacementIndex = 0;
    char *substring;

    if (this->length < pattern->length) return NULL;
    for (thisIndex = 0; thisIndex < this->length; thisIndex++) {
        substring = strstr(&this->bytes[thisIndex], pattern->bytes);
        if (substring == NULL) break;
        replacementsCount++;
        thisIndex = (substring - this->bytes) + pattern->length;
    }
    replaced = CString_New(replacementsCount * (replacement->length - pattern->length) + this->length);
    if (replaced == NULL) return NULL;
    replaced->length = replacementsCount * (replacement->length - pattern->length) + this->length;
    for (thisIndex = 0; thisIndex < this->length; thisIndex++) {
        replaced->bytes[replacedIndex] = this->bytes[thisIndex];
        replacedIndex++;
        if (this->bytes[thisIndex] == pattern->bytes[patternIndex]) {
            if (patternIndex == pattern->length - 1) {
                replacedIndex -= pattern->length;
                for (replacementIndex = 0; replacementIndex < replacement->length; replacementIndex++) {
                    replaced->bytes[replacedIndex] = replacement->bytes[replacementIndex];
                    replacedIndex++;
                }
                patternIndex = 0;
            } else {
                patternIndex++;
            }
        } else {
            patternIndex = 0;
        }
    }
    return replaced;
}

int CString_equals(struct CString *this, struct CString *string) {
    int cmpResult = strcmp(this->bytes, string->bytes);
    return cmpResult == 0 ? 1 : 0;
}

int CString_includes(struct CString *this, struct CString *string) {
    char *firstCharInString = strstr(this->bytes, string->bytes);
    return firstCharInString == NULL ? 0 : 1;
}

void CString_free(struct CString *this) {
    free(this->bytes);
    free(this);
}
