//
//  CompetitionTMXMap.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//

#ifndef __Koumechan__CompetitionTMXMap__
#define __Koumechan__CompetitionTMXMap__

#include "cocos2d.h"
#include "PuzzleTMXTiledMap.h"

class CompetitionTMXMap : public PuzzleTMXTiledMap
{
public:
	static CompetitionTMXMap* create();
	virtual bool loadSpriteBatchNode();
	virtual long findUnitNoFromRate(long rate);
	int findUnitOrderFromRate(long rate);

protected:
	virtual bool init();
	
};

#endif /* defined(__Koumechan__CompetitionTMXMap__) */
