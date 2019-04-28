#include "Monster.h"
#include "MonsterState.h"



Monster::Monster(HTEXTURE moveTex,HTEXTURE attackTex)
{
	animation=new Animation(moveTex,attackTex);
	
	patroling=new PatrolState;
	following=new FollowState;
	attacking=new AttackState;
	underAttacking=new Monster_UnderAttackState;
	state=(MonsterState*)patroling;
	
	spr=animation->GetAnimation();

	
	SetX(600.0f);
	SetY(900.0f);
	forward=LEFT;
	isActive=true;
	isUnderAttack=false;
	
}

Monster::~Monster()
{
	delete animation;
	delete patroling;
	delete following;
	delete attacking;
	delete underAttacking;
}

Animation* Monster::GetAniamtion()
{
	return animation;
}



void Monster::HandleInput()
{
	state->HandleInput(*this);
}

void Monster::Update()
{
	state->Update(*this);
	spr=animation->GetAnimation();
}


void Monster::SetAnimation(MONSTER_STATE state)
{
	switch(state)
	{
		case MONSTER_PATROL:
		case MONSTER_FOLLOW:
			if(forward=LEFT) {animation->MoveLeft();}
			else if(forward=RIGHT) {animation->MoveRight();}
			else if(forward=UP) {animation->MoveUp();}
			else if(forward=DOWN) {animation->MoveDown();}
			animation->Play();
			break;
		case MONSTER_UNDER_ATTACK:
			if(forward==DOWN) {animation->MoveDown();}
			else if(forward==LEFT) {animation->MoveLeft();}
			else if(forward==RIGHT) {animation->MoveRight();}
			else if(forward==UP) {animation->MoveUp();}
			animation->Stop();
			break;
		case MONSTER_ATTACK:
			if(forward==DOWN) {animation->AttackDown();}
			else if(forward==LEFT) {animation->AttackLeft();}
			else if(forward==RIGHT) {animation->AttackRight();}
			else if(forward==UP) {animation->AttackUp();}
			animation->Play();
			break;
	}
}






