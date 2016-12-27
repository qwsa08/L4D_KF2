#pragma once

#define g_pSoundManager soundManager::GetInstance()

#include <map>
#include <string>

//fmod.hpp �߰�
#include "inc/fmod.hpp"

//lib ��ũ
#pragma comment (lib, "lib/fmodex_vc.lib")

//ä�� ���� ���� (����)

#define TOTAL_SOUND_CHANNEL 100

using namespace FMOD;

class soundManager
{
private:
	SINGLETONE(soundManager);

private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelIter;

private:
	System* _system;
	Sound** _sound;

	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	HRESULT init();
	void release();

	//���� �߰�
	void addSound( string keyName, string soundName, bool background = false, bool loop = false );

	//���
	void play( string keyName, float volume );

	//����
	void stop( string keyName );

	//����
	void pause( string keyName );

	//�ٽ� ���
	void resume( string keyName );

	//�����ִ�?
	bool isPauseSound( string keyName );

	//������̴�?
	bool isPlaySound( string keyName );

	//fmod �ý����� ����
	void update();
};

