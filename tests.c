#include <stdio.h>
#include <string.h>
#include "CString.h"

void test_CString_New(void);
void test_CString_From(void);
void test_CString_clone(void);
void test_CString_concat(void);
void test_CString_equals(void);
void test_CString_includes(void);
void test_CString_substring(void);

int main(void) {
    test_CString_New();
    test_CString_From();
    test_CString_clone();
    test_CString_concat();
    test_CString_equals();
    test_CString_includes();
    test_CString_substring();
    return 0;
}

void test_CString_New(void) {
    struct CString *string = CString_New(10);
    if (string == NULL) {
        printf("FAIL [test_CString_New]: CString_New(10) == NULL\n");
        return;
    }
    if (string->bytes == NULL) {
        printf("FAIL [test_CString_New]: string->bytes == NULL\n");
        return;
    }
    CString_free(string);
    printf("SUCCESS [test_CString_New]\n");
}

void test_CString_From(void) {
    struct CString *string = CString_From("0123456789");
    if (string == NULL) {
        printf("FAIL [test_CString_From]: CString_New(\"0123456789\") == NULL\n");
        return;
    }
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
    if (stringA == NULL) {
        printf("FAIL [test_CString_clone]: CString_From(\"0123456789\") == NULL\n");
        return;
    }
    if (stringB == NULL) {
        printf("FAIL [test_CString_clone]: CString_clone(stringA) == NULL\n");
        return;
    }
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
    if (stringA == NULL) {
        printf("FAIL [test_CString_concat]: CString_From(\"Hello\") == NULL\n");
        return;
    }
    if (stringB == NULL) {
        printf("FAIL [test_CString_concat]: CString_From(\"World\") == NULL\n");
        return;
    }
    if (stringC == NULL) {
        printf("FAIL [test_CString_concat]: CString_concat(stringA, stringB) == NULL\n");
        return;
    }
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
    if (stringA == NULL) {
        printf("FAIL [test_CString_equals]: CString_From(\"Hello\") == NULL\n");
        return;
    }
    if (stringB == NULL) {
        printf("FAIL [test_CString_equals]: CString_From(\"World\") == NULL\n");
        return;
    }
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
    if (stringA == NULL) {
        printf("FAIL [test_CString_includes]: CString_From(\"Hello\") == NULL\n");
        return;
    }
    if (stringB == NULL) {
        printf("FAIL [test_CString_includes]: CString_From(\"ell\") == NULL\n");
        return;
    }
    if (stringC == NULL) {
        printf("FAIL [test_CString_includes]: CString_From(\"World\")\n");
        return;
    }
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

void test_CString_substring(void) {
    struct CString *stringA = CString_From("Hello World");
    struct CString *stringB = CString_substring(stringA, 0, 5);
    struct CString *stringC = CString_substring(stringA, 6, 11);
    struct CString *stringB_check = CString_From("Hello");
    struct CString *stringC_check = CString_From("World");
    if (stringA == NULL) {
        printf("FAIL [test_CString_substring]: CString_From(\"Hello World\") == NULL\n");
        return;
    }
    if (stringB == NULL) {
        printf("FAIL [test_CString_substring]: CString_substring(stringA, 0, 5) == NULL\n");
        return;
    }
    if (stringC == NULL) {
        printf("FAIL [test_CString_substring]: CString_substring(stringA, 6, 11) == NULL\n");
        return;
    }
    if (stringB_check == NULL) {
        printf("FAIL [test_CString_substring]: CString_From(\"Hello\") == NULL\n");
        return;
    }
    if (stringC_check == NULL) {
        printf("FAIL [test_CString_substring]: CString_From(\"World\") == NULL\n");
        return;
    }
    if (!CString_equals(stringB, stringB_check)) {
        printf("stringB: \"%s\"; stringB_check: \"%s\"\n", stringB->bytes, stringB_check->bytes);
        printf("FAIL [test_CString_substring]: !CString_equals(stringB, stringB_check)\n");
        return;
    }
    if (!CString_equals(stringC, stringC_check)) {
        printf("stringC: \"%s\"; stringC_check: \"%s\"\n", stringC->bytes, stringC_check->bytes);
        printf("FAIL [test_CString_substring]: !CString_equals(stringC, stringC_check)\n");
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    CString_free(stringC);
    CString_free(stringB_check);
    CString_free(stringC_check);
    printf("SUCCESS [test_CString_substring]\n");
}
