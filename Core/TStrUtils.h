/* TStrUtils.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TStrUtilsH
#define TStrUtilsH

namespace asi
{

/******************************************************************************/

void tStrWordWrapCalcCharLines(const char* str, int width, std::vector<int>& linesVector);
void tStrWordWrapCalcPixelLines(const char* str, int width, const FontPtr& fontPtr,
	std::vector<int>& linesVector);
CStrVar tStrWordWrapGetNextLine(const char* str, const std::vector<int>& linesVector,
	int cur);

/******************************************************************************/

}; //namespace asi

#endif	//TStrUtilsH
/******************************************************************************/
/******************************************************************************/
