#pragma once
#include "Position.h"
class Actor;
class Camera
{
	public:
		Camera()
		{
			x_=80.0f;
			y_=660.0f;
		}
		Position Transform(Position);//������������������ 
		void Follow(Actor*);//���ݺ�����ƫ���������������λ�� 
	private:
		float x_;
		float y_;
		float dx;
		float dy;
	
};
