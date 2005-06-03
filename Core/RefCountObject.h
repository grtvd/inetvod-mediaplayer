/* RefCountObject.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RefCountObjectH
#define RefCountObjectH

namespace asi
{

/******************************************************************************/

class RefCountObject
{
private:
	int fRefCount;

protected:
	void addReference() { fRefCount++; }
	void removeReference()
		{ if(--fRefCount == 0) delete this; }
	
public:
	RefCountObject() : fRefCount(0) {}
	RefCountObject(const RefCountObject& /*rhs*/) : fRefCount(0) {}
	virtual ~RefCountObject() {}
	
	RefCountObject& operator=(const RefCountObject& /*rhs*/) { return(*this); }
};

/******************************************************************************/

template<class T>
class RefCountPtr
{
protected:
	T *fT;
	
public:
	RefCountPtr<T>(T* t = 0) : fT(t) { init(); }
	RefCountPtr<T>(const RefCountPtr<T>& rhs) : fT(rhs.fT) { init(); }
	virtual ~RefCountPtr<T>() { if(fT != NULL) fT->removeReference(); }
	bool isNull() const { return(fT == NULL); }

	const RefCountPtr<T>& operator=(const RefCountPtr<T>& rhs)
	{
		if(fT != rhs.fT)
		{
			if(fT != NULL)
				fT->removeReference();
				
			fT = rhs.fT;
			init();
		}

		return(*this);
	}
	
	const T* operator->() const { return(fT); }
	T* operator->() { return(fT); }

	const T& operator*() const { return(*fT); }
	T& operator*() { return(*fT); }
	
private:
	void init()
	{
		if(fT == NULL)
			return;

		fT->addReference();
	}
};

/******************************************************************************/

}; //namespace asi

#endif //RefCountObjectH
/******************************************************************************/
/******************************************************************************/

