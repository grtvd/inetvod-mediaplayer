/* TStringVector.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TStringVectorH
#define TStringVectorH

namespace asi
{

/******************************************************************************/

class CStr32Vector : public std::vector<CStr32>
{
public:
	void copy(const CStr32Vector& cstr32Vector)
		{ clear(); insert(end(), cstr32Vector.begin(), cstr32Vector.end()); }

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;
};

typedef std::vector<CStr64> CStr64Vector;

class CStrVarVector : public std::vector<CStrVar>
{
public:
	void split(const char* data, const char* search);
};

/******************************************************************************/

}; //namespace asi

#endif	//TStringVectorH
/******************************************************************************/
/******************************************************************************/
