/* RentData.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentDataH
#define RentDataH

namespace asi
{

/******************************************************************************/

class RentData : public Object
{
protected:
	ShowDetailPtr fShowDetailPtr;
	ProviderPtr fProviderPtr;

	CStr64 fUserID;
	CStr32 fPassword;

	ShowCostPtr fShowCostPtr;

protected:
	RentData(const ShowDetailPtr& showDetailPtr);
	virtual ~RentData() {}

public:
	static ObjectPtr newInstance(const ShowDetailPtr& showDetailPtr)
		{ return ObjectPtr(new RentData(showDetailPtr)); }

	ShowDetailPtr getShowDetail() const { return fShowDetailPtr; }
	ShowID getShowID() const { return fShowDetailPtr->getShowID(); }

	ProviderID getProviderID() const { return fProviderPtr->getProviderID(); }
	const char* getProviderName() const { return fProviderPtr->getName(); }

	void setUserID(const char* userID) { fUserID.copy(userID); }
	const char* getUserID() const { return fUserID.c_str(); }

	void setPassword(const char* password) { fPassword.copy(password); }
	const char* getPassword() const { return fPassword.c_str(); }

	ShowCostPtr getShowCost() const { return fShowCostPtr; }
	void setShowCost(ShowCostPtr& showCostPtr) { fShowCostPtr = showCostPtr; }

	friend class RefCountPtr<RentData>;
};

class RentDataPtr : public RefCountPtr<RentData>
{
public:
	RentDataPtr(ObjectPtr objectPtr = ObjectPtr()) : 
		RefCountPtr<RentData>(objectPtr.isNull() ? NULL :
		&dynamic_cast<RentData&>(*objectPtr)) {}

	operator ObjectPtr() { return(ObjectPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//RentDataH
/******************************************************************************/
/******************************************************************************/
