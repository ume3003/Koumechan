//
//  PuzzleTMXTiledMap.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/02.
//
//
#include "KoumeChan.h"
#include "MasterMap.h"
#include "QuestUnit.h"
#include "MasterUnit.h"
#include "PuzzleTMXTiledMap.h"
using namespace cocos2d;
using namespace std;

PuzzleTMXTiledMap::PuzzleTMXTiledMap()
{
	setMinX(0);
	setMaxX(0);
	setMinY(0);
	setMaxY(0);
	
}

PuzzleTMXTiledMap::~PuzzleTMXTiledMap()
{
	clearSpriteBatchNode();
	m_supplyCells.clear();
	m_shadowCells.clear();
}



bool PuzzleTMXTiledMap::init()
{
	if(TMXTiledMap::init()){
		KoumeChan* chan = KoumeChan::getInstance();
		MasterMap* map = chan->getMapMaster(getMapNo());
		if(map){
			std::string mapFileName = map->getImage().asString();
			if(mapFileName.length() > 0){
				if(initWithTMXFile(mapFileName)){
					setMinX(getMapWidth());
					setMaxX(0);
					setMinY(getMapHeight());
					setMaxY(0);
					for(int x = 0; x < getMapWidth();x++){
						for(int y = 0 ; y < getMapHeight();y++){
							if(isSupplyCell(Point(x,y))){
								m_supplyCells.push_back(xyToIdx(x, y));
							}
							if(isMovableCell(Point(x,y))){
								setMinX(MIN(getMinX(),x));
								setMaxX(MAX(getMaxX(),x));
								setMinY(MIN(getMinY(),y));
								setMaxY(MAX(getMaxY(),y));
							}
						}
					}
					m_mapPos[LEFT_SIDE]		= getCenterPos(Point(-1,getMapHeight() / 2));
					m_mapPos[RIGHT_SIDE]	= getCenterPos(Point(getMapWidth(),getMapHeight() / 2));
					m_mapPos[TOP_SIDE]		= getCenterPos(Point(getMapWidth() / 2,getMapHeight()));
					m_mapPos[BOTTOM_SIDE]	= getCenterPos(Point(getMapWidth() / 2,-1));
					return true;
				}
			}
		}
	}

	return false;
};

bool PuzzleTMXTiledMap::isMovableCell(Point mapPos)
{
	if(mapPos.x >= 0 && mapPos.y >= 0){
		int iPr = getCellProperty(mapPos);
		return iPr % 100 == 1;
	}
	return false;
};
bool PuzzleTMXTiledMap::isSupplyCell(cocos2d::Point mapPos)
{
	int ip = int(getCellProperty(mapPos) / 100);
	return ip == 1;
}

int PuzzleTMXTiledMap::getCellProperty(cocos2d::Point mapPos)
{
	TMXLayer* pLayer = getBaseLayer();
	Point tilePos = Point(mapPos.x, getMapSize().height - mapPos.y -1);
	if(pLayer != NULL && tilePos.x < getCelWidth() && tilePos.y < getCelHeight() && tilePos.y >= 0){
		int iGID = pLayer->getTileGIDAt(tilePos);
		if(iGID != 0){
			Value pDic = getPropertiesForGID(iGID);
			ValueMap& map = pDic.asValueMap();
			return map["Attr"].asInt();
		}
	}
	return -1;
};

Point PuzzleTMXTiledMap::convertMapToPos(cocos2d::Point mapPos)
{
	return Point(mapPos.x * getCelWidth(),mapPos.y * getCelHeight());
};

Point PuzzleTMXTiledMap::convertPosToMap(cocos2d::Point pos)
{
	return Point((int)(pos.x / getCelWidth()),(int)(pos.y / getCelHeight()));
};

Point PuzzleTMXTiledMap::getCenterPos(cocos2d::Point mapPos)
{
	return Point(mapPos.x * getCelWidth() + getCelWidth() / 2, mapPos.y * getCelHeight() + getCelHeight() / 2);
};

