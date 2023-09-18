#include "Stdafx.h"
#include "SceneManager.h"
#include "../FrameWork/GameNode/GameNode.h"
#include "../Scene/TitleScene.h"
#include "../Scene/MapToolScene.h"
#include "../Scene/FarmScene.h"
#include "../Scene/DynusScene.h"
#include "../Scene/DizzyScene.h"
#include "../Scene/ShopScene.h"
#include "../Scene/IntroScene.h"
#include "../Scene/MineScene.h"

HRESULT SceneManager::init(void)
{
    SCENEMANAGER->addScene("Title", new TitleScene);
    SCENEMANAGER->addScene("MapTool", new MapToolScene);
    SCENEMANAGER->addScene("Shop", new ShopScene);
    SCENEMANAGER->addScene("Farm", new FarmScene);
    SCENEMANAGER->addScene("Dynus", new DynusScene);
    SCENEMANAGER->addScene("Dizzy", new DizzyScene);
    SCENEMANAGER->addScene("Intro", new IntroScene);
    SCENEMANAGER->addScene("Mine", new MineScene);
    _currentScene = nullptr;
    return S_OK;
}

void SceneManager::update(void)
{
    if (_currentScene != nullptr)
    {
        _currentScene->update();
    }
}

void SceneManager::release(void)
{
    for (auto iter = _sceneMap.begin(); iter != _sceneMap.end();)
    {
        if (iter->second != nullptr)
        {
            iter = _sceneMap.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    _sceneMap.clear();
}

void SceneManager::render(void)
{
    if (_currentScene != nullptr)
    {
        _currentScene->render();
    }
}



void SceneManager::addScene(string sceneName, GameNode* scene)
{
    if (scene != nullptr)
    {
        _sceneMap.insert(make_pair(sceneName, scene));
    }
}

HRESULT SceneManager::changeScene(string sceneName)
{
    auto iter = _sceneMap.find(sceneName);
    if (iter->second == _currentScene)
    {
        return S_OK;
    }
    if (SUCCEEDED(iter->second->init()))
    {
        _currentScene = iter->second;
        return S_OK;
    }
    return E_FAIL;
}