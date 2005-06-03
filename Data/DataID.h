/* DataID.h */

/******************************************************************************/
/******************************************************************************/
#ifndef DataIDH
#define DataIDH

namespace asi
{

/******************************************************************************/

typedef CStr32ID MemberID;
typedef CStr32ID ManufacturerID;
typedef CStr64ID ProviderID;
typedef CStr64ID ShowID;
typedef CStr64ID RentedShowID;
typedef CStr32ID CategoryID;
typedef CStr32ID RatingID;

/******************************************************************************/

class ProviderIDVector : public std::vector<ProviderID>
{
public:
	void copy(const ProviderIDVector& providerIDVector)
		{ clear(); insert(end(), providerIDVector.begin(), providerIDVector.end()); }

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;
};

class CategoryIDVector : public std::vector<CategoryID>
{
public:
	void copy(const CategoryIDVector& categoryIDVector)
		{ clear(); insert(end(), categoryIDVector.begin(), categoryIDVector.end()); }

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;
};

class RatingIDVector : public std::vector<RatingID>
{
public:
	void copy(const RatingIDVector& ratingIDVector)
		{ clear(); insert(end(), ratingIDVector.begin(), ratingIDVector.end()); }

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;
};

/******************************************************************************/

}; //namespace asi

#endif	//DataIDH
/******************************************************************************/
/******************************************************************************/
