/* TString.ccpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/

#define MAX_VARG_STR	1024		// Largest Varg string, this should be changed so it is not needed

/******************************************************************************/

ushort CStrVar::fInitGrowSize = 64;
ushort CStrVar::fMinGrowSize = 32;

/******************************************************************************/

enum TVargListTypeCharEnum
{
	vtc_Undefined = 0,
	vtc_SignedInteger,
	vtc_UnsignedInteger,
	vtc_FloatingPoint,
	vtc_Character,
	vtc_String,
	vtc_Percent,
	vtc_PointerToInt,
	vtc_Pointer,
};
#define vtc_Last vtc_Pointer
class TVargListTypeChar : public EnumType<TVargListTypeCharEnum,vtc_Undefined,
	vtc_Pointer>
{
public:
	explicit TVargListTypeChar(int t = vtc_Undefined) :
		EnumType<TVargListTypeCharEnum,vtc_Undefined,vtc_Last>(t) {}
	explicit TVargListTypeChar(const char ch);

	long getWidth() const;
};

/******************************************************************************/

static bool tIsBinaryChar(char ch);
static bool tStrVargListGetNext(PConstChar& fmtStr,TVargListTypeChar& argType,
	int& numSkips,int& fieldWidth);
static long tStrVargListSize(const char* fmtStr,va_list argList);

/******************************************************************************/
/******************************************************************************/

/* This function copies src string to dst string checking dstsize. Dst string
	is padded with NULLs */

char* tStrCpy(char* dst,short dstsize,const char* src)
{
	short srclen = cast2short(STRLEN(src));

	if(srclen < 0)		// If src points to a bad string, strlen may overflow
	{					//  and return a negative length.
		srclen = 0;
		ERRORDEBUG( ErrorMsg("tStrCpy", "srclen (%d) < 0",srclen); );
	}

	if(srclen < dstsize - 1)
	{
		strncpy(dst,src,srclen);
		memset(&dst[srclen],0,dstsize - srclen);
	}
	else
	{
		strncpy(dst,src,dstsize - 1);
		dst[dstsize - 1] = '\0';
	}

	return(dst);
}

/******************************************************************************/

/* This function copies srcnum bytes from src string to dst string checking
	dstsize. Dst string	is padded with NULLs */

char* tStrNCpy(char* dst,short dstsize,const char* src,short srcnum)
{
	if(srcnum < dstsize - 1)
	{
		strncpy(dst,src,srcnum);
		memset(&dst[srcnum],0,dstsize - srcnum);
	}
	else
	{
		strncpy(dst,src,dstsize - 1);
		dst[dstsize - 1] = '\0';
	}

	return(dst);
}

/******************************************************************************/

char* tStrCpyVargList(char* dst,short dstsize,const char* fmt,va_list argList)
{
	static char bigStr[MAX_VARG_STR];

	if((dst == NULL) || (fmt == NULL))
		return(dst);

	vsprintf(bigStr,fmt,argList);

	return(tStrCpy(dst,dstsize,bigStr));
}

/******************************************************************************/

char* tStrCpyVarg(char* dst,short dstsize,const char* fmt,...)
{
	va_list argList;

	va_start(argList,fmt);
	return(tStrCpyVargList(dst,dstsize,fmt,argList));
}
				
/******************************************************************************/

/* This function concats src string to dst string checking dstsize. Dst string
	is padded with NULLs */

char* tStrCat(char* dst,short dstsize,const char* src)
{
	short dstpos = cast2short(STRLEN(dst));
	short srclen = cast2short(STRLEN(src));

	if(dstpos < 0)		// If dst points to a bad string, strlen may overflow
	{					//  and return a negative length.
		dstpos = 0;
		ERRORDEBUG( ErrorMsg("tStrCat", "dstpos (%d) < 0",dstpos); );
	}

	if(srclen < 0)		// If src points to a bad string, strlen may overflow
	{					//  and return a negative length.
		srclen = 0;
		ERRORDEBUG( ErrorMsg("tStrCat", "srclen (%d) < 0",srclen); );
	}

	dstsize -= dstpos;
	if(srclen < dstsize - 1)
	{
		strncpy(&dst[dstpos],src,srclen);
		memset(&dst[dstpos + srclen],0,dstsize - srclen);
	}
	else
	{
		strncpy(&dst[dstpos],src,dstsize - 1);
		dst[dstpos + dstsize + - 1] = '\0';
	}

	return(dst);
}

/******************************************************************************/

/* This function concats srcnum bytes from src string to dst string checking
	dstsize. Dst string	is padded with NULLs */

