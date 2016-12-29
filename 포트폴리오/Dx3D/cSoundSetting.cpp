#include "stdafx.h"
#include "cSoundSetting.h"


cSoundSetting::cSoundSetting()
{
}


cSoundSetting::~cSoundSetting()
{
}

void cSoundSetting::Setup()
{
	//=============================== Player ===============================
	Player_Sound_Setting();

	//=============================== Gun ===============================
	Weapon_Sound_Setting();

	//=============================== Zombie ===============================
	Zombie_Sound_Setting();
}

void cSoundSetting::Player_Sound_Setting()
{
	g_pSoundManager->addSound("Player_Breath", "Sound/Player/Malebreath.wav", false, true);
	g_pSoundManager->addSound("Player_Hit", "Sound/Player/hpain3.wav", false, false);
	g_pSoundManager->addSound("Player_Step", "Sound/Player/FPSetpLeft.wav", false, false);
	g_pSoundManager->addSound("Player_Death", "Sound/Player/death01.wav", false, false);
	g_pSoundManager->addSound("Player_Pickup", "Sound/Player/getweaponout3.wav", false, false);
}

void cSoundSetting::Weapon_Sound_Setting()
{
	//9mm handgun=====================
	g_pSoundManager->addSound("9mm_Fire", "Sound/Weapon/9mm/9mm_Fire.wav", false, false);
	g_pSoundManager->addSound("9mm_Pickup", "Sound/Weapon/9mm/9mm_Pickup.wav", false, false);
	g_pSoundManager->addSound("9mm_Select", "Sound/Weapon/9mm/9mm_Select.wav", false, false);
	g_pSoundManager->addSound("9mm_Reload01", "Sound/Weapon/9mm/9mm_Single_Reload_000.wav", false, false);
	g_pSoundManager->addSound("9mm_Reload02", "Sound/Weapon/9mm/9mm_Single_Reload_026.wav", false, false);
	g_pSoundManager->addSound("9mm_Reload03", "Sound/Weapon/9mm/9mm_Single_Reload_036.wav", false, false);
	g_pSoundManager->addSound("9mm_Reload04", "Sound/Weapon/9mm/9mm_Single_Reload_049.wav", false, false);

	//Bullpup=======================
	g_pSoundManager->addSound("Bullpup_Aim", "Sound/Weapon/Bullpup/Bullpup_Aim.wav", false, false);
	g_pSoundManager->addSound("Bullpup_Fire", "Sound/Weapon/Bullpup/Bullpup_Fire1.wav", false, false);
	g_pSoundManager->addSound("Bullpup_Pickup", "Sound/Weapon/Bullpup/Bullpup_Pickup.wav", false, false);
	g_pSoundManager->addSound("Bullpup_Select", "Sound/Weapon/Bullpup/Bullpup_Select.wav", false, false);
	g_pSoundManager->addSound("Bullpup_Reload01", "Sound/Weapon/Bullpup/Bullpup_Reload1.wav", false, false);
	g_pSoundManager->addSound("Bullpup_Reload02", "Sound/Weapon/Bullpup/Bullpup_Reload_013.wav", false, false);
	g_pSoundManager->addSound("Bullpup_Reload03", "Sound/Weapon/Bullpup/Bullpup_Reload_042.wav", false, false);

	//Shotgun=======================
	g_pSoundManager->addSound("Shotgun_Fire", "Sound/Weapon/ShotGun/KF_Shotgun_Dragon_Fire_M.wav", false, false);
	g_pSoundManager->addSound("Shotgun_Pickup", "Sound/Weapon/Bullpup/Bullpup_Pickup.wav", false, false);
	g_pSoundManager->addSound("Shotgun_Reload", "Sound/Weapon/ShotGun/TrenchGun_Bullet_Insert.wav", false, false);
	g_pSoundManager->addSound("Shotgun_Pump_Back", "Sound/Weapon/ShotGun/TrenchGun_Pump_Back.wav", false, false);
	g_pSoundManager->addSound("Shotgun_Pump_Forward", "Sound/Weapon/ShotGun/TrenchGun_Pump_Forward.wav", false, false);

	//Knife========================
	g_pSoundManager->addSound("Knife_Fire", "Sound/Weapon/Knife/Knife_Fire1.wav", false, false);
	g_pSoundManager->addSound("Knife_Select", "Sound/Weapon/Knife/Knife_Select1.wav", false, false);
}

