/* TNumeric.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TNumericH
#define TNumericH

#include "DataFiler.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

class TNumericUtil
{
private:
	#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
	TNumericUtil() = 0;
	#endif

public:
	static bool isNumericChar(char ch);
	static bool allNumericString(const char* str);
	static bool stringToNumeric(const char* str, long& value);
	static CStr32 numericToString(long value);
};

/******************************************************************************/

/* Template for creating Numeric objects that support a nullable concept. */
	
template<class T>
class TNumeric
{
protected:
	static const T UNDEFINED_VALUE;
	static const T DEFAULT_VALUE;

	T fValue;
	auto_ptr<char> fFormatted;
	
public:
	TNumeric<T>(T value = UNDEFINED_VALUE) { fValue = value; }
	TNumeric<T>(const TNumeric<T>& value) { fValue = value.fValue; }
	TNumeric<T>(const char* str)
	{
		fValue = UNDEFINED_VALUE;
		if(!tStrHasLen(str))
			return;

		long value;
		if(!TNumericUtil::stringToNumeric(str, value))
			return;

		fValue = (T)value;
	}

	TNumeric<T>& operator=(const TNumeric<T>& value) { fValue = value.fValue; fFormatted.release(); return *this; }
	void clear() { fValue = UNDEFINED_VALUE; fFormatted.release(); }
	bool isUndefined() const { return(fValue == UNDEFINED_VALUE); }
	
	void setValue(T value) { fValue = value; }
	T getValue() const { if(!isUndefined()) return fValue; return DEFAULT_VALUE; }

	const char* c_str() const
	{
		CStr32 str = TNumericUtil::numericToString(fValue);

		int size = str.len() + 1;
		#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
		(const_cast<TNumeric*>(this))->fFormatted.reset(new char[size]);
		#else
		(const_cast<TNumeric*>(this))->fFormatted = auto_ptr<char>(new char[size]);
		#endif
		tStrCpy(fFormatted.get(), size, str.c_str());

		return fFormatted.get();
	}

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;
};

/******************************************************************************/

typedef TNumeric<short> TInt16;
typedef TNumeric<long> TInt32;

/******************************************************************************/

}; //namespace asi

#endif	//TNumericH
/******************************************************************************/
/******************************************************************************/
