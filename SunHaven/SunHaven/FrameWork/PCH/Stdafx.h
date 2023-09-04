#pragma once
#pragma warning(disable : 4005)
#include<SDKDDKVER.h>
#include <ole2.h>
#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

#pragma comment (lib, "msimg32.lib")
//#pragma comment (lib, "JsonCPP/lib_json/json_vc71_libmtd.lib")


#include <windows.h>

// 외부 헤더파일
//#include "../../JsonCPP/include/json/json.h"


#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <chrono>
#include <random>
#include <memory>
#include <vector>
#include<map>
#include<string.h>
#include <algorithm>
#include <functional>
#include <fstream>
#include <queue>
#include <deque>
#include <unordered_map>
#include<cassert>
#include<bitset>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
/*
//! D2D/D3D 헤더파일
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

ID2D1Factory* _ID2DFactory = nullptr;
ID2D1HwndRenderTarget* _ID2DRanderTarget = nullptr;*/

// # 사용자 정의 헤더 파일 #
#include "../Utility/CommonMacroFunction.h"
#include "../Utility/RandomFunction.h"
#include "../../Manager/KeyManager.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/FontManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/TimeManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Class/Data/INIData.h"
//#include "../../Class/Data/JsonSaveLoader.h"
#include "../Utility/Utils.h"

using namespace MY_UTIL;

// # 싱글톤 #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define INIDATA INIData::getSingleton()
//#define JSONSAVELOADER JsonSaveLoader::getSingleton()

// # 매크로 # (윈도우창 초기화)
#define WINNAME					(LPTSTR)(TEXT("WindowsAPI"))
#define WINSTART_X				400
#define WINSTART_Y				100
#define WINSIZE_X				1280
#define WINSIZE_Y				720
#define CENTER_X				WINSIZE_X / 2
#define CENTER_Y				WINSIZE_Y / 2
#define TILEWIDTH				24
#define TILEHEIGHT				24

#define PI                       3.141592
#define WINSTYLE				WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}
#define SAFE_DELETE_SCENE(p)	{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE				_hInstance;
extern HWND						_hWnd;
extern POINT					_ptMouse;
