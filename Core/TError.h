/* TError.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TErrorH
#define TErrorH

//#include "CommType.h"

namespace asi
{

/******************************************************************************/

#ifdef ERRORDEBUGON
	#define ERRORDEBUG(x)	x
#else
	#define ERRORDEBUG(x)
#endif

/******************************************************************************/

#define CATCH_ERROR_NOACTION(method)																	\
	catch(const ASIException& e)																		\
	{																									\
		ERRORDEBUG( ErrorMsg(method, "Caught ASIException(%s, %s)", e.getMethod(), e.getMsg()); )		\
	}																									\
	catch(const exception& e)																			\
	{																									\
		ERRORDEBUG( ErrorMsg(method, "Caught exception(%s)", e.what()); )								\
	}																									\
	catch(const exception* e)																			\
	{																									\
		ERRORDEBUG( ErrorMsg(method, "Caught exception(%s)", e->what()); )								\
	}																									\
	catch(...)																							\
	{																									\
		ERRORDEBUG( ErrorMsg(method, "Caught unknown exception"); )										\
	}

/******************************************************************************/

/* Error Output */
enum ErrorOutput
{
	eo_File = 0,
	eo_Debugger
	//BOB eo_Screen
};

/* Error Format */
enum ErrorFormat
{
	ef_Default = 10,
	ef_Pipe,
};

/* Error Level */
enum ErrorLevelValue
{
	el_Info = 20,
	el_Warning,
	el_Error
};

/******************************************************************************/

void ErrorInit(const char* source, const ErrorOutput output = eo_File,
	const ErrorFormat format = ef_Default);
void ErrorDispose();

#ifdef ERRORDEBUGON
void ErrorSetOutputFileName(const char* fileName);		// can be called before ErrorInit
void ErrorMsgNoVarg(const ErrorLevelValue level, const char* method, const char* text);
void ErrorMsg(const ErrorLevelValue level, const char* method, const char* format, ...);
void ErrorMsg(const char* method, const char* format, ...);
#endif

/******************************************************************************/

}; //namespace asi

#endif //TErrorH
/******************************************************************************/
/******************************************************************************/
