#ifndef clLogApi_hpp
#define clLogApi_hpp
#include <clHandleApi.hxx>

#ifdef __GNUC__
#define CL_DEPRECATED __attribute__((__deprecated__))
#define CL_PRINTF_FORMAT(fmtPos, argPos) __attribute__((format(printf, fmtPos, argPos)))
#else
#define CL_DEPRECATED
#define CL_PRINTF_FORMAT(fmtPos, argPos)
#endif


/**
 * Area string for unspecified component area
 */
#define CL_LOG_AREA_UNSPECIFIED "---"

/**
 * Context string for unspecified component context
 */
#define CL_LOG_CONTEXT_UNSPECIFIED "---"

#define CL_LOG_CLIENT_VERSION    {'B', 0x01, 0x01}

namespace SAFplus
{

//? <section name="Logging">

  /* Log handle */
class Logger
{
public:
};
  
enum
  {
    CL_LOG_BUFFER_DEFAULT_LENGTH = 1024*1024,  // use clLogBufferSize in your code for the actual size.
    LOG_MAX_MSG_LEN  = 1024,

  };
  
  
typedef enum
  {
    LOG_SEV_EMERGENCY = 0x1,  //? System is unusable, therefore service affecting.  Often used to indicate an error that affects multiple applications, or sites.  Notify all tech staff on call.

    LOG_SEV_ALERT,     //? Action must be taken immediately.  Service affecting.  Notify tech staff who can fix the problem.

    LOG_SEV_CRITICAL,  //? Critical conditions.  Should be corrected immediately but does not affect service.

    LOG_SEV_ERROR,     //? Error conditions.  Non-urgent failures that should be forwarded to developers or admins for resolution.

    LOG_SEV_WARNING,   //? Warning conditions.  Not an error, but indicates that an error may develop if action is not taken.

    LOG_SEV_NOTICE,    //? Normal but significant condition.

    LOG_SEV_INFO,      //? Normal operational messages.

    LOG_SEV_DEBUG,     //? Debug-level messages.  This info may be useful to developers debugging the application.
    LOG_SEV_DEBUG1   =      LOG_SEV_DEBUG,  //? Debug-level messages.  This info may be useful to developers debugging the application.
    LOG_SEV_DEBUG2,    //? Debug-level messages.  This info may be useful to developers debugging the application.  Increasing detail...
    LOG_SEV_DEBUG3,    //? Debug-level messages.  This info may be useful to developers debugging the application.  Increasing detail...
    LOG_SEV_DEBUG4,    //? Debug-level messages.  This info may be useful to developers debugging the application.  Increasing detail...
    LOG_SEV_DEBUG5,    //? Debug-level messages.  This info may be useful to developers debugging the application.  Increasing detail...

    LOG_SEV_TRACE  =    LOG_SEV_DEBUG5,  //? Debug-level message pertaining to the entry or exit of functions or code blocks.
    LOG_SEV_DEBUG6,
    LOG_SEV_DEBUG7,
    LOG_SEV_DEBUG8,
    LOG_SEV_DEBUG9,
/**
 * Maximum severity level. 
 */
    LOG_SEV_MAX = LOG_SEV_DEBUG9 //? The highest number but lowest in importance log severity level.
  } LogSeverity;

  //? Parse log severity from a string.  The string can either be one of the enums or an integer.
  LogSeverity logSeverityGet(const char *pSevValue);

  /*? Write a printf-style log message.  To write to the "default" log for the application, use the convenience macros logXXX (i.e logWrite(), logInfo(), etc) instead of this function.
    <arg name="streamHdl">The handle of the destination log stream</arg>
    <arg name="severity">The severity (importance) of the log message.  Se the LogSeverity constants for choices.</arg>
    <arg name="serviceId">An arbitrary number that you can assign to applications to help filter logs.</arg>
    <arg name="pArea">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="pContext">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="pFileName">Use the __FILE__ macro here</arg>
    <arg name="pFileName">Use the __LINE__ macro here</arg>
    <arg name="pFmtStr">The printf-style format string and subsequent arguments that make up this log</arg>
   */
  void logMsgWrite(Handle streamHdl, LogSeverity  severity, uint_t serviceId, const char *pArea, const char  *pContext, const char *pFileName, uint_t lineNum, const char *pFmtStr,...) CL_PRINTF_FORMAT(8, 9);

