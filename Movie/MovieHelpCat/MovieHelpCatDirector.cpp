//*****************************************************************************
//
// 捕らわれている猫ムービーディレクター
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "MovieHelpCatDirector.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;


MovieHelpCatDirector::MovieHelpCatDirector()
{
}

//更新
void MovieHelpCatDirector::Update(Engine * pEngine, MovieCat & cat, MoviePrison & prison, MoviePrisonCat & prisonCat, MovieMessage& message, Sound& sound, const bool bGaugeMax)
{
	//フェードイン
	if (!m_bFadeInEnd) {
		FadeIn();
	}
	else {
		//猫を助ける
		cat.ChangeFlagHelpCat();

		//猫が移動し終わっているか調べる(trueなら移動済み)
		if (cat.IsMoved()) {

			//檻を解錠する
			prison.UnlockPrison();

			//解錠する音
			sound.OnePlay(pEngine, sound.UNLOCK);
		}

		//檻が開いてるか調べる
		if (prison.IsPrison()) {

			//檻を出る
			prisonCat.OutPrison();
		}

		//檻から出たか調べる
		if (prisonCat.IsOutPrison()) {
			//メッセージ再生
			message.Update();
		}

		//メッセージが終了したか調べる
		if (message.IsMessageEnd()) {

			//画面外に逃げる
			prisonCat.Escape(pEngine, sound);
		}

		//エンター長押しでスキップ
		MovieSkipEnterHold(bGaugeMax);
	}

	//ムービー終了
	if (prisonCat.IsLastPerform() || m_bSkip) {
		FadeOut();
	}
}