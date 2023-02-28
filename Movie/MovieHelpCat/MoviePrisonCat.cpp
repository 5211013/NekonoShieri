//*****************************************************************************
//
// ムービー用の捕らわれている猫
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "MoviePrisonCat.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;


MoviePrisonCat::MoviePrisonCat()
	: m_controlFlag(0x00)
	, CAT_SIZE(102)
	, BEFORE_PRISON(430)
	, BEFORE_STAIRS(342)
	, RUN_SPEED(5.0f)
	, JUMP_SPEED(11.0f)
	, ANGLE_SPEED(5.0f)
	, MAX_ANGLE(-125.0f)
	, m_jumpHeight(250)
	, m_angle(0)
	, m_bFootStep(true)
{
	m_speed = 2.0f;
	m_animation = 0;
	m_imFootStep.SetInterval(300);
	m_imAnimation.SetInterval(250);
}

//更新
void MoviePrisonCat::Update(Engine * pEngine, Sound & sound)
{
	//転送元セット
	SourSet(m_drawWidth * m_animation, m_drawWidth * m_direction);

	//歩いている時の音
	WalkSe(pEngine, sound);
}

//檻から出る
void MoviePrisonCat::OutPrison()
{
	//タイミングをとる
	if (Timer(750)){
		m_controlFlag |= LOCK_OPEN;
	}

	//鍵が開いたか確認したか調べる
	if (m_controlFlag & LOCK_OPEN) {

		if (m_position.x >= BEFORE_PRISON) {
			//移動
			m_position.x -= m_speed;

			//動く時だけアニメーション
			Animation();

			//歩いている
			m_controlFlag |= WALK;
		}
		else {
			//立ち止まるテクスチャにする
			if (!(m_controlFlag & STOP)){
				m_animation = FRAME_1;
				m_controlFlag |= STOP;
			}

			//歩いている
			m_controlFlag &= ~WALK;

			if (Timer(500, 1)) {
				//振り向かせる
				m_direction = RIGHT;
				
				if (Timer(500, 2)) {
					m_controlFlag |= OUT_PRISON;
				}
			}
		}
	}
}

//逃げる
void MoviePrisonCat::Escape(Engine * pEngine, Sound & sound)
{
	//左方向に振り向く
	m_direction = LEFT;

	//タイミング調整
	if (Timer(1000, 3)) {
		m_controlFlag |= TURN_AROUND;
	}

	//階段まで進む
	if (m_controlFlag & TURN_AROUND) {

		if (m_position.x >= BEFORE_STAIRS) {

			m_position.x -= RUN_SPEED;
			//動く時だけアニメーション
			Animation();

			//歩いている
			m_controlFlag |= WALK;
		}
		else{
			if (!(m_controlFlag & JUMPED)){

				//ジャンプする
				Jump();	

				//横にジャンプする
				m_position.x -= JUMP_SPEED;

				//歩いている
				m_controlFlag &= ~WALK;

				//SE再生
				sound.OnePlay(pEngine, sound.CATJUMP);

			}
			else{
				if (Timer(75, 4)) {
					//時間を少し空けて再度ジャンプをする
					m_controlFlag &= ~JUMPED;

					sound.StopPlay(sound.CATJUMP);
				}
			}
		}
	}

	//画面外に逃げたか調べる
	if (m_position.x <= -CAT_SIZE){

		//止める
		m_position.x = -(float)CAT_SIZE;

		//ジャンプ終了
		m_controlFlag |= JUMPED;

		//ムービー最後の演出
		m_bMovieLastPerform = true;
	}
}

/*---------------private関数---------------*/

//檻から出たか
bool MoviePrisonCat::IsOutPrison() const
{
	if (m_controlFlag & OUT_PRISON){
		
		return true;
	}
	else{
		return false;
	}
}

//ジャンプ
void MoviePrisonCat::Jump()
{
	//ジャンプする
	//今ジャンプ中か調べる
	if (!(m_controlFlag & JUMP)) {
			
			//現在の高さ保存
			m_saveHeight = m_position.y;
			//リセット
			m_angle = 0;
			//フラグをtrueに
			m_controlFlag |= JUMP;
	}

	//ジャンプ中か調べる
	if (m_controlFlag & JUMP) {

		m_position.y = sin(D3DXToRadian(m_angle)) * m_jumpHeight + m_saveHeight;

		m_angle -= ANGLE_SPEED;

		if (m_angle < MAX_ANGLE) {
		
			//ジャンプ自体のフラグtrue
			m_controlFlag |= JUMPED;

			//ジャンプ中フラグtrue
			m_controlFlag &= ~JUMP;
		}
	}

	//ジャンプ中か調べる
	if (m_controlFlag & JUMP) {
		//ジャンプ用のテクスチャに変える
		m_animation = FRAME_4;
	}
	else{
		Animation();
	}
}

//アニメーション
void MoviePrisonCat::Animation()
{
	if (m_imAnimation.GetTiming()) {
		m_animation = (m_animation + 1) % FRAME_4;
	}
}

//歩いている
void MoviePrisonCat::WalkSe(Engine * pEngine, Sound & sound)
{
	if (m_controlFlag & WALK){

		if (m_imFootStep.GetTiming()){

			if (m_bFootStep){
				sound.PlayingPlay(pEngine, sound.FOOTSTEPS_MOVIE_A);
				m_bFootStep = false;
			}
			else {
				sound.PlayingPlay(pEngine, sound.FOOTSTEPS_MOVIE_B);
				m_bFootStep = true;
			}
		}
	}
}


