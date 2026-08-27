#ifndef CStringLib
#define CStringLib
#include <stddef.h>

struct CString {
    size_t length;
    char *bytes;
};

struct CStringArray {
    size_t length;
    struct CString *strings;
};

/* CString methods */
struct CString *CString_New(size_t length);
struct CString *CString_From(char *str);
struct CString *CString_clone(struct CString *this);
struct CString *CString_concat(struct CString *this, struct CString *string);
struct CString *CString_substring(struct CString *this, size_t start, size_t end);
struct CString *CString_replaceAll(struct CString *this, struct CString *pattern, struct CString *replacement);
int CString_equals(struct CString *this, struct CString *string);
int CString_includes(struct CString *this, struct CString *string);
struct CStringArray *CString_split(struct CString *this, struct CString *string); /* Not implemented */
void CString_free(struct CString *this);
/*  */

/* CStringArray methods */
struct CStringArray *CStringArray_New(size_t length); /* Not implemented */
void CStringArray_push(struct CStringArray *this, struct CString *string); /* Not implemented */
void CStringArray_pop(struct CStringArray *this); /* Not implemented */
void CStringArray_shift(struct CStringArray *this); /* Not implemented */
void CStringArray_unshift(struct CStringArray *this, struct CString *string); /* Not implemented */
void CStringArray_replace(struct CStringArray *this, size_t index, struct CString *string); /* Not implemented */
struct CStringArray *CStringArray_slice(struct CStringArray *this, size_t start, size_t end); /* Not implemented */
struct CStringArray *CStringArray_unique(struct CStringArray *this); /* Not implemented */
void CStringArray_forEach(struct CStringArray *this, void (*f)(struct CString*, size_t index, struct CStringArray*)); /* Not implemented */
struct CStringArray *CStringArray_filter(struct CStringArray *this, int (*f)(struct CString*, size_t index, struct CStringArray*)); /* Not implemented */
void CStringArray_sort(struct CStringArray *this); /* Not implemented */
int CStringArray_includes(struct CStringArray *this, struct CString *string); /* Not implemented */
struct CString *CStringArray_join(struct CStringArray *this); /* Not implemented */
void CStringArray_free(struct CStringArray *this); /* Not implemented */
/*  */
#endif
