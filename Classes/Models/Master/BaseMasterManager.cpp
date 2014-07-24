//
//  BaseMasterManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#include "BaseMasterManager.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "KCDef.h"
#include "sqlite3.h"
#include "LocalDatabase.h"

using namespace cocos2d;
using namespace std;

BaseMasterManager::BaseMasterManager()
{
	
};

BaseMasterManager::~BaseMasterManager()
{
	m_data.clear();
};
bool BaseMasterManager::init(long version)
{
	setVersion(version);
	return loadFromLocal();
}

string BaseMasterManager::toJsonString()
{
	string str = string("[");
	Map<long,BaseMaster*>::iterator it = m_data.begin();
	while(it != m_data.end()){
		BaseMaster* master = (BaseMaster*)(*it).second;
		str.append(master->toJsonString());
		++it;
		if(it != m_data.end()){
			str.append(",");
		}
	}
	str.append("]");
	return str;
};
BaseMaster* BaseMasterManager::getMaster(long no)
{
	if(m_data.find(no) != m_data.end()){
		return m_data.at(no);
	}
	return NULL;
}
void BaseMasterManager::setMaster(BaseMaster *master)
{
	if(master != NULL){
		m_data.insert(master->getMasterNo(), master);
	}
}
bool BaseMasterManager::loadFromLocal()
{
	LocalDatabase* db = LocalDatabase::getInstance();
	sqlite3 *sqlite = NULL;
	if(db->openDatabase(&sqlite) == SQLITE_OK){
		string strSQL = StringUtils::format(SELECT_MASTER_SQL,getVersion(),getTableNo());
		sqlite3_stmt* stmt = NULL;
		if(sqlite3_prepare_v2(sqlite, strSQL.c_str(), -1, &stmt, NULL) == SQLITE_OK){
			clearData();
			while(sqlite3_step(stmt) == SQLITE_ROW){
				const char* row = (const char*)sqlite3_column_text(stmt, 3);
				Json* json = Json_create(row);
				if(json){
					BaseMaster* master = createMaster(json);
					setMaster(master);
					Json_dispose(json);
				}
				else{
					log("error %s",row);
				}
			}
			sqlite3_reset(stmt);
		}
		sqlite3_finalize(stmt);
	}
	sqlite3_close(sqlite);
	return true;
};

void BaseMasterManager::registerToParentAll()
{
	for(long i = 0; i < size();i++){
		BaseMaster* master = getMaster(i);
		if(master){
			master->registerToParent();
		}
	}
};

void BaseMasterManager::clearChildData(BaseMaster::MASTERNO masterNo)
{
	for(long i = 0; i < size();i++){
		BaseMaster* master = getMaster(i);
		if(master){
			master->clearChild(masterNo);
		}
	}
}

void BaseMasterManager::clearData()
{
	m_data.clear();
}

void BaseMasterManager::saveDataToLocal()
{
	LocalDatabase* kb = LocalDatabase::getInstance();
	sqlite3 *db = NULL;
	if(kb->openDatabase(&db) == SQLITE_OK){
			sqlite3_stmt* stmt = NULL;
		for(long i = 0; i < size();i++){
			BaseMaster* master = getMaster(i);
			if(master){
				string strSQL = StringUtils::format(SELECT_MASTER_ROW,getVersion(),getTableNo(),i);
				if(sqlite3_prepare_v2(db, strSQL.c_str(), -1, &stmt, NULL) == SQLITE_OK){
					string strUpsert;
					if(sqlite3_step(stmt) == SQLITE_ROW){
						strUpsert = StringUtils::format(UPDATE_MASTER_ROW,master->toJsonString().c_str(),getVersion(),getTableNo(),master->getMasterNo());
					}
					else{
						strUpsert = StringUtils::format
						(INSERT_MASTER_ROW,getVersion(),getTableNo(),master->getMasterNo(),
						 master->toJsonString().c_str());
					}
					if(strUpsert.length() > 0){
//						log("sql:%s",strUpsert.c_str());
						kb->executeSQL(strUpsert);
					}
					sqlite3_reset(stmt);
				}
				sqlite3_finalize(stmt);
			}
		}
	}
	sqlite3_close(db);
	
};

bool BaseMasterManager::loadFromServer(Json *json)
{
	if(json != NULL){
		Json* row = NULL;
		int i = 0;
		clearData();
		for (row = json->child,i = 0; row ; row = row->next, ++i) {
			BaseMaster* master = createMaster(row);
			setMaster(master);
		}
		saveDataToLocal();
		registerToParentAll();
		return true;
	}
	return false;
};

bool BaseMasterManager::isServerVersionNew(Json *json)
{
	long serverVersion = KoumeChan::getLLong(json,JS_VERSION,0);
	return serverVersion > getVersion();
};

void BaseMasterManager::deleteLocalData()
{
	LocalDatabase* kb = LocalDatabase::getInstance();
	string sql = StringUtils::format(DELETE_MASTER_SQL,getVersion(),getTableNo());
	kb->executeSQL(sql.c_str());
};
