/* ContainerControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

//#define DRAW_CONTROLS_OUTLINE

/******************************************************************************/
/******************************************************************************/

ControlPtr ContainerControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new ContainerControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void ContainerControl::newControl(ControlPtr controlPtr)
{
	if(!findControl(controlPtr->getControlID()).isNull())
		throw ASIException("ContinerControl::newControl", "ControlID(%s) already in use", controlPtr->getControlID().c_str());

	fControlVector.push_back(controlPtr);
	MainApp::getThe()->requestDraw();
}

/******************************************************************************/

ControlPtr ContainerControl::findControl(const ControlID& controlID)
{
	ControlPtr controlPtr = fControlVector.findByID(controlID);
	ControlVector::iterator iter;

	if(!controlPtr.isNull())
		return controlPtr;
	
	for(iter = fControlVector.begin(); iter != fControlVector.end(); ++iter)
		if(ContainerControlPtr::isA(*iter))
		{
			controlPtr = ContainerControlPtr(*iter)->fControlVector.findByID(controlID);

			if(!controlPtr.isNull())
				return controlPtr;
		}

	return ControlPtr();
}

/******************************************************************************/

ControlPtr ContainerControl::getControl(const ControlID& controlID)
{
	ControlPtr controlPtr = findControl(controlID);
	
	if(!controlPtr.isNull())
		return controlPtr;

	throw ASIException("ContainerControl::getControl", "Invalid ControlID(%s)", controlID.c_str());
}

/******************************************************************************/

void ContainerControl::deleteControl(const ControlID& controlID)
{
	//Does this function need to search its children?
	//For now, assume not, but add check for missing controlID
	if(!fControlVector.findByID(controlID).isNull())
	{
		fControlVector.removeByID(controlID);
		return;
	}

	throw ASIException("ContainerControl::deleteControl", "Invalid ControlID(%s)", controlID.c_str());
}

/******************************************************************************/

const char* ContainerControl::getTitle() const
{
	ControlVector::const_iterator iter;
	const char* title;

	if(fTitle.hasLen())
		return fTitle.c_str();

	for(iter = fControlVector.begin(); iter != fControlVector.end(); ++iter)
		if(ContainerControlPtr::isA(*iter))
		{
			title = ContainerControlPtr(*iter)->getTitle();
			if (tStrHasLen(title))
				return title;
		}

	return "";
}

/******************************************************************************/

bool ContainerControl::canFocus() const
{
	ControlVector::const_iterator iter;

	for(iter = fControlVector.begin(); iter != fControlVector.end(); ++iter)
		if((*iter)->canFocus())
			return true;

	return false;
}

/******************************************************************************/

void ContainerControl::setFocus(bool set)
{
	ControlVector::iterator iter;
	int focusedPos;

	Control::setFocus(set);

	// make sure to unfocus child controls
	focusedPos = fControlVector.getFocusedPos();
	if(focusedPos != -1)
		(fControlVector[focusedPos])->setFocus(false);

	// if setting, first first child the focus
	if(set)
	{
		for(iter = fControlVector.begin(); iter != fControlVector.end(); ++iter)
			if((*iter)->canFocus())
			{
				(*iter)->setFocus(true);
				break;
			}
	}
}

/******************************************************************************/

void ContainerControl::draw(bool showFocus)
{
	ControlVector::iterator iter;
	int drawCoordH;
	int drawCoordV;

	GetDrawCoordOffset(drawCoordH,drawCoordV);

	for(iter = fControlVector.begin(); iter != fControlVector.end(); ++iter)
	{
		AdjustDrawCoordOffset((*iter)->getRect().left,(*iter)->getRect().top);
		(*iter)->draw(showFocus);
		SetDrawCoordOffset(drawCoordH,drawCoordV);
		#if defined(DRAW_CONTROLS_OUTLINE)
		DrawBorder2((*iter)->getRect(), 1, gWhiteColor);
		#endif
	}
}

/******************************************************************************/

bool ContainerControl::key(int key)
{
	ControlPtr curControlPtr;
	ControlPtr nextControlPtr;
	int focusedPos = fControlVector.getFocusedPos();

	if(focusedPos != -1)
	{
		curControlPtr = fControlVector[focusedPos];
		if(curControlPtr->key(key))
			return true;
	}

	if((key == ek_DownButton) || (key == ek_RightButton))
	{
		for(ControlVector::size_type i = focusedPos + 1; i < fControlVector.size(); ++i)
		{
			if(fControlVector[i]->canFocus())
			{
				if(!curControlPtr.isNull())
					curControlPtr->setFocus(false);
				fControlVector[i]->setFocus(true);
				return true;
			}
		}
	}

	if((key == ek_UpButton) || (key == ek_LeftButton))
	{
		for(int i = focusedPos - 1; i >= 0; --i)
		{
			if(fControlVector[i]->canFocus())
			{
				if(!curControlPtr.isNull())
					curControlPtr->setFocus(false);
				fControlVector[i]->setFocus(true);
				return true;
			}
		}
	}

	return false;
}

/******************************************************************************/

bool ContainerControl::mouseClick(bool leftButton, bool buttonDown, int x, int y)
{
	for(ControlVector::reverse_iterator iter = fControlVector.rbegin();
		iter != fControlVector.rend(); ++iter)
	{
		if((*iter)->getRect().ptIn(Point(fRect.left + x, fRect.top + y)))
		{
			return (*iter)->mouseClick(leftButton, buttonDown, x - (*iter)->getRect().left,
				y - (*iter)->getRect().top);
		}
	}

	return false;
}

/******************************************************************************/

void ContainerControl::mouseMove(bool buttonDown, int x, int y)
{
	if(buttonDown)
		return;

	for(ControlVector::reverse_iterator iter = fControlVector.rbegin();
		iter != fControlVector.rend(); ++iter)
	{
		if((*iter)->getRect().ptIn(Point(fRect.left + x, fRect.top + y)))
		{
			if((*iter)->canFocus())
			{
				int focusedPos = fControlVector.getFocusedPos();

				if((focusedPos == -1) || (fControlVector[focusedPos]->getControlID()
					!= (*iter)->getControlID()))
				{
					if(focusedPos != -1)
						fControlVector[focusedPos]->setFocus(false);

					(*iter)->setFocus(true);
				}
			}
			(*iter)->mouseMove(buttonDown, x - (*iter)->getRect().left,
				y - (*iter)->getRect().top);

			return;
		}
	}
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
