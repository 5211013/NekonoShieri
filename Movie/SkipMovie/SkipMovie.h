//*****************************************************************************
//
// スキップ
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\MovieObject.h"

class SkipMovie : public MovieObject
{
public:
	
	static const int WIDTH;
	static const int HEIGHT;

	SkipMovie();

	//更新
	void Update(Engine* pEngine, const bool bFadeInEnd);

	//描画
	void Draw(Engine* pEngine);

	//フェード描画(ナレーション時のみ)
	void DrawNarrationFade(Engine* pEngine);

	//ゲージマックス取得
	bool IsGaugeMax() const;

	//フェードアウト(ナレーションのみ)終わったかどうか
	bool IsNarrationFadeOut();
	
private:

	//ラインのサイズ
	const int LINE_SIZE;

	//描画ラインの数
	enum {
		FIRST_HALF,
		LATTER_HALF,
		LINE_NUM,
	};

	//描画用変数
	int m_line_x[LINE_NUM];
	int m_line_y[LINE_NUM];

	//ラインの添え字
	int m_lineIndex;

	//ナレーション用アルファ値
	int m_narrationAlpha;

	//キーが押された(RIGHT, LEFT, ENTER, SPACE, C, Q)
	bool m_bKeyPush;

	//エンターキーが押された
	bool m_bEnterPush;

	//描画用
	bool m_bDraw;

	//表示しているか
	bool m_bDisplay;

	//ゲージマックス
	bool m_bGaugeMax;

	//描画用タイマー
	IntervalManage m_imDraw;

	//キー入力
	void Input(Engine* pEngine);

	//キー入力時の処理
	void Display();

	//フェード処理
	void Fade();

	//線の制御
	void LineControl();

	//描画(UI)
	void DrawUI(Engine * pEngine);

	//描画(スキップライン)
	void DrawSkipLine(Engine * pEngine);
};
