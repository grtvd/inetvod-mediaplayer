/* MainApp.h */

/******************************************************************************/
/******************************************************************************/
#ifndef MainAppH
#define MainAppH

#if defined(WIN32)
#include <GL/gl.h>
#if defined(USE_GLUT)
#include <glut.h>
#endif
#else
#include "GL/psx2mesa.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#endif

#include "Session.h"

namespace asi
{

/******************************************************************************/

/* App Fonts */
extern const FontID gBigWhiteFontID;
extern const FontID gNormalWhiteFontID;
extern const FontID gNormalBlackFontID;
extern const FontID gNormalYellowFontID;
extern const FontID gSmallWhiteFontID;

/* Event Keys */
#define ek_Select		(256)		// PS2 X Button
#define ek_Back			(257)		// PS2 Triangle Button
#define ek_NextValue	(258)		// PS2 Circle Button
#define ek_PrevValue	(259)		// PS2 Square Button
#define ek_UpButton		(260)
#define ek_DownButton	(261)
#define ek_LeftButton	(262)
#define ek_RightButton	(263)
#define ek_PageUp		(264)
#define ek_PageDown		(265)

/******************************************************************************/

class MainApp;	//forward reference
typedef RefCountPtr<MainApp> MainAppPtr;

class MainApp : public RefCountObject
{
protected:
	bool fDoExit;

	Rect fScreenCoord;	// drawing coordinates
	Rect fOrthoCoord;	// rect for Ortho2D

	#if !defined(WIN32)
	PSX2MesaContext fPSX2MesaContext;
	#endif
	int fBGTextOffset;
	FontVector fFontVector;
	ScreenVector fScreenVector;
	SessionPtr fSessionPtr;

	bool fDrawRequested;
	long fDrawsPerSecond;
	long fLastDrawTime;

protected:
	MainApp();
	virtual ~MainApp() {}

private:
	MainApp(const MainApp&);						// don't allow copy constructor
	const MainApp& operator=(const MainApp&);		// or operator=

public:
	static MainAppPtr& getThe();

	void reset();
	bool init();
	bool init(int argc, char* argv[]);
	void dispose();

	bool getDoExit() const { return fDoExit; }

	const Rect& getScreenCoord() const { return fScreenCoord; }

	void mainLoop();
	void modelLoop(const ScreenID& screenID);
	void processAvail();

protected:
	void loadFonts();
public:
	FontPtr getFont(const FontID& fontID) { return fFontVector.getByID(fontID); }

	void openScreen(ScreenPtr& screenPtr);
	void closeScreen(const ScreenID& screenID);
	void closeAllScreens();
	ScreenPtr findScreen(const ScreenID& screenID) { return fScreenVector.findByID(screenID); }
	ScreenPtr getScreen(const ScreenID& screenID) { return fScreenVector.getByID(screenID); }

protected:
	void draw(bool newFrame);
public:
	void requestDraw() { fDrawRequested = true; }
	void reshape(int w, int h);
	void key(int key, int x, int y);
protected:
	int mapKey(int key);
public:
	void idle();
	void mouseClick(int button, int state, int x, int y);
	void mouseMove(bool buttonDown, int x, int y);

	SessionPtr& getSession() { return fSessionPtr; }
	const char* getVersion() { return fSessionPtr->getVersion(); }

	friend class RefCountPtr<MainApp>;
};

/******************************************************************************/

}; //namespace asi

#endif	//MainAppH
/******************************************************************************/
/******************************************************************************/
