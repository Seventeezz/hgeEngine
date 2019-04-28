#include "Map.h"

Map::Map(HTEXTURE mapTex)
{
	spr=new hgeSprite(mapTex,0,0,960,1920);
	isActive=false;
}

Map::~Map()
{
	delete spr;
}

void Map::Update()
{
	
}//地图不执行更新(静态地图)


 