char* tStrNCat(char* dst,short dstsize,const char* src,short srcnum)
{
	short dstpos = cast2short(STRLEN(dst));

	if(dstpos < 0)		// If dst points to a bad string, strlen may overflow
	{					//  and return a negative length.
		dstpos = 0;
		ERRORDEBUG( ErrorMsg("tStrNCat", "dstpos (%d) < 0",dstpos); );
	}

	dstsize -= dstpos;
	if(srcnum < dstsize - 1)
	{
		strncpy(&dst[dstpos],src,srcnum);
		memset(&dst[dstpos + srcnum],0,dstsize - srcnum);
	}
	else
	{
		strncpy(&dst[dstpos],src,dstsize - 1);
		dst[dstpos + dstsize + - 1] = '\0';
	}

	return(dst);
}

/******************************************************************************/

char* tStrCatVargList(char* dst,short dstsize,const char* fmt,va_list argList)
{
	static char bigStr[MAX_VARG_STR];

	if((dst == NULL) || (fmt == NULL))
		return(dst);

	vsprintf(bigStr,fmt,argList);

	return(tStrCat(dst,dstsize,bigStr));
}
				
/******************************************************************************/

char* tStrCatVarg(char* dst,short dstsize,const char* fmt,...)
{
	va_list argList;

	va_start(argList,fmt);
	return(tStrCatVargList(dst,dstsize,fmt,argList));
}
				 
/******************************************************************************/

/* This function either pads or truncates a string so it is the 'len' length */

char* tFitStr(char* str,int len)
{
	int i,length;

	length = STRLEN(str);
	if(length < len)
		for(i = length; i < len; i++)
			str[i] = ' ';
	str[len] = '\0';

	return(str);
}

/******************************************************************************/

char* tSqueezeStr(char* str)
{
	short i;

	for(i = cast2short(STRLEN(str) - 1); (i >= 0) && (str[i] == ' '); i--)
		str[i] = '\0';

	return(str);
}

/******************************************************************************/

char* tCompressStr(char* str,short which)
{
	short i,len;
	short j;

	if(which == csw_All)
	{
		len = cast2short(STRLEN(str));
		for(i = j = 0; i < len; i++)
		{
			if(str[i] != ' ')
				str[j++] = str[i];
		}
		str[j] = '\0';
	}
	else
	{
		if(which & csw_Trailing)
		{
			for(i = cast2short(STRLEN(str)) - 1; (i >= 0) && (str[i] == ' '); i--)
				str[i] = '\0';
		}

		if(which & csw_Leading)
		{
			len = cast2short(STRLEN(str));
			for(i = 0; (i < len) && (str[i] == ' '); i++)
				;

			if(i > 0)	// Any leading spaces found
			{
				for(j = 0; (i < len); i++)
					str[j++] = str[i];
				str[j] = '\0';
			}
		}
	}

	return(str);
}

/******************************************************************************/

char* tStrToUpper(char* str)
{
	int i;

	for(i = 0; str[i]; i++)
		if(islower(str[i]))
			str[i] -= cast2char('a' - 'A');

	return(str);
}

/******************************************************************************/

char* tStrToLower(char* str)
{
	int i;

	for(i = 0; str[i]; i++)
		if(isupper(str[i]))
			str[i] += cast2char('a' - 'A');

	return(str);
}

/******************************************************************************/

bool tStrMatchWild(const char* str,const char* strMatch)
{
	for (; *str != '\0' && *strMatch != '\0'; str++, strMatch++ )
	{
		if ( *strMatch == '?' )
			continue;

		if ( *strMatch == '*' )
		{
			strMatch++;
			while ( !tStrMatchWild( str, strMatch ) )
			{
				if ( *str == '\0' )
					return FALSE;
				str++;
			}

			return TRUE;
		}

		if ( *str != *strMatch )
			return FALSE;
	}

	while ( *strMatch == '*' )
		strMatch++;

	return ( *str == '\0' && *strMatch == '\0' );
}

/******************************************************************************/

bool tStrIMatchWild(const char* str,const char* strMatch)
{
	for (; *str != '\0' && *strMatch != '\0'; str++, strMatch++ )
	{
		if ( *strMatch == '?' )
			continue;

		if ( *strMatch == '*' )
		{
			strMatch++;
			while ( !tStrIMatchWild( str, strMatch ) )
			{
				if ( *str == '\0' )
					return FALSE;
				str++;
			}

			return TRUE;
		}

		if ( toupper(*str) != toupper(*strMatch))
			return FALSE;
	}

	while ( *strMatch == '*' )
		strMatch++;

	return ( *str == '\0' && *strMatch == '\0' );
}

/******************************************************************************/
/******************************************************************************/

