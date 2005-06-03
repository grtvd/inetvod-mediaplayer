/* EnrollRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef EnrollRqstH
#define EnrollRqstH

namespace asi
{

/******************************************************************************/

class EnrollRqst : public Streamable
{
protected:
	CStr64 fUserID;
	CStr32 fPassword;

	CStr16 fFirstName;
	CStr32 fLastName;
	CStr64 fAddrStreet1;
	CStr64 fAddrStreet2;
	CStr64 fCity;
	CStr64 fState;
	CStr32 fPostalCode;
	CStr64 fPhone;

	TDate fBirthDate;
	CurrencyID fCurrencyID;
//TODO:	MemberPrefsPtr fMemberPrefsPtr;

protected:
	EnrollRqst() {}
	virtual ~EnrollRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new EnrollRqst()); }

	virtual const char* className() const { return "EnrollRqst"; }

	void setUserID(const char* userID) { fUserID = userID; }
	const char* getUserID() const { return fUserID.c_str(); }

	void setPassword(const char* password) { fPassword = password; }
	const char* getPassword() const { return fPassword.c_str(); }

	void setFirstName(const char* firstName) { fFirstName.copy(firstName); }
	const char* getFirstName() const { return fFirstName.c_str(); }

	void setLastName(const char* lastName) { fLastName.copy(lastName); }
	const char* getLastName() const { return fLastName.c_str(); }
	
	void setAddrStreet1(const char* addrStreet1) { fAddrStreet1.copy(addrStreet1); }
	const char* getAddrStreet1() const { return fAddrStreet1.c_str(); }
	
	void setAddrStreet2(const char* addrStreet2) { fAddrStreet2.copy(addrStreet2); }
	const char* getAddrStreet2() const { return fAddrStreet2.c_str(); }
	
	void setCity(const char* city) { fCity.copy(city); }
	const char* getCity() const { return fCity.c_str(); }
	
	void setState(const char* state) { fState.copy(state); }
	const char* getState() const { return fState.c_str(); }
	
	void setPostalCode(const char* postalCode) { fPostalCode.copy(postalCode); }
	const char* getPostalCode() const { return fPostalCode.c_str(); }
	
	void setPhone(const char* phone) { fPhone.copy(phone); }
	const char* getPhone() const { return fPhone.c_str(); }

	void setBirthDate(TDate birthDate) { fBirthDate = birthDate; }
	TDate getBirthDate() const { return fBirthDate; }

	void setCurrencyID(const CurrencyID& currencyID) { fCurrencyID = currencyID; }
	CurrencyID getCurrencyID() const { return fCurrencyID; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<EnrollRqst>;
};

class EnrollRqstPtr : public RefCountPtr<EnrollRqst>
{
public:
	EnrollRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<EnrollRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<EnrollRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class EnrollResp : public Streamable
{
protected:
	EnrollResp() {}
	virtual ~EnrollResp() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new EnrollResp()); }

	virtual const char* className() const { return "EnrollResp"; }

	virtual void readFromFiler(DataFilerPtr filerPtr) {}
	virtual void writeToFiler(DataFilerPtr filerPtr) const { throw ASIException("EnrollResp::writeToFiler", "not implemented"); }

	friend class RefCountPtr<EnrollResp>;
};

class EnrollRespPtr : public RefCountPtr<EnrollResp>
{
public:
	EnrollRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<EnrollResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<EnrollResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//EnrollRqstH
/******************************************************************************/
/******************************************************************************/
