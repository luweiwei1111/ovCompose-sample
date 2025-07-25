#ifndef GLOBAL_TEST_FILE_H
#define GLOBAL_TEST_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

    int callHello(int num);

    void printString(const char *str);

    void printStringBegin(const char *str);
#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_TEST_FILE_H
