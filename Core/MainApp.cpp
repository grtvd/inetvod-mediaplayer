/* MainApp.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "StartScreen.h"
#include "WelcomeScreen.h"

namespace asi
{

/******************************************************************************/

void MainAppDisplay();
void MainAppReshape(int w, int h);
void MainAppKey(unsigned char key, int x, int y);
void MainAppSpecial(int key, int x, int y);
void MainAppIdle();
void MainAppMouse(int button, int state, int x, int y);
void MainAppMotion(int x, int y);
void MainAppPassiveMotion(int x, int y);

/******************************************************************************/

/* App Fonts */
const FontID gBigWhiteFontID("Font001");
const FontID gNormalWhiteFontID("Font002");
const FontID gNormalBlackFontID("Font003");
const FontID gNormalYellowFontID("Font004");
const FontID gSmallWhiteFontID("Font005");

/******************************************************************************/
/******************************************************************************/

MainAppPtr& MainApp::getThe()
{
	static MainAppPtr theMainAppPtr(new MainApp);

	return theMainAppPtr;
}

/******************************************************************************/

MainApp::MainApp() : fScreenCoord(-300, -240, 300, 240), fOrthoCoord(-1, 1, 1, -1)
{
	fDoExit = false;

	fBGTextOffset = 0;
	fSessionPtr = Session::newInstance();

	fDrawRequested = true;
	fDrawTenths = 5;
	fLastDrawTime = 0;

	SetDrawCoord(fScreenCoord, fOrthoCoord);
	//SetDrawCoord(fScreenCoord, Rect(fScreenCoord.left, -fScreenCoord.top, fScreenCoord.right, -fScreenCoord.bottom));
}

/******************************************************************************/

void MainApp::reset()
{
	SetDrawCoord(fScreenCoord, fOrthoCoord);

	loadFonts();
	fScreenVector.clear();
	fSessionPtr = Session::newInstance();
}

/******************************************************************************/

bool MainApp::init()
{
	int argc = 1;
	char* argv[] = { "Storm Media Player" };

	return init(argc, argv);
}

/******************************************************************************/

bool MainApp::init(int argc, char* argv[])
{
	ErrorInit("PS2");
	#if defined(WIN32)
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(fScreenCoord.getWidth(), fScreenCoord.getHeight());
	glutCreateWindow("Storm Media Player");
	//#if !defined(WIN32)
	//glutFullScreen();
	//#endif
	#else
	int doubleBuffer = 0;
	int waitVSync = 0;
	int inter = PS2_GS_INTERLACE;
	int omode = PS2_GS_NTSC;
	int ffmode = PS2_GS_FRAME;
	int resolution = PS2_GS_640x480;
	int refreshRate = PS2_GS_60Hz;
	int width = 640;
	int height = 480;

	PSX2MesaInit(doubleBuffer, waitVSync, inter, omode, ffmode, resolution, refreshRate, &width, &height);
	fPSX2MesaContext = PSX2MesaCreateContext(0, NULL);
	PSX2MesaMakeCurrent(fPSX2MesaContext);
	#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

//	glClearColor(0.0, 0.0, 0.0, 1.0);
	#if defined(WIN32)
	glutDisplayFunc(MainAppDisplay);
	glutReshapeFunc(MainAppReshape);
	glutKeyboardFunc(MainAppKey);
	glutSpecialFunc(MainAppSpecial);
	glutIdleFunc(MainAppIdle);
	glutMouseFunc(MainAppMouse);
	glutMotionFunc(MainAppMotion);
	glutPassiveMotionFunc(MainAppPassiveMotion);
	#endif

	loadFonts();

	return true;
}

/******************************************************************************/

void MainApp::dispose()
{
	ErrorDispose();
	#if !defined(WIN32)
	PSX2MesaDestroyContext(fPSX2MesaContext);
	#endif
}

/******************************************************************************/

