#pragma once
#include "hgesprite.h"

const float HSCAILING=0.4f;
const float VSCAILING=0.125f;

class BloodSlider
{
	public:
		BloodSlider(HTEXTURE tex,float x,float y,float width,float height);
		~BloodSlider();
		void Update();//更新血条的比例
		void Render(float x,float y);//根据物体的位置显示在其上方;
		void operator -= (float x);//物体血量减少


	private:
		hgeSprite *spr;//血条的精灵
		float hp;
};