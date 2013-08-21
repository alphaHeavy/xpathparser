#include <stdio.h>
#include <string.h>
#include <libxml/xmlstring.h>

#include "eval.h"
#include "parse.h"

int htmlGetText(const char* uri, const char* inBuffer, size_t inLength, const char** outBuffer, size_t* outLength)
{
    static const xmlChar* xpath = BAD_CAST("/html/body//text()[not(ancestor::script) and not(ancestor::style)]");

    return htmlEvalXPath(xpath, uri, inBuffer, inLength, outBuffer, outLength);
}

