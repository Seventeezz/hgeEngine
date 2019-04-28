#pragma once
#include "Entity.h"
#include "hgeanim.h"

enum STATE{STAND,MOVE,ATTACK,UNDER_ATTACK};


class Animation;
class ActorState; 

class AttackingState;
class MovingState;
class StandingState;
class UnderAttackState;

class Actor:public Entity
{
	public:
		friend class AttackingState;
		friend class MovingState;
		friend class StandingState;
		friend class UnderAttackState;
		
		Actor(HTEXTURE MoveTex, HTEXTURE AttackTex);
		~Actor();
		void SetAnimation(STATE);
		virtual void HandleInput();
		virtual void Update();


	private:
		ActorState *state;
		Animation *animation;
	
		
};
