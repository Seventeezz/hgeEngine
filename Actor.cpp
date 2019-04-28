#include "Actor.h"
#include "ActorState.h"


Actor::Actor(HTEXTURE moveTex, HTEXTURE attackTex)
{
	/**********���䶯����Դ**********/
	animation=new Animation(moveTex,attackTex);
	forward=DOWN;
	/**********��ʼ������״̬**********/	
	spr=animation->GetAnimation();//���������������(������̬����Ⱦ)
	state=&ActorState::standing;//��ʼ״̬����Ϊվ��
	
	
	/**********��ʼ����������**********/
	SetX(480.0f);							
	SetY(960.0f);

	isActive=true;
	isUnderAttack=false;
}

Actor::~Actor()
{
	/**********�ͷŶ�����Դ**********/
	delete animation;
} 

void Actor::SetAnimation(STATE state)//����״̬���ö���ͼ��
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














