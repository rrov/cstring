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
void test_CString_replaceAll(void);

int main(void) {
    test_CString_New();
    test_CString_From();
    test_CString_clone();
    test_CString_concat();
    test_CString_equals();
    test_CString_includes();
    test_CString_substring();
    test_CString_replaceAll();
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
    struct CString *stringA;
    struct CString *stringB;
    struct CString *stringC;
    stringA = CString_From("Hello");
    if (stringA == NULL) {
        printf("FAIL [test_CString_concat]: CString_From(\"Hello\") == NULL\n");
        return;
    }
    stringB = CString_From("World");
    if (stringB == NULL) {
        printf("FAIL [test_CString_concat]: CString_From(\"World\") == NULL\n");
        CString_free(stringA);
        return;
    }
    stringC = CString_concat(stringA, stringB);
    if (stringC == NULL) {
        printf("FAIL [test_CString_concat]: CString_concat(stringA, stringB) == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    if (strcmp(stringC->bytes, "HelloWorld") != 0) {
        printf("FAIL [test_CString_concat]: strcmp(stringA->bytes, \"HelloWorld\") != 0\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    if (stringC->length != (stringA->length + stringB->length)) {
        printf("FAIL [test_CString_concat]: stringC->length != (stringA->length + stringB->length)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    CString_free(stringC);
    printf("SUCCESS [test_CString_concat]\n");
}

void test_CString_equals(void) {
    struct CString *stringA;
    struct CString *stringB;
    stringA = CString_From("Hello");
    if (stringA == NULL) {
        printf("FAIL [test_CString_equals]: CString_From(\"Hello\") == NULL\n");
        return;
    }
    stringB = CString_From("World");
    if (stringB == NULL) {
        printf("FAIL [test_CString_equals]: CString_From(\"World\") == NULL\n");
        CString_free(stringA);
        return;
    }
    if (CString_equals(stringA, stringB)) {
        printf("FAIL [test_CString_equals]: CString_equals(stringA, stringB)\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    if (!CString_equals(stringA, stringA)) {
        printf("FAIL [test_CString_equals]: !CString_equals(stringA, stringA)\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    printf("SUCCESS [test_CString_equals]\n");
}

void test_CString_includes(void) {
    struct CString *stringA;
    struct CString *stringB;
    struct CString *stringC;
    stringA = CString_From("Hello");
    if (stringA == NULL) {
        printf("FAIL [test_CString_includes]: CString_From(\"Hello\") == NULL\n");
        return;
    }
    stringB = CString_From("ell");
    if (stringB == NULL) {
        printf("FAIL [test_CString_includes]: CString_From(\"ell\") == NULL\n");
        CString_free(stringA);
        return;
    }
    stringC = CString_From("World");
    if (stringC == NULL) {
        printf("FAIL [test_CString_includes]: CString_From(\"World\")\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    if (CString_includes(stringA, stringC)) {
        printf("FAIL [test_CString_includes]: CString_includes(stringA, stringC)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    if (!CString_includes(stringA, stringA)) {
        printf("FAIL [test_CString_includes]: !CString_includes(stringA, stringA)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    if (!CString_includes(stringA, stringB)) {
        printf("FAIL [test_CString_includes]: !CString_includes(stringA, stringB)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    if (CString_includes(stringB, stringA)) {
        printf("FAIL [test_CString_includes]: CString_includes(stringB, stringA)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    CString_free(stringC);
    printf("SUCCESS [test_CString_includes]\n");
}

void test_CString_substring(void) {
    struct CString *stringA;
    struct CString *stringB;
    struct CString *stringC;
    struct CString *stringB_check;
    struct CString *stringC_check;
    stringA = CString_From("Hello World");
    if (stringA == NULL) {
        printf("FAIL [test_CString_substring]: CString_From(\"Hello World\") == NULL\n");
        return;
    }
    stringB = CString_substring(stringA, 0, 5);
    if (stringB == NULL) {
        printf("FAIL [test_CString_substring]: CString_substring(stringA, 0, 5) == NULL\n");
        CString_free(stringA);
        return;
    }
    stringC = CString_substring(stringA, 6, 11);
    if (stringC == NULL) {
        printf("FAIL [test_CString_substring]: CString_substring(stringA, 6, 11) == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    stringB_check = CString_From("Hello");
    if (stringB_check == NULL) {
        printf("FAIL [test_CString_substring]: CString_From(\"Hello\") == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    stringC_check = CString_From("World");
    if (stringC_check == NULL) {
        printf("FAIL [test_CString_substring]: CString_From(\"World\") == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        CString_free(stringB_check);
        return;
    }
    if (!CString_equals(stringB, stringB_check)) {
        printf("stringB: \"%s\"; stringB_check: \"%s\"\n", stringB->bytes, stringB_check->bytes);
        printf("FAIL [test_CString_substring]: !CString_equals(stringB, stringB_check)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        CString_free(stringB_check);
        CString_free(stringC_check);
        return;
    }
    if (!CString_equals(stringC, stringC_check)) {
        printf("stringC: \"%s\"; stringC_check: \"%s\"\n", stringC->bytes, stringC_check->bytes);
        printf("FAIL [test_CString_substring]: !CString_equals(stringC, stringC_check)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        CString_free(stringB_check);
        CString_free(stringC_check);
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    CString_free(stringC);
    CString_free(stringB_check);
    CString_free(stringC_check);
    printf("SUCCESS [test_CString_substring]\n");
}

void test_CString_replaceAll(void) {
    struct CString *stringA;
    struct CString *stringB;
    struct CString *stringC;
    struct CString *stringD;
    struct CString *stringE;
    stringA = CString_From("World");
    if (stringA == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_From(\"World\") == NULL\n");
        return;
    }
    stringB = CString_From("rl");
    if (stringB == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_From(\"rl\") == NULL\n");
        CString_free(stringA);
        return;
    }
    stringC = CString_From("11");
    if (stringC == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_From(\"11\") == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    stringD = CString_From("Wo11d");
    if (stringD == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_From(\"He11o\") == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    stringE = CString_replaceAll(stringA, stringB, stringC);
    if (stringE == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_replaceAll(stringA, stringB, stringC) == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        CString_free(stringD);
        return;
    }
    if (!CString_equals(stringE, stringD)) {
        printf("FAIL [test_CString_replaceAll]: !CString_equals(stringE, stringD)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        CString_free(stringD);
        CString_free(stringE);
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    CString_free(stringC);
    CString_free(stringD);
    CString_free(stringE);
    stringA = CString_From("Half-life 3 Half-life 3 Half-life 3");
    if (stringA == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_From(\"World\") == NULL\n");
        return;
    }
    stringB = CString_From("Half-life 3");
    if (stringB == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_From(\"rl\") == NULL\n");
        CString_free(stringA);
        return;
    }
    stringC = CString_From("GabeN The Wise");
    if (stringC == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_From(\"11\") == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        return;
    }
    stringD = CString_From("GabeN The Wise GabeN The Wise GabeN The Wise");
    if (stringD == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_From(\"He11o\") == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        return;
    }
    stringE = CString_replaceAll(stringA, stringB, stringC);
    if (stringE == NULL) {
        printf("FAIL [test_CString_replaceAll]: CString_replaceAll(stringA, stringB, stringC) == NULL\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        CString_free(stringD);
        return;
    }
    if (!CString_equals(stringE, stringD)) {
        printf("FAIL [test_CString_replaceAll]: !CString_equals(stringE, stringD)\n");
        CString_free(stringA);
        CString_free(stringB);
        CString_free(stringC);
        CString_free(stringD);
        CString_free(stringE);
        return;
    }
    CString_free(stringA);
    CString_free(stringB);
    CString_free(stringC);
    CString_free(stringD);
    CString_free(stringE);
    printf("SUCCESS [test_CString_replaceAll]\n");
}
