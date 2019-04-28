#include "World.h"
#include "hgevector.h"
#include "Entity.h"
World::World()
{
	num=0;
	camera=new Camera();
	for(int i=0;i<MAX_ENTITY;i++)
		entity[i]=NULL;
}

World::~World()
{
	delete camera;
}


void World::AddEntity(Entity* entity_)
{
	entity[num++]=entity_;

	
}

void World::Update()
{
	for(int i=0;i<num;i++)
	{
		entity[i]->Update();
	}
	camera->Follow((Actor*)entity[1]);
}

void World::Render()
{
	for(int i=0;i<num;i++)
	{
		entity[i]->Render(camera->Transform(entity[i]->GetPosition()));
	}
}

void World::HandleInput()
{
	for(int i=0;i<num;i++)
	{
		entity[i]->HandleInput();
	}
}

void World::AttackDetect(Entity* current,float maxDistance,float maxAngle)
{
	for(int i=0;i<num;i++)
	{
		if(entity[i]->isActive)//����ǻ���
			if(entity[i] != current)//������ǵ�ǰ����
			{
				hgeVector toEnemy(entity[i]->X()-current->X(),entity[i]->Y()-current->Y());//�ӵ�ǰ����ָ����˵�����
				if(toEnemy.Length()<=maxDistance)//�������������ָ����Χ֮��
				{
					hgeVector right(1,0),left(-1,0),up(0,1),down(0,-1);
					float angle;
					switch(current->forward)
					{
						case RIGHT:
							angle=toEnemy.Angle(&right);
							break;
						case LEFT:
							angle=toEnemy.Angle(&left);
							break;
						case UP:
							angle=toEnemy.Angle(&up);
							break;
						case DOWN:
							angle=toEnemy.Angle(&down);
							break;
					}
					if(angle <= maxAngle) //����н�С��30��,���ڷ�Χ֮��
					{
						entity[i]->isUnderAttack=true;
					}
				}
			}

	} 

}
