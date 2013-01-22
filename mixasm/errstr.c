#include <stdio.h>

#include "errstr.h"

const char *_errstr[] = {
    "no error",
    "unrecognized option",
    "cannot open input file",
    "cannot open output file",
    "invalid instruction",
    "invalid alphanumeric constant",
    "symbol already defined",
    "invalid symbol name",
    "undefined symbol",
    "undefined local symbol",
    "forward symbol used in expression",
    "division by zero",
    "parse error"
}; 

static int _errstr_count  = sizeof(_errstr) / sizeof(char *);

const char * errstr(int err)
{
    return (err < _errstr_count ? _errstr[err] : NULL);
}

