/* TString.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TStringH
#define TStringH

namespace asi
{

/******************************************************************************/

/* tCompressStr which */
enum CompressStrWhich
{
	csw_All =		0x00,	// Leading, Trailing, and Middle
	csw_Leading =	0x01,	// Can be OR'ed together
	csw_Trailing = 	0x02
};

char* tStrCpy(char* dst,short dstsize,const char* src);
char* tStrNCpy(char* dst,short dstsize,const char* src,short srcnum);
char* tStrCpyVargList(char* dst,short dstsize,const char* fmt,va_list argList);
char* tStrCpyVarg(char* dst,short dstsize,const char* fmt,...);

char* tStrCat(char* dst,short dstsize,const char* src);
char* tStrNCat(char* dst,short dstsize,const char* src,short srcnum);
char* tStrCatVargList(char* dst,short dstsize,const char* fmt,va_list argList);
char* tStrCatVarg(char* dst,short dstsize,const char* fmt,...);

char* tFitStr(char* str,int len);
char* tSqueezeStr(char* str);
char* tCompressStr(char* str,short which);
char* tStrToUpper(char* str);
char* tStrToLower(char* str);
bool tStrMatchWild(const char* str,const char* strMatch);
bool tStrIMatchWild(const char* str,const char* strMatch);

char* tCopyCRLFtoCR(char* dst,short dstsize,const char* src);
char* tCopyCRtoCRLF(char* dst,short dstsize,const char* src);
bool tStrHasBinary(const char* str);
char* tCopyBintoText(char* dst,short dstsize,const char* src);
char* tCopyTexttoBin(char* dst,short dstsize,const char* src);

ulong tHexStrToULong(const char* str);

#ifdef __cplusplus

inline bool tStrHasLen(const char* str) { return((str == NULL) ? false : (str[0] != '\0')); }
inline void tStrNull(char* str) { str[0] = '\0'; }

#else

#define tStrHasLen(str)		((bool)((str) == NULL) ? false : (((const char*)(str))[0] != '\0'))
#define tStrNull(str)		(((char*)(str))[0] = '\0')

#endif	//__cplusplus

#define STRLEN(str) (((str) == NULL) ? 0 : strlen(str))

/******************************************************************************/

#ifdef __cplusplus

template<int StrSize>
struct StrClass
{
protected:
	char data[StrSize];

public:
	StrClass(const char* str = NULL) { copy(str); }

	StrClass& operator=(const StrClass& str) { return(copy(str)); }
	StrClass& operator=(const char* str) { return(copy(str)); }

	StrClass& operator+=(const StrClass& str) { return(concat(str)); }
	StrClass& operator+=(const char* str) { return(concat(str)); }

	bool operator==(const StrClass& str) const
		{ return(strcmp(data,str.data) == 0); }
	bool operator==(const char* str) const
		{ return(strcmp(data,str) == 0); }

	bool operator<(const StrClass& str) const
		{ return(strcmp(data,str.data) < 0); }
	bool operator<(const char* str) const
		{ return(strcmp(data,str) < 0); }

	bool operator<=(const StrClass& str) const
		{ return(strcmp(data,str.data) <= 0); }
	bool operator<=(const char* str) const
		{ return(strcmp(data,str) <= 0); }

	bool operator>(const StrClass& str) const
		{ return(strcmp(data,str.data) > 0); }
	bool operator>(const char* str) const
		{ return(strcmp(data,str) > 0); }

	bool operator>=(const StrClass& str) const
		{ return(strcmp(data,str.data) >= 0); }
	bool operator>=(const char* str) const
		{ return(strcmp(data,str) >= 0); }

	bool operator!=(const StrClass& str) const
		{ return(strcmp(data,str.data) != 0); }
	bool operator!=(const char* str) const
		{ return(strcmp(data,str) != 0); }

	//operator const char*() const { return(data); }
	char operator[](int pos) const { return(data[pos]); }
	const char* c_str() const { return(data); }

	short len() const { return((short)strlen(data)); }
	bool hasLen() const { return(data[0] != '\0'); }
	short maxLen() const { return(sizeof(data) - 1); }

	void clear() { memset(data,0,sizeof(data)); }
	StrClass& copy(const StrClass& str)
		{ tStrCpy(data,sizeof(data),str.data); return(*this); }
	StrClass& copy(const char* str = NULL)
		{ tStrCpy(data,sizeof(data),(str == NULL) ? "" : str); return(*this); }

