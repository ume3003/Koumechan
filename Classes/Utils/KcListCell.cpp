//
//  KcListCell.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/20.
//
//

#include "KcListCell.h"
#include "cocosbuilder/cocosbuilder.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
using namespace cocosbuilder;

KcListCell::KcListCell() : m_coverSprite(NULL),m_nameSprite(NULL),m_nameLabelTTF(NULL),m_node(NULL)
{
	
}

KcListCell::~KcListCell()
{
	if(m_node){
		if(m_nameSprite){
			m_node->removeChild(m_nameSprite);
			CC_SAFE_RELEASE(m_nameSprite);
		}
		if(m_coverSprite){
			m_node->removeChild(m_coverSprite);
			CC_SAFE_RELEASE(m_coverSprite);
		}
		if(m_nameLabelTTF){
			m_node->removeChild(m_nameLabelTTF);
			CC_SAFE_RELEASE(m_nameLabelTTF);
		}
		CC_SAFE_RELEASE(m_node);
	}
};

KcListCell* KcListCell::create(long id,Value name,Value nameImage, Size size)
{
	KcListCell* pRet = new KcListCell();
	if(pRet && pRet->init(id, name, nameImage, size)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool KcListCell::init(long id, Value name, Value nameImage, Size size)
{
	setId(id);
	setName(name);
	setNameImage(nameImage);
	setCellHeight(size.height);
	setCellWidth(size.width);
	
	if(TableViewCell::init()){
		Node* node = NULL;
		NodeLoaderLibrary* library = NodeLoaderLibrary::getInstance();
		CCBReader* reader = new CCBReader(library);
		reader->autorelease();
		node = reader->readNodeGraphFromFile(getCCBFileName());
		if(node){
			node->setScale(min(getCellHeight() / node->getContentSize().height,getCellWidth() / node->getContentSize().width));
			node->setPosition(Point(getCellWidth() / 2,getCellHeight() / 2));
			node->setAnchorPoint(Point(0.5f,0.5f));
			addChild(node,KZO_BASE,KTAG_BASE);
			setNode(node);
			if(createNameLabel() && createCoverSprite()){
				return true;
			}
		}
	}
	return false;
	
};

bool KcListCell::createNameLabel()
{
	Node* node = getNode();
	if(node){
		Node* nameNode = node->getChildByTag(KTAG_NAME);
		Size nameSize = nameNode->getContentSize();
		if(nameNode){
			if(getNameImage().asString().length() > 0){
				Sprite* sprite = (Sprite*)nameNode->getChildByTag(CTAG_SPRITE);
				if(!sprite){
					sprite = Sprite::createWithSpriteFrameName(getNameImage().asString());
					nameNode->addChild(sprite, KZO_BASE,CTAG_SPRITE);
				}
				else{
					sprite->setSpriteFrame(getNameImage().asString());
				}
				Size spSize = sprite->getContentSize();
				sprite->setScale(min(nameSize.width / spSize.width ,nameSize.height / spSize.height));
				setNameSprite(sprite);
			}
			setNameLabelTTF((Label*)nameNode->getChildByTag(CTAG_VAL));
			if(getNameLabelTTF()){
				getNameLabelTTF()->setString(getName().asString().c_str());
				return true;
			}
		}
	}
	return false;
}

bool KcListCell::createCoverSprite()
{
	Node* node = getNode();
	Size nodeSize = node->getContentSize();
	if(node && getCoverImage().asString().length() > 0){
		Sprite* sprite = (Sprite*)node->getChildByTag(KTAG_COVER);
		if(!sprite){
			sprite = Sprite::createWithSpriteFrameName(getCoverImage().asString());
			node->addChild(sprite, KZO_COVER, KTAG_COVER);
		}
		else{
			sprite->setSpriteFrame(getCoverImage().asString());
		}
		Size spSize = sprite->getContentSize();
		sprite->setScale(min(nodeSize.width / spSize.width, nodeSize.height / spSize.height));
		setCoverSprite(sprite);
	}
	return true;
}
