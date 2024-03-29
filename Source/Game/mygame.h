/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include <string>
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_MenuSelect,
		AUDIO_GameStage,
		AUDIO_GameBoss,
		AUDIO_GameOver,
		AUDIO_Attack,
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	class CGanestage {
		public:
			CGanestage() {};
		private:
			int a;

	};

	class CGameStateValueStorage {
	public:
		CGameStateValueStorage();
		static void set_init_background_value(int);
		static int get_init_background_value();

		static void set_victory_value(int);
		static int get_victory_value();
		static void set_data(string tmp_t, string tmp_dead, string tmp_name);
		static string get_show_time();
		static string get_dead_number();
		static string get_weapon_name();
	private:
		static int init_background_value; //static => chaaracter 
		static int victory;
		static string show_time;
		static string dead_number;
		static string weapon_name;

	};
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState, public CGameStateValueStorage {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);
		bool isSelect(UINT nFlags, CPoint point, CMovingBitmap &item);
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap select1;
		CMovingBitmap select2;
		CMovingBitmap check_blank1;
		CMovingBitmap check_blank2;
		CMovingBitmap check1;
		CMovingBitmap check2;
		CMovingBitmap select_scene1;
		CMovingBitmap select_scene2;
		CMovingBitmap play;
		CMovingBitmap play_bg;
		CMovingBitmap character_logo;
		CMovingBitmap comunicate_logo;
		CMovingBitmap com_bg;		
		CMovingBitmap com_no;

		int show_text = 0;

	};


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState, public CGameStateValueStorage {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作

		void show_baclground_selected();
		void show_text();

		void set_over_data();

		bool isSelect(UINT nFlags, CPoint point, CMovingBitmap &item);

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();		// 顯示這個狀態的遊戲畫面
	private:
		CGamestage0 t0;
		CGamestage1 t1;
		CGamestage2 t2;


		CGamestageSelect select_stage; 
		CGamestageBoss1 b1;
		CGamestageBoss2 b2;
		CGamestageBoss3 b3;

		CMovingBitmap character;
		CMovingBitmap background;
		CMovingBitmap opera;
		CMovingBitmap blood_bar;
		CMovingBitmap energy_bar;
		vector <CMovingBitmap> dart;
		vector<CMovingBitmap> bullet;
		vector<CMovingBitmap> bricks;
		vector<CMovingBitmap> lightning;

		CMovingBitmap timer_express;
		CMovingBitmap dead_logo;
		CMovingBitmap suspend_logo;
		CMovingBitmap not_dead_logo;

		clock_t a, b;
		clock_t suspend_start  = 0, suspend_end = 0;
		int boss_level = 0;
		int level = 0;
		int current_t = 0;
		int pre_boss_t = 0;
		int current_stage = 0;
		int not_dead = 0;

		CMovingBitmap weapon_logo[3] ;

		template<typename T>
		void select_temp(T &t);

		int suspend = 0;

		int weapon_list[4] = { 0,0,0,0 };//s
		string weapon_name[3] = { "Bricks","Guardian","Lightning" };//

	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState, public CGameStateValueStorage {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnMouseMove(UINT nFlags, CPoint point);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		bool isSelect(UINT nFlags, CPoint point, CMovingBitmap &item);
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器

		CMovingBitmap victory;
		CMovingBitmap die;
		CMovingBitmap again;
	};

}