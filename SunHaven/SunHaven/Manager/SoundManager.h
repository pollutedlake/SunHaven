#pragma once
#include "../FrameWork/SingletonBase/SingletonBase.h"

// »ç¿îµå °¹¼ö
constexpr auto soundBuffer = 40;

// ¿©ºÐÀÇ Ã¤³Î °¹¼ö (¹öÆÛ)
constexpr auto extraSoundChannel = 40;

// ÃÑ »ç¿îµå °¹¼ö
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;



using namespace FMOD;

class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator  arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator  arrChannelsIter;

	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;


public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool background, bool loop);

	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);


	SoundManager();
	~SoundManager() {}

};