void MainApp::loadFonts()
{
	fFontVector.clear();
	#if defined(USE_GLUT_FONT)
	fFontVector.push_back(Font::newInstance(gBigWhiteFontID, GLUT_BITMAP_TIMES_ROMAN_24, 22, 17, gWhiteColor));
	fFontVector.push_back(Font::newInstance(gNormalWhiteFontID, GLUT_BITMAP_HELVETICA_18, 18, 14, gWhiteColor));
	fFontVector.push_back(Font::newInstance(gSmallWhiteFontID, GLUT_BITMAP_HELVETICA_12, 12, 9, gWhiteColor));
	#elif FALSE //Haettenschweiler
	fFontVector.push_back(Font::newInstance(gBigWhiteFontID, "Haettenschweiler.ttf", 42, gWhiteColor));
	fFontVector.push_back(Font::newInstance(gNormalWhiteFontID, "Haettenschweiler.ttf", 30, gWhiteColor));
	fFontVector.push_back(Font::newInstance(gNormalBlackFontID, "Haettenschweiler.ttf", 30, gBlackColor));
	fFontVector.push_back(Font::newInstance(gNormalYellowFontID, "Haettenschweiler.ttf", 30, gYellowColor));
	fFontVector.push_back(Font::newInstance(gSmallWhiteFontID, "Haettenschweiler.ttf", 18, gWhiteColor));
	#elif TRUE //Tahoma
	fFontVector.push_back(Font::newInstance(gBigWhiteFontID, "Tahoma.ttf", 36, gWhiteColor));
	fFontVector.push_back(Font::newInstance(gNormalWhiteFontID, "Tahoma.ttf", 20, gWhiteColor));
	fFontVector.push_back(Font::newInstance(gNormalBlackFontID, "Tahoma.ttf", 20, gBlackColor));
	fFontVector.push_back(Font::newInstance(gNormalYellowFontID, "Tahoma.ttf", 20, gYellowColor));
	fFontVector.push_back(Font::newInstance(gSmallWhiteFontID, "Tahoma.ttf", 16, gWhiteColor));
	#endif
}

/******************************************************************************/

void MainApp::mainLoop()
{
	#if defined(WIN32)
	glutMainLoop();
	#else
	while(!getDoExit())
		idle();
	#endif
}

/******************************************************************************/

void MainApp::modelLoop(const ScreenID& screenID)
{
	ScreenPtr screenPtr;

	while(!(screenPtr = fScreenVector.findByID(screenID)).isNull())
	{
		#if defined(WIN32)
		MSG event;

		while(PeekMessage(&event, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&event);		/* translate virtual-key messages */
			DispatchMessage(&event);		/* call the window proc */
			if(event.message == WM_QUIT)
				fDoExit = true;
		}
		#endif

		idle();

		if(fDoExit)
			throw ASIException("MainApp::modelLoop", "Exiting");
	}
}

/******************************************************************************/

void MainApp::processAvail()
{
	#if defined(WIN32)
	MSG event;

	while(PeekMessage(&event, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&event);		/* translate virtual-key messages */
		DispatchMessage(&event);		/* call the window proc */
		if(event.message == WM_QUIT)
			fDoExit = true;
	}
	#endif

	idle();

	if(fDoExit)
		throw ASIException("MainApp::processAvail", "Exiting");
}

/******************************************************************************/

void MainApp::openScreen(ScreenPtr& screenPtr)
{
	if(!(fScreenVector.findByID(screenPtr->getScreenID())).isNull())
		throw ASIException("MainApp::openScreen", "Screen already opened with ScreenID(%s)", screenPtr->getScreenID().c_str());

	fScreenVector.insert(fScreenVector.begin(), screenPtr);
	fDrawRequested = true;
}

/******************************************************************************/

void MainApp::closeScreen(const ScreenID& screenID)
{
	fScreenVector.removeByID(screenID);
	fDrawRequested = true;
}

/******************************************************************************/

void MainApp::closeAllScreens()
{
	fScreenVector.clear();
	fDrawRequested = true;
}

/******************************************************************************/

