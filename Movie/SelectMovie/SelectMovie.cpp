//*****************************************************************************
//
// どのムービーシーンに移動するか
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "SelectMovie.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

SelectMovie::SelectMovie()
	: m_moveControlFlag(0x00)
	, m_sceneNo(0)
	, m_bSubScene(false)
{
}

//更新(ムービーシーンに移動するとき)(サブシーンも含む)
void SelectMovie::Update(SceneData& nowScene, Scene* const pOriginalScene, const bool bFadeOutEnd, const bool bFadeInEnd)
{
	//リセット
	Reset(bFadeInEnd);

	if (m_moveControlFlag & MOVIE) {
		//ムービーシーンに移動
		MovieSceneMovement(nowScene, bFadeOutEnd, pOriginalScene);
	}
}

//更新(ムービーシーンから次のシーンに移動するとき)
void SelectMovie::Update(SceneData& nowScene, const bool bEndMovie, const int retrunSceneNo)
{
	//ムービーシーンから戻るシーンを選ぶ
	MovieEndSceneSelect(bEndMovie, retrunSceneNo);

	//次のシーンに移動
	NextSceneMovement(nowScene);
}

//ムービーへ移る時はこの関数を呼ぶ
//ムービーシーンを選ぶ(引数 : 移動したいシーンの番号、サブシーンかどうか)
void SelectMovie::MovieSceneSelect(const int sceneNo, const bool bSubScene)
{
	m_sceneNo = sceneNo;
	m_bSubScene = bSubScene;

	//ムービーフラグをtrue
	m_moveControlFlag |= MOVIE;
}


//ムービー中フラグ取得
bool SelectMovie::IsMovie() const
{
	if (m_moveControlFlag & MOVIE) {

		return true;
	}
	else {
		return false;
	}
}

//ムービー移動フラグ取得
bool SelectMovie::IsMovieMove() const
{
	if (m_moveControlFlag & MOVIE_MOVE) {

		return true;
	}
	else {
		return false;
	}
}

//ムービー終了フラグ取得
bool SelectMovie::IsMovieEnd() const
{
	if (m_moveControlFlag & MOVIE_END) {

		return true;
	}
	else {
		return false;
	}
}


/*---------------private関数---------------*/

//ムービーシーンに移動
void SelectMovie::MovieSceneMovement(SceneData& nowScene, const bool bFadeOutEnd, Scene* const pOriginalScene)
{
	//フェードアウトしたか
	if (bFadeOutEnd) {

		m_moveControlFlag |= MOVIE_MOVE;

		//ムービー終了フラグtrueにする
		m_moveControlFlag |= MOVIE_END;

		if (m_bSubScene) {
			nowScene.Set(m_sceneNo, true, pOriginalScene);
		}
		else {
			nowScene.Set(m_sceneNo, false, nullptr);
		}
	}
}

//次のシーンに移動
void SelectMovie::NextSceneMovement(SceneData& nowScene)
{
	//シーン移動フラグを調べる
	if (m_moveControlFlag & MOVIE_MOVE) {

		m_moveControlFlag &= ~MOVIE_MOVE;

		//シーン移動
		nowScene.Set(m_sceneNo, false, nullptr);
	}
}

//ムービーシーンから次のシーンを選ぶ
void SelectMovie::MovieEndSceneSelect(const bool bEndMovie, const int retrunSceneNo)
{
	//ムービーが終了したか調べる
	if (bEndMovie) {

		//ムービーから戻るシーンを代入
		m_sceneNo = retrunSceneNo;

		//移動フラグtrueにする
		m_moveControlFlag |= MOVIE_MOVE;
	}
}

//リセット
void SelectMovie::Reset(const bool bFadeInEnd)
{
	//ムービーが終了したら
	if (m_moveControlFlag & MOVIE_END) {

		//ムービー中フラグをfalseにする
		m_moveControlFlag &= ~MOVIE;

		m_moveControlFlag &= ~MOVIE_END;
	}

	//フェードイン終了したら
	if (bFadeInEnd) {

		m_moveControlFlag &= ~MOVIE_MOVE;
	}
}