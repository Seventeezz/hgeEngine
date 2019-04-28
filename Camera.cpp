#include "Camera.h"
#include "Actor.h"

Position Camera::Transform(Position p)
{
	p.x-=x_;
	p.y-=y_;
	return p;
}

void Camera::Follow(Actor *actor)
{
	float x=actor->X();
	float y=actor->Y();
	if(x-x_>=100 && x-x_<=700 && y-y_>=100 && y-y_<=500)
	{
		dx=x-x_;
		dy=y-y_;
		return ;
	}
	else
	{
		x_=x-dx;
		y_=y-dy;
		return ;
	}
	
	
	
	
	
	
	
}