void MainApp::draw(bool newFrame)
{
	fDrawRequested = false;

	glClearColor((double)gBackgroundColor[0]/255.0, (double)gBackgroundColor[1]/255.0,
		(double)gBackgroundColor[2]/255.0, (double)gBackgroundColor[3]/255.0);
	//glClearColor(16.0/255.0, 114.0/255.0, 196.0/255.0, 1.0);
	//glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

#if FALSE
	AdjustDrawCoordOffset(fScreenCoord.left, fScreenCoord.top);

	FontPtr fontPtr = MainApp::getThe()->getFont(gBigFontID);
	DrawText(0, fBGTextOffset + 50, "VIDEO ON DEMAND INTERNET VIDEO ON DEMAND INTERNET", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 100, "ON DEMAND INTERNET VIDEO ON DEMAND INTERNET VIDEO", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 150, "DEMAND INTERNET VIDEO ON DEMAND INTERNET VIDEO ON", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 200, "INTERNET VIDEO ON DEMAND INTERNET VIDEO ON DEMAND", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 250, "VIDEO ON DEMAND INTERNET VIDEO ON DEMAND INTERNET", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 300, "ON DEMAND INTERNET VIDEO ON DEMAND INTERNET VIDEO", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 350, "DEMAND INTERNET VIDEO ON DEMAND INTERNET VIDEO ON", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 400, "INTERNET VIDEO ON DEMAND INTERNET VIDEO ON DEMAND", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 450, "INTERNET VIDEO ON DEMAND INTERNET VIDEO ON DEMAND", fontPtr, gBackgroundTextColor);
	DrawText(0, fBGTextOffset + 500, "INTERNET VIDEO ON DEMAND INTERNET VIDEO ON DEMAND", fontPtr, gBackgroundTextColor);

	if(newFrame)
	{
		fBGTextOffset += 5;
		if(fBGTextOffset >= 50)
			fBGTextOffset = 0;
	}

	AdjustDrawCoordOffset(-fScreenCoord.left, -fScreenCoord.top);
#endif

	// Determin which Screens need to be drawn
	ScreenPtr screenPtr;
	int count = fScreenVector.size();
	int drawScrs = 0;
	int i;
	for(i = 0; i < count; ++i)
	{
		++drawScrs;
		ScreenPtr screenPtr = fScreenVector[i];
		if (screenPtr->isFullScreen())
			break;
	}

	// draw the Screens
	for(i = drawScrs - 1; i >= 0; --i)
	{
		screenPtr = fScreenVector[i];
		screenPtr->draw(i == 0);
		if(i > 0)	// dim screens in the background
			DrawRect(fScreenCoord, gScreenBackgroundTransColor);
	}

	#if defined(WIN32)
	glutSwapBuffers();
	#else
	PSX2MesaSwapBuffers();
	#endif
}

/******************************************************************************/

void MainApp::reshape(int w, int h)
{
	fDrawRequested = true;

	fScreenCoord.left = -(w / 2);
	fScreenCoord.right = (w / 2);
	fScreenCoord.top = -(h / 2);
	fScreenCoord.bottom = (h /2);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, w, h, 0);
	//gluOrtho2D(-(w / 2), w / 2, h / 2, -(h / 2));
	//gluOrtho2D(-1, 1, -1, 1);
	//gluOrtho2D(fScreenCoord.left, fScreenCoord.right, -fScreenCoord.bottom, -fScreenCoord.top);
	gluOrtho2D(fOrthoCoord.left, fOrthoCoord.right, fOrthoCoord.bottom, fOrthoCoord.top);
	glMatrixMode(GL_MODELVIEW);

	SetDrawCoord(fScreenCoord, fOrthoCoord);
}

/******************************************************************************/

void MainApp::key(int key, int /*x*/, int /*y*/)
{
	key = mapKey(key);

	//TODO: REMOVE Temp short-circuit exit
	if (key == 27)
	{
		fDoExit = true;
		throw ASIException("MainApp::key", "Exiting");
	}

	if(fScreenVector.size() > 0)
	{
		ScreenPtr screenPtr = *fScreenVector.begin();

		//if(screenPtr->didLoadDataFail())
		//	screenPtr->close();
		//else 
		if(!screenPtr->key(key))
			#if defined(WIN32)
			MessageBeep(0);
			#else
			;
			#endif
	}

	fDrawRequested = true;
}

