#include "Animation.h"


Animation::Animation(HTEXTURE moveTex,HTEXTURE attackTex)
{
	moveDown=new hgeAnimation(moveTex,4,4,0,0,48,64);
	moveLeft=new hgeAnimation(moveTex,4,4,0,64,48,64);
	moveRight=new hgeAnimation(moveTex,4,4,0,128,48,64);
	moveUp=new hgeAnimation(moveTex,4,4,0,192,48,64);
	
	attackDown=new hgeAnimation(attackTex,4,4,0,0,64,64);
	attackLeft=new hgeAnimation(attackTex,4,4,0,64,64,64);
	attackRight=new hgeAnimation(attackTex,4,4,0,128,64,64);
	attackUp=new hgeAnimation(attackTex,4,4,0,192,64,64);

	animation=moveDown;
	SetHotSpot();
}

Animation::~Animation()
{
	delete moveDown;
	delete moveLeft;
	delete moveRight;
	delete moveUp;
	
	delete attackDown;
	delete attackLeft;
	delete attackRight;
	delete attackUp;
}


void Animation::MoveRight()
{
	animation=moveRight;
}
void Animation::MoveLeft()
{
	animation=moveLeft;
}
void Animation::MoveUp()
{
	animation=moveUp;
}
void Animation::MoveDown()
{
	animation=moveDown;
}

void Animation::AttackRight()
{
	animation=attackRight;
}
void Animation::AttackLeft()
{
	animation=attackLeft;
}
void Animation::AttackUp()
{
	animation=attackUp;
}
void Animation::AttackDown()
{
	animation=attackDown;
}

void Animation::KeepPlaying()
{
	if(! animation->IsPlaying())
		animation->Play();
}

void Animation::Play()
{
	animation->Play();
}

void Animation::Stop()
{
	animation->SetFrame(0);
	animation->Stop();
}

void Animation::Update(float dt)
{
	animation->Update(dt);
}

hgeAnimation* Animation::GetAnimation()
{
	return animation;
}

void Animation::SetHotSpot()
{
	moveDown->SetHotSpot(24,32);
	moveUp->SetHotSpot(24,32);
	moveLeft->SetHotSpot(24,32);
	moveRight->SetHotSpot(24,32);
	attackDown->SetHotSpot(32,32);
	attackUp->SetHotSpot(32,32);
	attackLeft->SetHotSpot(32,32);
	attackRight->SetHotSpot(32,32);

}