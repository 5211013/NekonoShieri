//*****************************************************************************
//
// どのムービーシーンに移動するか
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\..\\Scene\\Scene\\Scene.h"

class SelectMovie
{
public:
	
	SelectMovie();
	
	//ムービーシーンへ移るときの更新
	void Update(SceneData& nowScene, Scene* const pOriginalScene, const bool bFadeOutEnd, const bool bFadeInEnd);

	//ムービーシーンから戻るときの更新
	void Update(SceneData& nowScene, const bool bEndMovie, const int retrunSceneNo);

	//ムービーシーンを選ぶ(引数 : 移動したいシーンの番号、サブシーンかどうか)
	void MovieSceneSelect(const int sceneNo, const bool bSubScene);

	//ムービー中フラグ取得
	bool IsMovie() const;

	//ムービー移動フラグ取得
	bool IsMovieMove() const;

	//ムービー終了フラグ取得
	bool IsMovieEnd() const;

private:

	enum {
		MOVIE      = 0x01,     //ムービー中か
		MOVIE_MOVE = 0x02,     //移動
		MOVIE_END  = 0x08,     //ムービー終了したか
	};
	
	//制御フラグ
	unsigned char m_moveControlFlag;

	//シーン番号
	int m_sceneNo;

	//サブシーンかどうか
	bool m_bSubScene;

	//ムービーシーンに移動
	void MovieSceneMovement(SceneData& nowScene, const bool bFadeOutEnd, Scene* const pOriginalScene = nullptr);

	//次のシーンに移動
	void NextSceneMovement(SceneData& nowScene);

	//ムービーシーンから次のシーンを選ぶ
	void MovieEndSceneSelect(const bool bEndMovie, const int retrunSceneNo);

	//リセット
	void Reset(const bool bFadeInEnd);
};