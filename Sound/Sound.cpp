//*****************************************************************************
//
// 音
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "Sound.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

Sound::Sound()
	: m_playSeFlag1					(0x00000000)
	, m_playSeFlag2					(0x00000000)
	, FLAG1_CAT_GRASS				(0x00000001)
	, FLAG1_UNLOCK					(0x00000002)
	, FLAG1_CAT_VOICE				(0x00000004)
	, FLAG1_CAT_DAMAGE_NEEDLE		(0x00000008)
	, FLAG1_MENU_OPENCLOSE			(0x00000010)
	, FLAG1_ENTERBOARD_LANDING		(0x00000020)
	, FLAG1_FOOTSTEPS_A				(0x00000040)
	, FLAG1_FOOTSTEPS_B				(0x00000080)
	, FLAG1_GRASS					(0x00000100)
	, FLAG1_BOSS_JUMP				(0x00000200)
	, FLAG1__SILENCE				(0x00000400)
	, FLAG1_MOUSEKEYPER_WALL		(0x00000800)
	, FLAG1_MOUSEKING_WALL			(0x00001000)
	, FLAG1_BRIDGE_DOWN				(0x00002000)
	, FLAG1_SAVE_POINT				(0x00004000)
	, FLAG1_MOUSEKING_LANDING		(0x00008000)
	, FLAG1_ROCKCOLLAPSE			(0x00010000)
	, FLAG1_CATJUMP					(0x00020000)
	, FLAG1_MOVEROCK_END			(0x00040000)
	, FLAG1_REACTION				(0x00080000)
	, FLAG1_BOSSDAMAGE				(0x00100000)
	, FLAG1_CAGE_FALL				(0x00200000)
	, FLAG1_OPENDOOR				(0x00400000)
	, FLAG1_RUSHWIND				(0x00800000)
	, FLAG1_FOOTSTEPS_MOVIE_A		(0x01000000)
	, FLAG1_FOOTSTEPS_MOVIE_B		(0x02000000)
	, FLAG1_SAVEPOINT_CATVOICE		(0x04000000)
	, FLAG1_MOUSES_FOOTSTEPS_A      (0x08000000)
	, FLAG1_MOUSES_FOOTSTEPS_B      (0x10000000)
	, FLAG1_TRENDMOUSE_GATHER		(0x20000000)
	, FLAG1_ROLLROCK				(0x40000000)
	, FLAG1_ROCKPUSH			    (0x80000000)
	, FLAG2_MOUSE_DISCOVERY         (0x00000001)
	, FLAG2_MOUSE_DAMAGE		    (0x00000002)
	, FLAG2_BRIDGEROPECUT			(0x00000004)
	, FLAG2_ROCKPUSH_UNDERGROUND    (0x00000008)
	, FLAG2_BOSSDAMAGELAST			(0x00000010)
	, FLAG2_BOSS_FOOTSTEPS_A        (0x00000020)
	, FLAG2_BOSS_FOOTSTEPS_B        (0x00000040)
{
}

//SEを再生(再生中に再生しない：連続再生にも対応)
void Sound::PlayingNoPlay(Engine* pEngine, const int index)
{
	//再生していなければ
	if (!(SelectGetFlag(index) & GetFlag(index))){

		//時間をセットする
		m_imPlaySound[index].SetInterval(GetTime(index));

		//SEのセットと再生
		SetAndPlay(pEngine, index);

		//フラグを選択、切替
		SelectChangeFlag(index, true);
	}

	//時間をセットする
	if (m_imPlaySound[index].GetTiming()) {

		//フラグを選択、切替
		SelectChangeFlag(index, false);
	}
}

//SEを再生(再生中に再生する可能性がある)
void Sound::PlayingPlay(Engine * pEngine, const int index)
{
	//再生中にもう一度呼ばれたらフラグを戻す
	if (SelectGetFlag(index) & GetFlag(index)) {
		SelectChangeFlag(index, false);
	}

	//再生していなければ
	if (!(SelectGetFlag(index) & GetFlag(index))) {
			
		//時間をセットする
		m_imPlaySound[index].SetInterval(GetTime(index));

		//SEのセットと再生
		SetAndPlay(pEngine, index);

		//フラグを選択、切替
		SelectChangeFlag(index, true);
	}
}

