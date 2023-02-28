//*****************************************************************************
//
// ムービー管理
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "ManageMovie.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

ManageMovie::ManageMovie()
	: m_movieFlag(0x00)
{
}

//ムービーフラグ取得
bool ManageMovie::IsMovieFlag(const int MovieFlag) const
{
	if (m_movieFlag & MovieFlag) {
		return true;
	}
	else {
		return false;
	}
}

//ムービーフラグ切替
void ManageMovie::ChangeMovieFlag(const int MovieFlag)
{
	m_movieFlag |= MovieFlag;
}

///ムービーフラグ
char ManageMovie::GetMovieFlag() const
{
	return m_movieFlag;
}

//ムービーフラグをセット
void ManageMovie::ReSetMovieFlag(unsigned char saveMovieFlag)
{
	m_movieFlag = saveMovieFlag;
}
