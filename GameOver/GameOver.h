//*****************************************************************************
//
// ゲームオーバー
//
//*****************************************************************************

#pragma once

#include "..\\..\\GameBase.h"
#include "..\\..\\GameData.h"
#include "..\\..\\Scene\\Scene\\Scene.h"
#include "..\\Sound\\Sound.h"

class GameOver
{
public:

	GameOver();

	//更新
	void Update(Engine* pEngine, SceneData& nowScene, Sound & sound, Common::CommonData& gameData, const bool bFadeOutEnd);

	//ゲームオーバー (引数 : ゲームオーバーシーンに移動するかtrueかfalse デフォルトでfalse)
	void PlayerGameOver(const bool bGameOverScene = false);

	//ゲームオーバーリセット(SceneGameOverで使用する)
	void GameOverReset(Common::CommonData& gameData);

	//ゲームオーバー取得
	bool IsGameOver() const;

private:

	//ゲームオーバーフラグ
	bool m_bGameOver;

	//ゲームオーバーシーンフラグ
	bool m_bGameOverScene;

	//ゲームオーバーシーンに移動
	void GameOverSceneMove(Engine* pEngine, SceneData& nowScene, Sound & sound, const bool bFadeOutEnd);

	//効果音を止める
	void SeStop(Engine * pEngine, Sound & sound);
};