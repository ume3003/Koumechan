//
//  PuzzleTMXTiledMap.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/02.
//
//

#ifndef __koumeChan__PuzzleTMXTiledMap__
#define __koumeChan__PuzzleTMXTiledMap__

#include "KCDef.h"
#include "cocos2d.h"

class PuzzleTMXTiledMap : public cocos2d::TMXTiledMap
{
public:
	enum MAP_POS {
		LEFT_SIDE ,
		RIGHT_SIDE,
		TOP_SIDE,
		BOTTOM_SIDE
	};
	
	enum TAGS {
		TAG_FRAME = 50,
		TAG_SHADOW_START = 10000,
	};
	
	
	void addSpriteBatchNode(int i,cocos2d::SpriteBatchNode* node);
	cocos2d::SpriteBatchNode* getSpriteBatchNode(int i)	{ return m_spriteBatchNode.at(i);};
	void setSpriteBatchNode(int i,cocos2d::SpriteBatchNode* node)	{m_spriteBatchNode.insert(i,node);};
	void clearSpriteBatchNode();
	virtual bool loadSpriteBatchNode() = 0;

	void addMapChild(int baseNo,cocos2d::Node* node,int zOrder,int tag);
	cocos2d::Node* getMapChildByTag(int baseNo,int tag);
	
	float getMapWidth()		{ return getMapSize().width; };
	float getMapHeight()	{ return getMapSize().height;};
	float getCelWidth()		{ return getContentSize().width / getMapWidth();};
	float getCelHeight()	{ return getContentSize().height / getMapHeight(); } ;

	bool isMovableCell(cocos2d::Point mapPos);
	bool isSupplyCell(cocos2d::Point mapPos);
	cocos2d::Point convertMapToPos(cocos2d::Point mapPos);
	cocos2d::Point convertPosToMap(cocos2d::Point pos);
	cocos2d::Point getCenterPos(cocos2d::Point mapPos);
	cocos2d::Point getNeighborPoint(cocos2d::Point mapPos,bool bTop,int diff);
	
	int getSupplyCell(int index)				{return m_supplyCells.at(index);	};
	cocos2d::Point getSupplyCellPos(int index)	{ return idxToPos(getSupplyCell(index));	};
	long getSupplyCellCount()	{ return m_supplyCells.size();};
	
	virtual long findUnitNoFromRate(long rate) = 0;
	cocos2d::Point getMapPoint(MAP_POS pos)	{return m_mapPos[pos];};

	void clearShadowCell();
	void addShadowCell(int idx);
	cocos2d::Node* getFrameNode();
	DIRECT getDirectionFromUnit(cocos2d::Point pos);
	cocos2d::Size getAvailableSize()		{return cocos2d::Size(getMaxX() - getMinX()+ 1,getMaxY() - getMinY() + 1);};
	
protected:
	PuzzleTMXTiledMap();
	virtual ~PuzzleTMXTiledMap();
	virtual bool init();
	
	cocos2d::TMXLayer* getBaseLayer()		{ return getLayer(NAME_BASE_LAYER);};
	cocos2d::Map<int,cocos2d::SpriteBatchNode*> m_spriteBatchNode;
	
	std::map<MAP_POS,cocos2d::Point> m_mapPos;
	int getCellProperty(cocos2d::Point mapPos);
	CC_SYNTHESIZE(int, m_minX, MinX);
	CC_SYNTHESIZE(int, m_maxX, MaxX);
	CC_SYNTHESIZE(int, m_minY, MinY);
	CC_SYNTHESIZE(int, m_maxY, MaxY);
	CC_SYNTHESIZE(std::vector<int> ,m_shadowCells,ShadowCells);
	CC_SYNTHESIZE(std::vector<int> ,m_supplyCells,SupplyCells);
	CC_SYNTHESIZE(std::vector<long>,m_appearances,Appearances);
	CC_SYNTHESIZE(long,m_appearanceRate,AppearanceRate);
	CC_SYNTHESIZE(long,m_mapNo,MapNo);

};

#endif /* defined(__koumeChan__PuzzleTMXTiledMap__) */
