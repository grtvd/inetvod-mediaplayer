/* SetupData.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SetupDataH
#define SetupDataH

namespace asi
{

/******************************************************************************/

enum StorePasswords
{
	spw_NotStored,
	spw_Locally,
	spw_Server
};

/******************************************************************************/

enum IncludeAdult
{
	ina_Never,
	ina_PromptPassword,
	ina_Always
};

/******************************************************************************/

class SetupData : public Object
{
protected:
	CStr64 fUserID;
	CStr32 fUserPassword;
	bool fRememberPassword;

	CStr16 fFirstName;
	CStr32 fLastName;
	CStr64 fAddrStreet1;
	CStr64 fAddrStreet2;
	CStr64 fCity;
	CStr64 fState;
	CStr32 fPostalCode;
	CStr64 fPhone;

	StorePasswords fStorePasswords;
	IncludeAdult fIncludeAdult;
	TDate fBirthDate;	//TODO: not being set

protected:
	SetupData() { fRememberPassword = false; fStorePasswords = spw_NotStored; fIncludeAdult = ina_Never; }
	virtual ~SetupData() {}

public:
	static ObjectPtr newInstance() { return ObjectPtr(new SetupData()); }

	void setUserID(const char* userID) { fUserID.copy(userID); }
	const char* getUserID() const { return fUserID.c_str(); }

	void setUserPassword(const char* userPassword) { fUserPassword.copy(userPassword); }
	const char* getUserPassword() const { return fUserPassword.c_str(); }

	void setRememberPassword(bool rememberPassword) { fRememberPassword = rememberPassword; }
	bool getRememberPassword() const { return fRememberPassword; }

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

	void setStorePasswords(StorePasswords storePasswords) { fStorePasswords = storePasswords; }
	StorePasswords getStorePasswords() const { return fStorePasswords; }

	void setIncludeAdult(IncludeAdult includeAdult) { fIncludeAdult = includeAdult; }
	IncludeAdult getIncludeAdult() const { return fIncludeAdult; }

	void setBirthDate(TDate birthDate) { fBirthDate = birthDate; }
	TDate getBirthDate() const { return fBirthDate; }

	friend class RefCountPtr<SetupData>;
};

class SetupDataPtr : public RefCountPtr<SetupData>
{
public:
	SetupDataPtr(ObjectPtr objectPtr = ObjectPtr()) : 
		RefCountPtr<SetupData>(objectPtr.isNull() ? NULL :
		&dynamic_cast<SetupData&>(*objectPtr)) {}

	operator ObjectPtr() { return(ObjectPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//SetupDataH
/******************************************************************************/
/******************************************************************************/
