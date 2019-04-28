#pragma once
#include "Actor.h"
#include "World.h"
#include "Animation.h"
extern float dt;
extern HGE* hge;
extern World* world;


class StandingState;
class MovingState;
class AttackingState;
class UnderAttackState;


class ActorState
{
	public:
		static StandingState standing;
		static MovingState moving;
		static AttackingState attacking;
		static UnderAttackState underAttack;
		
		
		bool GetMoveOrder()
		{
			if(hge->Input_GetKeyState(HGEK_UP) || hge->Input_GetKeyState(HGEK_DOWN)||hge->Input_GetKeyState(HGEK_LEFT) ||hge->Input_GetKeyState(HGEK_RIGHT) ) 
				return true;
			return false;
		}
		bool GetAttackOrder()
		{
			if(hge->Input_GetKeyState(HGEK_SPACE) )
				return true;
			return false;
		}
		virtual void HandleInput(Actor&){}//根据输入改变人物状态 
		virtual void Update(Actor&){}//在该状态的时候时刻进行更新 
		virtual void Enter(Actor&){}

};



class MovingState:public ActorState
{
	public:
		virtual void Enter(Actor &actor)
		{
			actor.SetAnimation(MOVE);
		}
		virtual void HandleInput(Actor& actor)
		{
			if(actor.isUnderAttack)
			{
				actor.state=(ActorState*)&ActorState::underAttack;
				actor.state->Enter(actor);
			}
			else if(GetAttackOrder())
			{
				actor.state=(ActorState*)&ActorState::attacking;
				actor.state->Enter(actor);
			}
			else if(!(GetMoveOrder() || GetAttackOrder()))
			{
				actor.state=(ActorState*)&ActorState::standing;
				actor.state->Enter(actor); 
			}
		}
		virtual void Update(Actor& actor)
		{
			if(hge->Input_GetKeyState(HGEK_LEFT))	{actor.SetX(actor.X()-0.3f);actor.animation->MoveLeft();actor.forward=LEFT;}
			if(hge->Input_GetKeyState(HGEK_RIGHT))	{actor.SetX(actor.X()+0.3f);actor.animation->MoveRight();actor.forward=RIGHT;}
			if(hge->Input_GetKeyState(HGEK_UP))		{actor.SetY(actor.Y()-0.3f);actor.animation->MoveUp();actor.forward=UP;}
			if(hge->Input_GetKeyState(HGEK_DOWN))	{actor.SetY(actor.Y()+0.3f);actor.animation->MoveDown();actor.forward=DOWN;}
			actor.animation->KeepPlaying();
			actor.animation->Update(dt);
		} 
		
};

class StandingState:public ActorState
{
	public:
		virtual void Enter(Actor &actor)
		{
			actor.SetAnimation(STAND);
		}
		virtual void HandleInput(Actor& actor)
		{
			if(actor.isUnderAttack)
			{
				actor.state=(ActorState*)&ActorState::underAttack;
				actor.state->Enter(actor);
			}
			//站立状态下按了方向键进入移动状态 
			else if(GetMoveOrder()) 
			{
				actor.state=&ActorState::moving;
				actor.state->Enter(actor);
				
			}
			//站立状态下按了空格键进入攻击状态 
			else if(GetAttackOrder())
			{
				actor.state=(ActorState*)&ActorState::attacking;
				actor.state->Enter(actor);
			}
		}	
		virtual void Update(Actor &actor)
		{
			actor.animation->Update(dt);
		}
		
		
		
		
};



class AttackingState:public ActorState
{
	public:
		AttackingState():attackTime(1.0f){}
		virtual void Enter(Actor &actor)
		{
			actor.SetAnimation(ATTACK);
			world->AttackDetect(&actor,30.0f,M_PI/6);
		}
		virtual void HandleInput(Actor& actor)
		{
			if(actor.isUnderAttack)
			{
				attackTime=1.0f;
				actor.state=(ActorState*)&ActorState::underAttack;
				actor.state->Enter(actor);
			}
			else if(attackTime<=0.0f)
			{
				actor.state=&ActorState::standing;
				actor.state->Enter(actor);
				attackTime=1.0f;
			}
		} 
		virtual void Update(Actor& actor)
		{
			attackTime-=dt;
			actor.animation->Update(dt);
		} 
	private:
		float attackTime;
		
};

class UnderAttackState:public ActorState
{
	public:
		UnderAttackState():rigidTime(0.5f){}
		virtual void Enter(Actor &actor)
		{
			actor.SetAnimation(UNDER_ATTACK);
			*(actor.hp)-=10;
		}
		virtual void HandleInput(Actor& actor)
		{
			if(rigidTime<=0.0f)
			{
				actor.state=&ActorState::standing;
				actor.state->Enter(actor);
				rigidTime=0.5f;
				actor.isUnderAttack=false;
			}
		}
		virtual void Update(Actor &actor)
		{
			rigidTime-=dt;
			actor.animation->Update(dt);
		}
	private:
		float rigidTime;
};






















 