/******************************************************************************/

int MainApp::mapKey(int key)
{
#if defined(USE_GLUT)
	if(key == 13)	// GLUT_KEY_F1
		return ek_Select;
	if(key == 8)	// GLUT_KEY_F2
		return ek_Back;
	if(key == '.')	// GLUT_KEY_F3
		return ek_NextValue;
	if(key == ',')	// GLUT_KEY_F4
		return ek_PrevValue;
#else
	//TODO:
#endif

	return key;
}

/******************************************************************************/

void MainApp::idle()
{
	ScreenVector::iterator iter;
	ScreenVector::iterator lastEndIter;

	if(fScreenVector.size() == 0)
	{
		if (fSessionPtr->isUserLoggedOn())
			WelcomeScreen::newInstance();
		else
			StartScreen::newInstance();
	}

	for(iter = fScreenVector.begin(); iter != fScreenVector.end(); ++iter)
	{
		lastEndIter = fScreenVector.end();
		(*iter)->idle();
		// detect changes to fScreenVector
		if(lastEndIter != fScreenVector.end())
			break;
	}

	if(fDrawRequested || tHaveTenthsPast(fLastDrawTime, fDrawTenths))
	{
		draw(true);
		fLastDrawTime = tGetTickCount();
	}
}

/******************************************************************************/

void MainApp::mouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_MIDDLE_BUTTON)
		return;

	if(fScreenVector.size() > 0)
	{
		ScreenPtr screenPtr = *fScreenVector.begin();

		if(!screenPtr->mouseClick(button == GLUT_LEFT_BUTTON, state == GLUT_DOWN,
				fScreenCoord.left + x, fScreenCoord.top + y))
			if(state == GLUT_UP)
			{
				#if defined(WIN32)
				MessageBeep(0);
				#else
				;
				#endif
			}
	}
}

/******************************************************************************/

void MainApp::mouseMove(bool buttonDown, int x, int y)
{
	if(fScreenVector.size() > 0)
	{
		ScreenPtr screenPtr = *fScreenVector.begin();
		screenPtr->mouseMove(buttonDown, fScreenCoord.left + x, fScreenCoord.top + y);
	}
}

/******************************************************************************/
/******************************************************************************/

void MainAppDisplay()
{
	MainApp::getThe()->requestDraw();
}

/******************************************************************************/

void MainAppReshape(int w, int h)
{
	MainApp::getThe()->reshape(w, h);
}

/******************************************************************************/

void MainAppKey(unsigned char key, int x, int y)
{
	MainApp::getThe()->key(key, x, y);
}

/******************************************************************************/

void MainAppSpecial(int key, int x, int y)
{
#if defined(USE_GLUT)
	switch(key)
	{
		case GLUT_KEY_UP:
			key = ek_UpButton;
			break;
		case GLUT_KEY_DOWN:
			key = ek_DownButton;
			break;
		case GLUT_KEY_LEFT:
			key = ek_LeftButton;
			break;
		case GLUT_KEY_RIGHT:
			key = ek_RightButton;
			break;
		case GLUT_KEY_PAGE_UP:
			key = ek_PageUp;
			break;
		case GLUT_KEY_PAGE_DOWN:
			key = ek_PageDown;
			break;
		default:
			return;
	}
	MainApp::getThe()->key(key, x, y);
#endif
}

/******************************************************************************/

void MainAppIdle()
{
	MainApp::getThe()->idle();
}

/******************************************************************************/

void MainAppMouse(int button, int state, int x, int y)
{
	MainApp::getThe()->mouseClick(button, state, x, y);
}

/******************************************************************************/

void MainAppMotion(int x, int y)
{
	MainApp::getThe()->mouseMove(true, x, y);
}

/******************************************************************************/

void MainAppPassiveMotion(int x, int y)
{
	MainApp::getThe()->mouseMove(false, x, y);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
