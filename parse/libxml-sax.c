#include <stdio.h>
#include <sys/time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "tools.h"

#if LIBXML_VERSION > 20600
#define _SAX2_BENCHMARK
#endif

void startElement_(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name, const xmlChar **atts) {
    return;
}

void endElement_(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name) {
    return;
}
void characters_(void *ctx ATTRIBUTE_UNUSED, const xmlChar *ch, int len) {
    return;
}


xmlSAXHandler handler = {
    NULL, /* internalSubset */
    NULL, /* isStandalone */
    NULL, /* hasInternalSubset */
    NULL, /* hasExternalSubset */
    NULL, /* resolveEntity */
    NULL, /* getEntity */
    NULL, /* entityDecl */
    NULL, /* notationDecl */
    NULL, /* attributeDecl */
    NULL, /* elementDecl */
    NULL, /* unparsedEntityDecl */
    NULL, /* setDocumentLocator */
    NULL, /* startDocument */
    NULL, /* endDocument */
    startElement_, /* startElement */
    endElement_, /* endElement */
    NULL, /* reference */
    characters_, /* characters */
    NULL, /* ignorableWhitespace */
    NULL, /* processingInstruction */
    NULL, /* comment */
    NULL, /* xmlParserWarning */
    NULL, /* xmlParserError */
    NULL, /* xmlParserError */
    NULL, /* getParameterEntity */
    NULL, /* cdataBlock; */
    NULL, /* externalSubset; */
#ifndef _SAX2_BENCHMARK
    1
#else
    XML_SAX2_MAGIC,    /* XML_SAX1_MAGIC, XML_SAX2_MAGIC */
    NULL,
    NULL, /* startElementNs */
    NULL, /* endElementNs */
    NULL  /* xmlStructuredErrorFunc */
#endif /* _SAX2_BENCHMARK */
};

void initXML(struct TestData *td) {
    xmlInitParser();
    (void)td;  // 未使用的参数
}

void releaseXML(struct TestData *td) {
    xmlCleanupParser();
}

void* parseXML(struct TestData *td, unsigned long iter) {
    xmlParserCtxtPtr ctxt;
    (void)iter;  // 未使用的参数
    
    // 使用 xmlCreatePushParserCtxt 和 xmlParseChunk 代替 xmlSAXUserParseMemory
    // xmlSAXUserParseMemory 在某些版本中可能有问题，改用更稳定的 API
    ctxt = xmlCreatePushParserCtxt(&handler, NULL, NULL, 0, NULL);
    if (ctxt == NULL) {
        return NULL;
    }
    
    // 分块解析 XML 数据
    xmlParseChunk(ctxt, (const char*)td->xml, td->xmllen, 1);  // 1 表示最后一块
    xmlFreeParserCtxt(ctxt);
    
    return NULL;
}

// SAX 解析器不需要实现 saveXML（流式解析，不保存文档）
void saveXML(struct TestData *td, void* doc) {
    (void)td;
    (void)doc;
    // SAX 解析器不保存文档，此函数为空实现
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
