//*****************************************************************************
//
// 檻
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\MovieObject.h"


class MoviePrison : public MovieObject
{
public:

	MoviePrison();

	//更新
	void Update();
	
	//檻を開錠する
	void UnlockPrison();

	//檻のロックフラグを取得する
	bool IsPrison() const;

private:

	//檻のロック
	bool m_bPrison;
};
