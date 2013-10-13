//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_alert_robot.h
//
// 내용: 경보로봇
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_ALERT_ROBOT_H__
#define  __MON_ALERT_ROBOT_H__


#include "monster.h"


class Mon_alert_robot: public Monster
{
	float search_angle;
	int count;
public:
	Mon_alert_robot(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_alert_robot();
	
	virtual bool charDraw(Game_Manager* gm_, coord_def offset, float size_);
		
	virtual bool Special_Action(Game_Manager* gm_);

	virtual bool GetSearchAngle(float& angle_){angle_ = search_angle;return true;};

	virtual float GetSearchRate(){return 3.0f;};

	virtual bool CanSpeeing(){return false;};	
};

#endif // __MON_ALERT_ROBOT_H__