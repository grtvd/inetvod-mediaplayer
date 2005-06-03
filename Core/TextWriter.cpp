/* TextWriter.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

void TextWriter::write(const char* data)
{
	short len = (short)STRLEN(data);
	fStreamPtr->writeBuffer(data, len);
}

/******************************************************************************/

void TextWriter::writeLine(const char* data)
{
	write(data);
	write("\r\n");
}

/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/

