//
//  BaseMasterManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#ifndef __koumeChan__BaseMasterManager__
#define __koumeChan__BaseMasterManager__

#include "cocos2d.h"
#include "BaseMaster.h"

class BaseMasterManager : public cocos2d::Ref
{
protected:
	BaseMasterManager();
	virtual ~BaseMasterManager();
	virtual bool init(long version);
	
	CC_SYNTHESIZE(long long, m_Version, Version);
	cocos2d::Map<long,BaseMaster*> m_data;
	std::string toJsonString();
	virtual void clearData();
public:
	BaseMaster* getMaster(long no);
	void setMaster(BaseMaster* master);
	long size()	{return m_data.size();};
	virtual std::string getTableName() = 0;
	virtual BaseMaster* createMaster(Json* json) = 0;
	virtual int getTableNo() = 0;
	bool loadFromLocal();
	bool loadFromServer(Json* json);
	void saveDataToLocal();
	bool isServerVersionNew(Json* json);
	void deleteLocalData();
	
	void registerToParentAll();
	
	void clearChildData(BaseMaster::MASTERNO masterNo);
};

#endif /* defined(__koumeChan__BaseMasterManager__) */
