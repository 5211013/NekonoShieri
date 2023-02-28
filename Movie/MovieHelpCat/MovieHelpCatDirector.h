//*****************************************************************************
//
// 捕らわれている猫ムービーディレクター
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\MovieObject.h"
#include "..\\MovieCat.h"
#include "..\\MovieHelpCat\\MoviePrison.h"
#include "..\\MovieHelpCat\\MoviePrisonCat.h"
#include "..\\MovieHelpCat\\MovieMessage.h"

class MovieHelpCatDirector : public MovieObject
{
public:

	MovieHelpCatDirector();

	//更新
	void Update(Engine * pEngine, MovieCat& cat, MoviePrison& prison, MoviePrisonCat& prisonCat, MovieMessage& message, Sound& sound, const bool bGaugeMax);

private:
};
