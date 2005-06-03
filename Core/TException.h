/* TException.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TExceptionH
#define TExceptionH

namespace asi
{

/******************************************************************************/
/******************************************************************************/

class ASIException
{
private:
	CStr64 fMethod;
	CStrVar fMsg;

public:
	ASIException(const char* method, const char* msg, ...);
	ASIException(const char* file, const int line, const char* msg, ...);

	const char* getMethod() const { return(fMethod.c_str()); }
	const char* getMsg() const { return(fMsg.c_str()); }
};

/******************************************************************************/

}; //namespace asi

#endif	//TExceptionH
/******************************************************************************/
/******************************************************************************/
