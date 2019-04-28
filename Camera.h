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
		Position Transform(Position);//返回相对摄像机的坐标 
		void Follow(Actor*);//根据和人物偏移量设置摄像机的位置 
	private:
		float x_;
		float y_;
		float dx;
		float dy;
	
};
