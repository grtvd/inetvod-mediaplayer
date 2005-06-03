/* EditControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef EditControlH
#define EditControlH

namespace asi
{

/******************************************************************************/

enum EditControlType
{
	ect_AlphaNumeric,		// all upper and lower A - Z and 0 - 9
	ect_UpperAlphaNumeric,	// upper only A - Z and 0 - 9
	ect_Numeric				// only 0 - 9
};

/******************************************************************************/

class EditControl : public Control
{
protected:
	EditControlType fType;
	Rect fTextRect;
	char fText[256];
	int fFirstPos;
	int fCurPos;
	int fCharWidth;
	int fMaxLength;
	bool fAutoButton;	// if true, when specific keys are inputted, will call OnButton when data length equals fMaxLength

	std::vector<char> fValidCharVector;

protected:
	EditControl(const ControlID& controlID, const ScreenID& screenID);
	virtual ~EditControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);
protected:
	void init();
	void fillValidCharVector();

public:
	void setType(const EditControlType editControlType) { fType = editControlType; fillValidCharVector(); }
	EditControlType getType() const { return fType; }

	void setText(const char* text) { tStrCpy(fText, sizeof(fText), text); tStrToUpper(fText); }
	const char* getText() const { return fText; }

	void setMaxLength(int maxLength) { fMaxLength = (maxLength < (int)sizeof(fText) - 1) ? maxLength : (int)sizeof(fText) - 1; }
	int getMaxLength() const { return fMaxLength; }

	void setAutoButton(bool autoButton) { fAutoButton = autoButton; }
	bool getAutoButton() const { return fAutoButton; }

	virtual void setFocus(bool set);
	virtual void draw(bool showFocus);
protected:
	void checkPositions();
	virtual void drawChangeIcons(bool showFocus) const;
	virtual void drawChars(bool showFocus);
public:
	virtual bool key(int key);

	friend class RefCountPtr<EditControl>;
};

class EditControlPtr : public RefCountPtr<EditControl>
{
public:
	EditControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<EditControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<EditControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//EditControlH
/******************************************************************************/
/******************************************************************************/