void cSoundSetting::Zombie_Sound_Setting()
{
	//Global===================
	g_pSoundManager->addSound("Zombie_Hit1", "Sound/Zombie/Global/Blood_Burst1.wav", false, false);
	g_pSoundManager->addSound("Zombie_Hit2", "Sound/Zombie/Global/Zomb_HitPlayer_BigHit2.wav", false, false);
	g_pSoundManager->addSound("Zombie_Step", "Sound/Zombie/Global/Zomb_StepDefault_Conc2.wav", false, false);

	//Clot=====================
	g_pSoundManager->addSound("Clot_Attack", "Sound/Zombie/Clot/Clot_Attack1.wav", false, false);
	g_pSoundManager->addSound("Clot_Death", "Sound/Zombie/Clot/Clot_Death1.wav", false, false);
	g_pSoundManager->addSound("Clot_Idle", "Sound/Zombie/Clot/Clot_Idle1Loop.wav", false, true);

	//Gorefast=================
	g_pSoundManager->addSound("Gorefast_Attack", "Sound/Zombie/Gorefast/Gorefast_Attack1.wav", false, false);
	g_pSoundManager->addSound("Gorefast_Attack_Swing", "Sound/Zombie/Gorefast/Gorefast_AttackSwish1.wav", false, false);
	g_pSoundManager->addSound("Gorefast_Death", "Sound/Zombie/Gorefast/Gorefast_Death1.wav", false, false);
	g_pSoundManager->addSound("Gorefast_Idle", "Sound/Zombie/Gorefast/Gorefast_Idle.wav", false, true);

	//Crawler==================
	g_pSoundManager->addSound("Crawler_Attack", "Sound/Zombie/Crawler/Crawler_Attack1.wav", false, false);
	g_pSoundManager->addSound("Crawler_Death", "Sound/Zombie/Crawler/Crawler_Death1.wav", false, false);
	g_pSoundManager->addSound("Crawler_Idle", "Sound/Zombie/Crawler/Crawler_Idle.wav", false, true);

	//Bloat====================
	g_pSoundManager->addSound("Bloat_Attack", "Sound/Zombie/Bloat/Bloat_Attack1.wav", false, false);
	g_pSoundManager->addSound("Bloat_AcidSplash", "Sound/Zombie/Bloat/Bloat_AcidSplash.wav", false, false);
	g_pSoundManager->addSound("Bloat_Death", "Sound/Zombie/Bloat/Bloat_Death1.wav", false, false);
	g_pSoundManager->addSound("Bloat_Idle", "Sound/Zombie/Bloat/Bloat_Idle1.wav", false, true);

	//BOSS_Patriarch===========
	g_pSoundManager->addSound("BOSS_Attack", "Sound/Zombie/Boss_Patriarch/Kev_AttackA1.wav", false, false);
	g_pSoundManager->addSound("BOSS_Death", "Sound/Zombie/Boss_Patriarch/Kev_Death1.wav", false, false);
	g_pSoundManager->addSound("BOSS_Entrance1", "Sound/Zombie/Boss_Patriarch/Kev_Entrance_Scream1.wav", false, false);
	g_pSoundManager->addSound("BOSS_Entrance2", "Sound/Zombie/Boss_Patriarch/Kev_Entrance_Scream2.wav", false, false);
	g_pSoundManager->addSound("BOSS_Entrance3", "Sound/Zombie/Boss_Patriarch/Kev_Entrance_Scream3.wav", false, false);
	g_pSoundManager->addSound("BOSS_Heal", "Sound/Zombie/Boss_Patriarch/Kev_Heal2.wav", false, false);
	g_pSoundManager->addSound("BOSS_Idle", "Sound/Zombie/Boss_Patriarch/Kev_IdleLoop.wav", false, true);
	g_pSoundManager->addSound("BOSS_Victory", "Sound/Zombie/Boss_Patriarch/Kev_Victory7.wav", false, false);
}