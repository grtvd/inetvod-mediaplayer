/* Currency.h */

/******************************************************************************/
/******************************************************************************/
#ifndef CurrencyH
#define CurrencyH

namespace asi
{

/******************************************************************************/

typedef CStr8 CurrencyID;	// max length of 3

/******************************************************************************/

/* Supported Currency Codes */
#define cur_USD	(CurrencyID("USD"))

/******************************************************************************/

class Money : public Streamable
{
protected:
	CurrencyID fCurrencyID;
	double fAmount;

protected:
	Money(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~Money() {}

private:
	Money(const Money&);						// don't allow copy constructor
	const Money& operator=(const Money&);		// or operator=

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new Money(filerPtr)); }

	virtual const char* className() const { return "Money"; }

	virtual void clear() { fCurrencyID.clear(); fAmount = 0.0; }

	// Data Get/Set Methods
	void setCurrencyID(CurrencyID currencyID) { fCurrencyID = currencyID; }
	CurrencyID getCurrencyID() const { return fCurrencyID; }

	void setAmount(double amount) { fAmount = amount; }
	double getAmount() const { return fAmount; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<Money>;
};

class MoneyPtr : public RefCountPtr<Money>
{
public:
	MoneyPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<Money>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<Money&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class MoneyConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return Money::newInstance(filerPtr); }
};

/******************************************************************************/

}; //namespace asi

#endif	//CurrencyH
/******************************************************************************/
/******************************************************************************/
