#pragma once
#include "Entity.h"

class Map:public Entity
{
	public:
		Map(HTEXTURE mapTex);//地图使用的纹理 
		~Map();
		virtual void Update();
	private:

	
};
