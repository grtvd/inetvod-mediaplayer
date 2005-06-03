/* TError.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
//#include <stdarg.h>

//TODO: #include "CriticalSectionLock.h"
//TODO: #include "PipeTextFiler.h"

namespace asi
{

/******************************************************************************/

class ErrorLevel : public EnumType<ErrorLevelValue, el_Info, el_Error>
{
public:
	ErrorLevel(int t = el_Info) :
		EnumType<ErrorLevelValue, el_Info, el_Error>(t) {}
	ErrorLevel(const char* str);

	const char* c_str() const;
};

/* Field classes */
typedef CStr128 ErrorSource;
typedef CStrVar ErrorMessage;

/******************************************************************************/
#ifdef ERRORDEBUGON

static void ErrorDebuggerMsg(const char* method, const char* text);
static void ErrorFileInit();
static void ErrorFileMsg(const ErrorLevel level, const char* method, const char* text);

/******************************************************************************/

//TODO: static CriticalSectionLock gErrorLock;

static CStrVar gErrSource("Unknown");
static ErrorOutput gOutput = eo_File;
static ErrorFormat gFormat = ef_Default;
static int gErrsOccurred = 0;
static int gMsgsLost = 0;	// Could not be written to error file.
static CStrVar gOutputFileName("Error.out");

#endif
/******************************************************************************/

class ErrorDataLine : public Streamable
{
public:
	TDateTime fDateTime;
	ErrorSource fSource;
	ErrorLevel fLevel;
	ErrorMessage fMessage;
	
public:
	virtual void clear();

	virtual void readFromFiler(DataFiler& dataFiler);
	virtual void writeToFiler(DataFiler& dataFiler);
};

/******************************************************************************/
/******************************************************************************/

ErrorLevel::ErrorLevel(const char* str)
{
	CStr32 value(str);

	value.toUpper();

	if(value == "INFO")
		fT = el_Info;
	else if(value == "WARNING")
		fT = el_Warning;
	else if(value == "ERROR")
		fT = el_Error;
	else
		throw ASIException("ErrorLevel::ErrorLevel", "invalid str");
}

/******************************************************************************/

const char* ErrorLevel::c_str() const
{
	switch(fT)
	{
		case el_Info:
			return("Info");
		case el_Warning:
			return("Warning");
		case el_Error:
			return("Error");
		default:
			break;
	}

	throw ASIException("ErrorLevel::c_str", "invalid fT");
}

/******************************************************************************/
/******************************************************************************/

void ErrorDataLine::clear()
{
	fDateTime = TDateTime();
	fSource.clear();
	fLevel.clear();
	fMessage.clear();
}

/******************************************************************************/

void ErrorDataLine::readFromFiler(DataFiler& dataFiler)
{
	fDateTime = dataFiler.readDateTime(dtf_M_D_YYYY_H_MM_SS_AM);
	//TODO: fDateTime += dataFiler.readTime(TF_HH_MM_SSA);
	fSource = dataFiler.readString().c_str();
	fLevel = ErrorLevel(dataFiler.readString().c_str());
	fMessage = dataFiler.readString().c_str();
}

/******************************************************************************/

void ErrorDataLine::writeToFiler(DataFiler& dataFiler)
{
	dataFiler.writeDateTime(fDateTime,dtf_M_D_YYYY_H_MM_SS_AM);
	//TODO: dataFiler.writeTime(fDateTime,TF_HH_MM_SSA);
	dataFiler.writeString(fSource.c_str());
	dataFiler.writeString(fLevel.c_str());
	dataFiler.writeString(fMessage.c_str());
}

/******************************************************************************/
/******************************************************************************/
#if defined(ERRORDEBUGON)

void ErrorSetOutputFileName(const char* fileName)
{
	//TODO: Guard guard(gErrorLock);

	gOutputFileName.copy(fileName);
}

#endif
/******************************************************************************/

void ErrorInit(const char* source,const ErrorOutput output,
	const ErrorFormat format)
{
#if defined(ERRORDEBUGON)
	//TODO: Guard guard(gErrorLock);

	gErrSource.copy(source);
	gOutput = output;
	gFormat = format;

	if(gOutput == eo_File)
		ErrorFileInit();
#endif
}

/******************************************************************************/

void ErrorDispose()
{
	if(gMsgsLost > 0)
		ErrorMsg(el_Error, "ErrorDispose", "%d messages lost", gMsgsLost);

	if(gErrsOccurred && ((gOutput == eo_Debugger) || (gOutput == eo_File)))
		printf("Errors have been sent to %s.\n", (gOutput == eo_Debugger) ? "the Debugger" : "\"Error.out\"");
}

/******************************************************************************/
/******************************************************************************/
#ifdef ERRORDEBUGON

void ErrorMsgNoVarg(const ErrorLevelValue level, const char* method, const char* text)
{
	try
	{
		//TODO: Guard guard(gErrorLock);

		++gErrsOccurred;

		switch(gOutput)
		{
			case eo_Debugger:
			default:
				ErrorDebuggerMsg(method, text);
				break;
			#if 0	//BOB
			case eo_Screen:
				msgWinStr(MW_OK,(char*)(const char*)text);	//BOB
				break;
			#endif
			case eo_File:
				ErrorFileMsg(ErrorLevel(level), method, text);
				break;
		}
	}
	catch(...)
	{
		++gMsgsLost;
	}
}

/******************************************************************************/

