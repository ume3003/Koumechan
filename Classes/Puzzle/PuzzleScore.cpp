//
//  PuzzleScore.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/18.
//
//

#include "PuzzleScore.h"

/*
 THREE_OWN = 0	, THREE_NEUTRAL, THREE_ENEMY,
 FOUR_OWN		, FOUR_NEUTRAL , FOUR_ENEMY,
 BORN_OWN		, BORN_NEUTRAL , BORN_ENEMY
 FIVE_OWN		, FIVE_NEUTRAL , FIVE_ENEMY,
*/

const long PuzzleScore::m_Player1Score[] =
{
	 3, 0, 0,
	 6, 0, 0,
	 9, 0, 0,
	12, 0, 0,
	 1
};
const long PuzzleScore::m_Player2Score[] =
{
	 -3, 0,-3,
	 -6, 0,-3,
	 -9, 0,-5,
	-15, 0,-7,
	 -1
};
const long PuzzleScore::m_Player1Power[] =
{
	 5,10, 3,
	 4, 8, 4,
	 6, 8, 6,
	 8,10, 8,
	 0
};
const long PuzzleScore::m_Player2Power[] =
{
	 0, 0, 0,
	 0, 0, 0,
	 0, 0, 0,
	 0, 0, 0,
	 0
};
PuzzleScore* PuzzleScore::m_instance = NULL;

PuzzleScore::PuzzleScore()
{
	
}
PuzzleScore::~PuzzleScore()
{
}
/*
PuzzleScore* PuzzleScore::getInstance()
{
	if(!m_instance){
		m_instance = new PuzzleScore();
	}
	return m_instance;
}
*/
long PuzzleScore::getPlayer1Power(SCORE_TYPE type)
{
	return m_Player1Power[type];
};
long PuzzleScore::getPlayer2Power(SCORE_TYPE type)
{
	return m_Player2Power[type];
};
long PuzzleScore::getPlayer1Score(SCORE_TYPE type)
{
	return m_Player1Score[type];
};
long PuzzleScore::getPlayer2Score(SCORE_TYPE type)
{
	return m_Player2Score[type];
};