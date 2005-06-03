/* Object.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ObjectH
#define ObjectH

namespace asi
{

/******************************************************************************/

class Object;	//forward reference
typedef RefCountPtr<Object> ObjectPtr;

class Object : public RefCountObject
{
protected:
	Object() {}
	virtual ~Object() {}

private:
	Object(const Object&);						// don't allow copy constructor
	const Object& operator=(const Object&);		// or operator=

public:
	virtual void clear() {}

	friend class RefCountPtr<Object>;
};

/******************************************************************************/

}; //namespace asi

#endif	//ObjectH
/******************************************************************************/
/******************************************************************************/
