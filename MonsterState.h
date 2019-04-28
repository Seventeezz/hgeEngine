#pragma once
#include "Monster.h"
#include "ActorState.h"
#include "hgevector.h"


extern float dt;
extern Actor* actor;
extern World* world;

class MonsterState
{
	public:
		virtual void HandleInput(Monster &){}
		virtual void Update(Monster &){}
		virtual void Enter(Monster &){}
					
		MONSTER_STATE GetState(Monster &monster)//获取当前状态
		{
			hgeVector toActor(actor->X()-monster.X(),actor->Y()-monster.Y());
			float distance=toActor.Length();
			if(distance >= 400.0f) return MONSTER_PATROL;
			else if(distance >= 60.0f) return MONSTER_FOLLOW;
			else if(distance >= 0.0f)  return MONSTER_ATTACK;
		}
		

};

class PatrolState:public MonsterState
{
	public:
		PatrolState()
		{
			isLeft=true;
		}
		virtual void Enter(Monster & monster)
		{
			monster.SetAnimation(MONSTER_PATROL);
		}
		virtual void HandleInput(Monster & monster)
		{
			switch(GetState(monster))
			{
				case MONSTER_FOLLOW:
					monster.state=(MonsterState*)monster.following;
					monster.state->Enter(monster);
					break;
			}
		} 
		virtual void Update(Monster & monster)
		{
			if(isLeft)
			{
				monster.forward=LEFT; 
				monster.animation->MoveLeft();
				if(monster.X()>0.0f)
					monster.SetX(monster.X()-0.2f);
				else
					isLeft=false;
			}
			else
			{
				monster.forward=RIGHT;
				monster.animation->MoveRight();
				if(monster.X()<960.0f)
					monster.SetX(monster.X()+0.2f);
				else
					isLeft=true;
			}
			monster.animation->KeepPlaying();
			monster.animation->Update(dt);
		}
	private:
		bool isLeft;
};


class FollowState:public MonsterState
{
	public:
		int GetActorPosition(Monster &monster) //获取主角的所在方位(1,2,3……按照从北偏东开始)
		{
			hgeVector toActor(actor->X()-monster.X(),actor->Y()-monster.Y());
			hgeVector up(0,-1),down(0,1),left(-1,0),right(1,0);
			if(toActor.x>=0.0f && toActor.y<=0.0f)
			{
				float angle=toActor.Angle(&right);
				if(angle<=M_PI/4)	return 2;
				else	return 1;
			}
			else if(toActor.x>=0.0f && toActor.y>=0.0f)
			{
				float angle=toActor.Angle(&right);
				if(angle<=M_PI/4)	return 3;
				else	return 4;
			}
			else if(toActor.x<=0.0f && toActor.y>=0.0f)
			{
				float angle=toActor.Angle(&left);
				if(angle<=M_PI/4)	return 6;
				else	return 5;
			}
			else if(toActor.x<=0.0f && toActor.y<=0.0f)
			{
				float angle=toActor.Angle(&left);
				if(angle<=M_PI/4)	return 7;
				else	return 8;
			}


		}
		
		void RunToActor(Monster &monster)
		{

			switch(GetActorPosition(monster))
			{
				case 1: monster.forward=UP;monster.SetX(monster.X()+0.2f);monster.SetY(monster.Y()-0.2f);break;
				case 2: monster.forward=RIGHT;monster.SetX(monster.X()+0.2f);monster.SetY(monster.Y()-0.2f);break;
				case 3: monster.forward=RIGHT;monster.SetX(monster.X()+0.2f);monster.SetY(monster.Y()+0.2f);break;
				case 4: monster.forward=DOWN;monster.SetX(monster.X()+0.2f);monster.SetY(monster.Y()+0.2f);break;
				case 5: monster.forward=DOWN;monster.SetX(monster.X()-0.2f);monster.SetY(monster.Y()+0.2f);break;
				case 6: monster.forward=LEFT;monster.SetX(monster.X()-0.2f);monster.SetY(monster.Y()+0.2f);break;
				case 7: monster.forward=LEFT;monster.SetX(monster.X()-0.2f);monster.SetY(monster.Y()-0.2f);break;
				case 8: monster.forward=UP;monster.SetX(monster.X()-0.2f);monster.SetY(monster.Y()-0.2f);break;
			}
		}
		
		virtual void Enter(Monster & monster)
		{
			monster.SetAnimation(MONSTER_FOLLOW);
		} 
		virtual void HandleInput(Monster & monster)
		{
			switch(GetState(monster))
			{
				case MONSTER_PATROL:
					monster.state=(MonsterState*)monster.patroling;
					monster.state->Enter(monster);
					break;
				case MONSTER_ATTACK:
					monster.state=(MonsterState*)monster.attacking;
					monster.state->Enter(monster);
					break;
				case MONSTER_UNDER_ATTACK:
					monster.state=(MonsterState*)monster.underAttacking;
					monster.state->Enter(monster);
					break;
			}				
		}
		virtual void Update(Monster& monster)
		{
			RunToActor(monster);
			if(monster.forward==DOWN) {monster.animation->MoveDown();}
			else if(monster.forward==LEFT) {monster.animation->MoveLeft();}
			else if(monster.forward==RIGHT) {monster.animation->MoveRight();}
			else if(monster.forward==UP) {monster.animation->MoveUp();}
			monster.animation->KeepPlaying();
			monster.animation->Update(dt); 
		}	
}; 

class AttackState:public MonsterState
{
	public:
		AttackState():attackTime(1.0f){}
		virtual void Enter(Monster &monster)
		{
			monster.SetAnimation(MONSTER_ATTACK);
			world->AttackDetect(&monster,30.0f,M_PI/6);
		}
		virtual void HandleInput(Monster& monster)
		{
			if(monster.isUnderAttack)
			{
				attackTime=1.0f;
				monster.state=(MonsterState*)monster.underAttacking;
				monster.state->Enter(monster);
			}
			else if(attackTime<=0.0f)
			{
				monster.state=(MonsterState*)monster.following;
				monster.state->Enter(monster);
				attackTime=1.0f;
			}
		} 
		virtual void Update(Monster& monster)
		{
			attackTime-=dt;
			monster.animation->Update(dt);
		} 
	private:
		float attackTime;
		
};


class Monster_UnderAttackState:public MonsterState
{
	public:
		Monster_UnderAttackState():rigidTime(1.0f){}
		virtual void Enter(Monster &monster)
		{
			monster.SetAnimation(MONSTER_UNDER_ATTACK);
			*(monster.hp)-=10;
		}
		virtual void HandleInput(Monster& monster)
		{
			if(rigidTime<=0.0f)
			{
				monster.state=(MonsterState*)monster.following;
				monster.state->Enter(monster);
				rigidTime=1.0f;
				monster.isUnderAttack=false;
			}
		}
		virtual void Update(Monster &monster)
		{
			rigidTime-=dt;
			monster.animation->Update(dt);
		}
	private:
		float rigidTime;
};

















