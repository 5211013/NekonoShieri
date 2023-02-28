//*****************************************************************************
//
// ムービー用メッセージ
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "MovieMessage.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;


MovieMessage::MovieMessage()
	: m_counter(0)
	, m_bMessageEnd(false)
{
	m_imMessageTimer.SetInterval(100);

	//表示用文字列の初期化
	m_showMessage.str("");

	for (int i = 0; i < TIMER_NUM; i++) {
		m_bSetTimer[i] = false;
	}
}

//更新
void MovieMessage::Update()
{
	//メッセージを設定
	MessageSet();
	//メッセージを更新
	Message();
}

//描画
void MovieMessage::DrawMessage(Engine * pEngine)
{
	RECT frame = { DRAW_FRAM1, DRAW_FRAM2, DRAW_FRAM3, DRAW_FRAM4 };

	if (!m_bMessageEnd){
		pEngine->DrawString(&frame, FONT_RM40, Color::WHITE, m_showMessage.str());
	}
}

//メッセージ終了フラグ取得
bool MovieMessage::IsMessageEnd() const
{
	return m_bMessageEnd;
}

/*---------------private関数---------------*/

//メッセージを設定
void MovieMessage::MessageSet()
{
	m_message = "ありがとう！この恩は忘れないよ";
}

//メッセージを更新
void MovieMessage::Message()
{
	if (m_counter < (int)m_message.size()){

		if (m_imMessageTimer.GetTiming()){
			
			m_showMessage << m_message[m_counter];
			m_counter++;

			m_showMessage << m_message[m_counter];
			m_counter++;
		}
	}
	else{
		//メッセージ表示が終わったらタイミングをとる
		if (Timer(2000)){
			m_bMessageEnd = true;
		}
	}
}
