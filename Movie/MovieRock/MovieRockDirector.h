//*****************************************************************************
//
// 岩ムービーディレクター
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\GameBase.h"

#include "..\\..\\MovieObject.h"
#include "..\\MovieCat.h"

class MovieRockDirector : public MovieObject
{
public:

	MovieRockDirector();

	//更新
	void Update(MovieCat& cat, const bool bGaugeMax);

private:

	//瞬きをし始める
	void CatStartWink(MovieCat& cat);
};