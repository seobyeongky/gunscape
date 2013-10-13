//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_base.h
//
// 내용: 총알을 관리하는 기본 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __Shot_H__
#define  __Shot_H__

#include "coord_def.h"

class Game_Manager;
class Texture;
class Map;
class Unit;

enum SHOT_PRIORITY //위로있을수록 먼저 그려진다.(뒤에있는게 올라감)
{
	STP_SHOT = 0,
	STP_FOG,
	STP_FOG_END,
	STP_TEXT = STP_FOG_END,
	STP_MAX
};

class Shot_base
{
	Texture* texture;


protected:
	int team;
	coord_def pos;
	coord_def speed;
	coord_def first_pos;

	SHOT_PRIORITY priority;

	Unit* unit;

	static Map* map;

	void Move()
	{
		pos+=speed;
	};
	void Move(float x_, float y_)
	{
		pos.x = x_;
		pos.y = y_;
	}
	bool collution(int radius_);
	bool collutionAngle(int radius_, float& return_); //bool collution(int radius_);와 같은 충돌처리를 한다. 대신 충돌위치와의 각도를 리턴한다.(가장 가까운 충돌위치) 
	int pre_collution(int step_); //이동될 곳에 미리 충돌처리하기(거리를 리턴). 인자는 충돌처리 최소단위
	int unit_collution(coord_def pos_, float radius_); //pos에 있는 radius크기의 유닛과 충돌처리. 맞을 거리를 리턴
public:
	/*Shot_base();*/
	Shot_base(Texture* texture_, Unit* unit_, int team_, coord_def pos_, coord_def speed_, SHOT_PRIORITY priority_ = STP_SHOT);
	virtual ~Shot_base();
	virtual bool Action(Game_Manager* gm_) = 0;
	virtual bool Draw(coord_def offset_, float size_) = 0;

	virtual bool isHouse(){return false;};

	Texture* GetTexture(){return texture;};
	virtual char* GetName(){return "기본총알";};
	int GetTeam(){return team;};
	coord_def GetPos(){return pos;};
	float GetX(){return pos.x;};
	float GetY(){return pos.y;};
	void SetPos(const coord_def& pos_){pos = pos_;};
	coord_def GetSpeed(){return speed;};
	coord_def GetFirstPos(){return first_pos;};
	SHOT_PRIORITY GetPriority(){return priority;};

	
	
	void SetSpeed(const coord_def& c){speed = c;};
	
	void ApplySpeedX(float ratio_){speed.x*=ratio_;};
	void ApplySpeedY(float ratio_){speed.y*=ratio_;};

	void UpDownSpeed(const coord_def& c){speed+=c;};

	bool TargetLost();
	virtual bool TargetLost_in(){return false;};

	static void SetMap(Map* map_); //이것을 해줘야 총알이 충돌처리를 한다.

	virtual bool Bomb(Game_Manager* gm_, float power_, float max_power_, float damage_, float range_, bool selfbomb_ = true, bool noise_ = true);

	virtual bool HouseCollution(const coord_def& c){return false;};
};

#endif // __Shot_H__