char* tCopyCRLFtoCR(char* dst,short dstsize,const char* src)
{
	short srclen = cast2short(STRLEN(src));
	short i,j;

	for(i = j = 0; (i < srclen) && (j < dstsize - 1); i++)
	{
		if((src[i] == '\r') && (src[i + 1] == '\n'))
		{
			dst[j++] = '\r';
			i++;
		}
		else
			dst[j++] = src[i];
	}
	dst[j] = '\0';
	return(dst);
}

/******************************************************************************/

char* tCopyCRtoCRLF(char* dst,short dstsize,const char* src)
{
	short srclen = cast2short(STRLEN(src));
	short i,j;

	for(i = j = 0; (i < srclen) && (j < dstsize - 1); i++)
	{
		if(src[i] == '\r')
		{
			if(j < dstsize - 2)
			{
				dst[j++] = '\r';
				dst[j++] = '\n';
			}
			else
				break;
		}
		else
			dst[j++] = src[i];
	}
	dst[j] = '\0';
	return(dst);
}

/******************************************************************************/

/* Chars are binary if not printable.  Since back slashs "\" and double quotes (")
	interfer with text file formats, also consider then binary. */

bool tIsBinaryChar(char ch)
{
	return(!isprint(ch) || (ch == '\"') || (ch == '\\') ||
		(ch == '|'));
}

/******************************************************************************/

bool tStrHasBinary(const char* str)
{
	const char* pTempStr = str;

	while(*pTempStr)
		if(tIsBinaryChar(*(pTempStr++)))
			return(TRUE);

	return(FALSE);
}

/******************************************************************************/

/* This function replaces binary chars with octal text. (ie. 0x0A => "\012").
	A few special binary chars get changed to C syntax. (ie. 0x0A => "\n",
	0x0D => "\r"). */

char* tCopyBintoText(char* dst,short dstsize,const char* src)
{
	short srclen = cast2short(STRLEN(src));
	short i,j;
	bool canFit = TRUE;

	for(i = j = 0; (i < srclen) && canFit; i++)
	{
		if(tIsBinaryChar(src[i]))
		{
			if(src[i] == '\r')
			{
				if(j < dstsize - 2)
				{
					dst[j++] = '\\';
					dst[j++] = 'r';
				}
				else
					canFit = FALSE;
			}
			else if(src[i] == '\n')
			{
				if(j < dstsize - 2)
				{
					dst[j++] = '\\';
					dst[j++] = 'n';
				}
				else
					canFit = FALSE;
			}
			else if(src[i] == '\t')
			{
				if(j < dstsize - 2)
				{
					dst[j++] = '\\';
					dst[j++] = 't';
				}
				else
					canFit = FALSE;
			}
			else
			{
				char tempStr[10];
				short templen;

				sprintf(tempStr,"\\%03o",(unsigned int)(uchar)src[i]);
				templen = cast2short(STRLEN(tempStr));

				if(j < dstsize - templen)
				{
					memcpy(&dst[j],tempStr,templen);
					j += templen;
				}
				else
					canFit = FALSE;
			}
		}
		else
		{
			if(j < dstsize - 1)
				dst[j++] = src[i];
			else
				canFit = FALSE;
		}
	}
	dst[j] = '\0';

	return(dst);
}

/******************************************************************************/

char* tCopyTexttoBin(char* dst,short dstsize,const char* src)
{
	short srclen = cast2short(STRLEN(src));
	short i,j;

	for(i = j = 0; (i < srclen) && (j < dstsize - 1); i++)
	{
		if(src[i] == '\\')
		{
			if(tolower(src[i + 1]) == 'r')
			{
				dst[j++] = '\r';
				i++;
			}
			else if(tolower(src[i + 1]) == 'n')
			{
				dst[j++] = '\n';
				i++;
			}
			else if(tolower(src[i + 1]) == 't')
			{
				dst[j++] = '\t';
				i++;
			}
			else
			{
				uchar val = 0;
				short vallen = 0;

				i++;
				while((src[i] >= '0') && (src[i] <= '7') &&
					(i < srclen) && (vallen < 3))
				{
					val = cast2byte((val * 8) + (src[i++] - '0'));
					vallen++;
				}
				i--;

				dst[j++] = val;
			}
		}
		else
			dst[j++] = src[i];
	}
	dst[j] = '\0';

	return(dst);
}

/******************************************************************************/

