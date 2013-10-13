//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: damage.h
//
// 내용: 데미지 타입
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DAMAGE_H__
#define  __DAMAGE_H__

enum Damage_Type
{
	DT_ALL,
	DT_BULLET,
	DT_FIRE,
	DT_EXPLOSION,
	DT_MELEE,
	DT_BACK_STAB,
	DT_SELF_EXPLOSION,
	DT_VIRUS,
	DT_POISON,
	DT_WATER,
	DT_MIRROR,
	DT_ROCK,
	DT_AP,
	DT_TRAP,
	DT_MAX
};



enum Vamp_Type
{
	VT_ALL,
	VT_ZOMBIE,
	VT_HUMAN,
	VT_BUG,
	VT_ROBOT,
	VT_ETC,
	VT_MAX
};
#endif // __DAMAGE_H__