void ErrorMsg(const ErrorLevelValue level, const char* method, const char* format, ...)
{
	try
	{
		//TODO: Guard guard(gErrorLock);

		va_list argList;
		CStrVar text;

		++gErrsOccurred;

		va_start(argList, format);
		text.copyVargList(format, argList, false);
		va_end(argList);

		switch(gOutput)
		{
			case eo_Debugger:
			default:
				ErrorDebuggerMsg(method, text.c_str());
				break;
			#if 0	//BOB
			case eo_Screen:
				msgWinStr(MW_OK, text.c_str());	//BOB
				break;
			#endif
			case eo_File:
				ErrorFileMsg(level, method, text.c_str());
				break;
		}
	}
	catch(...)
	{
		++gMsgsLost;
	}
}

/******************************************************************************/

void ErrorMsg(const char* method, const char* format, ...)
{
	try
	{
		//TODO: Guard guard(gErrorLock);

		va_list argList;
		CStrVar text;

		++gErrsOccurred;

		va_start(argList, format);
		text.copyVargList(format, argList, false);
		va_end(argList);

		switch(gOutput)
		{
			case eo_Debugger:
			default:
				ErrorDebuggerMsg(method, text.c_str());
				break;
			#if 0	//BOB
			case eo_Screen:
				msgWinStr(MW_OK, text.c_str());	//BOB
				break;
			#endif
			case eo_File:
				ErrorFileMsg(el_Info, method, text.c_str());
				break;
		}
	}
	catch(...)
	{
		++gMsgsLost;
	}
}

/******************************************************************************/
/******************************************************************************/

void ErrorDebuggerMsg(const char* method, const char* text)
{
//TODO:
	printf("%s: %s\n", method, text);
	//#if defined(_TOOL_MAC_)
	//{
	//	DebugStr(CtoPstr(text));
	//	PtoCstr((uchar*)text);
	//}
	//#elif defined(_TOOL_DOS_)
	//{
	//	puts(text);
	//	puts("\n");
	//}
	//#elif defined(_TOOL_WIN_)
	//	#if defined(_TOOL_NTCON_)
	//	{
			//HANDLE hStdOut;
			//DWORD bytesWritten;

			//if((hStdOut = GetStdHandle(STD_OUTPUT_HANDLE)) != INVALID_HANDLE_VALUE)
			//{
			//	WriteConsole(hStdOut, method, strlen(method), &bytesWritten, NULL);
			//	WriteConsole(hStdOut, ": ", 2, &bytesWritten, NULL);
			//	WriteConsole(hStdOut, text, strlen(text), &bytesWritten, NULL);
			//	WriteConsole(hStdOut, "\n", 1, &bytesWritten, NULL);
			//}
	//	}
	//	#else
	//	{
	//		OutputDebugString(text);
	//		OutputDebugString("\n");
	//	}
	//	#endif
	//#else
	//	#error ErrorDebuggerMsg: no environment defined
	//#endif
}

/******************************************************************************/

void ErrorFileInit(void)
{
	ErrorFileMsg(el_Info, "ErrorFileInit", "########################################" /*"########################################"*/);
}

/******************************************************************************/

void ErrorFileMsg(const ErrorLevel level, const char* method, const char* text)
{
	if(gFormat == ef_Default)
	{
		FILE *fp;
	
		if((fp = fopen(gOutputFileName.c_str(), "a")) != NULL)
		{
			fputs(TDateTime::getSystemDateTime().c_str(dtf_M_D_YYYY_H_MM_SS_AM), fp);
			fputs(": ", fp);

			fputs(method, fp);
			fputs(": ", fp);

			fputs(text, fp);
			fputs("\n", fp);
			fclose(fp);
		}
		else
			++gMsgsLost;
	}
	else if(gFormat == ef_Pipe)
	{
//TODO:
#if FALSE
		try
		{
			auto_ptr<TFileStream> fileStream;
			auto_ptr<TTextFiler> dataFiler;
			TDateTime today = TDateTime::CurrentDateTime();
			int attempts;

			// Attempt to open file with pause between each try.
			for(attempts = 5; (fileStream.get() == NULL) && (attempts >= 0); --attempts)
			{
				try
				{
					#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
					if(!FileExists(gOutputFileName.c_str()))	// Create a new, empty file.
						fileStream.reset(new TFileStream(gOutputFileName.c_str(),
							fmCreate | /* fmShareDenyWrite */ fmShareExclusive));
					else
						fileStream.reset(new TFileStream(gOutputFileName.c_str(),
							fmOpenReadWrite | /* fmShareDenyWrite */ fmShareExclusive));
					#else
					if(!FileExists(gOutputFileName.c_str()))	// Create a new, empty file.
						fileStream = auto_ptr<TFileStream>(new TFileStream(gOutputFileName.c_str(),
							fmCreate | /* fmShareDenyWrite */ fmShareExclusive));
					else
						fileStream = auto_ptr<TFileStream>(new TFileStream(gOutputFileName.c_str(),
							fmOpenReadWrite | /* fmShareDenyWrite */ fmShareExclusive));
					#endif
				}
				catch(...)
				{
					tPauseTenths(2);
				}
			}
			if(fileStream.get() != NULL)
			{
				fileStream->Seek(0,soFromEnd);

				//BOB Later, new formats can be added by creating different TDataFilers
				dataFiler.reset(new TPipeTextFiler(fileStream.release(),true));

				dataFiler->writeDate(today,DF_MM_DD_YYYY);
				dataFiler->writeTime(today,TF_HH_MM_SSA);
				dataFiler->writeString(gErrSource.c_str());
				dataFiler->writeString(level.c_str());
				dataFiler->writeString(text);
				dataFiler->writeEOL();
			}
			else
				++gMsgsLost;
		}
		catch(...)
		{
			++gMsgsLost;
		}
#else
		++gMsgsLost;
#endif
	}
	else
		++gMsgsLost;
}

#endif
/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/