ulong tHexStrToULong(const char* str)
{
	ulong value = 0;
	int i, len = STRLEN(str);
	char hex;

	for(i = 0; i < len; i++)
	{
		hex = str[i];
		if(!isxdigit(hex))
			return 0;
		if(isdigit(hex))
			hex -= '0';
		else if((hex >= 'A') && (hex <= 'F'))
			hex = (hex - 'A') + 10;
		else
			hex = (hex - 'a') + 10;

		value = (value << 4UL) + (ulong)hex;
	}

	return value;
}

/******************************************************************************/
/******************************************************************************/

bool tStrVargListGetNext(PConstChar& fmtStr,TVargListTypeChar& argType,
	int& numSkips,int& fieldWidth)
{
	const char* nextStart = fmtStr;
	bool decimalFound = false;

	if(!tStrHasLen(fmtStr))
		return(false);

	numSkips = 0;
	fieldWidth = 0;
	argType.clear();
	nextStart = strstr(nextStart,"%");
	if(nextStart != NULL)
	{
		nextStart++;
		argType = TVargListTypeChar(*nextStart);
		//check for "%%" case
		if(argType == vtc_Percent)
		{
			nextStart++;
			fmtStr = nextStart;
			return(true);
		}

		while(argType.isUndefined() && tStrHasLen(nextStart))
		{
			if(isdigit(*nextStart))
			{
				if(!decimalFound)
					fieldWidth = (fieldWidth * 10) + (*nextStart - '0');
			}
			else if(*nextStart == '.')
				decimalFound = true;
			else if(*nextStart == '*')
				numSkips++;
			nextStart++;
			argType = TVargListTypeChar(*nextStart);
		}

		if(!tStrHasLen(nextStart))
		{
			//BOB: restore CommErrMsg(el_Error, "tStrVargListGetNext", "!tStrHasLen(nextStart)");
			return(false);
		}

		fmtStr = nextStart;
		return(true);
	}

	return(false);
}

/******************************************************************************/

long tStrVargListSize(const char* fmtStr,va_list argList)
{
	long size;
	TVargListTypeChar argType;
	int numSkips;
	int fieldWidth;

	size = STRLEN(fmtStr);
	while(tStrVargListGetNext(fmtStr,argType,numSkips,fieldWidth))
	{
		// skip width specifiers if they exist
		while(numSkips > 0)
		{
			va_arg(argList,int);
			numSkips--;
		}

		if((argType != vtc_String) && !argType.isUndefined())
		{
			size += argType.getWidth();
			switch(argType)
			{
				case vtc_SignedInteger:
				case vtc_UnsignedInteger:
				case vtc_Pointer:
				case vtc_Character:
					va_arg(argList,int);
					break;
				case vtc_FloatingPoint:
					va_arg(argList,double);
					break;
				case vtc_PointerToInt:
					va_arg(argList,int*);
					break;
				default:
					break;
			}
		}
		else
		{
			if(!argType.isUndefined())
			{
				char* tempStr = va_arg(argList,char*);
				int strSize = STRLEN(tempStr);
				size += max(strSize,fieldWidth);
			}
			else
				;	//BOB: restore CommErrMsg(el_Error,"tStrVargListSize", "argType.isUndefined()");
		}
	}

	return(size);
}

/******************************************************************************/
/******************************************************************************/

TVargListTypeChar::TVargListTypeChar(const char ch)
{
	if((ch == 'd') || (ch == 'i'))
		fT = vtc_SignedInteger;
	else if((ch == 'o') || (ch == 'u') || (ch == 'x') || (ch == 'X'))
		fT = vtc_UnsignedInteger;
	else if((ch == 'f') || (ch == 'e') || (ch == 'E') || (ch == 'g') || (ch == 'G'))
		fT = vtc_FloatingPoint;
	else if(ch == 'c')
		fT = vtc_Character;
	else if(ch == 's')
		fT = vtc_String;
	else if(ch == '%')
		fT = vtc_Percent;
	else if(ch == 'n')
		fT = vtc_PointerToInt;
	else if(ch == 'p')
		fT = vtc_Pointer;
	else
		fT = vtc_Undefined;
}

/******************************************************************************/

long TVargListTypeChar::getWidth() const
{
	switch(fT)
	{
		case vtc_SignedInteger:
		case vtc_UnsignedInteger:
		case vtc_FloatingPoint:
		case vtc_Character:
		case vtc_Pointer:
			return(64);
		case vtc_Percent:
			return(1);
		case vtc_PointerToInt:
			return(0);
		default:
			break;
	}
	//BOB: restore CommErrMsg(el_Error,"TVargListTypeChar::getWidth()", "invalid fT");
	return(0);
}

/******************************************************************************/
/******************************************************************************/

CStrVar CStrVar::build(const char* fmt,...)
{
	va_list argList;
	CStrVar text;

	va_start(argList,fmt);
	text.copyVargList(fmt,argList,false);
	va_end(argList);

	return(text);
}

