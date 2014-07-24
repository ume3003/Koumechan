//
//  PuzzleScore.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/18.
//
//

#ifndef __Koumechan__PuzzleScore__
#define __Koumechan__PuzzleScore__

#include "cocos2d.h"

class PuzzleScore : public cocos2d::Ref
{
public:
//	static PuzzleScore* getInstance();
	
	enum SCORE_TYPE {
		THREE_OWN = 0,
		THREE_NEUTRAL,
		THREE_ENEMY,
		FOUR_OWN,
		FOUR_NEUTRAL,
		FOUR_ENEMY,
		BORN_OWN,
		BORN_NEUTRAL,
		BORN_ENEMY,
		FIVE_OWN,
		FIVE_NEUTRAL,
		FIVE_ENEMY,
		RAIL_OWN
	};
	
	long getPlayer1Power(SCORE_TYPE type);
	long getPlayer2Power(SCORE_TYPE type);
	long getPlayer1Score(SCORE_TYPE type);
	long getPlayer2Score(SCORE_TYPE type);
	
	
protected:
	PuzzleScore();
	virtual ~PuzzleScore();
	
	static PuzzleScore* m_instance;
	static const long m_Player1Power[];
	static const long m_Player2Power[];
	static const long m_Player1Score[];
	static const long m_Player2Score[];
	
};


#endif /* defined(__Koumechan__PuzzleScore__) */
