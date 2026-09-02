#include <stdio.h>
#include <string.h>
#include "CString.h"

void test_CString_From(void);
void test_CString_clone(void);
void test_CString_concat(void);
void test_CString_equals(void);
void test_CString_includes(void);
void test_CString_substring(void);
void test_CString_replaceAll(void);

int main(void) {
    test_CString_From();
    test_CString_clone();
    test_CString_concat();
    test_CString_equals();
    test_CString_includes();
    test_CString_substring();
    test_CString_replaceAll();
    return 0;
}

void test_CString_From(void) {
    struct CString *string = CString_From("0123456789");
    if (string == NULL) {
        printf("FAIL [test_CString_From]: CString_New(\"0123456789\") == NULL\n");
        return;
    }
    if (strcmp(string->bytes, "0123456789") != 0) {
        printf("FAIL [test_CString_From]: strcmp(string->bytes, \"0123456789\") != 0\n");
        CString_free(string);
        return;
    }
    CString_free(string);
    printf("SUCCESS [test_CString_From]\n");
}

void test_CString_clone(void) {
    struct CString *stringA;
    struct CString *stringB;
    stringA = CString_From("0123456789");
    if (stringA == NULL) {
        printf("FAIL [test_CString_clone]: CString_From(\"0123456789\") == NULL\n");
        return;
    }
    stringB = CString_clone(stringA);
    if (stringB == NULL) {
        printf("FAIL [test_CString_clone]: CString_clone(stringA) == NULL\n");
        CString_free(stringA);
        return;
    }
    if (strcmp(stringA->bytes, stringB->bytes) != 0) {
        printf("FAIL [test_CString_clone]: strcmp(stringA->bytes, stringB->bytes) != 0\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    if (stringA->length != stringB->length) {
        printf("FAIL [test_CString_clone]: stringA->length != stringB->length\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    if (stringA == stringB) {
        printf("FAIL [test_CString_clone]: stringA == stringB\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    printf("SUCCESS [test_CString_clone]\n");
}

void test_CString_concat(void) {
    struct CString stringA;
    struct CString stringB;
    struct CString *stringC;
    CString_init(&stringA, "Hello");
    CString_init(&stringB, "World");
    stringC = CString_concat(&stringA, &stringB);
    if (stringC == NULL) {
        printf("FAIL [test_CString_concat]: CString_concat(stringA, stringB) == NULL\n");
        return;
    }
    if (strcmp(stringC->bytes, "HelloWorld") != 0) {
        printf("FAIL [test_CString_concat]: strcmp(stringA->bytes, \"HelloWorld\") != 0\n");
        CString_free(stringC);
        return;
    }
    if (stringC->length != (stringA.length + stringB.length)) {
        printf("FAIL [test_CString_concat]: stringC->length != (stringA.length + stringB.length)\n");
        CString_free(stringC);
        return;
    }
    CString_free(stringC);
    printf("SUCCESS [test_CString_concat]\n");
}

void test_CString_equals(void) {
    struct CString stringA;
    struct CString stringB;
    CString_init(&stringA, "Hello");
    CString_init(&stringB, "World");
    if (CString_equals(&stringA, &stringB)) {
        printf("FAIL [test_CString_equals]: CString_equals(&stringA, &stringB)\n");
        return;
    }
    if (!CString_equals(&stringA, &stringA)) {
        printf("FAIL [test_CString_equals]: !CString_equals(&stringA, &stringA)\n");
        return;
    }
    printf("SUCCESS [test_CString_equals]\n");
}

void test_CString_includes(void) {
    struct CString stringA;
    struct CString stringB;
    struct CString stringC;
    CString_init(&stringA, "Hello");
    CString_init(&stringB, "ell");
    CString_init(&stringC, "World");
    if (CString_includes(&stringA, &stringC)) {
        printf("FAIL [test_CString_includes]: CString_includes(&stringA, &stringC)\n");
        return;
    }
    if (!CString_includes(&stringA, &stringA)) {
        printf("FAIL [test_CString_includes]: !CString_includes(&stringA, &stringA)\n");
        return;
    }
    if (!CString_includes(&stringA, &stringB)) {
        printf("FAIL [test_CString_includes]: !CString_includes(stringA, stringB)\n");
        return;
    }
    if (CString_includes(&stringB, &stringA)) {
        printf("FAIL [test_CString_includes]: CString_includes(stringB, stringA)\n");
        return;
    }
    printf("SUCCESS [test_CString_includes]\n");
}

void test_CString_substring(void) {
    struct CString stringA;
    struct CString *stringB;
    struct CString *stringC;
    struct CString stringB_check;
    struct CString stringC_check;

    CString_init(&stringA, "Hello World");
    CString_init(&stringB_check, "Hello");
    CString_init(&stringC_check, "World");
    stringB = CString_substring(&stringA, 0, 5);
    if (stringB == NULL) {
        printf("FAIL [test_CString_substring]: CString_substring(&stringA, 0, 5) == NULL\n");
        return;
    }
    stringC = CString_substring(&stringA, 6, 11);
    if (stringC == NULL) {
        printf("FAIL [test_CString_substring]: CString_substring(&stringA, 6, 11) == NULL\n");
        CString_free(stringB);
        return;
    }
    if (!CString_equals(stringB, &stringB_check)) {
        printf("stringB: \"%s\"; stringB_check: \"%s\"\n", stringB->bytes, stringB_check.bytes);
        printf("FAIL [test_CString_substring]: !CString_equals(stringB, &stringB_check)\n");
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    if (!CString_equals(stringC, &stringC_check)) {
        printf("stringC: \"%s\"; stringC_check: \"%s\"\n", stringC->bytes, stringC_check.bytes);
        printf("FAIL [test_CString_substring]: !CString_equals(stringC, &stringC_check)\n");
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    CString_free(stringB);
    CString_free(stringC);
    printf("SUCCESS [test_CString_substring]\n");
}

void test_CString_replaceAll(void) {
    struct CString stringA;
    struct CString stringB;
    struct CString stringC;
    struct CString stringD;
    struct CString *stringE;
    
    CString_init(&stringA, "World");
    CString_init(&stringB, "rl");
    CString_init(&stringC, "11");
    CString_init(&stringD, "Wo11d");
    stringE = CString_replaceAll(&stringA, &stringB, &stringC);
    if (stringE == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_replaceAll(&stringA, &stringB, &stringC) == NULL\n");
        return;
    }
    if (!CString_equals(stringE, &stringD)) {
        printf("FAIL [test_CString_replaceAll]: !CString_equals(stringE, &stringD)\n");
        CString_free(stringE);
        return;
    }
    CString_free(stringE);

    CString_init(&stringA, "Half-life 3 Half-life 3 Half-life 3");
    CString_init(&stringB, "Half-life 3");
    CString_init(&stringC, "GabeN The Wise");
    CString_init(&stringD, "GabeN The Wise GabeN The Wise GabeN The Wise");
    stringE = CString_replaceAll(&stringA, &stringB, &stringC);
    if (stringE == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_replaceAll(&stringA, &stringB, &stringC) == NULL\n");
        return;
    }
    if (!CString_equals(stringE, &stringD)) {
        printf("FAIL [test_CString_replaceAll]: !CString_equals(stringE, &stringD)\n");
        CString_free(stringE);
        return;
    }
    CString_free(stringE);
    printf("SUCCESS [test_CString_replaceAll]\n");
}
