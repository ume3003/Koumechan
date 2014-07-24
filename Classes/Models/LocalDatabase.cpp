//
//  LocalDatabase.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/18.
//
//

#include "LocalDatabase.h"
#include "KCDef.h"

using namespace cocos2d;
using namespace std;

LocalDatabase* LocalDatabase::m_Singleton = NULL;

LocalDatabase* LocalDatabase::getInstance()
{
	if(NULL == m_Singleton){
		m_Singleton = new LocalDatabase();
	}
	return m_Singleton;
}

int LocalDatabase::openDatabase(sqlite3 ** db)
{
	std::string strPath = FileUtils::getInstance()->getWritablePath();
	strPath.append(DB_FILE_NAME);
	return sqlite3_open(strPath.c_str(), db);

}
bool LocalDatabase::clearAllMaster()
{
	return executeSQL(DELETE_MASTER_ALL);
};

bool LocalDatabase::executeSQL(string strSQL)
{
	sqlite3 *db = NULL;
	bool bSuccess = false;
	if(openDatabase(&db) == SQLITE_OK){
		sqlite3_stmt* stmt = NULL;
		if(sqlite3_prepare_v2(db, strSQL.c_str(), -1, &stmt, NULL) == SQLITE_OK){
			if(sqlite3_step(stmt) == SQLITE_DONE){
				bSuccess = true;
			}
			sqlite3_reset(stmt);
		}
		sqlite3_finalize(stmt);
	}
	sqlite3_close(db);
	return bSuccess;
};

bool LocalDatabase::init()
{
	executeSQL(CREATE_MASTER_TABLE);
	return true;
}