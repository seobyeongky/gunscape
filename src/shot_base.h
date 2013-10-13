//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: Shot_base.h
//
// ����: �Ѿ��� �����ϴ� �⺻ Ŭ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __Shot_H__
#define  __Shot_H__

#include "coord_def.h"

class Game_Manager;
class Texture;
class Map;
class Unit;

enum SHOT_PRIORITY //������������ ���� �׷�����.(�ڿ��ִ°� �ö�)
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
	bool collutionAngle(int radius_, float& return_); //bool collution(int radius_);�� ���� �浹ó���� �Ѵ�. ��� �浹��ġ���� ������ �����Ѵ�.(���� ����� �浹��ġ) 
	int pre_collution(int step_); //�̵��� ���� �̸� �浹ó���ϱ�(�Ÿ��� ����). ���ڴ� �浹ó�� �ּҴ���
	int unit_collution(coord_def pos_, float radius_); //pos�� �ִ� radiusũ���� ���ְ� �浹ó��. ���� �Ÿ��� ����
public:
	/*Shot_base();*/
	Shot_base(Texture* texture_, Unit* unit_, int team_, coord_def pos_, coord_def speed_, SHOT_PRIORITY priority_ = STP_SHOT);
	virtual ~Shot_base();
	virtual bool Action(Game_Manager* gm_) = 0;
	virtual bool Draw(coord_def offset_, float size_) = 0;

	virtual bool isHouse(){return false;};

	Texture* GetTexture(){return texture;};
	virtual char* GetName(){return "�⺻�Ѿ�";};
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

	static void SetMap(Map* map_); //�̰��� ����� �Ѿ��� �浹ó���� �Ѵ�.

	virtual bool Bomb(Game_Manager* gm_, float power_, float max_power_, float damage_, float range_, bool selfbomb_ = true, bool noise_ = true);

	virtual bool HouseCollution(const coord_def& c){return false;};
};

#endif // __Shot_H__