//SEを再生(一回再生されたらもう再生しない)
void  Sound::OnePlay(Engine* pEngine, const int index)
{
	//再生していなければ
	if (!(SelectGetFlag(index) & GetFlag(index))) {

		//時間をセットする
		m_imPlaySound[index].SetInterval(GetTime(index));

		//SEのセットと再生
		SetAndPlay(pEngine, index);

		//フラグを選択、切替
		SelectChangeFlag(index, true);
	}
}

//SE再生停止
void Sound::StopPlay(const int index)
{
	SelectChangeFlag(index, false);
}


/*---------------private関数---------------*/

//再生するSEに応じた時間を取得する
int Sound::GetTime(const int index) const
{
	switch (index) {

	case CAT_GRASS:
		return 350; break;

	case UNLOCK:
		return 600; break;

	case CAT_VOICE:
		return 660; break;

	case CAT_DAMAGE_NEEDLE:
		return 100; break;

	case MENU_OPENCLOSE:
		return 110; break;

	case ENTERBOARD_LANDING:
		return 140; break;

	case FOOTSTEPS_A:
		return 100; break;

	case FOOTSTEPS_B:
		return 100; break;

	case GRASS:
		return 880; break;

	case BOSS_JUMP:
		return 600; break;

	case _SILENCE:
		return 1; break;

	case MOUSEKEYPER_WALL:
		return 800; break;

	case MOUSEKING_WALL:
		return 800; break;

	case BRIDGE_DOWN:
		return 400; break;

	case SAVE_POINT:
		return 300; break;

	case MOUSEKING_LANDING:
		return 800; break;

	case ROCKCOLLAPSE:
		return 300; break;

	case CATJUMP:
		return 200; break;

	case MOVEROCK_END:
		return 110; break;

	case REACTION:
		return 550; break;

	case BOSSDAMAGE:
		return 200; break;

	case CAGE_FALL:
		return 100; break;

	case OPENDOOR:
		return 2500; break;

	case RUSHWIND:
		return 11000; break;

	case FOOTSTEPS_MOVIE_A:
		return 100; break;

	case FOOTSTEPS_MOVIE_B:
		return 100; break;

	case SAVEPOINT_CATVOICE:
		return 660; break;

	case MOUSES_FOOTSTEPS_A:
		return 150; break;

	case MOUSES_FOOTSTEPS_B:
		return 150; break;

	case TRENDMOUSE_GATHER:
		return 800; break;

	case ROLLROCK:
		return 7800; break;

	case ROCKPUSH:
		return 5000; break;

	case MOUSE_DISCOVERY:
		return 600; break;

	case MOUSE_DAMAGE:
		return 100; break;

	case BRIDGEROPECUT:
		return 200; break;

	case ROCKPUSH_UNDERGROUND:
		return 5000; break;

	case BOSSDAMAGELAST:
		return 300; break; 

	case BOSS_FOOTSTEPS_A:
		return 150; break;

	case BOSS_FOOTSTEPS_B:
		return 150; break;

	}
	return 0;
}

