//*****************************************************************************
//
// 音
//
//*****************************************************************************

#pragma once

#include "..\\..\\GameBase.h"

class Sound
{
public:

	//SEの種類
	enum {
		CAT_GRASS,				 //０.  猫じゃらしの音
		UNLOCK,					 //１.  檻の鍵を開ける音
		CAT_VOICE,				 //２.  猫の鳴き声
		CAT_DAMAGE_NEEDLE,		 //３.  針に刺さってダメージをくらった時の音
		MENU_OPENCLOSE,			 //４.  メニューの開閉時の音
		ENTERBOARD_LANDING,		 //５.  エンターボードが着地した時の音
		FOOTSTEPS_A,			 //６.  猫の足音A
		FOOTSTEPS_B,			 //７.  猫の足音B
		GRASS,					 //８.  草の音
		BOSS_JUMP,				 //９.  ボスのジャンプ音
		_SILENCE,				 //１０.無音
		MOUSEKEYPER_WALL,		 //１１.マウスキーパーが壁に衝突した時の音
		MOUSEKING_WALL,			 //１２.マウスキングが壁に衝突した時の音
		BRIDGE_DOWN,			 //１３.橋が降りきった時の音
		SAVE_POINT,				 //１４.セーブポインに触れた時の音
		MOUSEKING_LANDING,		 //１５.マウスキングが着地した時の音
		ROCKCOLLAPSE,			 //１６.岩が崩壊していく音
		CATJUMP,				 //１７.猫がジャンプする時の音
		MOVEROCK_END,			 //１８.動く岩が端まで行った時の音
		REACTION,				 //１９.リアクションマークの音
		BOSSDAMAGE,				 //２０.ボスがダメージを食らった時の音
		CAGE_FALL,				 //２１.ケージが落ちる音
		OPENDOOR,				 //２２.ボス戦前の扉を開ける時の音
		RUSHWIND,				 //２３.風を切る音
		FOOTSTEPS_MOVIE_A,		 //２４.猫のムービー用足音A
		FOOTSTEPS_MOVIE_B,		 //２５.猫のムービー用足音B
		SAVEPOINT_CATVOICE,		 //２６.セーブポイントの最初の音
		MOUSES_FOOTSTEPS_A,      //２７.鼠のムービー用足音A
		MOUSES_FOOTSTEPS_B,      //２８.鼠のムービー用足音B
		TRENDMOUSE_GATHER,       //２９.大量のネズミが猫に集まってくる時の音
		ROLLROCK,			     //３０.転がる岩の音
		ROCKPUSH,                //３１.岩を押す音(橋前)
	
		MAX_SOUND1,				 //３２.サウンド１の数

		MOUSE_DISCOVERY,         //３３.鼠が発見した時の音
		MOUSE_DAMAGE,			 //３４.鼠がダメージを受けた時の音
		BRIDGEROPECUT,			 //３５.ロープが切れた時の音
		ROCKPUSH_UNDERGROUND,    //３６.岩を押す音(地下)
		BOSSDAMAGELAST,			 //３７.ボスに最後のダメージが入った時の音
		BOSS_FOOTSTEPS_A,        //３８.ボスの足音A  
		BOSS_FOOTSTEPS_B,        //３９.ボスの足音B

		MAX_SOUND2,          //サウンド２の数
		MAX_ALLSOUND,        //全てのサウンドの数
	};

	Sound();

	//SEを再生(再生中に再生しない：連続再生にも対応)
	void PlayingNoPlay(Engine* pEngine, const int index);

	//SEを再生(再生中に再生する可能性がある)
	void PlayingPlay(Engine* pEngine, const int index);

	//SEを再生(一回再生されたらもう再生しない)
	void OnePlay(Engine* pEngine, const int index);

	//SE連続再生停止
	void StopPlay(const int index);

private:

	//SE再生用フラグ
	unsigned long m_playSeFlag1;
	unsigned long m_playSeFlag2;

	//サウンド１
	const unsigned long FLAG1_CAT_GRASS;
	const unsigned long FLAG1_UNLOCK;
	const unsigned long FLAG1_CAT_VOICE;
	const unsigned long FLAG1_CAT_DAMAGE_NEEDLE;
	const unsigned long FLAG1_MENU_OPENCLOSE;
	const unsigned long FLAG1_ENTERBOARD_LANDING;
	const unsigned long FLAG1_FOOTSTEPS_A;
	const unsigned long FLAG1_FOOTSTEPS_B;
	const unsigned long FLAG1_GRASS;
	const unsigned long FLAG1_BOSS_JUMP;
	const unsigned long FLAG1__SILENCE;
	const unsigned long FLAG1_MOUSEKEYPER_WALL;
	const unsigned long FLAG1_MOUSEKING_WALL;
	const unsigned long FLAG1_BRIDGE_DOWN;
	const unsigned long FLAG1_SAVE_POINT;
	const unsigned long FLAG1_MOUSEKING_LANDING;
	const unsigned long FLAG1_ROCKCOLLAPSE;
	const unsigned long FLAG1_CATJUMP;
	const unsigned long FLAG1_MOVEROCK_END;
	const unsigned long FLAG1_REACTION;
	const unsigned long FLAG1_BOSSDAMAGE;
	const unsigned long FLAG1_CAGE_FALL;
	const unsigned long FLAG1_OPENDOOR;
	const unsigned long FLAG1_RUSHWIND;
	const unsigned long FLAG1_FOOTSTEPS_MOVIE_A;
	const unsigned long FLAG1_FOOTSTEPS_MOVIE_B;
	const unsigned long FLAG1_SAVEPOINT_CATVOICE;
	const unsigned long FLAG1_MOUSES_FOOTSTEPS_A;
	const unsigned long FLAG1_MOUSES_FOOTSTEPS_B;
	const unsigned long FLAG1_TRENDMOUSE_GATHER;
	const unsigned long FLAG1_ROLLROCK;
	const unsigned long FLAG1_ROCKPUSH;
	

	//サウンド２
	const unsigned long FLAG2_MOUSE_DISCOVERY;
	const unsigned long FLAG2_MOUSE_DAMAGE;
	const unsigned long FLAG2_BRIDGEROPECUT;
	const unsigned long FLAG2_ROCKPUSH_UNDERGROUND;
	const unsigned long FLAG2_BOSSDAMAGELAST;
	const unsigned long FLAG2_BOSS_FOOTSTEPS_A;
	const unsigned long FLAG2_BOSS_FOOTSTEPS_B;



	//再生時間
	IntervalManage m_imPlaySound[MAX_ALLSOUND];

	//時間をセットする
	int GetTime(const int index) const;

	//フラグ取得
	unsigned long GetFlag(const int index) const;

	//SEのセットと再生
	void SetAndPlay(Engine* pEngine, const int index);

	//フラグを選択、取得
	unsigned long SelectGetFlag(const int index) const;

	//フラグを選択、切替(第２引数はtrue、falseどっちに切り替えたいのかを入れる)
	void SelectChangeFlag(const int index, const bool bWhich);
};