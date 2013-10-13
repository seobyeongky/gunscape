//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_base.cpp
//
// 내용: 총알을 관리하는 기본 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "shot_base.h"
#include "image.h"
#include "map.h"
#include "gamemanager.h"
#include "effect_piece.h"
#include "unit.h"

Map* Shot_base::map = NULL;

//
//Shot_base::Shot_base():
//texture(NULL), team(0), pos(), speed()
//{
//
//}

Shot_base::Shot_base(Texture* texture_, Unit* unit_, int team_, coord_def pos_, coord_def speed_, SHOT_PRIORITY priority_):
texture(texture_), team(team_), pos(pos_), speed(speed_), first_pos(pos_), unit(unit_), priority(priority_)
{

}
Shot_base::~Shot_base()
{

}
bool Shot_base::collution(int radius_)
{
	if(!map)
		return false;
	if(!radius_)
	{
		return map->CollutionPos((int)pos.x, (int)pos.y);
	}
	else
	{
		for(int i = -radius_; i<=radius_;i++)
		{
			for(int j = -radius_; j<=radius_;j++)
			{
				if(i*i+j*j<=radius_*radius_)
				{
					if(map->CollutionPos((int)pos.x+i, (int)pos.y+j))
						return true;
				}
			}
		}
		return false;
	}
}
bool Shot_base::collutionAngle(int radius_, float& return_)
{
	if(!map)
		return false;

	bool ok_=false;
	int minimum = radius_*radius_*2;
	coord_def collution_pos;
	if(!radius_)
	{
		return_ = 0;
		return map->CollutionPos((int)pos.x, (int)pos.y);
	}
	else
	{
		for(int i = -radius_; i<=radius_;i++)
		{
			for(int j = -radius_; j<=radius_;j++)
			{
				if(i*i+j*j<=radius_*radius_)
				{
					if(map->CollutionPos((int)pos.x+i, (int)pos.y+j))//충돌한다.
					{
						int temp = i*i+j*j; //중앙과 거리

						if(minimum > temp)
						{
							minimum = temp;
							collution_pos.set((float)i,(float)j);
						}
						ok_ = true;
					}
				}
			}
		}
	}

	if(ok_)
	{
		return_ = GetAngleToTarget(coord_def(), collution_pos);
		return true;
	}
	else
		return false;

}
int Shot_base::pre_collution(int step_)
{	
	if(!map)
		return false;
	float division_ = distan_coord(speed,coord_def())/step_;
	coord_def temp = pos;
	coord_def speed_temp = speed / division_;
	for(int i=0;i<(int)division_;i++)
	{
		temp+=speed_temp;
		if(map->CollutionPos((int)temp.x, (int)temp.y))
			return step_*(i+1);
	}
	return 0;
}
int Shot_base::unit_collution(coord_def pos_, float radius_)
{
	// y = tan*x + b;
	// tan*x - y + b  = 0;
	//l tan*x0-y0+b l /루트(tan^2 +-1^2)  <- 이것이 점과 직선사이 거리
	float tan_ = speed.y / speed.x; //기울기
	float b_ = pos.y - tan_ * pos.x;
	float result_ = abs(tan_*pos_.x-pos_.y+b_)/sqrt(tan_*tan_+1);
	if(result_ <= radius_)
	{
		//cot_ * tan_ = -1
		// cot_*x - y + b1_  = 0; -> pos에서의 법선방정식
		// cot_*x - y + b2_  = 0; -> 한프레임후의 법선방정식
		// cot_*x - y + b3_  = 0; -> 적의 위치의 법선방정식
		//이제 b3_이 b1_이랑 b2_사이에 있으면 된다?
		float cot_ = -1 / tan_;
		float b1_ = pos.y - cot_ * pos.x;
		float b2_ = pos.y+speed.y - cot_ * (pos.x+speed.x);
		float b3_ = pos_.y - cot_ * pos_.x;

		return (b1_ <=  b3_ && b3_ <= b2_) || (b2_ <=  b3_ && b3_ <= b1_);
	}
	return false;
}
bool Shot_base::TargetLost()
{
	TargetLost_in();
	if(unit && !unit->isLive())
	{
		unit = NULL;
		return true;
	}
	return false;
}

void Shot_base::SetMap(Map* map_)
{
	map = map_;
}

bool Shot_base::Bomb(Game_Manager* gm_, float power_, float max_power_, float damage_, float range_, bool selfbomb_, bool noise_)
{
	if(gm_)
	{
		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if((*it)->isLive() && !(*it)->isNonTarget() )
			{
				if(selfbomb_ || (*it)->GetTeam() != GetTeam())
				{
					if((*it)->collution(GetPos(), range_))
					{
						if(!map->CollutionPosToPos(GetPos(), (*it)->GetPos()))
						{
							(*it)->SetKnockback(power_, max_power_, GetAngleToTarget(GetPos(), (*it)->GetPos()));
							int final_damge_ = (*it)->SetDamage(gm_, first_pos, DT_EXPLOSION, damage_, GetTeam());
							if(unit)
								unit->GiveDamage(gm_, (*it), DT_EXPLOSION, final_damge_);
						}
					}
				}
			}
		}
	}
	
	if(noise_)
		gm_->Noise(GetTeam(),GetPos(),80.0f+range_*2.0f);
	Effect_bomb(gm_, GetPos(), 10, 2.0f, range_/20.0f);
	return true;
}