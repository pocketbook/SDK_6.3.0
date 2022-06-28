/**
  \brief file contains macroses for logging and error handling purposes
  */
#ifndef INKLOG_H
#define INKLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#undef TRUE
#undef FALSE
#include "GTypes.h"
#include "P7_Cproxy.h"

#ifdef __cplusplus
extern "C"
{

#endif // __cplusplus

// Log level constant
#define PB_LOG_LEVEL_NONE 0     /// No logging at all
#define PB_LOG_LEVEL_ERROR 1   /// Output only errors
#define PB_LOG_LEVEL_WARNING 2  /// Output only errors and warnings
#define PB_LOG_LEVEL_INFO 3     /// Output all messages except traces and verbose
#define PB_LOG_LEVEL_TRACE 4    /// Output include trace messages
#define PB_LOG_LEVEL_VERBOSE 5    /// Output all messages

extern hP7_Trace g_p7_trace;

/**
 * \brief Print message to logger, do not call this function directly, use macroses below instead
 * \param log_level - message level 
 * \param file_name - file name log is written from
 * \param line - source code line log is written from
 * \param format - printf like format followed by variable length argument list (depending on format argument)
 */
void pb_print_log(int log_level, const char * file_name, int line, const char* format, ...);
void pb_print_log2(int log_level, const char * file_name, int line, const char* pretty_func, const char* format, ...);
void pb_print_log2_with_module(int log_level, const char * module_name, const char * file_name, int line, const char* pretty_func, const char* format, ...);
void vpb_print_log(int log_level, const char * file_name, int line, const char *pretty_func, const char* format, va_list args);


void pb_set_log_file(FILE* file);

#ifndef PB_LOG_LEVEL
#define PB_LOG_LEVEL PB_LOG_LEVEL_TRACE
#endif

/**
 * Four macroses defined for logging purposes: PB_TRACE, PB_INFO, PB_WARN, PB_ERROR
 * Each of them has parameter format (which is printf like format) followed by variable length parameter list depending from format parameter (same as for printf function)
 * Wether log printed or not determined by value of PB_LOG_LEVEL which can take values descriped above.
 * If your source file doesn't define variable PB_LOG_LEVEL before inclusion of this file its has default value PB_LOG_LEVEL_INFO
 * If DEBUG is not defined P7 is used for logging instead of console
 **/

#define PB_LOG_MSG(level, module, format, ...) pb_print_log2_with_module(level, module, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)

void release_logger();
extern int g_process_pid;
#ifdef TRACE_MODULE_NAME

#define PB_VERBOSE(format, ...) pb_print_log2_with_module(PB_LOG_LEVEL_VERBOSE, TRACE_MODULE_NAME, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#define PB_TRACE(format, ...) pb_print_log2_with_module(PB_LOG_LEVEL_TRACE, TRACE_MODULE_NAME, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#define PB_INFO(format, ...) pb_print_log2_with_module(PB_LOG_LEVEL_INFO, TRACE_MODULE_NAME, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#define PB_WARN(format, ...) pb_print_log2_with_module(PB_LOG_LEVEL_WARNING, TRACE_MODULE_NAME, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#define PB_ERROR(format, ...) pb_print_log2_with_module(PB_LOG_LEVEL_ERROR, TRACE_MODULE_NAME, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#else

#define PB_VERBOSE(format, ...) pb_print_log2(PB_LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#define PB_TRACE(format, ...) pb_print_log2(PB_LOG_LEVEL_TRACE, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#define PB_INFO(format, ...) pb_print_log2(PB_LOG_LEVEL_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#define PB_WARN(format, ...) pb_print_log2(PB_LOG_LEVEL_WARNING, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#define PB_ERROR(format, ...) pb_print_log2(PB_LOG_LEVEL_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, "[pid:%d]" format, g_process_pid, ##__VA_ARGS__)

#endif

/**
 * Next code contains macroses intended to error handling. Each of them print information about error to the log 
 * and then perform appropriate action.
 * There are 2 types of actions:
 * 1. Return on error. This variant suitable for C++ code which use RAII and so don't need to release resources manually
 * 2. Goto mark on error. This variant suitable for C code which usually need to perform some resource deallocation 
 * before returning on error. Don't use mark name "error" for this variant.
 *
 * Also there are 2 types of error detection used in macroses below:
 * 1. Check condition (if failed than error)
 * 2. Check integer variable for succesfull value. If not equal than failure.
 */

/// Return if condition failed
#define PB_FRETURN_IF(cond, val)\
        do{\
                if(cond){\
                        PB_ERROR("Condition: \""#cond"\", return(\""#val"\")]");\
                        return (val);\
                }\
        }while(0)

/// assert Return if condition failed
#define PB_FRETURN_IF_ASSERT(cond, val)\
        do{\
                assert(!(cond)); \
                if(cond){\
                        PB_ERROR("Condition: \""#cond"\", return(\""#val"\")]");\
                        return (val);\
                }\
        }while(0)


#define PB_FRETURN_IF_MSG(cond, val, msg, ...)\
		do{\
				if(cond){\
						PB_ERROR("Condition: \""#cond"\", return(\""#val"\")]" msg, ## __VA_ARGS__);\
						return (val);\
				}\
		}while(0)


#define PB_FRETURN_IF_NOT(cond, val)\
	do{\
                if(!(cond)){\
                        PB_ERROR("Condition: \""#cond"\", return(\""#val"\")]");\
			return (val);\
		}\
	}while(0)

#define PB_FRETURN_IF_NOT_MSG(cond, val, msg, ...)\
        do{\
                if(!(cond)){\
                        PB_ERROR("Condition: \""#cond"\", return(\""#val"\")]" msg, ## __VA_ARGS__);\
                        return (val);\
                }\
        }while(0)
/// Return void if condition failed
#define PB_FRETURN_VOID_IF_NOT(cond)\
	do{\
                if(!(cond)){\
                        PB_ERROR("Condition: \""#cond"\", return]");\
			return;\
		}\
	}while(0)

#define PB_FRETURN_VOID_IF(cond)\
	do{\
                if((cond)){\
                        PB_ERROR("Condition: \""#cond"\", return]");\
			return;\
		}\
	}while(0)

#define PB_FRETURN_VOID_IF_ASSERT(cond)\
        do{\
                assert(!(cond)); \
                if(cond){\
                        PB_ERROR("Condition: \""#cond"\", return]");\
                        return ;\
                }\
        }while(0)

#define PB_FRETURN_VOID_IF_MSG(cond, msg, ...)\
    do{\
                if((cond)){\
                        PB_ERROR("Condition: \""#cond"\", return]" msg, ## __VA_ARGS__);\
            return;\
        }\
    }while(0)

/// Return if var != 0 
#define PB_FRETURN_ON_ERR(var, val) \
    do{\
        int var_int = var;\
        if (var_int != val)\
        {\
                        PB_ERROR(" err:[%d] " , var_int);\
            return var_int;\
        }\
    }while(0)

#define PB_FRETURN_ON_ERR_MSG(var, val, msg, ...) \
    do{\
        int var_int = var;\
        if (var_int != val)\
        {\
                        PB_ERROR("err:[%d] " msg, var_int, ## __VA_ARGS__);\
            return var_int;\
        }\
    }while(0)

/// Return void if var != 0 
#define PB_FRETURN_VOID_ON_ERR(var, val, msg, ...)\
    do{\
        int var_int = var;\
        if (val != var_int)\
        {\
                        PB_ERROR("err:[%d] "  msg, var_int, ## __VA_ARGS__);\
            return;\
        }\
    }while(0)

/// Goto mark if condition failed
#define PB_DONE_IF_NOT(cond, mark, var, val)\
    do { \
    if (!(cond)) \
        {\
            PB_ERROR("Condition %s failed. ", #cond);\
            var = (val);\
            goto mark;\
        }\
    } while (0)

#define PB_DONE_IF_NOT_MSG(cond, mark, var, val, msg, ...)\
    do { \
    if (!(cond)) \
        {\
            PB_ERROR("Condition %s failed. " msg, #cond, ## __VA_ARGS__);\
            var = (val);\
            goto mark;\
        }\
    } while (0)

/// Goto mark if condition true
#define PB_DONE_IF(cond, mark, var, val)\
    do { \
    if (cond) \
        {\
            PB_ERROR("Condition %s is true. ", #cond);\
            var = (val);\
            goto mark;\
        }\
    } while (0)

/// Goto mark if var != 0
#define PB_DONE_ON_ERR(var, val, mark) \
    do { \
        int var_int = var;\
        if ((var_int) != (val)) \
        {\
            PB_ERROR("Failed with [%d] " , var_int);\
            goto mark;\
        }\
    } while (0)

#define PB_DONE_ON_ERR_MSG(var, val, mark, msg, ...) \
    do { \
        int var_int = var;\
        if ((var_int) != (val)) \
        {\
            PB_ERROR("Failed with [%d] " msg, var_int, ## __VA_ARGS__);\
            goto mark;\
        }\
    } while (0)

#define PB_CHECK(cond) PB_FRETURN_IF_NOT((cond), false)
#define PB_CHECK0(cond) PB_FRETURN_VOID_IF_NOT((cond))

// Function from Marat version of log
#define PB_ALWAYS_TRACE(format, ...) pb_print_log2(PB_LOG_LEVEL_TRACE, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__) ///< deprecated
#define PB_ALWAYS_INFO(format, ...) pb_print_log2(PB_LOG_LEVEL_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__,format, ##__VA_ARGS__) ///< deprecated
#define PB_ALWAYS_WARN(format, ...) pb_print_log2(PB_LOG_LEVEL_WARNING, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__) ///< deprecated
#define PB_ALWAYS_ERROR(format, ...) pb_print_log2(PB_LOG_LEVEL_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__) ///< deprecated

#define PB_LOG(...)		fprintf(stderr, ## __VA_ARGS__) ///< deprecated
#define PB_ECHO(x)		do{PB_ALWAYS_TRACE(#x); (x);}while(0) ///< deprecated
#define PB_TRACE1(msg)	PB_ALWAYS_TRACE(msg) ///< deprecated
#define PB_FINFON(...)	PB_ALWAYS_ERROR(__VA_ARGS__) ///< deprecated
#define PB_TRACEN(...)	PB_ALWAYS_TRACE(__VA_ARGS__) ///< deprecated
#define PB_TRACE0		PB_ALWAYS_TRACE("%s", __PRETTY_FUNCTION__) ///< deprecated

#define XSTRINGIFY_MACROS(a) STRINGIFY_MACROS(a)
#define STRINGIFY_MACROS(a) #a

#define PB_TRACE_ PB_TRACE(XSTRINGIFY_MACROS(__LINE__));
#define PB_INFO_ PB_INFO(XSTRINGIFY_MACROS(__LINE__))
#define PB_WARN_ PB_WARN(XSTRINGIFY_MACROS(__LINE__))
#define PB_ERROR_ PB_ERROR(XSTRINGIFY_MACROS(__LINE__))

#ifdef DEBUG
#	define PB_DBG_TRACE			PB_TRACE
#	define PB_DBG_TRACE1(msg)	PB_TRACE1(msg)
#	define PB_DBG_LOG(...)	PB_LOG(__VA_ARGS__)
//-----------------------------
#else
#	define PB_DBG_TRACE void(0)
#	define PB_DBG_TRACE1(msg) void(0)
#	define PB_DBG_LOG(...) void(0)
#endif

#ifdef DEBUG
#	define PB_ASSERT1(cond, val) assert(cond)
#else
#	define PB_ASSERT1(cond, val) PB_FRETURN_IF(!(cond), val)
#endif

#ifdef DEBUG
#	define PB_ASSERT(cond) assert(cond)
#else
#	define PB_ASSERT(cond) PB_FRETURN_VOID_IF(!(cond))
#endif

#define PB_FINFO_IF(cond)\
	do{\
		if((cond)){\
			PB_ERROR("Condition " #cond);\
		}\
	}while(0)

#define PB_FINFON_IF(cond, format, ...)\
	do{\
		if((cond)){\
			PB_ERROR("Condition " #cond format, __VA_ARGS__);\
		}\
	}while(0)

#define PB_CORRECT_TO(val)\
	(\
		PB_WARN("[CORRECTION: " #val ),\
		val\
	)
	
/// Return if condition failed and print message by specified macros
#define PB_PRINT_RETURN_IF(print, cond, val)\
        do{\
                if(cond){\
                        print("Condition: \""#cond"\", return(\""#val"\")]");\
                        return (val);\
                }\
        }while(0)
        
#define PB_PRINT_RETURN_VOID_IF(print, cond)\
        do{\
                if(cond){\
                        print("Condition: \""#cond"\", return]");\
                        return ;\
                }\
        }while(0)
        
#define PB_PRINT_RETURN_IF_MSG(print, cond, val, msg, ...)\
        do{\
                if(cond){\
                        print("Condition: \""#cond"\", return(\""#val"\")]" msg, ## __VA_ARGS__);\
                        return (val);\
                }\
        }while(0)

#define PB_PRINT_RETURN_VOID_IF_MSG(print, cond, msg, ...)\
        do{\
                if(cond){\
                        print("Condition: \""#cond"\", return]" msg, ## __VA_ARGS__);\
                        return ;\
                }\
        }while(0)

void pb_print_log_argv(int log_level, const char * file_name, int line, const char *pretty_func, int argc, const char * const* argv);
#if PB_LOG_LEVEL >= PB_LOG_LEVEL_TRACE
#define PB_TRACE_ARGV(ARGC, ARGV) pb_print_log_argv(PB_LOG_LEVEL_TRACE, __FILE__, __LINE__, __PRETTY_FUNCTION__, ARGC, ARGV)
#else
#define PB_TRACE_ARGV(ARGC, ARGV) (void)(0)
#endif

#if PB_LOG_LEVEL >= PB_LOG_LEVEL_INFO
#define PB_INFO_ARGV(ARGC, ARGV) pb_print_log_argv(PB_LOG_LEVEL_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, ARGC, ARGV)
#else
#define PB_INFO_ARGV(ARGC, ARGV) (void)(0)
#endif
void pb_xlog(const char *filename, const char *format, ...);

#define XLOG(name, fmt...) pb_xlog("/tmp/" #name ".log", fmt)

#define PB_BOOL_TO_STR(val) (val ? "true" : "false")


//#define KLOG(fmt...)
#define KLOG(fmt...) do { FILE *klogf = fopen("/dev/kmsg", "w"); if (klogf) { fprintf(klogf, "U[%d] ", getpid()); fprintf(klogf, fmt); fclose(klogf); } } while (0)

#define KDBG(fmt...) KLOG(fmt)

//#define FDBG(s...) { FILE *fff=fopen("/tmp/gs.log","a"); if (fff) {fprintf(fff,"[%d] ",getpid());fprintf(fff,s);fprintf(fff,"\n");fclose(fff);} }
#define FDBG(s...) do {} while(0)

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // INKLOG_H