	StrClass& ncopy(const StrClass& str,short strnum)
		{ tStrNCpy(data,sizeof(data),str.data,strnum); return(*this); }
	StrClass& ncopy(const char* str,short strnum)
		{ tStrNCpy(data,sizeof(data),str,strnum); return(*this); }

	StrClass& copyVargList(const char* fmt,va_list argList)
		{ tStrCpyVargList(data,sizeof(data),fmt,argList); return(*this); }
	StrClass& copyVarg(const char* fmt,...)
	{
		va_list argList;
		va_start(argList,fmt);
		copyVargList(fmt,argList);
		return(*this);
	}

	StrClass& concat(const StrClass& str)
		{ tStrCat(data,sizeof(data),str.data); return(*this); }
	StrClass& concat(const char* str = NULL)
		{ tStrCat(data,sizeof(data),(str == NULL) ? "" : str); return(*this); }

	StrClass& nconcat(const StrClass& str,short strnum)
		{ tStrNCat(data,sizeof(data),str.data,strnum); return(*this); }
	StrClass& nconcat(const char* str,short strnum)
		{ tStrNCat(data,sizeof(data),str,strnum); return(*this); }

	StrClass& concatVargList(const char* fmt,va_list argList)
		{ tStrCatVargList(data,sizeof(data),fmt,argList); return(*this); }
	StrClass& concatVarg(const char* fmt,...)
	{
		va_list argList;
		va_start(argList,fmt);
		concatVargList(fmt,argList);
		return(*this);
	}

	StrClass& compress(short which)
		{ tCompressStr(data,which); return(*this); }
	StrClass& toUpper()
		{ tStrToUpper(data); return(*this); }
	StrClass& toLower()
		{ tStrToLower(data); return(*this); }
};

//#define DeclareCStrGlobal(StrClass)	\
//inline bool operator==(const char* lhs,const StrClass& rhs)	\
//	{ return (strcmp(lhs, rhs.c_str()) == 0); }

//template<class StrClass>
//inline bool operator==(const char* lhs,const StrClass& rhs)
////	{ return (StrClass(lhs) == rhs); }
//	{ return (strcmp(lhs, rhs.c_str()) == 0); }

/******************************************************************************/

class CStrVar
{
protected:
	char* fData;
	long fDataLen;		// Current length of fData string
	long fDataSize;		// Current size of fData allocation
	ushort fGrowSize;	// Grow size of fData for new allocations

public:
	static ushort fInitGrowSize;
	static ushort fMinGrowSize;

public:
	CStrVar(const char* str = NULL) : fData(NULL),fDataLen(0),fDataSize(0),
		fGrowSize(fInitGrowSize) { copy(str); }
	CStrVar(const CStrVar& str) : fData(NULL),fDataLen(0),fDataSize(0),
		fGrowSize(str.fGrowSize) { copy(str); }

	virtual ~CStrVar() { clear(); }

	void setGrowSize(ushort growSize)
		{ fGrowSize = growSize; if(fGrowSize < fMinGrowSize)
			fGrowSize = fMinGrowSize; }

	static CStrVar build(const char* fmt,...);

protected:
	void init(long needSize,bool keepData);
	void copyData(const char* data,long dataLen);
	void concatData(const char* data,long dataLen);
	long minStrLen(const char* data,long minLen);

public:
	CStrVar& operator=(const CStrVar& str) { return(copy(str)); }
	CStrVar& operator=(const char* str) { return(copy(str)); }

	CStrVar& operator+=(const CStrVar& str) { return(concat(str)); }
	CStrVar& operator+=(const char* str) { return(concat(str)); }

	bool operator==(const CStrVar& str) const
		{ return(strcmp(fData,str.fData) == 0); }
	bool operator==(const char* str) const
		{ return(strcmp(fData,str) == 0); }

	bool operator<(const CStrVar& str) const
		{ return(strcmp(fData,str.fData) < 0); }
	bool operator<(const char* str) const
		{ return(strcmp(fData,str) < 0); }

	bool operator<=(const CStrVar& str) const
		{ return(strcmp(fData,str.fData) <= 0); }
	bool operator<=(const char* str) const
		{ return(strcmp(fData,str) <= 0); }

	bool operator>(const CStrVar& str) const
		{ return(strcmp(fData,str.fData) > 0); }
	bool operator>(const char* str) const
		{ return(strcmp(fData,str) > 0); }

