#pragma once
#pragma warning(disable : 4005)
#include<SDKDDKVER.h>
#include <ole2.h>
#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "JsonCPP/lib_json/json_vc71_libmtd.lib")

#pragma comment (lib, "lib/FMOD/fmodex_vc.lib")
#pragma comment(lib,"Winmm.lib")
#include <windows.h>

// 외부 헤더파일
#include "../../JsonCPP/include/json/json.h"
#include "../../inc/FMOD/fmod.hpp"

#include <mmsystem.h>

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
#include "../../Class/Data/JsonSaveLoader.h"
#include "../../Manager/DataManager.h"
#include "../Utility/Utils.h"
#include "../../Class/Camera.h"

using namespace MY_UTIL;

// # 싱글톤 #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define INIDATAMANAGER INIData::getSingleton()
#define DATAMANAGER DataManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()
#define CAMERA Camera::getSingleton()

// # 매크로 # (윈도우창 초기화)
#define WINNAME					(LPTSTR)(TEXT("WindowsAPI"))
#define WINSTART_X				50
#define WINSTART_Y				50
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
