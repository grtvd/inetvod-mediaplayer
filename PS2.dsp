# Microsoft Developer Studio Project File - Name="PS2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=PS2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PS2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PS2.mak" CFG="PS2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PS2 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "PS2 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PS2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "PS2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "c:\Projects\glut" /I "c:\Projects\FreeType\include" /I "c:\Projects\FreeType\include\freetype2" /I "C:\Projects\FTGL\include" /I "core" /I "controls" /I "data" /I "welcome" /I "nowplaying" /I "setup" /I "search" /I "request" /I "rent" /I "prefs" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "USE_GLUT" /D "XUSE_GLUT_FONT" /D "FTGL_LIBRARY_STATIC" /D "ERRORDEBUGON" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib Ws2_32.lib c:\projects\glut\glut32.lib C:\Projects\FreeType\lib\libfreetype.lib C:\Projects\FTGL\win32_vcpp\build\ftgl_static_MT_d.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"LIBCMTD" /out:"Debug/iNetVOD Media Player.exe" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no /nodefaultlib

!ENDIF 

# Begin Target

# Name "PS2 - Win32 Release"
# Name "PS2 - Win32 Debug"
# Begin Group "Main"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Main\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Main\StdAfx.h
# End Source File
# End Group
# Begin Group "Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Core\BinaryFiler.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\BinaryFiler.h
# End Source File
# Begin Source File

SOURCE=.\Core\ButtonControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\ButtonControl.h
# End Source File
# Begin Source File

SOURCE=.\Core\ContainerControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\ContainerControl.h
# End Source File
# Begin Source File

SOURCE=.\Core\Control.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\Control.h
# End Source File
# Begin Source File

SOURCE=.\Core\Core.h
# End Source File
# Begin Source File

SOURCE=.\Core\CoreID.h
# End Source File
# Begin Source File

SOURCE=.\Core\Currency.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\Currency.h
# End Source File
# Begin Source File

SOURCE=.\Core\DataFiler.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\DataFiler.h
# End Source File
# Begin Source File

SOURCE=.\Core\Draw.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\Draw.h
# End Source File
# Begin Source File

SOURCE=.\Core\EditControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\EditControl.h
# End Source File
# Begin Source File

SOURCE=.\Core\Encoding.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\Encoding.h
# End Source File
# Begin Source File

SOURCE=.\Core\Font.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\Font.h
# End Source File
# Begin Source File

SOURCE=.\Core\LabelControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\LabelControl.h
# End Source File
# Begin Source File

SOURCE=.\Core\ListControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\ListControl.h
# End Source File
# Begin Source File

SOURCE=.\Core\MainApp.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\MainApp.h
# End Source File
# Begin Source File

SOURCE=.\Core\MemoryStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\MemoryStream.h
# End Source File
# Begin Source File

SOURCE=.\Core\MessageScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\MessageScreen.h
# End Source File
# Begin Source File

SOURCE=.\Core\NameValuePair.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\NameValuePair.h
# End Source File
# Begin Source File

SOURCE=.\Core\Object.h
# End Source File
# Begin Source File

SOURCE=.\Core\Rect.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\Rect.h
# End Source File
# Begin Source File

SOURCE=.\Core\RefCountObject.h
# End Source File
# Begin Source File

SOURCE=.\Core\Screen.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\Screen.h
# End Source File
# Begin Source File

SOURCE=.\Core\SelectControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\SelectControl.h
# End Source File
# Begin Source File

SOURCE=.\Core\Stream.h
# End Source File
# Begin Source File

SOURCE=.\Core\Streamable.h
# End Source File
# Begin Source File

SOURCE=.\Core\StreamableConstructor.h
# End Source File
# Begin Source File

SOURCE=.\Core\TDateTime.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TDateTime.h
# End Source File
# Begin Source File

SOURCE=.\Core\TError.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TError.h
# End Source File
# Begin Source File

SOURCE=.\Core\TException.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TException.h
# End Source File
# Begin Source File

