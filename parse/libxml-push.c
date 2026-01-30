#include <stdio.h>
#include <sys/time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "tools.h"

//xmlSAXHandler handler;

void initXML(struct TestData *td) {
    xmlInitParser();
//    initxmlDefaultSAXHandler(&handler,0);
}

void releaseXML(struct TestData *td) {
    xmlCleanupParser();
}

void* parseXML(struct TestData *td, unsigned long iter) {
    xmlParserCtxtPtr ctx;
    xmlChar *mem;
    int memsize;
    
//    ctx=xmlCreatePushParserCtxt(&handler,NULL,td->xml,4,"opc");
    ctx=xmlCreatePushParserCtxt(NULL,NULL,td->xml,4,"opc");
    xmlParseChunk(ctx,td->xml+4,td->xmllen-4,1);
    
/*    xmlDocDumpMemory(ctx->myDoc,&mem,&memsize);
    if (iter==td->iterations) puts(mem);
    free(mem);*/
    
    xmlFreeDoc(ctx->myDoc);
    xmlFreeParserCtxt(ctx);
    return NULL;
}

// Push 解析器不需要实现 saveXML（流式解析，不保存文档）
void saveXML(struct TestData *td, void* doc) {
    (void)td;
    (void)doc;
    // Push 解析器不保存文档，此函数为空实现
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
