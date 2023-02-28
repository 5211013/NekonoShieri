//*****************************************************************************
//
// ムービー用の捕らわれている猫
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\MovieObject.h"


class MoviePrisonCat : public MovieObject
{
public:

	MoviePrisonCat();

	//更新
	void Update(Engine * pEngine, Sound & sound);

	//檻から出る
	void OutPrison();

	//逃げる
	void Escape(Engine * pEngine, Sound & sound);

	//檻から出たか
	bool IsOutPrison() const;

private:

	//制御するフラグ
	unsigned char m_controlFlag;

	enum {                     
		LOCK_OPEN   = 0x01,   //鍵が開いたのを確認したか
		OUT_PRISON  = 0x02,   //檻から出たか
		TURN_AROUND = 0x04,   //振り向いたか
		MOVED       = 0x08,   //移動したか
		JUMP        = 0x10,   //ジャンプ中か
		JUMPED      = 0x20,   //1回ジャンプをしたか
		STOP        = 0x40,   //立ち止まったか
		WALK        = 0x80,   //歩いている
	};

	//サイズ
	const int CAT_SIZE;

	//檻の前
	const int BEFORE_PRISON;

	//階段の前
	const int BEFORE_STAIRS;

	//逃げるスピード
	const float RUN_SPEED;

	//ジャンプの横移動のスピード
	const float JUMP_SPEED;

	//ジャンプ角度のスピード
	const float ANGLE_SPEED;

	//ジャンプ角度の最大
	const float MAX_ANGLE;

	//ジャンプの高さ
	float m_jumpHeight;

	//高さ保存
	float m_saveHeight;

	//角度
	float m_angle;

	//足音用
	bool m_bFootStep;

	//足音の間隔用
	IntervalManage m_imFootStep;

	//ジャンプ
	void Jump();

	//アニメーション
	void Animation();

	//歩いている
	void WalkSe(Engine * pEngine, Sound & sound);
};
