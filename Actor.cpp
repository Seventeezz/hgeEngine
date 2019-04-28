#include "Actor.h"
#include "ActorState.h"


Actor::Actor(HTEXTURE moveTex, HTEXTURE attackTex)
{
	/**********分配动画资源**********/
	animation=new Animation(moveTex,attackTex);
	forward=DOWN;
	/**********初始化代理及状态**********/	
	spr=animation->GetAnimation();//将动画代理给精灵(用来多态性渲染)
	state=&ActorState::standing;//初始状态设置为站立
	
	
	/**********初始化人物属性**********/
	SetX(480.0f);							
	SetY(960.0f);

	isActive=true;
	isUnderAttack=false;
}

Actor::~Actor()
{
	/**********释放动画资源**********/
	delete animation;
} 

void Actor::SetAnimation(STATE state)//根据状态设置动画图像
{
	switch(state)
	{
		case STAND:
			if(forward==DOWN) {animation->MoveDown();}
			else if(forward==LEFT) {animation->MoveLeft();}
			else if(forward==RIGHT) {animation->MoveRight();}
			else if(forward==UP) {animation->MoveUp();}
			animation->Stop();
			break;
		case MOVE:
			if(forward==DOWN) {animation->MoveDown();}
			else if(forward==LEFT) {animation->MoveLeft();}
			else if(forward==RIGHT) {animation->MoveRight();}
			else if(forward==UP) {animation->MoveUp();}
			animation->Play();
			break;
		case ATTACK:
			if(forward==DOWN) {animation->AttackDown();}
			else if(forward==LEFT) {animation->AttackLeft();}
			else if(forward==RIGHT) {animation->AttackRight();}
			else if(forward==UP) {animation->AttackUp();}
			animation->Play();
			break;
		case UNDER_ATTACK:
			if(forward==DOWN) {animation->MoveDown();}
			else if(forward==LEFT) {animation->MoveLeft();}
			else if(forward==RIGHT) {animation->MoveRight();}
			else if(forward==UP) {animation->MoveUp();}
			animation->Stop();
			break;			
	}
}

void Actor::HandleInput()
{
	state->HandleInput(*this);
}


void Actor::Update()
{
	state->Update(*this);
	spr=animation->GetAnimation();
	
}














