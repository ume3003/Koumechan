//
//  LocalDatabase.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/18.
//
//

#ifndef __koumeChan__LocalDatabase__
#define __koumeChan__LocalDatabase__

#include "cocos2d.h"
#include "sqlite3.h"

class LocalDatabase
{
public:
	static LocalDatabase* getInstance();
	int openDatabase(sqlite3 ** db);
	bool executeSQL(std::string sql);
	bool init();
	bool clearAllMaster();
protected:
	static LocalDatabase* m_Singleton;
	LocalDatabase() {};
	virtual ~LocalDatabase() {};
};

#endif /* defined(__koumeChan__LocalDatabase__) */
