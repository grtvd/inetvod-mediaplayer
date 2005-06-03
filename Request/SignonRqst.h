/* SignonRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SignonRqstH
#define SignonRqstH

#include "Player.h"
#include "MemberState.h"

namespace asi
{

/******************************************************************************/

class SignonRqst : public Streamable
{
protected:
	CStr64 fUserID;
	CStr32 fPassword;
	PlayerPtr fPlayerPtr;

protected:
	SignonRqst() {}
	virtual ~SignonRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new SignonRqst()); }

	virtual const char* className() const { return "SignonRqst"; }

	void setUserID(const char* userID) { fUserID = userID; }
	const char* getUserID() const { return fUserID.c_str(); }

	void setPassword(const char* password) { fPassword = password; }
	const char* getPassword() const { return fPassword.c_str(); }

	void setPlayer(const PlayerPtr& playerPtr) { fPlayerPtr = playerPtr; }
	const PlayerPtr& getPlayer() const { return fPlayerPtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<SignonRqst>;
};

class SignonRqstPtr : public RefCountPtr<SignonRqst>
{
public:
	SignonRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<SignonRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<SignonRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class SignonResp : public Streamable
{
protected:
	CStrVar fSessionData;
	TDateTime fSessionExpires;
	MemberStatePtr fMemberStatePtr;

protected:
	SignonResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~SignonResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new SignonResp(filerPtr)); }

	virtual const char* className() const { return "SignonResp"; }

	void setSessionData(const char* sessionData) { fSessionData = sessionData; }
	const char* getSessionData() const { return fSessionData.c_str(); }

	TDateTime getSessionExpires() const { return fSessionExpires; }

	MemberStatePtr getMemberState() const { return fMemberStatePtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<SignonResp>;
};

class SignonRespPtr : public RefCountPtr<SignonResp>
{
public:
	SignonRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<SignonResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<SignonResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class SignonRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return SignonResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//SignonRqstH
/******************************************************************************/
/******************************************************************************/