/******************************************************************************/

void CStrVar::init(long needSize,bool keepData)
{
	if(fDataSize >= needSize)
		return;
	if(needSize <= 0)
	{
		clear();
		return;
	}

	long newDataSize;
	long growSets;

	growSets = ((needSize - 1) / (long)fGrowSize) + 1;
	newDataSize = growSets * (long)fGrowSize;

	auto_ptr<char> newData(new char[newDataSize]);

	if(keepData && (fData != NULL) && (fDataSize > 0))
		memcpy(newData.get(),fData,fDataSize);
	else
		fDataLen = 0;

	if(fData != NULL)
		delete fData;
	fData = NULL;
	fDataSize = 0;

	fData = newData.release();
	fDataSize = newDataSize;
}

/******************************************************************************/

void CStrVar::copyData(const char* data,long dataLen)
{
	if(dataLen > 0)
	{
		init(dataLen + 1,false);

		memcpy(fData,data,dataLen);
		fDataLen = dataLen;
		*(fData + fDataLen) = '\0';
	}
	else
		clear();
}

/******************************************************************************/

void CStrVar::concatData(const char* data,long dataLen)
{
	if(dataLen > 0)
	{
		init(fDataLen + dataLen + 1,true);

		memcpy(fData + fDataLen,data,dataLen);
		fDataLen += dataLen;
		*(fData + fDataLen) = '\0';
	}
}

/******************************************************************************/

/* Determine if strlen(data) < minLen, but we don't want to assume "data" is 
	NULL terminated. */

long CStrVar::minStrLen(const char* data,long minLen)
{
	long i;

	for(i = 0; i < minLen; i++, data++)
		if(*data == '\0')
			return(i);

	return(minLen);
}

/******************************************************************************/

void CStrVar::clear()
{
	if(fData != NULL)
		delete fData;
	fData = NULL;
	fDataLen = 0;
	fDataSize = 0;
}

/******************************************************************************/

CStrVar& CStrVar::copyVargList(const char* fmt,va_list argList,bool doConcat)
{
	auto_ptr<char> tempAutoStr;
	char tempStr[1024];
	char* pStr;
	long sizeNeeded;

	if(fmt != NULL)
	{
		sizeNeeded = tStrVargListSize(fmt,argList);
		if(sizeNeeded >= cast2long(sizeof(tempStr)))
		{
			#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
			tempAutoStr.reset(new char[sizeNeeded + 1 + 32]);	//BOB extra 32 for sanity
			#else
			tempAutoStr = auto_ptr<char>(new char[sizeNeeded + 1 + 32]);	//BOB extra 32 for sanity
			#endif
			pStr = tempAutoStr.get();
		}
		else
			pStr = tempStr;

		vsprintf(pStr,fmt,argList);
		#ifdef ERRORDEBUGON	//BOB remove later
		{
			int resultSize = STRLEN(pStr);
			if(resultSize > sizeNeeded)
				ErrorMsg(el_Error, "CStrVar::copyVargList", "FATAL: resultSize(%d) > sizeNeeded(%ld) - (%s)",
					resultSize, sizeNeeded, fmt);
		}
		#endif
		if(doConcat)
			concat(pStr);
		else
			copy(pStr);
	}

	return(*this);
}

/******************************************************************************/

CStrVar& CStrVar::compress(short which)
{
	if(fData != NULL)
	{
		tCompressStr(fData,which);
		fDataLen = STRLEN(fData);
	}

	return(*this);
}

/******************************************************************************/

bool operator==(const char* lhs,const CStrVar& rhs)
	{ return(CStrVar(lhs) == rhs); }
bool operator!=(const char* lhs,const CStrVar& rhs)
	{ return(CStrVar(lhs) != rhs); }
bool operator<(const char* lhs,const CStrVar& rhs)
	{ return(CStrVar(lhs) < rhs); }
bool operator<=(const char* lhs,const CStrVar& rhs)
	{ return(CStrVar(lhs) <= rhs); }
bool operator>(const char* lhs,const CStrVar& rhs)
	{ return(CStrVar(lhs) > rhs); }
bool operator>=(const char* lhs,const CStrVar& rhs)
	{ return(CStrVar(lhs) >= rhs); }

/******************************************************************************/
/******************************************************************************/

//DefineFixStrClassCode(CStr32)
//DefineFixStrClassCode(CStr64)
//DefineFixStrClassCode(CStr128)
//DefineFixStrClassCode(CStr256)
//DefineFixStrClassCode(CStr512)
//DefineFixStrClassCode(CStr1024)

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
