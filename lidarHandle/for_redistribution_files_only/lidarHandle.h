//
// MATLAB Compiler: 8.5 (R2022b)
// Date: Wed Jun 21 14:29:02 2023
// Arguments:
// "-B""macro_default""-W""cpplib:lidarHandle,all,version=1.0""-T""link:lib""-d"
// "D:\qt\QTWorkSpace\upperComputer\lidarHandle\for_testing""-v""D:\Documents\MA
// TLAB\附件2\lidarHandle.m"
//

#ifndef lidarHandle_h
#define lidarHandle_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_lidarHandle_C_API 
#define LIB_lidarHandle_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_lidarHandle_C_API 
bool MW_CALL_CONV lidarHandleInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_lidarHandle_C_API 
bool MW_CALL_CONV lidarHandleInitialize(void);

extern LIB_lidarHandle_C_API 
void MW_CALL_CONV lidarHandleTerminate(void);

extern LIB_lidarHandle_C_API 
void MW_CALL_CONV lidarHandlePrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_lidarHandle_C_API 
bool MW_CALL_CONV mlxLidarHandle(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_lidarHandle
#define PUBLIC_lidarHandle_CPP_API __declspec(dllexport)
#else
#define PUBLIC_lidarHandle_CPP_API __declspec(dllimport)
#endif

#define LIB_lidarHandle_CPP_API PUBLIC_lidarHandle_CPP_API

#else

#if !defined(LIB_lidarHandle_CPP_API)
#if defined(LIB_lidarHandle_C_API)
#define LIB_lidarHandle_CPP_API LIB_lidarHandle_C_API
#else
#define LIB_lidarHandle_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_lidarHandle_CPP_API void MW_CALL_CONV lidarHandle(int nargout, mwArray& dataZtj, mwArray& dataDensity, const mwArray& filename);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