SOURCE=.\Core\TextControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TextControl.h
# End Source File
# Begin Source File

SOURCE=.\Core\TextWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TextWriter.h
# End Source File
# Begin Source File

SOURCE=.\Core\TNumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TNumeric.h
# End Source File
# Begin Source File

SOURCE=.\Core\TString.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TString.h
# End Source File
# Begin Source File

SOURCE=.\Core\TStringVector.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TStringVector.h
# End Source File
# Begin Source File

SOURCE=.\Core\TStrUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TStrUtils.h
# End Source File
# Begin Source File

SOURCE=.\Core\TTick.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TTick.h
# End Source File
# Begin Source File

SOURCE=.\Core\TType.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\TType.h
# End Source File
# Begin Source File

SOURCE=.\Core\WaitScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\WaitScreen.h
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Controls\RentedShowListControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\RentedShowListControl.h
# End Source File
# Begin Source File

SOURCE=.\Controls\ShowProviderListControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\ShowProviderListControl.h
# End Source File
# Begin Source File

SOURCE=.\Controls\ShowSearchListControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\ShowSearchListControl.h
# End Source File
# Begin Source File

SOURCE=.\Controls\TextListControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\TextListControl.h
# End Source File
# End Group
# Begin Group "Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Data\Category.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\Category.h
# End Source File
# Begin Source File

SOURCE=.\Data\DataID.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\DataID.h
# End Source File
# Begin Source File

SOURCE=.\Data\IncludeAdult.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\IncludeAdult.h
# End Source File
# Begin Source File

SOURCE=.\Data\MemberPrefs.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\MemberPrefs.h
# End Source File
# Begin Source File

SOURCE=.\Data\MemberProvider.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\MemberProvider.h
# End Source File
# Begin Source File

SOURCE=.\Data\MemberState.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\MemberState.h
# End Source File
# Begin Source File

SOURCE=.\Data\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\Player.h
# End Source File
# Begin Source File

SOURCE=.\Data\Provider.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\Provider.h
# End Source File
# Begin Source File

SOURCE=.\Data\Rating.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\Rating.h
# End Source File
# Begin Source File

SOURCE=.\Data\RentedShow.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\RentedShow.h
# End Source File
# Begin Source File

SOURCE=.\Data\RentedShowSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\RentedShowSearch.h
# End Source File
# Begin Source File

SOURCE=.\Data\Session.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\Session.h
# End Source File
# Begin Source File

SOURCE=.\Data\ShowCost.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\ShowCost.h
# End Source File
# Begin Source File

SOURCE=.\Data\ShowDetail.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\ShowDetail.h
# End Source File
# Begin Source File

SOURCE=.\Data\ShowProvider.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\ShowProvider.h
# End Source File
# Begin Source File

SOURCE=.\Data\ShowSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\Data\ShowSearch.h
# End Source File
# End Group
# Begin Group "Request"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Request\CheckShowAvailRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\CheckShowAvailRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\DataRequestor.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\DataRequestor.h
# End Source File
# Begin Source File

SOURCE=.\Request\EnableAdultAccessRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\EnableAdultAccessRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\EnrollRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\EnrollRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\HTTPRequestor.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\HTTPRequestor.h
# End Source File
# Begin Source File

SOURCE=.\Request\INetVODPlayerRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\INetVODPlayerRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\PingRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\ProviderEnrollRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\ProviderEnrollRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\ReleaseShowRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\ReleaseShowRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\RentedShowListRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\RentedShowListRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\RentedShowRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\RentedShowRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\RentShowRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\RentShowRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\RequestData.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\RequestData.h
# End Source File
# Begin Source File

SOURCE=.\Request\SetProviderRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\SetProviderRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\ShowDetailRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\ShowDetailRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\ShowSearchRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\ShowSearchRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\SignonRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\SignonRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\StatusCode.h
# End Source File
# Begin Source File

