//*****************************************************************************
//
// ムービー管理
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\GameBase.h"


class ManageMovie
{
public:
	
	ManageMovie();

	//ムービーフラグ用
	enum {
		MOVIE_LIGHT       = 0x01,
		MOVIE_HELP_CAT    = 0x02,
		MOVIE_BRIDGE      = 0x04,
		MOVIE_MOUSEKEYPER = 0x08,
		MOVIE_MOUSEKING   = 0x10,
	};
	
	//ムービーフラグ取得
	bool IsMovieFlag(const int MovieFlag) const;

	//ムービーフラグ切替
	void ChangeMovieFlag(const int MovieFlag);

	//ムービーフラグ取得
	char GetMovieFlag() const;

	//ムービーフラグをセット
	void ReSetMovieFlag(unsigned char saveMovieFlag);

private:
	
	//ムービー用フラグ(そのムービをみたらそのビットがつく)
	unsigned char m_movieFlag;
};
