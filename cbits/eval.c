#include <stdio.h>
#include <string.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <libxml/xmlsave.h>

#include "eval.h"

int htmlEvalXPathRemove(const xmlChar* xpath, const char* uri, const char* inBuffer, size_t inLength, const char** outBuffer, size_t* outLength)
{
    static const int options = HTML_PARSE_NONET | HTML_PARSE_RECOVER | HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING;

    *outBuffer = 0;
    *outLength = 0;

    int status = -1;
    char* buffer = NULL;
    xmlDoc* doc = NULL;
    xmlXPathContext* xpathCtx = NULL;
    xmlXPathObject* xpathObj = NULL;

    doc = htmlReadMemory(inBuffer, inLength, uri, NULL, options);
    if (doc == NULL)
    {
        goto done;
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL)
    {
        goto done;
    }

    xpathObj = xmlXPathEvalExpression(xpath, xpathCtx);
    if (xpathObj == NULL)
    {
        goto done;
    }

    if (__builtin_expect(xpathObj->type != XPATH_NODESET
                      || xpathObj->nodesetval == NULL
                      || xpathObj->nodesetval->nodeTab == NULL, 0))
    {
        goto done;
    }

    int i;
    size_t length = 0;
    const int nodeNr = xpathObj->nodesetval->nodeNr;
    const xmlNodePtr* nodeTab = xpathObj->nodesetval->nodeTab;
    for (i = 0; i < nodeNr; ++i)
    {
      xmlUnlinkNode(nodeTab[i]);
      xmlFreeNode(nodeTab[i]);
    }
    xmlBufferPtr xBuffer = xmlBufferCreate();
    xmlSaveCtxtPtr saveCtx = xmlSaveToBuffer(xBuffer,NULL,0);
    xmlSaveDoc(saveCtx, doc);
    xmlSaveClose(saveCtx);
    const xmlChar* content = xmlBufferContent(xBuffer);
    length = strlen((const char *)content);
    // add space for '\0', the returned length should not include the trailing null
    buffer = malloc(length + 1);
    strcpy(buffer,(const char *)content);
    xmlBufferFree(xBuffer);

    if (buffer == NULL)
    {
        goto done;
    }

        

    *outBuffer = buffer;
    *outLength = length;

    status = 0;

done:
    if (xpathObj != NULL)
    {
        xmlXPathFreeObject(xpathObj);
        xpathObj = NULL;
    }

    if (xpathCtx != NULL)
    {
        xmlXPathFreeContext(xpathCtx);
        xpathCtx = NULL;
    }

    if (doc != NULL)
    {
        xmlFreeDoc(doc);
        doc = NULL;
    }

    return status;

}

