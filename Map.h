#pragma once
#include "Entity.h"

class Map:public Entity
{
	public:
		Map(HTEXTURE mapTex);//��ͼʹ�õ����� 
		~Map();
		virtual void Update();
	private:

	
};
