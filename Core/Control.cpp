/* Control.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

const int Control::fFocusedBorderWidth = 4;

/******************************************************************************/
/******************************************************************************/

ControlPtr Control::newInstance(Control* pControl,const Rect& rect)
{
	ControlPtr controlPtr(pControl);
	controlPtr->clear();
	controlPtr->setRect(rect);
	if (controlPtr->fRect.getHeight() <= 0)
		controlPtr->fRect.setHeight(controlPtr->getStandardHeight());

//	controlPtr->getScreen()->newControl(controlPtr);

	return controlPtr;
}

/******************************************************************************/

ScreenPtr Control::getScreen() const
{
	return MainApp::getThe()->getScreen(fScreenID);
}

/******************************************************************************/

void Control::setFocus(bool set)
{
	MainApp::getThe()->requestDraw();
	fFocused = set;
	if(set)
		getScreen()->onFocus(fControlID);
}

/******************************************************************************/
/******************************************************************************/

ControlPtr ControlVector::findByID(const ControlID& controlID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(controlID));
	if(iter != end())
		return(*iter);

	return ControlPtr();
}

/******************************************************************************/

ControlPtr ControlVector::getByID(const ControlID& controlID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(controlID));
	if(iter != end())
		return(*iter);

	throw ASIException("ControlVector::getByID","Invalid ControlID(%s)", controlID.c_str());
}

/******************************************************************************/

void ControlVector::removeByID(const ControlID& controlID)
{
	iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(controlID));
	if(iter != end())
		erase(iter);
}

/******************************************************************************/

int ControlVector::getFocusedPos() const
{
	const_iterator iter;

	for(iter = begin(); iter != end(); ++iter)
		if((*iter)->hasFocus())
			return(iter - begin());

	return(-1);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
