/* TextWriter.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TextWriterH
#define TextWriterH

#include "MemoryStream.h"

namespace asi
{

/******************************************************************************/

class TextWriter;	//forward reference
typedef RefCountPtr<TextWriter> TextWriterPtr;

class TextWriter : public RefCountObject
{
protected:
	StreamPtr fStreamPtr;

protected:
	TextWriter(StreamPtr streamPtr) { fStreamPtr = streamPtr; }
	virtual ~TextWriter() {}

public:
	static TextWriterPtr newInstance(StreamPtr streamPtr)
		{ return TextWriterPtr(new TextWriter(streamPtr)); }

	void write(const char* data);
	void writeLine(const char* data);

	friend class RefCountPtr<TextWriter>;
};

/******************************************************************************/

}; //namespace asi

#endif	//TextWriterH
/******************************************************************************/
/******************************************************************************/

