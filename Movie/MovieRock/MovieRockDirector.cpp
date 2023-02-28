//*****************************************************************************
//
// 岩ムービーディレクター
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "MovieRockDirector.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

MovieRockDirector::MovieRockDirector()
{
}

//更新
void MovieRockDirector::Update(MovieCat& cat, const bool bGaugeMax)
{
	//フェードイン
	if (!m_bFadeInEnd) {
		FadeIn();
	}
	else {
		//瞬きをし始める
		CatStartWink(cat);

		//エンター長押しでスキップ
		MovieSkipEnterHold(bGaugeMax);
	}

	//ムービー終了
	if (cat.IsLastPerform() || m_bSkip) {
		FadeOut();
	}
}


/*---------------private関数---------------*/

//瞬きをし始める
void MovieRockDirector::CatStartWink(MovieCat& cat)
{
	cat.StartWink();
}