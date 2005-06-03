/* CoreID.h */

/******************************************************************************/
/******************************************************************************/
#ifndef CoreIDH
#define CoreIDH

namespace asi
{

/******************************************************************************/
/******************************************************************************/

/* Template for creating ID classes. Purpose is to remove need of having to
	know what type an ID is (usually unsigned long or string). */
	
template<class T>
class TNumericID
{
protected:
	T fID;
	
public:
	TNumericID<T>(T id = 0) { fID = id; }
	void clear() { fID = 0; }
	bool isUndefined() const { return(fID == 0); }
	
	//BOB operator T() const { return(fID); }
	bool operator==(TNumericID<T> rhs) const { return(fID == rhs.fID); }
	bool operator!=(TNumericID<T> rhs) const { return(fID != rhs.fID); }
	bool operator<(TNumericID<T> rhs) const { return(fID < rhs.fID); }
	bool operator<=(TNumericID<T> rhs) const { return(fID <= rhs.fID); }
	bool operator>(TNumericID<T> rhs) const { return(fID > rhs.fID); }
	bool operator>=(TNumericID<T> rhs) const { return(fID >= rhs.fID); }
	
	void setID(T id) { fID = id; }
	T getID() const { return(fID); }

	const char* c_str() const;
};

template<class BaseClass>
class TStringIDClass : public BaseClass
{
public:
	TStringIDClass(const char* str = NULL) { copy(str); }

	bool isUndefined() const { return(len() == 0); }
	void setID(const char* str) { copy(str); }
	const char* getID() const { return(data); }
};

// Common IDs
typedef TStringIDClass<CStr32> CStr32ID;
typedef TStringIDClass<CStr64> CStr64ID;
typedef TNumericID<unsigned long> TNumericIDULong;

/******************************************************************************/

typedef CStr32ID FontID;
typedef CStr32ID ScreenID;
typedef CStr32ID ControlID;

/******************************************************************************/

}; //namespace asi

#endif	//CoreIDH
/******************************************************************************/
/******************************************************************************/
