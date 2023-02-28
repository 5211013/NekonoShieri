//*****************************************************************************
//
// ムービー用のメッセージ
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\MovieObject.h"

#include <sstream>

class MovieMessage : public MovieObject
{
public:

	MovieMessage();

	//更新
	void Update();

	//描画
	void DrawMessage(Engine * pEngine);

	//メッセージ終了フラグ取得
	bool IsMessageEnd() const;
	
private:

	enum 
	{
		DRAW_FRAM1 = 350,
		DRAW_FRAM2 = 640,
		DRAW_FRAM3 = 950,
		DRAW_FRAM4 = 680,
	};

	//メッセージの保存用
	std::string m_message;

	//表示用文字列
	std::stringstream m_showMessage;

	//表示用カウンター
	int	m_counter;

	//メッセージ再生スピード
	IntervalManage m_imMessageTimer;

	//メッセージ終了フラグ
	bool m_bMessageEnd;

	//メッセージを設定
	void MessageSet();

	//メッセージを更新
	void Message();
};
