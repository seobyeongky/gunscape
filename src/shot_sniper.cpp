//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_sniper.cpp
//
// 내용: 스나이퍼 팡!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_sniper.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "map.h"

Shot_sniper::Shot_sniper(Texture* texture_, Unit* unit_, float damage_, float sniper_, float power_, float max_power_, int team_, coord_def pos_, float angle_, float distance_, int delay_):
Shot_base(texture_, unit_, team_, pos_, coord_def(0, 0)), 
damage(damage_), sniper(sniper_), power(power_), max_power(max_power_), distance(distance_), 
count(0),delay(delay_), start_pos(pos_), end_pos(pos_.x+distance_*cos(angle_),pos_.y+distance_*sin(angle_)), angle(angle_)
{
	int see_ = map->CollutionPosToPos(start_pos, end_pos);
	if(see_)
	{
		distance_ = (float)see_;
		end_pos = coord_def(pos_.x+distance_*cos(angle_),pos_.y+distance_*sin(angle_));
	}
	coord_def temp_(pos_.x+distance_*cos(angle_),pos_.y+distance_*sin(angle_));
	pos_ = temp_;
}
Shot_sniper::~Shot_sniper()
{

}
bool Shot_sniper::Action(Game_Manager* gm_)
{
	 //0이 안막혀있는거
	if(count == 0)
	{
	
		int coll_ = pre_collution(3);

		if(gm_)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam())
				{

					coord_def pos_ = (*it)->GetPos();
					float radius_ = (*it)->GetSize()+((*it)->isPlayer()?0.0f:3.0f);
					float tan_ = sin(angle) / cos(angle); //기울기
					float b_ = start_pos.y - tan_ * start_pos.x;
					float result_ = abs(tan_*pos_.x-pos_.y+b_)/sqrt(tan_*tan_+1);
					if(result_ <= radius_)
					{
						//cot_ * tan_ = -1
						// cot_*x - y + b1_  = 0; -> pos에서의 법선방정식
						// cot_*x - y + b2_  = 0; -> 한프레임후의 법선방정식
						// cot_*x - y + b3_  = 0; -> 적의 위치의 법선방정식
						//이제 b3_이 b1_이랑 b2_사이에 있으면 된다?
						float cot_ = -1 / tan_;
						float b1_ = start_pos.y - cot_ * start_pos.x;
						float b2_ = end_pos.y - cot_ * end_pos.x;
						float b3_ = pos_.y - cot_ * pos_.x;

						if((b1_ <=  b3_ && b3_ <= b2_) || (b2_ <=  b3_ && b3_ <= b1_)){
							(*it)->SetKnockback(power, max_power, angle);
							int final_damge_ = (*it)->SetDamage(gm_, GetFirstPos(), DT_BULLET, damage, GetTeam(), sniper,unit?unit->GetCritical():0);
							if(unit)
								unit->GiveDamage(gm_, (*it), DT_BULLET, final_damge_);
						}
					}	

				}
			}
		}
	}
	count++;
	if(count == delay)
	{
		return true;
	}
	return false;
}


bool Shot_sniper::Draw(coord_def offset_, float size_)
{
	int alpha_ = 255*(delay-count)/delay;
	if(GetTexture())
		return GetTexture()->Draw(((start_pos.x+end_pos.x)/2-offset_.x)*size_, ((start_pos.y+end_pos.y)/2-offset_.y)*size_, size_*distan_coord(start_pos,end_pos), size_ , angle , D3DCOLOR_ARGB(alpha_,255,255,255));
	else
		return false;
}