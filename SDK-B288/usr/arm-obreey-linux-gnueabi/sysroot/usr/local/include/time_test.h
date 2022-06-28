#ifndef TIME_TEST_H
#define TIME_TEST_H

#include <inkinternal.h>
#include <inkview.h>

static int time_test_update_called = 0;

#define TIME_TEST_PATH TEMPDIR"/test/time"
#define TIME_TEST_GET_TIME_BUF_SIZE 32

#ifdef IS_MONITOR
    #define BOOT_TIME_MS time_bootclock_ms()
    #define TEST_BUILD_PATH(path) \
    { \
        if (NULL != path) \
        { \
            char *tpath = strdup(path); \
            char *p = tpath; \
            struct stat sb; \
            while ((p = strchr(p+1, '/')) != NULL) { \
                *p = 0; \
                if (stat(tpath,&sb) != 0) mkdir(tpath, 0777); \
                *p = '/'; \
            } \
            free(tpath); \
        } \
    }
#else
    #define BOOT_TIME_MS hw_boottime_ms()
    #define TEST_BUILD_PATH(path) iv_buildpath(path)
#endif
// Internal defines

#define TIME_TEST_INIT_TIME_BUF \
    char time_buf[TIME_TEST_GET_TIME_BUF_SIZE]; \
    memset(time_buf, 0, TIME_TEST_GET_TIME_BUF_SIZE); \
    snprintf(time_buf, TIME_TEST_GET_TIME_BUF_SIZE, "%lld", BOOT_TIME_MS);

#define TIME_TEST_WRITE_BUF(fname, skip_on_exist, buf_to_write, buf_size) \
{ \
    char test_path[256]; \
    snprintf(test_path, sizeof(test_path), TIME_TEST_PATH "/%d/" fname, getpid()); \
    if (!skip_on_exist || access(test_path, F_OK) != 0) \
    { \
        int fd = open(test_path, O_RDWR | O_CREAT, 0777); \
        if (fd != -1) \
        { \
            write(fd, buf_to_write, buf_size); \
            close(fd); \
        } \
    } \
}

#define TEST_BUILD_PATH(path) \
{ \
    if (NULL != path) \
    { \
        char *tpath = strdup(path); \
        char *p = tpath; \
        struct stat sb; \
        while ((p = strchr(p+1, '/')) != NULL) { \
            *p = 0; \
            if (stat(tpath,&sb) != 0) mkdir(tpath, 0777); \
            *p = '/'; \
        } \
        free(tpath); \
    } \
}

// User defines

#define TIME_TEST_INIT \
{ \
    char test_path[256]; \
    snprintf(test_path, sizeof(test_path), TIME_TEST_PATH"/%d/", getpid()); \
    TEST_BUILD_PATH(test_path); \
}

// call init before exec
#define TIME_TEST_EXEC(app_name) \
{ \
    TIME_TEST_INIT_TIME_BUF; \
    TIME_TEST_WRITE_BUF("exec", 0, time_buf, TIME_TEST_GET_TIME_BUF_SIZE); \
    if (app_name && *app_name) \
        TIME_TEST_WRITE_BUF("app_name", 0, app_name, strlen(app_name)); \
}

#define TIME_TEST_INIT_INKVIEW \
{ \
    TIME_TEST_INIT_TIME_BUF; \
    TIME_TEST_WRITE_BUF("init", 1, time_buf, TIME_TEST_GET_TIME_BUF_SIZE); \
}

#define TIME_TEST_FIRST_UPDATE \
{ \
    if (!time_test_update_called) \
    { \
        time_test_update_called = 1; \
        TIME_TEST_INIT_TIME_BUF; \
        TIME_TEST_WRITE_BUF("fupdate", 1, time_buf, TIME_TEST_GET_TIME_BUF_SIZE); \
    } \
}

#endif // TIME_TEST_H
