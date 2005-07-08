/* TType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TTypeH
#define TTypeH

typedef unsigned char       uchar;
typedef unsigned char       byte;
typedef unsigned short      ushort;
typedef unsigned short      word;
typedef unsigned long       ulong;
typedef unsigned long       dword;

typedef const char*			PConstChar;

/******************************************************************************/

#ifndef NULL
#define NULL    0
#endif
#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MAKELONG
#define MAKELONG(h,l)       (((dword)h << (dword)16) | (dword)l)
#define MAKESHORT(h,l)      (((word)h << (word)8) | (word)l)
#define MAKEBYTE(h,l)       (((byte)h << (byte)4) | (byte)l)
#endif

#ifndef LONIBBLE
#define LONIBBLE(w)         ((byte)((byte)w & (byte)0x0F))
#define HINIBBLE(w)         ((byte)(((byte)w & (byte)0xF0) >> (byte)4))
#endif

#ifndef LOBYTE
#define LOBYTE(w)           ((byte)((word)w & (word)0xFF))
#define HIBYTE(w)           ((byte)(((word)w & (word)0xFF00) >> (word)8))
#endif

#ifndef LOWORD
#define LOWORD(w)           ((word)((dword)w & (dword)0xFFFF))
#define HIWORD(w)           ((word)(((dword)w & (dword)0xFFFF0000l) >> (dword)16))
#endif

#ifndef OFFSET
#define OFFSET(type,field)  ((int) &((type *) 0)->field)
#endif

#ifndef SIZEOFFLD            /* returns the size of a field within a structure */
#define SIZEOFFLD(type,field)  (sizeof(((type *) 0)->field))
#endif

#define SETFLAG(flag,value,on)	((on) ? (flag |= (value)) : (flag &= ~(value)))
#define GETFLAG(flag,value)		((flag & (value)) ? TRUE : FALSE)

/******************************************************************************/

namespace asi
{

/******************************************************************************/

/* Template for creating a class from an enum. Purpose is to avoid using
	cast to convert to and from an int plus it enables validation when
	converting from an int. */
	
template<class T,int LowerBound,int UpperBound>
class EnumType
{
protected:
	T fT;
	
public:
	explicit EnumType<T,LowerBound,UpperBound>(T t = (T)LowerBound) { setFromInt(t); }
	explicit EnumType<T,LowerBound,UpperBound>(int t) { setFromInt(t); }
	
	void setFromInt(int t)
	{
		if((t >= LowerBound) && (t <= UpperBound))
			fT = (T)t;
		else
			#if defined(WIN32)
			throw ASIException("EnumType::setFromInt","Invalid t");
			#else
			;
			#endif
	}
	
	bool operator==(EnumType<T,LowerBound,UpperBound> t) const { return(t.fT == fT); }
	bool operator!=(EnumType<T,LowerBound,UpperBound> t) const { return(t.fT != fT); }
	bool operator==(T t) const { return(t == fT); }
	bool operator!=(T t) const { return(t != fT); }
	operator int() const { return(fT); }
	EnumType<T,LowerBound,UpperBound>& operator=(int t)
		{ setFromInt(t); return(*this); }
	bool isValid() const { return((fT >= LowerBound) && (fT <= UpperBound)); }
	
	// clear and isUndefined are just a helper functions. There is no
	//	requirement that the LowerBound value is an undefined value,
	//	but it can be.
	void clear() { fT = (T)LowerBound; }
	bool isUndefined() const { return(fT == LowerBound); }
};

/******************************************************************************/
/******************************************************************************/

#if defined(ERRORDEBUGON)
char cast2char(int rhs);
byte cast2byte(short rhs);
byte cast2byte(int rhs);
byte cast2byte(long rhs);
short cast2short(int rhs);
short cast2short(unsigned int rhs);
short cast2short(long rhs);
int cast2int(long rhs);
int cast2int(unsigned long rhs);
int cast2int(unsigned int rhs);
long cast2long(unsigned long rhs);
long cast2long(size_t rhs);
#else
inline char cast2char(int rhs) { return((char)rhs); }
inline byte cast2byte(short rhs) { return((byte)rhs); }
inline byte cast2byte(int rhs) { return((byte)rhs); }
inline byte cast2byte(long rhs) { return((byte)rhs); }
inline short cast2short(int rhs) { return((short)rhs); }
inline short cast2short(unsigned int rhs) { return((short)rhs); }
inline short cast2short(long rhs) { return((short)rhs); }
inline int cast2int(long rhs) { return((int)rhs); }
inline int cast2int(unsigned long rhs) { return((int)rhs); }
inline int cast2int(unsigned int rhs) { return((int)rhs); }
inline long cast2long(unsigned long rhs) { return((long)rhs); }
inline long cast2long(size_t rhs) { return((long)rhs); }
#endif

/******************************************************************************/

}; //namespace asi

#endif	//TTypeH
/******************************************************************************/
/******************************************************************************/
