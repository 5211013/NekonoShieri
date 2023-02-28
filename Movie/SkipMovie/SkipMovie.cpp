//*****************************************************************************
//
// スキップ
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "SkipMovie.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

const int SkipMovie::WIDTH  = 194;
const int SkipMovie::HEIGHT = 48;

SkipMovie::SkipMovie()
	: LINE_SIZE(4)
	, m_lineIndex(0)
	, m_narrationAlpha(0)
	, m_bKeyPush(false)
	, m_bEnterPush(false)
	, m_bDraw(false)
	, m_bDisplay(false)
	, m_bGaugeMax(false)
{

	for (int i = 0; i < LINE_NUM; i++){

		m_line_x[i] = 0;
		m_line_y[i] = LINE_SIZE;
	}

	m_alpha = 0;

	//ゲージラインの変更速度に使用
	m_speed = 6.0f;
}

//更新
void SkipMovie::Update(Engine* pEngine, const bool bFadeInEnd)
{
	//ゲージがマックスでない且つフェードインが終了してたら
	if (!m_bGaugeMax && bFadeInEnd) {

		//キー入力
		Input(pEngine);

		//キー入力時の処理
		Display();

		//フェード処理
		Fade();

		//線の制御
		LineControl();
	}
}

//描画
void SkipMovie::Draw(Engine* pEngine)
{
	if (m_bDraw) {
			
		//UI
		DrawUI(pEngine);

		//スキップライン
		DrawSkipLine(pEngine);
	}
}

//フェード描画(ナレーション時のみ)
void SkipMovie::DrawNarrationFade(Engine* pEngine)
{
	SetRect(&m_sour, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SetRect(&m_dest, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	pEngine->Blt(&m_dest, TEXTURE_FADEOUT, &m_sour, m_narrationAlpha);
}

//ゲージマックス取得
bool SkipMovie::IsGaugeMax() const
{
	return m_bGaugeMax;
}

//フェードアウト(ナレーションのみ)終わったかどうか
bool SkipMovie::IsNarrationFadeOut()
{
	if (m_narrationAlpha < MAX_ALPHA) {

		m_narrationAlpha++;
		return false;
	}
	else {
		return true;
	}
}

/*---------------------private関数---------------------*/

//キー入力
void SkipMovie::Input(Engine* pEngine)
{
	//指定のキーが押されていたら
	if (pEngine->GetKeyState(DIK_RIGHT) ||
		pEngine->GetKeyState(DIK_LEFT)  || 
		pEngine->GetKeyState(DIK_RETURN)|| 
		pEngine->GetKeyState(DIK_SPACE) || 
		pEngine->GetKeyState(DIK_Q)     ||
		pEngine->GetKeyState(DIK_C)) {

		//キーを押した
		m_bKeyPush = true;
	}
	else{
		//キーを離した
		m_bKeyPush = false;
	}

	//エンターキーが押されたか
	if (pEngine->GetKeyState(DIK_RETURN)) {

		//キーを押した
		m_bEnterPush = true;
	}
	else{
		//キーを離した
		m_bEnterPush = false;
	}
}

//キー入力時の処理
void SkipMovie::Display()
{
	//キーしたか
	if (m_bKeyPush){

		//描画フラグ切替
		m_bDraw = true;

		//表示
		m_bDisplay = true;

		//描画用タイマーセット
		m_imDraw.SetInterval(3000);
	}

	//時間がたてば
	if (m_imDraw.GetTiming()){

		//描画を消す
		m_bDisplay = false;
	}
}

//フェード処理
void SkipMovie::Fade()
{
	//描画しているなら
	if (m_bDisplay) {

		//フェードイン
		m_alpha += (int)m_speed;

		//上限を設定
		if (m_alpha > MAX_ALPHA) {

			m_alpha = MAX_ALPHA;
		}
	}
	else {

		//フェードアウト
		m_alpha -= (int)m_speed;

		if (m_alpha < 0){

			m_alpha = 0;
			//描画をきる
			m_bDraw = false;
		}
	}
}

//線の制御
void SkipMovie::LineControl()
{
	//エンターキーを押したか
	if (m_bEnterPush) {

		//左に広がる
		if (m_line_x[m_lineIndex] < WIDTH - m_speed) {

			m_line_x[m_lineIndex] += (int)m_speed;
		}
		else {
			//上限の設定
			m_line_x[m_lineIndex] = WIDTH;

			//下に広がる
			if (m_line_y[m_lineIndex] < HEIGHT - m_speed) {

				m_line_y[m_lineIndex] += (int)m_speed;
			}
			else {
				//上限に設定
				m_line_y[m_lineIndex] = HEIGHT;


				//２回目ならゲージマックス
				if (m_lineIndex == 1) {
					m_bGaugeMax = true;
				}

				m_lineIndex = 1;
			}
		}
	}
	else {
		//離したとき
		if (m_line_y[m_lineIndex] > LINE_SIZE + m_speed) {

			m_line_y[m_lineIndex] -= (int)m_speed * 2;
		}
		else {
			//上限を設定
			m_line_y[m_lineIndex] = LINE_SIZE;

			if (m_line_x[m_lineIndex] > 0 + m_speed) {
				m_line_x[m_lineIndex] -= (int)m_speed * 2;
			}
			else {
				//上限を設定
				m_line_x[m_lineIndex] = 0;
				m_lineIndex = 0;
			}
		}
	}
}

//描画(UI)
void SkipMovie::DrawUI(Engine * pEngine)
{
	//UI
	int wx = (int)m_position.x;
	int wy = (int)m_position.y;

	SetRect(&m_sour, 0, 0, m_drawWidth, m_drawHeight);

	SetRect(&m_dest, wx, wy, wx + m_drawWidth, wy + m_drawHeight);

	pEngine->Blt(&m_dest, TEXTURE_SKIP, &m_sour, m_alpha);
}

//描画(スキップライン)
void SkipMovie::DrawSkipLine(Engine * pEngine)
{
	int wx = (int)m_position.x;
	int wy = (int)m_position.y;
	
	SetRect(&m_sour, 0, 0, m_line_x[FIRST_HALF], m_line_y[FIRST_HALF]);

	SetRect(&m_dest, wx, wy, wx + m_line_x[FIRST_HALF], wy + m_line_y[FIRST_HALF]);

	pEngine->Blt(&m_dest, TEXTURE_SKIP_LINE, &m_sour, m_alpha);


	//半分以降
	wx = (int)m_position.x + WIDTH;
	wy = (int)m_position.y + HEIGHT;

	SetRect(&m_sour, 0, 0, m_line_x[LATTER_HALF], m_line_y[LATTER_HALF]);

	SetRect(&m_dest, wx, wy, wx - m_line_x[LATTER_HALF], wy - m_line_y[LATTER_HALF]);

	pEngine->Blt(&m_dest, TEXTURE_SKIP_LINE, &m_sour, m_alpha);
}
