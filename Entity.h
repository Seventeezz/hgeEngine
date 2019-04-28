#pragma once
#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "Position.h"
#include "BloodSlider.h"

extern HTEXTURE HpTex;

enum FORWARD{RIGHT,LEFT,UP,DOWN};

class Entity
{
	public:
		Entity():x_(0),y_(0)//初始化物体的坐标为(0,0),血条为不存在状态
		{
			if(isActive)
			hp=new BloodSlider(HpTex,0,52,128,28);
		}
		~Entity()
		{
			if(isActive)
			delete hp;
		}
		float X(){return x_;}				 //获取物体横坐标
		float Y(){return y_;}				 //获取物体纵坐标
		void SetX(float x){x_=x;}		 //设置物体横坐标
		void SetY(float y){y_=y;}		 //设置物体纵坐标
		virtual void HandleInput(){}   //（虚函数）接受输入/指令
		virtual void Update(){}			  //（虚函数）每秒更新
		void Render(Position p)			//在屏幕上渲染物体图像及其血条(存在的话)
		{
			spr->Render(p.x,p.y);
			if(isActive)
			hp->Render(p.x,p.y);
		}
		Position GetPosition()			  //获取物体的Position
		{
			Position p;
			p.x=x_;
			p.y=y_;
			return p;
		}

		bool isActive;						 //是否为活体
		bool isUnderAttack;				//是否遭受攻击
		FORWARD forward;			 //物体所正对的方向
		BloodSlider *hp;				   //存储血条
	protected:
		hgeSprite *spr;						//存储图像/动画



	private:	
		float x_;
		float y_;
		
};


