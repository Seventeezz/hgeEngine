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
		void AttackDetect(Entity* ,float distance,float angle);//�Ե�ǰentityΪ���壬����������������й����ж�������һ�����롢�Ƕ�����ɹ�



	private:
		Entity* entity[MAX_ENTITY]; //entity[0]��map entity[1]��actor
		Camera* camera;
		int num;//����ʵ������ 
		
};



