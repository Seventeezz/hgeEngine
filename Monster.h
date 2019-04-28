#pragma once
#include "Entity.h"


enum MONSTER_STATE{MONSTER_PATROL,MONSTER_FOLLOW,MONSTER_ATTACK,MONSTER_UNDER_ATTACK};

class Animation;
class MonsterState;
class AttackState;
class PatrolState;
class FollowState;
class Monster_UnderAttackState;




class Monster:public Entity
{
	public:
		friend class MonsterState;
		friend class AttackState;
		friend class PatrolState;
		friend class FollowState;
		friend class Monster_UnderAttackState;

		Monster(HTEXTURE moveTex,HTEXTURE attackTex);
		~Monster();
		virtual void HandleInput();
		virtual void Update();
		void SetAnimation(MONSTER_STATE);
		Animation* GetAniamtion();

	private:
		Animation* animation;
		MonsterState* state;

		PatrolState* patroling;
		FollowState* following;
		AttackState* attacking;
		Monster_UnderAttackState* underAttacking;
};