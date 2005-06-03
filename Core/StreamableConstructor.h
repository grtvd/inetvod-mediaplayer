/* StreamableConstructor.h */

/******************************************************************************/
/******************************************************************************/
#ifndef StreamableConstructorH
#define StreamableConstructorH

#include "DataFiler.h"

namespace asi
{

/******************************************************************************/

class StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const = 0;
};


/******************************************************************************/

}; //namespace asi

#endif	//StreamableConstructorH
/******************************************************************************/
/******************************************************************************/