  /*? Write a string log message.
    <arg name="streamHdl">The handle of the destination log stream</arg>
    <arg name="severity">The severity (importance) of the log message.  Se the LogSeverity constants for choices.</arg>
    <arg name="serviceId">An arbitrary number that you can assign to applications to help filter logs.</arg>
    <arg name="pArea">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="pContext">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="pFileName">Use the __FILE__ macro here</arg>
    <arg name="pFileName">Use the __LINE__ macro here</arg>
    <arg name="pFmtStr">The NULL terminated string log message.</arg>
   */
  void logStrWrite(Handle streamHdl, LogSeverity  severity, uint_t serviceId, const char *pArea, const char  *pContext, const char *pFileName, uint_t lineNum, const char *str);

  //? Initialize the logging subsystem.  Typically this is called during execution of safplusInitialize(), so applications would only call this if they are using logging standalone.
  Logger* logInitialize(void);

};

#ifndef SAFPLUS_COMPONENT

//? Write a printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
//    <arg name="severity">The severity (importance) of the log message.  Se the LogSeverity constants for choices.</arg>
//    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
//    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
#define logWrite(severity, area, context, ...) appLog(SAFplus::APP_LOG, severity, 0, area, context, __VA_ARGS__)

/*? Write an emergency level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logEmergency(area, context, ...) appLog(SAFplus::APP_LOG, SAFplus::LOG_SEV_EMERGENCY, 0, area, context, __VA_ARGS__)

/*? Write an alert level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logAlert(area, context, ...) appLog(SAFplus::APP_LOG,SAFplus::LOG_SEV_ALERT, 0,area, context, __VA_ARGS__)

/*? Write a critical level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logCritical(area, context, ...) appLog(SAFplus::APP_LOG,SAFplus::LOG_SEV_CRITICAL,0, area, context, __VA_ARGS__)

/*? Write an error level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logError(area, context, ...) appLog(SAFplus::APP_LOG,SAFplus::LOG_SEV_ERROR, 0,area, context, __VA_ARGS__)

/*? Write a warning level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logWarning(area, context, ...) appLog(SAFplus::APP_LOG,SAFplus::LOG_SEV_WARNING, 0,area, context, __VA_ARGS__)

/*? Write a notice level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logNotice(area, context, ...) appLog(SAFplus::APP_LOG,SAFplus::LOG_SEV_NOTICE, 0,area, context, __VA_ARGS__)

/*? Write an info level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logInfo(area, context, ...) appLog(SAFplus::APP_LOG,SAFplus::LOG_SEV_INFO, 0,area, context, __VA_ARGS__)

/*? Write a debug level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logDebug(area, context, ...) appLog(SAFplus::APP_LOG,SAFplus::LOG_SEV_DEBUG,0, area, context, __VA_ARGS__)

/*? Write a trace level printf-style log message to the application's default stream.  This is a convenience wrapper around logMsgWrite().
    <arg name="area">A preferably 3 letter abbreviation for the area of code.  Used to help identify and filter logs.  This will appear in the log as the 2nd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg>
    <arg name="context">A preferably 3 letter abbreviation for the specific context of the code that issued the log.  Used to help identify and filter logs.  This will appear in the log as the 3rd parameter of a dotted 3-set of identifiers.  i.e. APP.AREA.CONTEXT </arg> 
 */
#define logTrace(area, context, ...) appLog(SAFplus::APP_LOG,SAFplus::LOG_SEV_TRACE,0, area, context, __VA_ARGS__)
#endif

#define appLog(streamHandle, severity, serviceId, area, context, ...) \
do                                                                      \
{                                                                       \
  SAFplus::logMsgWrite(streamHandle, severity, serviceId, area, context, __FILE__, __LINE__, __VA_ARGS__); \
} while(0)
#endif

//? </section>
