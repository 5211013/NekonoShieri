//*****************************************************************************
//
// 檻
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "MoviePrison.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

MoviePrison::MoviePrison()
	: m_bPrison(false)
{
}

//更新
void MoviePrison::Update()
{
	//転送元セット
	SourSet(m_bPrison * m_drawWidth, 0);
}

//檻を開錠する
void MoviePrison::UnlockPrison()
{
	m_bPrison = true;
}

//檻のロックフラグを取得する
bool MoviePrison::IsPrison() const
{
	return m_bPrison;
}



