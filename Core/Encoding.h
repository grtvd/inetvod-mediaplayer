/* Encoding.cpp */

/******************************************************************************/
/******************************************************************************/
#ifndef EncodingH
#define EncodingH

namespace asi
{

/******************************************************************************/

class Encoding;	//forward reference
typedef RefCountPtr<Encoding> EncodingPtr;

class Encoding : public RefCountObject
{
protected:
	Encoding() {}
	virtual ~Encoding() {}

private:
	Encoding(const Encoding&);						// don't allow copy constructor
	const Encoding& operator=(const Encoding&);		// or operator=

public:
	static const EncodingPtr UTF8;

	virtual auto_ptr<wchar_t> getString(const char* str) const = 0;

	friend class RefCountPtr<Encoding>;
};

/******************************************************************************/


class UTF8Encoding : public Encoding
{
public:
	static EncodingPtr newInstance() { return EncodingPtr(new UTF8Encoding()); }

	virtual auto_ptr<wchar_t> getString(const char* str) const;
};

/******************************************************************************/

}; //namespace asi

#endif	//EncodingH
/******************************************************************************/
/******************************************************************************/
