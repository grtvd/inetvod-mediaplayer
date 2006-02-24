/* StatusCode.h */

/******************************************************************************/
/******************************************************************************/
#ifndef StatusCodeH
#define StatusCodeH

namespace asi
{

/******************************************************************************/

enum StatusCode
{
	sc_Success = 0,

	sc_InvalidUserIDPassword = 1000,
	sc_InvalidSession = 1001,
	sc_InvalidProviderUserIDPassword = 1003,

	sc_GeneralError = 9999
};

/******************************************************************************/

}; //namespace asi

#endif	//StatusCodeH
/******************************************************************************/
/******************************************************************************/
