/* TStrUtils.ccpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

/* Calculates line starts for word-wraping a string. Width in chars. */

void tStrWordWrapCalcCharLines(const char* str, int width, std::vector<int>& linesVector)
{
	int i;
	int curWidth;
	int lastStart;
	int lastSpace;
	int len;

	linesVector.clear();

	lastStart = 0;
	lastSpace = 0;

	curWidth = 0;
	len = strlen(str);
	if(!len)
		return;

	for(i = 0; i < len; i++)
	{
		if(str[i] == ' ')
			lastSpace = i;
		
		if((str[i] == '\r') || (str[i] == '\n'))
		{
			linesVector.push_back(lastStart);

			lastStart = i + 1;
			lastSpace = 0;
			curWidth = 0;

			if((i < len) && (str[i] == '\r') && (str[i + 1] == '\n'))
			{
				++i;
				++lastStart;
			}
		}
		else
		{
			if(curWidth + 1 > width)
			{
				if(lastSpace)
				{
					linesVector.push_back(lastStart);

					i = lastStart = lastSpace + 1;
					lastSpace = 0;
					curWidth = 0;
				}
				else
				{
					linesVector.push_back(lastStart);

					lastStart = i;
					curWidth = 0;
				}
			}
			curWidth++;
		}
	}
	linesVector.push_back(lastStart);
}

/******************************************************************************/

/* Calculates line starts for word-wraping a string. Width in pixels. */

void tStrWordWrapCalcPixelLines(const char* str, int width, const FontPtr& fontPtr,
	std::vector<int>& linesVector)
{
	CStrVar lineStr;
	int i;
	//float curWidth;
	int lastStart;
	int lastSpace;
	int len;
	//float chWidth;

	linesVector.clear();

	lastStart = 0;
	lastSpace = 0;

	//curWidth = 0;
	len = strlen(str);
	if(!len)
		return;

	if(fontPtr->getWidth(str) <= width)
	{
		linesVector.push_back(0);
		return;
	}

	for(i = 0; i < len; i++)
	{
		if(str[i] == ' ')
			lastSpace = i;
		
		if((str[i] == '\r') || (str[i] == '\n'))
		{
			linesVector.push_back(lastStart);

			lastStart = i + 1;
			lastSpace = 0;
			lineStr.clear();
			//curWidth = 0;

			if((i < len) && (str[i] == '\r') && (str[i + 1] == '\n'))
			{
				++i;
				++lastStart;
			}
		}
		else
		{
			lineStr.concat(str[i]);
			//chWidth = fontPtr->getWidth(str[i]);
			//if(curWidth + chWidth > width)
			if(fontPtr->getWidth(lineStr.c_str()) > width)
			{
				if(lastSpace)
				{
					linesVector.push_back(lastStart);

					i = lastStart = lastSpace + 1;
					lastSpace = 0;
					//curWidth = 0;
					lineStr.ncopy(&str[i], 1);
				}
				else
				{
					linesVector.push_back(lastStart);

					lastStart = i;
					//curWidth = 0;
					lineStr.ncopy(&str[i], 1);
				}
			}
			//curWidth += chWidth;
		}
	}
	linesVector.push_back(lastStart);
}

/******************************************************************************/

CStrVar tStrWordWrapGetNextLine(const char* str, const std::vector<int>& linesVector,
	int cur)
{
	CStrVar newStr;
	int length,curLineStart,nextLineStart;
	int num = linesVector.size();

	if((cur < 0) || (cur >= num))
		throw ASIException("GetNextWordWrapLine", "Invalid cur(%d)", cur);
	curLineStart = linesVector[cur];

	if(cur == num - 1)
	{
		length = strlen(str) - curLineStart;
	}
	else
	{
		if((cur + 1 < 0) || (cur + 1 >= num))
			throw ASIException("GetNextWordWrapLine", "Invalid cur(%d)", cur);
		nextLineStart = linesVector[cur + 1];

		length = nextLineStart - curLineStart;
	}

	// Remove trailing \r, \n, and spaces.
	if((length > 0) && (str[curLineStart + length - 1] == '\n'))
		length--;
	if((length > 0) && (str[curLineStart + length - 1] == '\r'))
		length--;
	while((length > 0) && (str[curLineStart + length - 1] == ' '))
		length--;

	newStr.ncopy(&str[curLineStart],length);
	return(newStr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
