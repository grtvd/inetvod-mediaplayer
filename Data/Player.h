/* Player.h */

/******************************************************************************/
/******************************************************************************/
#ifndef PlayerH
#define PlayerH

#include "DataID.h"

namespace asi
{

/******************************************************************************/

class Player : public Streamable
{
protected:
	ManufacturerID fManufacturerID;
	CStr32 fModelNo;
	CStr64 fSerialNo;
	CStr16 fVersion;

protected:
	Player() {}
	virtual ~Player() {}

private:
	Player(const Player&);						// don't allow copy constructor
	const Player& operator=(const Player&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance() { return StreamablePtr(new Player()); }

	virtual const char* className() const { return "Player"; }

	// Data Get/Set Methods
	void setManufacturerID(const ManufacturerID& manufacturerID) { fManufacturerID = manufacturerID; }
	void setModelNo(const char* modelNo) { fModelNo.copy(modelNo); }
	void setSerialNo(const char* serialNo) { fSerialNo.copy(serialNo); }
	void setVersion(const char* version) { fVersion.copy(version); }
	const char* getVersion() const { return fVersion.c_str(); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<Player>;
};

class PlayerPtr : public RefCountPtr<Player>
{
public:
	PlayerPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<Player>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<Player&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//PlayerH
/******************************************************************************/
/******************************************************************************/