SOURCE=.\Request\SystemDataRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\SystemDataRqst.h
# End Source File
# Begin Source File

SOURCE=.\Request\TCPRequestor.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\TCPRequestor.h
# End Source File
# Begin Source File

SOURCE=.\Request\WatchShowRqst.cpp
# End Source File
# Begin Source File

SOURCE=.\Request\WatchShowRqst.h
# End Source File
# End Group
# Begin Group "Welcome"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Welcome\StartScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Welcome\StartScreen.h
# End Source File
# Begin Source File

SOURCE=.\Welcome\WelcomeScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Welcome\WelcomeScreen.h
# End Source File
# End Group
# Begin Group "Setup"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Setup\AskPINScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup\AskPINScreen.h
# End Source File
# Begin Source File

SOURCE=.\Setup\AskSignedUpControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup\AskSignedUpControl.h
# End Source File
# Begin Source File

SOURCE=.\Setup\HaveLogonIDControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup\HaveLogonIDControl.h
# End Source File
# Begin Source File

SOURCE=.\Setup\MemCardLoadScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup\MemCardLoadScreen.h
# End Source File
# Begin Source File

SOURCE=.\Setup\MemCardSaveScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup\MemCardSaveScreen.h
# End Source File
# Begin Source File

SOURCE=.\Setup\NeedLogonIDControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup\NeedLogonIDControl.h
# End Source File
# Begin Source File

SOURCE=.\Setup\SetupScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup\SetupScreen.h
# End Source File
# End Group
# Begin Group "Search"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Search\CategorySearchScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Search\CategorySearchScreen.h
# End Source File
# Begin Source File

SOURCE=.\Search\CategorySelectScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Search\CategorySelectScreen.h
# End Source File
# Begin Source File

SOURCE=.\Search\PickProviderScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Search\PickProviderScreen.h
# End Source File
# Begin Source File

SOURCE=.\Search\ProviderSelectScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Search\ProviderSelectScreen.h
# End Source File
# Begin Source File

SOURCE=.\Search\RatingSelectScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Search\RatingSelectScreen.h
# End Source File
# Begin Source File

SOURCE=.\Search\SearchData.h
# End Source File
# Begin Source File

SOURCE=.\Search\SearchDetailScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Search\SearchDetailScreen.h
# End Source File
# Begin Source File

SOURCE=.\Search\SearchResultsScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Search\SearchResultsScreen.h
# End Source File
# Begin Source File

SOURCE=.\Search\SearchScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Search\SearchScreen.h
# End Source File
# End Group
# Begin Group "NowPlaying"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NowPlaying\NowPlayingScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\NowPlaying\NowPlayingScreen.h
# End Source File
# Begin Source File

SOURCE=.\NowPlaying\RentedShowDetailScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\NowPlaying\RentedShowDetailScreen.h
# End Source File
# End Group
# Begin Group "Rent"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Rent\AskHaveProviderControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Rent\AskHaveProviderControl.h
# End Source File
# Begin Source File

SOURCE=.\Rent\ConfirmChargeControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Rent\ConfirmChargeControl.h
# End Source File
# Begin Source File

SOURCE=.\Rent\HaveProviderControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Rent\HaveProviderControl.h
# End Source File
# Begin Source File

SOURCE=.\Rent\NeedProviderControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Rent\NeedProviderControl.h
# End Source File
# Begin Source File

SOURCE=.\Rent\RentData.cpp
# End Source File
# Begin Source File

SOURCE=.\Rent\RentData.h
# End Source File
# Begin Source File

SOURCE=.\Rent\RentScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Rent\RentScreen.h
# End Source File
# End Group
# Begin Group "Prefs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Prefs\AskAdultPINScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Prefs\AskAdultPINScreen.h
# End Source File
# Begin Source File

SOURCE=.\Prefs\PreferencesScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Prefs\PreferencesScreen.h
# End Source File
# End Group
# End Target
# End Project
