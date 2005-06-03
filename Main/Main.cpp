/* Main.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "MainApp.h"

using namespace asi;

/******************************************************************************/
/******************************************************************************/

//int main(int argc, char* argv[])
int WINAPI WinMain(HINSTANCE hCurrInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	MainAppPtr mainAppPtr = MainApp::getThe();
	if(mainAppPtr->init())
	{
		while(!mainAppPtr->getDoExit())
		{
			try
			{
				mainAppPtr->mainLoop();
			}
			CATCH_ERROR_NOACTION("main");

			if(!mainAppPtr->getDoExit())
				mainAppPtr->reset();
		}

		mainAppPtr->dispose();
	}

	return 0;
}

/******************************************************************************/
/******************************************************************************/