//フラグ取得
unsigned long Sound::GetFlag(const int index) const
{
	switch (index) {

	case CAT_GRASS:
		return FLAG1_CAT_GRASS; break;

	case UNLOCK:
		return FLAG1_UNLOCK; break;

	case CAT_VOICE:
		return FLAG1_CAT_VOICE; break;

	case CAT_DAMAGE_NEEDLE:
		return FLAG1_CAT_DAMAGE_NEEDLE; break;

	case MENU_OPENCLOSE:
		return FLAG1_MENU_OPENCLOSE; break;

	case ENTERBOARD_LANDING:
		return FLAG1_ENTERBOARD_LANDING; break;

	case FOOTSTEPS_A:
		return FLAG1_FOOTSTEPS_A; break;

	case FOOTSTEPS_B:
		return FLAG1_FOOTSTEPS_B; break;

	case GRASS:
		return FLAG1_GRASS; break;

	case BOSS_JUMP:
		return FLAG1_BOSS_JUMP; break;

	case _SILENCE:
		return FLAG1__SILENCE; break;

	case MOUSEKEYPER_WALL:
		return FLAG1_MOUSEKEYPER_WALL; break;

	case MOUSEKING_WALL:
		return FLAG1_MOUSEKING_WALL; break;

	case BRIDGE_DOWN:
		return FLAG1_BRIDGE_DOWN; break;

	case SAVE_POINT:
		return FLAG1_SAVE_POINT; break;

	case MOUSEKING_LANDING:
		return FLAG1_MOUSEKING_LANDING; break;

	case ROCKCOLLAPSE:
		return FLAG1_ROCKCOLLAPSE; break;

	case CATJUMP:
		return FLAG1_CATJUMP; break;

	case MOVEROCK_END:
		return FLAG1_MOVEROCK_END; break;

	case REACTION:
		return FLAG1_REACTION; break;

	case BOSSDAMAGE:
		return FLAG1_BOSSDAMAGE; break;

	case CAGE_FALL:
		return FLAG1_CAGE_FALL; break;

	case OPENDOOR:
		return FLAG1_OPENDOOR; break;

	case RUSHWIND:
		return FLAG1_RUSHWIND; break;

	case FOOTSTEPS_MOVIE_A:
		return FLAG1_FOOTSTEPS_MOVIE_A; break;

	case FOOTSTEPS_MOVIE_B:
		return FLAG1_FOOTSTEPS_MOVIE_B; break;

	case SAVEPOINT_CATVOICE:
		return FLAG1_SAVEPOINT_CATVOICE; break;

	case MOUSES_FOOTSTEPS_A:
		return FLAG1_MOUSES_FOOTSTEPS_A; break;

	case MOUSES_FOOTSTEPS_B:
		return FLAG1_MOUSES_FOOTSTEPS_B; break;

	case TRENDMOUSE_GATHER:
		return FLAG1_TRENDMOUSE_GATHER; break;

	case ROLLROCK:
		return FLAG1_ROLLROCK; break;

	case ROCKPUSH:
		return FLAG1_ROCKPUSH; break;

	case MOUSE_DISCOVERY:
		return FLAG2_MOUSE_DISCOVERY; break;

	case MOUSE_DAMAGE:
		return FLAG2_MOUSE_DAMAGE; break;

	case BRIDGEROPECUT:
		return FLAG2_BRIDGEROPECUT; break; 

	case ROCKPUSH_UNDERGROUND:
		return FLAG2_ROCKPUSH_UNDERGROUND; break;

	case BOSSDAMAGELAST:
		return FLAG2_BOSSDAMAGELAST; break;

	case BOSS_FOOTSTEPS_A:
		return FLAG2_BOSS_FOOTSTEPS_A; break;

	case BOSS_FOOTSTEPS_B:
		return FLAG2_BOSS_FOOTSTEPS_B; break;
	}

	return 0;
}

