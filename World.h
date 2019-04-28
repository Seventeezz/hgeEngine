#pragma once

#include "Camera.h"

const int MAX_ENTITY=100;
class Entity;
class World
{
	public:
		World();
		~World();
		void AddEntity(Entity*);
		void HandleInput();
		void Update();
		void Render();
		void AttackDetect(Entity* ,float distance,float angle);//以当前entity为主体，对其他所有物体进行攻击判定，进入一定距离、角度则算成功



	private:
		Entity* entity[MAX_ENTITY]; //entity[0]是map entity[1]是actor
		Camera* camera;
		int num;//现有实体数量 
		
};



