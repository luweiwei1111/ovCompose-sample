#include "test_ffi.h"
#include "HiTraceSystraceSection.h"
#include "container.h"
#include <hilog/log.h>

int callHello(int num) {
    return num + 1;
}

void printString(const char *str) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "printString", "lww str:%{public}s", str);
    HiTraceSystraceSection s("#Compose::printString::KeyToCPPFast");
}
void printStringBegin(const char *str) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "printString", "lww str:%{public}s", str);
    HiTraceSystraceSection s("#Compose::printString::KeyToCPPFastBegin");
}