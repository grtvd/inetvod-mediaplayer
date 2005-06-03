/* Rect.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/
#if 0	//TODO: BOB:

bool Rect::Read(PStream pStream)
{
	bool error = FALSE;

	error |= !pStream->ReadData(&top);
	error |= !pStream->ReadData(&left);
	error |= !pStream->ReadData(&bottom);
	error |= !pStream->ReadData(&right);

	return(!error);
}

/******************************************************************************/

bool Rect::Write(PStream pStream)
{
	bool error = FALSE;

	error |= !pStream->WriteData(top);
	error |= !pStream->WriteData(left);
	error |= !pStream->WriteData(bottom);
	error |= !pStream->WriteData(right);

	return(!error);
}

#endif
/******************************************************************************/

Point Rect::getCorner(RectCorner corner)
{
	Point pt;

	if(corner == rc_TopLeft)
	{
		pt.h = left;
        pt.v = top;
	}
	else if(corner == rc_TopRight)
	{
		pt.h = right;
        pt.v = top;
	}
	else if(corner == rc_BottomRight)
	{
		pt.h = right;
		pt.v = bottom;
	}
	else //if(corner == rc_BottomLeft)
	{
		pt.h = left;
        pt.v = bottom;
	}

	return(pt);
}

/******************************************************************************/

void Rect::moveTo(short newLeft,short newTop)
{
	short diff;

	diff = newLeft - left;
	left += diff;
    right += diff;

	diff = newTop - top;
	top += diff;
	bottom += diff;
}

/******************************************************************************/

void Rect::inset(short horz,short vert)
{
	top += vert;
	left += horz;
	bottom -= vert;
	right -= horz;
}

/******************************************************************************/

void Rect::unionRect(const Rect& rect)
{
	left = (left < rect.left) ? left : rect.left;
	right = (right > rect.right) ? right : rect.right;
	top = (top < rect.top) ? top : rect.top;
	bottom = (bottom > rect.bottom) ? bottom : rect.bottom;
}

/******************************************************************************/

/* This returns TRUE or FALSE if pRect intersets with 'this' */

bool Rect::intersects(const Rect& rect) const
{
//	return((left <= rect.right) && (right >= rect.left) &&
//		(top <= rect.bottom) && (bottom >= rect.top));
	return((left < rect.right) && (right > rect.left) &&
		(top < rect.bottom) && (bottom > rect.top));
}

/******************************************************************************/

/* This returns TRUE or FALSE and sets 'this' to the intesection of pRect
	with 'this' */

bool Rect::intersection(const Rect& rect)
{
	if((getWidth() < 1) || (getHeight() < 1) ||
		(rect.getWidth() < 1) || (rect.getHeight() < 1))
	{
		set(0,0,0,0);
		return false;
	}

	if(left <= rect.left)
	{
		if(right <= rect.left)
		{
			set(0,0,0,0);
			return true;
		}
		else
		{
			left = rect.left;

			if(right > rect.right)
				right = rect.right;
		}
	}
	else
	{
		if(left >= rect.right)
		{
			set(0,0,0,0);
			return false;
		}
		else
		{
			if(right > rect.right)
				right = rect.right;
		}
	}

	if(top <= rect.top)
	{
		if(bottom <= rect.top)
		{
			set(0,0,0,0);
			return false;
		}
		else
		{
			top = rect.top;

			if(bottom > rect.bottom)
				bottom = rect.bottom;
		}
	}
	else
	{
		if(top >= rect.bottom)
		{
			set(0,0,0,0);
			return false;
		}
		else
		{
			if(bottom > rect.bottom)
				bottom = rect.bottom;
		}
	}

	return true;
}

/******************************************************************************/

bool Rect::inPosLimit(const Rect& limitRect) const
{
	if(right <= limitRect.left)
		return false;	//Offset(limitRect.left - right + 1,0);
	
	if(left >= limitRect.right)
		return false;	//Offset(limitRect.right - left - 1,0);

	if(bottom <= limitRect.top)
		return false;	//Offset(0,limitRect.top - bottom + 1);

	if(top >= limitRect.bottom)
		return false;	//Offset(0,limitRect.bottom - top - 1);

	return true;
}

/******************************************************************************/

bool Rect::inSizeLimit(const Rect& limitRect) const
{
	if(getWidth() < limitRect.left)
		return false;	//SetWidth(limitRect.left);

	if(getWidth() > limitRect.right)
		return false;	//SetWidth(limitRect.right);

	if(getHeight() < limitRect.top)
		return false;	//SetHeight(limitRect.top);
	
	if(getHeight() > limitRect.bottom)
		return false;	//SetHeight(limitRect.bottom);

	return true;
}

/******************************************************************************/

/* This function test to make sure left < right and top < bottom and swaps
	them if they are not. */

void Rect::validate()
{
	short tempShort;

	if(left > right)
	{
		tempShort = left;
		left = right;
		right = tempShort;
	}

	if(top > bottom)
	{
		tempShort = top;
		top = bottom;
		bottom = tempShort;
    }
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/

