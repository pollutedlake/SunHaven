#include "stdafx.h"
#include "SoundManager.h"

HRESULT SoundManager::init(void)
{
    //! Do Nothing

    return S_OK;
}

void SoundManager::addMp3FileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;
    const char* str = finalQuery.c_str();

    // mciSendString() : ��ġ�� Ư�� ���ɾ �����Ͽ� ������Ű�� �Լ�
    // �� ���ڿ� ���ɾ�, ��ȯ���� �˷��� ���ɾ�, ��ȯ�� ����, �ڵ��ݹ�
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type waveautio alias ";
    string finalQuery = first + fileName + end + key;
    const char* str = finalQuery.c_str();

    // mciSendString() : ��ġ�� Ư�� ���ɾ �����Ͽ� ������Ű�� �Լ�
    // �� ���ڿ� ���ɾ�, ��ȯ���� �˷��� ���ɾ�, ��ȯ�� ����, �ڵ��ݹ�
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::playEffectSoundWave(char* fileName)
{
    /*
    // PlaySound() : TEXT("���� �̸�.wav"),
    // ���ϸ��� �ÿ��ϸ� NULL != �ش� �ν��Ͻ� �ڵ�
    // fdwSount (�ɼ� | �ɼ� | �ɼ�)

    SND_ASYNC : ����ϸ鼭 �����ڵ带 ����
    �� �񵿱� �÷���

    SND_LOOP : �ݺ� ���

    SND_NODEFAULT : ������ ��ο� ������ ��� ������� ������� �ʴ´�.
    */
    PlaySound(fileName, NULL, SND_ASYNC);
}

void SoundManager::playSoundWithKey(string key)
{
    string first = "play ";
    string finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::stopMp3WithKey(string key)
{
    string first = "stop ";
    string finalQuery = "";
    finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}