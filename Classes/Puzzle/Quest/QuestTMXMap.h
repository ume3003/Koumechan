//
//  QuestTMXMap.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//

#ifndef __Koumechan__QuestTMXMap__
#define __Koumechan__QuestTMXMap__

#include "cocos2d.h"
#include "PuzzleTMXTiledMap.h"

class QuestTMPMap : public PuzzleTMXTiledMap
{
public:
	static QuestTMPMap* create();
	virtual bool loadSpriteBatchNode();
	virtual long findUnitNoFromRate(long rate);
	
protected:
	virtual bool init();

};

#endif /* defined(__Koumechan__QuestTMXMap__) */
