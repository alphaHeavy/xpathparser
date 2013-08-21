#ifndef _XPATHPARSERS_PARSE_H_
#define _XPATHPARSERS_PARSE_H_

#ifdef __cplusplus
extern "C" {
#endif

int htmlEvalXPath(const xmlChar* xpath, const char* uri, const char* inBuffer, size_t inLength, const char** outBuffer, size_t* outLength);
int htmlEvalXPathContents(const xmlChar* xpath, const char* uri, const char* inBuffer, size_t inLength, const char** outBuffer, size_t* outLength);
int htmlEvalXPathRemove(const xmlChar* xpath, const char* uri, const char* inBuffer, size_t inLength, const char** outBuffer, size_t* outLength);
#ifdef __cplusplus
    throw ();
#else
    ;
#endif

#ifdef __cplusplus
}
#endif

#endif // _XPATHPARSERS_PARSE_H_
