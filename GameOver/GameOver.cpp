//*****************************************************************************
//
// ゲームオーバー
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "GameOver.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

GameOver::GameOver()
	: m_bGameOver(false)
	, m_bGameOverScene(false)
{
}

//更新
void GameOver::Update(Engine* pEngine, SceneData& nowScene, Sound & sound, Common::CommonData& gameData, const bool bFadeOutEnd)
{
	//ゲームオーバーシーンに移動
	GameOverSceneMove(pEngine, nowScene, sound, bFadeOutEnd);
}


//ゲームオーバー (引数 : ゲームオーバーシーンに移動するかtrueかfalse デフォルトでfalse, アニメーションを再生するか)
void GameOver::PlayerGameOver(const bool bGameOverScene)
{
	//ゲームオーバーフラグセット
	m_bGameOver = true;

	if (bGameOverScene){
		m_bGameOverScene = true;
	}
}

//ゲームオーバーリセット(ゲームオーバーシーンで呼び出す)
void GameOver::GameOverReset(Common::CommonData& gameData)
{
	//ムービーフラグをセーブ時の状態に戻す(セーブしていない場合は初期値の0x00が代入される)
	gameData.m_manageMovie.ReSetMovieFlag(gameData.m_saveMovieFlag);
}

//ゲームオーバー取得
bool GameOver::IsGameOver() const
{
	return m_bGameOver;
}


/*---------------private関数---------------*/

//ゲームオーバーシーンに移動
void GameOver::GameOverSceneMove(Engine* pEngine, SceneData& nowScene, Sound & sound, const bool bFadeOutEnd)
{
	//ゲームオーバーなら
	if (m_bGameOverScene) {

		if (bFadeOutEnd) {

			//効果音を止める
			SeStop(pEngine, sound);

			//ゲームオーバーシーンに移動する
			nowScene.Set(Common::SCENE_GAMEOVER, false, nullptr);
		}
	}
}

//効果音を止める
void GameOver::SeStop(Engine * pEngine, Sound & sound)
{
	for (int i = 0; i < sound.MAX_ALLSOUND; i++) {
		sound.StopPlay(i);
	}

	pEngine->StopAllSE();
}