Point PuzzleTMXTiledMap::getNeighborPoint(Point mapPos,bool bTop,int diff)
{
	return bTop ? Point(mapPos.x,mapPos.y + diff) : Point(mapPos.x + diff,mapPos.y);
};
///////////////////////////////////////////////////////////////////////////////
//	SpriteBatchNode
///////////////////////////////////////////////////////////////////////////////
void PuzzleTMXTiledMap::addSpriteBatchNode(int i, SpriteBatchNode *node)
{
	setSpriteBatchNode(i, node);
	addChild(node, i + 50, i + 100);
};

void PuzzleTMXTiledMap::addMapChild(int baseNo,Node* node,int zOrder,int tag)
{
	addChild(node,zOrder,tag);
	/*
	SpriteBatchNode* batchNode = getSpriteBatchNode(baseNo);
	CCASSERT(batchNode, StringUtils::format("%d spriteBatchNode is null",baseNo).c_str());
	if(batchNode){
		batchNode->addChild(node, zOrder, tag);
	}
	 */
};
Node* PuzzleTMXTiledMap::getMapChildByTag(int baseNo,int tag)
{
	return getChildByTag(tag);
	/*
	SpriteBatchNode* batchNode = getSpriteBatchNode(baseNo);
	CCASSERT(batchNode, StringUtils::format("%d spriteBatchNode is null",baseNo).c_str());
	if(batchNode){
		return batchNode->getChildByTag(tag);
	}
	return NULL;
	 */
};

void PuzzleTMXTiledMap::clearSpriteBatchNode()
{
	removeAllChildrenWithCleanup(true);
	/*
	Map<int,SpriteBatchNode*>::iterator it = m_spriteBatchNode.begin();
	while(it != m_spriteBatchNode.end())
	{
		SpriteBatchNode* node = (SpriteBatchNode*)(*it).second;
		node->removeAllChildrenWithCleanup(true);
		++it;
	}
	 */
};



void PuzzleTMXTiledMap::clearShadowCell()
{
	for(int i = 0;i < m_shadowCells.size();i++){
		int idx = m_shadowCells.at(i);
		Sprite* sp = (Sprite*)getChildByTag(idx + TAG_SHADOW_START);
		if(sp){
			sp->stopAllActions();
			sp->removeFromParentAndCleanup(true);
		}
	}
	m_shadowCells.clear();
}

void PuzzleTMXTiledMap::addShadowCell(int idx)
{
	Point pos = getCenterPos(idxToPos(idx));
	Sprite* sp = Sprite::createWithSpriteFrameName("shadow.png");
	sp->setVisible(true);
	sp->setAnchorPoint(Point(0.5,0.5));
	sp->setPosition(pos);
	sp->setContentSize(Size(getCelWidth(),getCelHeight()));
	addChild(sp, 99,idx + TAG_SHADOW_START);
	m_shadowCells.push_back(idx);
}

Node* PuzzleTMXTiledMap::getFrameNode()
{
	return getChildByTag(TAG_FRAME);
}

DIRECT PuzzleTMXTiledMap::getDirectionFromUnit(Point pos)
{
	Size s = getAvailableSize();
	int mx = s.width / 2;
	int my = s.height / 2;
	int px = pos.x - getMinX();
	int py = pos.y - getMinY();
	
	if(mx > px){
		if(my > py){
			if(s.width - px > s.height - py || px == 0){
				return EAST;
			}
			return NORTH;
		}
		else{
			if(s.width - px > py || px == 0){
				return EAST;
			}
			return SOUTH;
		}
	}
	else{
		if(my > py){
			if(px > s.height - py || px == s.width){
				return WEST;
			}
			return NORTH;
		}
		else{
			if(px > py || px == s.width){
				return WEST;
			}
			return SOUTH;
		}
	}
	return NORTH;
}