int htmlEvalXPathContents(const xmlChar* xpath, const char* uri, const char* inBuffer, size_t inLength, const char** outBuffer, size_t* outLength)
{
    static const int options = HTML_PARSE_NONET | HTML_PARSE_RECOVER | HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING;

    *outBuffer = 0;
    *outLength = 0;

    int status = -1;
    char* buffer = NULL;
    xmlDoc* doc = NULL;
    xmlXPathContext* xpathCtx = NULL;
    xmlXPathObject* xpathObj = NULL;

    doc = htmlReadMemory(inBuffer, inLength, uri, NULL, options);
    if (doc == NULL)
    {
        goto done;
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL)
    {
        goto done;
    }

    xpathObj = xmlXPathEvalExpression(xpath, xpathCtx);
    if (xpathObj == NULL)
    {
        goto done;
    }

    if (__builtin_expect(xpathObj->type != XPATH_NODESET
                      || xpathObj->nodesetval == NULL
                      || xpathObj->nodesetval->nodeTab == NULL, 0))
    {
        goto done;
    }

    int i;
    size_t length = 0;
    const int nodeNr = xpathObj->nodesetval->nodeNr;
    const xmlNodePtr* nodeTab = xpathObj->nodesetval->nodeTab;
    for (i = 0; i < nodeNr; ++i)
    {
        xmlBufferPtr xBuffer = xmlBufferCreate();
        xmlSaveCtxtPtr saveCtx = xmlSaveToBuffer(xBuffer,NULL,0);
        xmlSaveTree(saveCtx, nodeTab[i]);
        xmlSaveClose(saveCtx);
        const xmlChar* content = xmlBufferContent(xBuffer);
        
        
        if (content != NULL)
        {
            // add space for '\n'
            length += xmlStrlen(content) + 1;
        }
        xmlBufferFree(xBuffer);
    }

    // add space for '\0', the returned length should not include the trailing null
    buffer = malloc(length + 1);
    if (buffer == NULL)
    {
        goto done;
    }

    buffer[0] = '\0';
    for (i = 0; i < nodeNr; ++i)
    {
        xmlBufferPtr xBuffer = xmlBufferCreate();
        xmlSaveCtxtPtr saveCtx = xmlSaveToBuffer(xBuffer,NULL,0);
        xmlSaveTree(saveCtx, nodeTab[i]);
        xmlSaveClose(saveCtx);
        xmlChar* content = (xmlChar *)xmlBufferContent(xBuffer);
        
        char* pch=strchr((char *)content,'\n');
        while (pch!=NULL)
        {
          *pch = ' ';
          pch=strchr(pch+1,'\n');
        }

        if (content != NULL)
        {
            strncat(buffer, (const char *)content, length);
            strncat(buffer, "\n", length);
        }
        xmlBufferFree(xBuffer);
    }

    *outBuffer = buffer;
    *outLength = length;

    status = 0;

done:
    if (xpathObj != NULL)
    {
        xmlXPathFreeObject(xpathObj);
        xpathObj = NULL;
    }

    if (xpathCtx != NULL)
    {
        xmlXPathFreeContext(xpathCtx);
        xpathCtx = NULL;
    }

    if (doc != NULL)
    {
        xmlFreeDoc(doc);
        doc = NULL;
    }

    return status;

}

int htmlEvalXPath(const xmlChar* xpath, const char* uri, const char* inBuffer, size_t inLength, const char** outBuffer, size_t* outLength)
{
    static const int options = HTML_PARSE_NONET | HTML_PARSE_RECOVER | HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING;

    *outBuffer = 0;
    *outLength = 0;

    int status = -1;
    char* buffer = NULL;
    xmlDoc* doc = NULL;
    xmlXPathContext* xpathCtx = NULL;
    xmlXPathObject* xpathObj = NULL;

    doc = htmlReadMemory(inBuffer, inLength, uri, NULL, options);
    if (doc == NULL)
    {
        goto done;
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL)
    {
        goto done;
    }

    xpathObj = xmlXPathEvalExpression(xpath, xpathCtx);
    if (xpathObj == NULL)
    {
        goto done;
    }

    if (__builtin_expect(xpathObj->type != XPATH_NODESET
                      || xpathObj->nodesetval == NULL
                      || xpathObj->nodesetval->nodeTab == NULL, 0))
    {
        goto done;
    }

    int i;
    size_t length = 0;
    const int nodeNr = xpathObj->nodesetval->nodeNr;
    const xmlNodePtr* nodeTab = xpathObj->nodesetval->nodeTab;
    for (i = 0; i < nodeNr; ++i)
    {
        if (nodeTab[i]->content != NULL)
        {
            // add space for '\n'
            length += xmlStrlen(nodeTab[i]->content) + 1;
        }
    }

    // add space for '\0', the returned length should not include the trailing null
    buffer = malloc(length + 1);
    if (buffer == NULL)
    {
        goto done;
    }

    buffer[0] = '\0';
    for (i = 0; i < nodeNr; ++i)
    {
        if (nodeTab[i]->content != NULL)
        {
            strncat(buffer, (const char *)nodeTab[i]->content, length);
            strncat(buffer, "\n", length);
        }
    }

    *outBuffer = buffer;
    *outLength = length;

    status = 0;

done:
    if (xpathObj != NULL)
    {
        xmlXPathFreeObject(xpathObj);
        xpathObj = NULL;
    }

    if (xpathCtx != NULL)
    {
        xmlXPathFreeContext(xpathCtx);
        xpathCtx = NULL;
    }

    if (doc != NULL)
    {
        xmlFreeDoc(doc);
        doc = NULL;
    }

    return status;
}

