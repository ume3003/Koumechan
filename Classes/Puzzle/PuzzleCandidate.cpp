//
//  PuzzleCandidate.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//

#include "PuzzleCandidate.h"


using namespace cocos2d;
using namespace std;

PuzzleCandidate* PuzzleCandidate::create(int idx, int rank, bool bTop, long force)
{
	PuzzleCandidate* pRet = new PuzzleCandidate();
	if(pRet && pRet->init(idx, rank, bTop, force)){
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet = NULL;
	return pRet;
};

PuzzleCandidate::PuzzleCandidate()
{
	
}
PuzzleCandidate::~PuzzleCandidate()
{
	
}

bool PuzzleCandidate::init(int idx, int rank, bool bTop, long force)
{
	setIdx(idx);
	setRank(rank);
	setTop(bTop);
	setForceNo(force);
	return true;
};
