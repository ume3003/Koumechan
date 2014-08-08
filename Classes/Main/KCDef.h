//
//  KCDef.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/11.
//
//

#ifndef koumeChan_KCDef_h
#define koumeChan_KCDef_h

#include "cocos2d.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define TARGET_URL	"http://localhost:9000"
//#define TARGET_URL	"http://dev02.tomoeto.com:9000"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define TARGET_URL	"http://192.168.0.4:9000"
//#define TARGET_URL	"http://dev02.tomoeto.com:9000"
#endif

//#define SOCKETIO_URL "ws://192.168.0.4:3000"
#define SOCKETIO_URL "ws://dev02.tomoeto.com:3000"
#define JSON_HEADER	"Content-type:application/json"
#define DB_FILE_NAME "KoumeChan"

#define CREATE_MASTER_TABLE "CREATE TABLE IF NOT EXISTS KCMASTER (id INTEGER PRIMARY KEY AUTOINCREMENT,masterType INTEGER NOT NULL,version INTEGER NOT NULL DEFAULT 0,no INTEGER NOT NULL,row TEXT ) "
#define DELETE_MASTER_TABLE "DROP TABLE KCMASTER"
#define DELETE_MASTER_SQL	 "DELETE FROM KCMASTER WHERE version=%lld AND masterType = %d"
#define DELETE_MASTER_ALL	 "DELETE FROM KCMASTER "
#define SELECT_MASTER_SQL	 "SELECT id,no,version,row FROM KCMASTER WHERE version=%lld AND masterType = %d ORDER BY no"
#define SELECT_MASTER_ROW	"SELECT row FROM KCMASTER WHERE version=%lld and masterType = %d and no=%ld"
#define UPDATE_MASTER_ROW	"UPDATE KCMASTER SET row = '%s' WHERE version=%lld and masterType=%d and no=%ld"
#define INSERT_MASTER_ROW   "INSERT INTO KCMASTER (version,masterType,no,row) values ( %lld,%d,%ld,'%s')"

////////////////////////////////////////
//	Font file Definision
////////////////////////////////////////
#define WHITE_FONT "font/whiteFont.fnt"
#define GRAY_FONT "font/grayFont.fnt"
#define RED_FONT "font/redFont.fnt"

//////////////////////////////////
//	for FORCE
//////////////////////////////////
#define NEUTRAL	0

#define STARTPOWER 30
#define POWER 100
#define MAXPOWER 300

#define LBLEVEL1 50
#define LBLEVEL2 150
#define LBLEVLE3 300
//////////////////////////////////
//	Direction
/////////////////////////////////
enum DIRECT {
	NORTH =0,
	EAST,
	WEST,
	SOUTH,
	CENTER	
};
//////////////////////////////////
//	for scale
///////////////////////////////////
#define SCALE_ZERO 0.0f
#define SCALE_NORMAL 1.0f
#define SCALE_SUPER 1.5f
////////////////////////////////////////////
//	For CCB LAYER
////////////////////////////////////////////
#define START_LAYER_CLASS	"StartLayer"
#define START_LAYER_FILE	"published/layers/StartLayer.ccbi"

#define MAIN_UILAYER_CLASS	"MainUILayer"
#define MAIN_UILAYER_FILE		"published/layers/MainUI.ccbi"

#define MAJOR_QUESTLAYER_CLASS	"MajorQuestLayer"
#define MAJOR_QUESTLAYER_FILE	"published/layers/MajorQuest.ccbi"

#define MINOR_QUESTLAYER_CLASS	"MinorQuestLayer"
#define MINOR_QUESTLAYER_FILE	"published/layers/MinorQuest.ccbi"

#define FRIEND_MATCHLAYER_CLASS	"FriendMatchLayer"
#define FRIEND_MATCHLAYER_FILE	"published/layers/FriendMatch.ccbi"


#define PUZZLE_UILAYER_CLASS	"PuzzleUILayer"
#define PUZZLE_UILAYER_FILE		"published/layers/PuzzleUI.ccbi"

