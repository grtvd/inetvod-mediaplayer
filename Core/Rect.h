/* Rect.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RectH
#define RectH

namespace asi
{

/******************************************************************************/

/* Rectangle Corners */
enum RectCorner
{
	rc_TopLeft = 0,
	rc_TopRight = 1,
	rc_BottomLeft = 2,
	rc_BottomRight = 3,
	rc_Invalid = -1
};

/******************************************************************************/

class Point
{
public:
	short	v;
	short	h;

	Point() { v = h = 0; }
	Point(short newHorz, short newVert) { h = newHorz; v = newVert; }

	void set(short newHorz, short newVert) { h = newHorz; v = newVert; }
	void offset(short dh, short dv) { h = h + dh; v = v + dv; }
	bool equal(Point pt) { return((h == pt.h) && (v == pt.v)); }
};
typedef Point *PPoint;

//inline Point MakePoint(short horz, short vert) { Point pt(horz, vert); return(pt); }

/******************************************************************************/

class Rect
{
public:
	short	top;
	short	left;
	short	bottom;
	short	right;

	Rect() { top = left = bottom = right = 0; }
	Rect(short newLeft, short newTop, short newRight, short newBottom)
		{ left = newLeft; top = newTop; right = newRight; bottom = newBottom; }

#if 0	//TODO:BOB
	bool read(PStream pStream);
	bool write(PStream pStream);
#endif

	void set(short newLeft, short newTop, short newRight, short newBottom)
		{ left = newLeft; top = newTop; right = newRight; bottom = newBottom; }

	short getWidth() const { return(right - left); }
	void setWidth(short width) { right = left + width; }
	short getHeight() const { return(bottom - top); }
	void setHeight(short height) { bottom = top + height; }
	Point topLeft() const { Point pt; pt.h = left; pt.v = top; return(pt); }
	Point bottomRight() const { Point pt; pt.h = right; pt.v = bottom; return(pt); }
	Point getCorner(RectCorner corner);

	void offset(short dh, short dv) { left = left + dh; top = top + dv; right = right + dh; bottom = bottom + dv; }
	void moveTo(short newLeft, short newTop);
	void inset(short horz, short vert);

	bool equal(const Rect& rect) const
	{
		return((left == rect.left) && (top == rect.top) &&
			(right == rect.right) && (bottom == rect.bottom));
	}
	void unionRect(const Rect& rect);
	bool intersects(const Rect& rect) const;
	bool intersection(const Rect& rect);
	bool ptIn(const Point& pt) const
	{
		return((pt.h >= left) && (pt.h < right) &&
			(pt.v >= top) && (pt.v < bottom));
	}

	void validate();
	bool inPosLimit(const Rect& limitRect) const;
	bool inSizeLimit(const Rect& limitRect) const;
};
typedef Rect *PRect;

inline Rect RectWH(short newLeft, short newTop, short newWidth, short newHeight)
	{ Rect rect(newLeft, newTop, newLeft + newWidth, newTop + newHeight); return(rect); }

/******************************************************************************/

}; //namespace asi

#endif	//RectH
/******************************************************************************/
/******************************************************************************/