	bool operator>=(const CStrVar& str) const
		{ return(strcmp(fData,str.fData) >= 0); }
	bool operator>=(const char* str) const
		{ return(strcmp(fData,str) >= 0); }

	bool operator!=(const CStrVar& str) const
		{ return(strcmp(fData,str.fData) != 0); }
	bool operator!=(const char* str) const
		{ return(strcmp(fData,str) != 0); }
	
	//operator const char*() const { return((fData == NULL) ? "" : fData); }
	char operator[](int pos) const
		{ if(fData == NULL) return('\0'); return(fData[pos]); }
	const char* c_str() const { return((fData == NULL) ? "" : fData); }

	long len() const { return(fDataLen); }
	bool hasLen() const { return(fDataLen > 0); }
	long maxLen() const { return(LONG_MAX); }

	void clear();

	CStrVar& copy(const CStrVar& str)
		{ copyData(str.fData,str.fDataLen); return(*this); }
	CStrVar& copy(const char* str = NULL)
		{ copyData(str,cast2long(STRLEN(str))); return(*this); }

	CStrVar& ncopy(const CStrVar& str,long strnum)
		{ copyData(str.fData,min(str.fDataLen,strnum)); return(*this); }
	CStrVar& ncopy(const char* str,long strnum)
		{ copyData(str,minStrLen(str,strnum)); return(*this); }

	CStrVar& copyVargList(const char* fmt,va_list argList,bool doConcat);
	CStrVar& copyVarg(const char* fmt,...)
	{
		va_list argList;
		va_start(argList,fmt);
		copyVargList(fmt,argList,false);
		return(*this);
	}

	CStrVar& concat(const CStrVar& str)
		{ concatData(str.fData,str.fDataLen); return(*this); }
	CStrVar& concat(const char* str = NULL)
		{ concatData(str,cast2long(STRLEN(str))); return(*this); }
	CStrVar& concat(const char ch)
		{ concatData(&ch,1); return(*this); }

	CStrVar& nconcat(const CStrVar& str,long strnum)
		{ concatData(str.fData,min(str.fDataLen,strnum)); return(*this); }
	CStrVar& nconcat(const char* str,long strnum)
		{ concatData(str,minStrLen(str,strnum)); return(*this); }

	CStrVar& concatVarg(const char* fmt,...)
	{
		va_list argList;
		va_start(argList,fmt);
		copyVargList(fmt,argList,true);
		return(*this);
	}

	CStrVar& compress(short which);
	CStrVar& toUpper()
		{ if(fData != NULL) tStrToUpper(fData); return(*this); }
	CStrVar& toLower()
		{ if(fData != NULL) tStrToLower(fData); return(*this); }
};

bool operator==(const char* lhs,const CStrVar& rhs);
bool operator!=(const char* lhs,const CStrVar& rhs);
bool operator<(const char* lhs,const CStrVar& rhs);
bool operator<=(const char* lhs,const CStrVar& rhs);
bool operator>(const char* lhs,const CStrVar& rhs);
bool operator>=(const char* lhs,const CStrVar& rhs);

/******************************************************************************/

// Common String Sizes
typedef StrClass<9> CStr8;
typedef StrClass<17> CStr16;
typedef StrClass<33> CStr32;
typedef StrClass<65> CStr64;
typedef StrClass<129> CStr128;
typedef StrClass<257> CStr256;
typedef StrClass<513> CStr512;
typedef StrClass<1025> CStr1024;

//DeclareCStrGlobal(CStr64)

//DefineFixStrClass(CStr8,9)
//DefineFixStrClass(CStr16,17)
//DefineFixStrClass(CStr32,33)
//DefineFixStrClass(CStr64,65)
//DefineFixStrClass(CStr128,129)
//DefineFixStrClass(CStr256,257)
//DefineFixStrClass(CStr512,513)
//DefineFixStrClass(CStr1024,1025)

//inline bool operator==(const char* lhs,const CStr32& rhs)
//	{ return(CStr32(lhs) == rhs); }
//inline bool operator==(const char* lhs,const CStr64& rhs)
//	{ return(CStr64(lhs) == rhs); }

/******************************************************************************/

#endif	//__cplusplus

}; //namespace asi

#endif	//TStringH
/******************************************************************************/
/******************************************************************************/
