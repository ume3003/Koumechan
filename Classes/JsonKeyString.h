//
//  JsonKeyString.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/14.
//
//

#ifndef koumeChan_JsonKeyString_h
#define koumeChan_JsonKeyString_h

#define  JS_NO				 "a001"
#define  JS_NAME			 "a002"
#define  JS_DETAIL			 "a003"
#define  JS_IMAGE			 "a004"
#define  JS_VERSION			 "a005"
#define  JS_APPEARANCE_RATE	 "a006"
#define  JS_KEY_NO			 "a007"
#define  JS_VALUE			 "a008"
#define  JS_KIND			 "a009"
#define  JS_CONDITION_TYPE	 "a010"
#define  JS_PARENT           "a011"
#define  JS_REFERENCE        "a012"
#define  JS_FRIEND           "a013"
#define	 JS_ENEMY_FORCE      "a014"
#define	 JS_HP				 "a015"
#define  JS_LEVEL            "a016"
#define  JS_ATTACK_COUNT     "a017"
#define  JS_EXPERIENCE		 "a018"
#define  JS_WORD			 "a019"
#define  JS_DESCRIPTION		 "a020"
#define  JS_OWN_HITPOINT	 "a021"
#define  JS_OWN_POWER		 "a022"
#define  JS_ENEMY_HITPOINT	 "a023"
#define  JS_ENEMY_POWER		 "a024"


// master keys
#define  JS_DIRECTION         "b001"
#define  JS_MAJOR             "b002"
#define  JS_MINOR             "b003"
#define  JS_MINOR_UNIT        "b004"
#define  JS_MINOR_APPEARANCE  "b005"
#define  JS_MINOR_CLEAR       "b006"
#define  JS_MINOR_REWARD      "b007"
#define  JS_UNIT              "b008"
#define  JS_MAP               "b009"
#define  JS_ITEM              "b010"
#define  JS_SCENARIO          "b011"
#define  JS_SCENARIO_RULE     "b012"
#define  JS_COMPETITION_RULE  "b013"
#define	 JS_CONDITION		  "b014"
#define  JS_SCENARIO_UNIT	  "b015"
#define  JS_CONDITION_KIND    "b016"
#define  JS_RANK              "b017"
#define  JS_CHARACTER_COLUMN  "b018"
#define  JS_SKILL             "b019"
#define  JS_UNIT_SKILL        "b020"
#define  JS_FORCE			  "b021"
#define	 JS_NPC               "b022"
#define  JS_WORDS			  "b023"
#define  JS_NPC_WORDS		  "b024"
#define  JS_BASE_DAMAGE		  "b025"

// json structure Key
#define  JS_DATA              "c001"
#define  JS_SESSION           "c002"
#define  JS_SESSION_ID        "c003"
#define	 JS_ERROR			  "c004"
#define  JS_MASTER_NO		  "c005"
#define	 JS_UNIX_TIME		  "c006"
#define  JS_SUCCESS           "c007"
#define  JS_PARENT_KEY        "c008"
#define  JS_CONDITION_KEY     "c009"
#define  JS_RAMDOM_SEED		  "c010"
#define  JS_ACTION_NO		  "c011"
#define  JS_POSITION		  "c012"
#define  JS_TAG_NO			  "c013"
#define  JS_DURATION		  "c014"
#define	 JS_COLOR             "c015"
#define  JS_FRAME             "c016"
#define  JS_SCORE_TYPE		  "c017"

// db table key
#define  JS_LOGIN             "d001"
#define  JS_GAMECHARACTER     "d002"

// db field key
#define  JS_ID                "d101"
#define  JS_GPP_UUID          "d102"
#define  JS_MAIL_ADDRESS      "d103"
#define  JS_DISPLAY_NAME      "d104"
#define  JS_IMAGE_URL         "d105"
#define  JS_UUID              "d106"
#define  JS_ACCESS_COUNT      "d107"
#define  JS_CREATE_DATE       "d108"
#define  JS_UPDATE_DATE       "d109"

#define  JS_STAMINA           "d110"
#define  JS_MAX_STAMINA       "d111"
#define  JS_MONEY             "d112"
#define  JS_GOLD              "d113"
#define  JS_LAST_COMMAND      "d114"
#define  JS_WIN_LOSE		  "d115"
#define  JS_WIN_CONDITION	  "d116"
#define  JS_TURN			  "d117"
#define  JS_AREA_TYPE		  "d118"

#define  JS_FRIEND_COM        "e001"
#define  JS_FRIEND_INVITE     "e002"
#define  JS_FRIEND_ME		  "e003"
#define  JS_FRIEND_YOU		  "e004"
#define  JS_FRIEND_COM_ID     "roomUUID"
#define  JS_FRIEND_COM_COUNT  "registeredUserCount"
#define  JS_FRIEND_REGISTERED "registered"


#define NR_SOCKET_ID		"socket id"
#define NR_RECEIVE_ROOM		"receiveRoom"
#define NR_LEAVE_ROOM		"leaveRoom"
#define NR_LINK_DOWN		"linkDown"
#define NR_RESUME_GAME		"resumeGame"
#define NR_JOIN_ROOM		"joinRoom"
#define NR_COMPETITOR_JOIN	"competitorJoin"
#define NR_COMPETITOR_BACK	"competitorBack"
#define NR_START_SESSION	"startSession"
#define NR_AUDIT_COUNT		"auditCount"
#define NR_CLOSE_ROOM		"closeRoom"
#define NR_GAME_DATA		"gameData"
#define NR_GAME_RESULT		"gameResult"
#define NR_SYSTEM_MESSAGE	"SystemMessage"
#define NR_GLOBAL			"global"
#define NR_SEED				"seed"
#define NR_READY			"readySession"

#define NS_CONNECT			"connection"             // 接続時
#define NS_DISCONNECT		"disconnect"             // 切断時
#define NS_ADD_USER			"addUser"               // 接続後、ユーザー登録を刷る
#define NS_RECONNECT		"reconnect"              // 再接続
#define NS_SAY_ROOM			"sayRoom"                // ルーム内のデータやりとり
#define NS_LEAVE_ROOM		"leaveRoom"              // 退出
#define NS_GAME_DATA		"gameData"               // 再接続者用のゲームデータ
#define NS_CONFIRM			"confirm"                // 勝利情報の送信
#define NS_FINISH			"finish"                  // 勝利者による勝利条件の送信（開始トリガー
#define NS_GLOBAL			"global"
#define NS_SEED				"seed"
#define NS_READY			"readySession"

#endif
