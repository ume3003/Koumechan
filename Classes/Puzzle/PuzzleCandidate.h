//
//  PuzzleCandidate.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//

#ifndef __Koumechan__PuzzleCandidate__
#define __Koumechan__PuzzleCandidate__

#include "cocos2d.h"

class PuzzleCandidate : public cocos2d::Ref
{
public:
	static PuzzleCandidate* create(int idx,int rank,bool bTop,long forceNo);
	CC_SYNTHESIZE(int ,m_posIdx, Idx);
	CC_SYNTHESIZE(bool,m_top,Top);
	CC_SYNTHESIZE(int ,m_rank,Rank);
	CC_SYNTHESIZE(long ,m_forceNo,ForceNo);
protected:
	PuzzleCandidate();
	~PuzzleCandidate();
	virtual bool init(int idx,int rank,bool bTop,long forceNo);
};

#endif /* defined(__Koumechan__PuzzleCandidate__) */
