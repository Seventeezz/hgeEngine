#include "World.h"
#include "Map.h"
#include "MonsterState.h"

/********************声明部分*******************/
HGE* hge=0;
float dt;

HTEXTURE	MoveTex,AttackTex;
HTEXTURE	Monster_MoveTex,Monster_AttackTex;
HTEXTURE	MapTex,HpTex;




World* world;
Map* map;

Actor* actor;
Monster* monster;

StandingState ActorState::standing;
MovingState ActorState::moving;
AttackingState ActorState::attacking;
UnderAttackState ActorState::underAttack;

/********************初始化部分*******************/
bool Initiate()//初始化成功返回1，否则返回0
{



		AttackTex=hge->Texture_Load("参军_melee.png");
		MoveTex=hge->Texture_Load("参军.png");
		MapTex=hge->Texture_Load("地图.jpg");
		HpTex=hge->Texture_Load("血条.png");
		Monster_MoveTex=hge->Texture_Load("盗贼头目.png");
		Monster_AttackTex=hge->Texture_Load("盗贼头目_melee.png");
		if(!MoveTex || !AttackTex || !MapTex ||!HpTex ||!Monster_MoveTex ||! Monster_AttackTex)
		{
			MessageBox(NULL, "Can't load sources, please examin it !","ERROR", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		actor = new Actor(MoveTex, AttackTex);
		monster=new Monster(Monster_MoveTex, Monster_AttackTex);
		map = new Map(MapTex);
		world=new World;
		world->AddEntity(map);
		world->AddEntity(monster);
		world->AddEntity(actor);
		return 1;
}

/********************释放部分*******************/
void Release()
{
		delete actor;
		delete monster;

		delete map;
		delete world;

		hge->Texture_Free(AttackTex);
		hge->Texture_Free(MoveTex);
		hge->Texture_Free(Monster_AttackTex);
		hge->Texture_Free(Monster_MoveTex);

		hge->Texture_Free(MapTex);
		hge->Texture_Free(HpTex);
}