#define PUZZLE_MAPLAYER_CLASS	"PuzzleMapLayer"
#define PUZZLE_MAPLAYER_FILE	"published/layers/PuzzleMap.ccbi"


#define YNDLG_LAYER_CLASS	"YNDlg"
#define YNDLG_LAYER_FILE	"published/layers/YNDlg.ccbi"

#define CONNECTINFODLG_LAYER_CLASS	"ConnectInfoDlg"
#define CONNECTINFODLG_LAYER_FILE	"published/layers/ConnectDlg.ccbi"

#define BASE_CELL "published/Nodes/BaseCell.ccbi"
#define QUEST_CELL "published/Nodes/QuestCell.ccbi"

///////////////////////////////////////////
//	for MAP LAYER
///////////////////////////////////////////
#define NAME_BASE_LAYER		"baseLayer"

#define BTN_PNG "btnImage"
#define BTN00_PNG "btnImage00.png"
#define BTN01_PNG "btnImage01.png"
#define BTN02_PNG "btnImage02.png"
#define BTN03_PNG "btnImage03.png"
#define BTN04_PNG "btnImage04.png"
#define BTN05_PNG "btnImage05.png"
#define BTN06_PNG "btnImage06.png"
#define BTN07_PNG "btnImage07.png"

///////////////////////////////////////
//	UI Def
////////////////////////////////////////
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define DLG_FONT	"07YasashisaGothicBold"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define DLG_FONT "fonts/yasashisa-gothic.ttf"
#endif

#define DLG_LARGE_FONT_SIZE 24
#define DLG_MIDDLE_FONT_SIZE 20
#define STR_LEFT "left"
#define STR_RIGHT "right"

#define MODAL_TAG_NO	90
////////////////////////////////////////
//	MACRO Definision
////////////////////////////////////////
#define ccsf(...) cocos2d::String::createWithFormat(__VA_ARGS__)->getCString()
#define csf(_X_) cocos2d::String::createWithFormat("%s",(const char*)(_X_))

#define jsStr(_X_,_Y_)		cocos2d::StringUtils::format("\"%s\":\"%s\"",(_X_),(_Y_))
#define jsLong(_X_,_Y_)		cocos2d::StringUtils::format("\"%s\":%ld"	,(_X_),(_Y_))
#define jsLLong(_X_,_Y_)	cocos2d::StringUtils::format("\"%s\":%lld"	,(_X_),(_Y_))
#define jsInt(_X_,_Y_)		cocos2d::StringUtils::format("\"%s\":%d"	,(_X_),(_Y_))
#define jsObj(_X_,_Y_)		cocos2d::StringUtils::format("\"%s\":{%s}"	,(_X_),(_Y_))
#define jsFloat(_X_,_Y_)	cocos2d::StringUtils::format("\"%s\":%3.2f"	,(_X_),(_Y_))

#define V2C(_X_)		(_X_).asString().c_str()
#define LOGPOS(_X_)		cocos2d::StringUtils::format("%3.2f/%3.2f",(_X_).x,(_X_).y).c_str()
#define LOGSIZE(_X_)	cocos2d::StringUtils::format("%3.2f/%3.2f",(_X_).width,(_X_).height).c_str()


inline int xyToIdx(cocos2d::Point pos) { return pos.x * 100 + pos.y;};
inline int xyToIdx(int x,int y)	{return x * 100 + y;};
inline cocos2d::Point idxToPos(int idx)	{return cocos2d::Point(idx / 100 ,idx % 100);};
inline int idxToX(int idx) { return idx / 100; };
inline int idxToY(int idx) { return idx % 100; };
inline int idxToCandidate(int idx,int rank) { return 10000 * rank + idx;};
inline int candidateRank(int candidate)		{ return candidate / 10000;};
inline int candidateIdx(int candidate)		{ return candidate % 10000;};
inline int vhCandidate(int candidate,bool b) { return candidate * 10 + b;};
inline bool candidateVH(int candidate)	{ return (bool)(candidate % 10);};
inline int candidateInt(int candidate)		{ return candidate / 10;};
#endif
