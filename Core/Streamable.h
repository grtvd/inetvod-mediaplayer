/* Streamable.h */

/******************************************************************************/
/******************************************************************************/
#ifndef StreamableH
#define StreamableH

#include "RefCountObject.h"
#include "Object.h"

namespace asi
{

/******************************************************************************/

class DataFiler;	//forward reference
typedef RefCountPtr<DataFiler> DataFilerPtr;

/******************************************************************************/

class Streamable : public Object
{
public:
	virtual const char* className() const = 0;

	virtual void readFromFiler(DataFilerPtr filerPtr) = 0;
	virtual void writeToFiler(DataFilerPtr filerPtr) const = 0;

	friend class RefCountPtr<Streamable>;
};

class StreamablePtr : public RefCountPtr<Streamable>
{
public:
	StreamablePtr(ObjectPtr objectPtr = ObjectPtr()) : 
		RefCountPtr<Streamable>(objectPtr.isNull() ? NULL :
		&dynamic_cast<Streamable&>(*objectPtr)) {}

	operator ObjectPtr() { return(ObjectPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//StreamableH
/******************************************************************************/
/******************************************************************************/
