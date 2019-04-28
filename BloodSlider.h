#pragma once
#include "hgesprite.h"

const float HSCAILING=0.4f;
const float VSCAILING=0.125f;

class BloodSlider
{
	public:
		BloodSlider(HTEXTURE tex,float x,float y,float width,float height);
		~BloodSlider();
		void Update();//����Ѫ���ı���
		void Render(float x,float y);//���������λ����ʾ�����Ϸ�;
		void operator -= (float x);//����Ѫ������


	private:
		hgeSprite *spr;//Ѫ���ľ���
		float hp;
};