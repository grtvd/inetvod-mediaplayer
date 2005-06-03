/* IncludeAdult.h */

/******************************************************************************/
/******************************************************************************/
#ifndef IncludeAdultH
#define IncludeAdultH

namespace asi
{

/******************************************************************************/

enum IncludeAdult
{
	ina_Never,
	ina_PromptPassword,
	ina_Always
};

CStr32 ConvertIncludeAdultToString(IncludeAdult ina);
IncludeAdult ConvertStringToIncludeAdult(const char* ina);

/******************************************************************************/

}; //namespace asi

#endif	//IncludeAdultH
/******************************************************************************/
/******************************************************************************/
