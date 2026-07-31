#include <stdio.h>
#include <string.h>
#include "CString.h"

void test_CString_New(void);
void test_CString_From(void);
void test_CString_clone(void);
void test_CString_concat(void);
void test_CString_equals(void);
void test_CString_includes(void);

int main(void) {
    test_CString_New();
    test_CString_From();
    test_CString_clone();
    test_CString_concat();
    test_CString_equals();
    test_CString_includes();
    return 0;
}

void test_CString_New(void) {
    struct CString *string = CString_New(10);
    if (string->bytes == NULL) {
        printf("FAIL [test_CString_New]: string->bytes == NULL\n");
        return;
    }
    CString_free(string);
    printf("SUCCESS [test_CString_New]\n");
}

void test_CString_From(void) {
    struct CString *string = CString_From("0123456789");
    if (strcmp(string->bytes, "0123456789") != 0) {
        printf("FAIL [test_CString_From]: strcmp(string->bytes, \"0123456789\") != 0\n");
        return;
    }
    CString_free(string);
    printf("SUCCESS [test_CString_From]\n");
}

void test_CString_clone(void) {
    struct CString *stringA = CString_From("0123456789");
    struct CString *stringB = CString_clone(stringA);
    if (strcmp(stringA->bytes, stringB->bytes) != 0) {
        printf("FAIL [test_CString_clone]: strcmp(stringA->bytes, stringB->bytes) != 0\n");
        return;
    }
    if (stringA->length != stringB->length) {
        printf("FAIL [test_CString_clone]: stringA->length != stringB->length\n");
        return;
    }
    if (stringA == stringB) {
        printf("FAIL [test_CString_clone]: stringA == stringB\n");
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    printf("SUCCESS [test_CString_clone]\n");
}

void test_CString_concat(void) {
    struct CString *stringA = CString_From("Hello");
    struct CString *stringB = CString_From("World");
    struct CString *stringC = CString_concat(stringA, stringB);
    if (strcmp(stringC->bytes, "HelloWorld") != 0) {
        printf("FAIL [test_CString_concat]: strcmp(stringA->bytes, \"HelloWorld\") != 0\n");
        return;
    }
    if (stringC->length != (stringA->length + stringB->length)) {
        printf("FAIL [test_CString_concat]: stringC->length != (stringA->length + stringB->length)\n");
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    CString_free(stringC);
    printf("SUCCESS [test_CString_concat]\n");
}

void test_CString_equals(void) {
    struct CString *stringA = CString_From("Hello");
    struct CString *stringB = CString_From("World");
    if (CString_equals(stringA, stringB)) {
        printf("FAIL [test_CString_equals]: CString_equals(stringA, stringB)\n");
        return;
    }
    if (!CString_equals(stringA, stringA)) {
        printf("FAIL [test_CString_equals]: !CString_equals(stringA, stringA)\n");
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    printf("SUCCESS [test_CString_equals]\n");
}

void test_CString_includes(void) {
    struct CString *stringA = CString_From("Hello");
    struct CString *stringB = CString_From("ell");
    struct CString *stringC = CString_From("World");
    if (CString_includes(stringA, stringC)) {
        printf("FAIL [test_CString_includes]: CString_includes(stringA, stringC)\n");
        return;
    }
    if (!CString_includes(stringA, stringA)) {
        printf("FAIL [test_CString_includes]: !CString_includes(stringA, stringA)\n");
        return;
    }
    if (!CString_includes(stringA, stringB)) {
        printf("FAIL [test_CString_includes]: !CString_includes(stringA, stringB)\n");
        return;
    }
    if (CString_includes(stringB, stringA)) {
        printf("FAIL [test_CString_includes]: CString_includes(stringB, stringA)\n");
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    CString_free(stringC);
    printf("SUCCESS [test_CString_includes]\n");
}