//SEのセットと再生
void Sound::SetAndPlay(Engine* pEngine, const int index)
{
	switch (index) {
		
	case CAT_GRASS:
		pEngine->PlaySE(SE_CAT_GRASS); break;

	case UNLOCK:
		pEngine->PlaySE(SE_UNLOCK); break;

	case CAT_VOICE:
		pEngine->PlaySE(SE_CAT_VOICE); break;

	case CAT_DAMAGE_NEEDLE:
		pEngine->PlaySE(SE_CAT_DAMAGE_NEEDLE); break;

	case MENU_OPENCLOSE:
		pEngine->PlaySE(SE_MENU_OPENCLOSE); break;

	case ENTERBOARD_LANDING:
		pEngine->PlaySE(SE_ENTERBOARD_LANDING); break;

	case FOOTSTEPS_A:
		pEngine->PlaySE(SE_FOOTSTEPS_A); break;

	case FOOTSTEPS_B:
		pEngine->PlaySE(SE_FOOTSTEPS_B); break;

	case GRASS:
		pEngine->PlaySE(SE_GRASS); break;

	case BOSS_JUMP:
		pEngine->PlaySE(SE_BOSS_JUMP); break;

	case _SILENCE:
		pEngine->PlaySE(_SE_SILENCE); break;

	case MOUSEKEYPER_WALL:
		pEngine->PlaySE(SE_MOUSEKEYPER_WALL); break;

	case MOUSEKING_WALL:
		pEngine->PlaySE(SE_MOUSEKING_WALL); break;

	case BRIDGE_DOWN:
		pEngine->PlaySE(SE_BRIDGE_DOWN); break;

	case SAVE_POINT:
		pEngine->PlaySE(SE_SAVE_POINT); break;

	case MOUSEKING_LANDING:
		pEngine->PlaySE(SE_MOUSEKING_LANDING); break;

	case ROCKCOLLAPSE:
		pEngine->PlaySE(SE_ROCKCOLLAPSE); break;

	case CATJUMP:
		pEngine->PlaySE(SE_CATJUMP); break;

	case MOVEROCK_END:
		pEngine->PlaySE(SE_MOVEROCK_END); break;

	case REACTION:
		pEngine->PlaySE(SE_REACTION); break;

	case BOSSDAMAGE:
		pEngine->PlaySE(SE_BOSSDAMAGE); break;

	case CAGE_FALL:
		pEngine->PlaySE(SE_CAGE_FALL); break;

	case OPENDOOR:
		pEngine->PlaySE(SE_OPENDOOR); break;

	case RUSHWIND:
		pEngine->PlaySE(SE_RUSHWIND); break;

	case FOOTSTEPS_MOVIE_A:
		pEngine->PlaySE(SE_FOOTSTEPS_MOVIE_A); break;

	case FOOTSTEPS_MOVIE_B:
		pEngine->PlaySE(SE_FOOTSTEPS_MOVIE_B); break;

	case SAVEPOINT_CATVOICE:
		pEngine->PlaySE(SE_SAVEPOINT_CATVOICE); break;

	case MOUSES_FOOTSTEPS_A:
		pEngine->PlaySE(SE_MOUSES_FOOTSTEPS_A); break;

	case MOUSES_FOOTSTEPS_B:
		pEngine->PlaySE(SE_MOUSES_FOOTSTEPS_B); break;

	case TRENDMOUSE_GATHER:
		pEngine->PlaySE(SE_TRENDMOUSE_GATHER); break;

	case ROLLROCK:
		pEngine->PlaySE(SE_ROLLROCK); break;

	case ROCKPUSH:
		pEngine->PlaySE(SE_ROCKPUSH); break;

	case MOUSE_DISCOVERY:
		pEngine->PlaySE(SE_MOUSE_DISCOVERY); break;

	case MOUSE_DAMAGE:
		pEngine->PlaySE(SE_MOUSE_DAMAGE); break;

	case BRIDGEROPECUT:
		pEngine->PlaySE(SE_BRIDGEROPECUT); break; 

	case ROCKPUSH_UNDERGROUND:
		pEngine->PlaySE(SE_ROCKPUSH_UNDERGROUND); break;

	case BOSSDAMAGELAST:
		pEngine->PlaySE(SE_BOSSDAMAGELAST); break;

	case BOSS_FOOTSTEPS_A:
		pEngine->PlaySE(SE_BOSS_FOOTSTEPS_A); break;

	case BOSS_FOOTSTEPS_B:
		pEngine->PlaySE(SE_BOSS_FOOTSTEPS_B); break;


	default:
		break;
	}
}

//フラグを選択、取得
unsigned long Sound::SelectGetFlag(const int index) const
{
	//m_playSeFlag1
	if (index <= MAX_SOUND1) {
		return m_playSeFlag1;
	}
	//m_playSeFlag2
	else if (index <= MAX_SOUND2) {
		return m_playSeFlag2;
	}
	//exception
	else {
		return 0x00000000;
	}
}

//フラグを選択、切替(第２引数はtrue、falseどっちに切り替えたいのかを入れる)
void Sound::SelectChangeFlag(const int index, const bool bWhich)
{
	//trueに切替
	if (bWhich) {

		//m_playSeFlag1
		if (index <= MAX_SOUND1) {
			m_playSeFlag1 |= GetFlag(index);
		}
		//m_playSeFlag2
		else if (index <= MAX_SOUND2) {
			m_playSeFlag2 |= GetFlag(index);
		}
	}
	//falseに切替
	else {

		//m_playSeFlag1
		if (index <= MAX_SOUND1) {
			m_playSeFlag1 &= ~GetFlag(index);
		}
		//m_playSeFlag2
		else if (index <= MAX_SOUND2) {
			m_playSeFlag2 &= ~GetFlag(index);
		}
	}
}
