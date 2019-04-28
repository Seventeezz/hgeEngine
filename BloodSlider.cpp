#include "BloodSlider.h"




BloodSlider::BloodSlider(HTEXTURE tex,float x,float y,float width,float height)
{
	spr=new hgeSprite(tex,x,y,width,height);
	hp=100.0f;
}

BloodSlider::~BloodSlider()
{
	delete spr;
}

void BloodSlider::Render(float x,float y)
{
	spr->RenderEx(x-24,y-40,0.0f,hp/100*HSCAILING,VSCAILING);
}

void BloodSlider::operator -= (float x)
{
	hp-=x;
}