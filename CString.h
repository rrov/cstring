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
void CString_replaceAll(struct CString *this, struct CString *string); /* Not implemented */
int CString_equals(struct CString *this, struct CString *string);
int CString_includes(struct CString *this, struct CString *string);
struct CStringArray *CString_split(struct CString *this, struct CString *string); /* Not implemented */
void CString_free(struct CString *this);
/*  */

/* CStringArray methods */
struct CStringArray *CStringArray_New(size_t length); /* Not implemented */
struct CStringArray *CStringArray_From(size_t length, struct CString *strings[]); /* Not implemented */
struct CStringArray *CStringArray_forEach(struct CStringArray *strings); /* Not implemented */
struct CStringArray *CStringArray_filter(struct CStringArray *strings); /* Not implemented */
struct CStringArray *CStringArray_sort(struct CStringArray *strings); /* Not implemented */
struct CStringArray *CStringArray_includes(struct CString *string); /* Not implemented */
struct CString *CStringArray_join(struct CStringArray *strings); /* Not implemented */
void CStringArray_free(struct CStringArray *strings); /* Not implemented */
/*  */
#endif
