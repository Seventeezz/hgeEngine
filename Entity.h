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
		Entity():x_(0),y_(0)//��ʼ�����������Ϊ(0,0),Ѫ��Ϊ������״̬
		{
			if(isActive)
			hp=new BloodSlider(HpTex,0,52,128,28);
		}
		~Entity()
		{
			if(isActive)
			delete hp;
		}
		float X(){return x_;}				 //��ȡ���������
		float Y(){return y_;}				 //��ȡ����������
		void SetX(float x){x_=x;}		 //�������������
		void SetY(float y){y_=y;}		 //��������������
		virtual void HandleInput(){}   //���麯������������/ָ��
		virtual void Update(){}			  //���麯����ÿ�����
		void Render(Position p)			//����Ļ����Ⱦ����ͼ����Ѫ��(���ڵĻ�)
		{
			spr->Render(p.x,p.y);
			if(isActive)
			hp->Render(p.x,p.y);
		}
		Position GetPosition()			  //��ȡ�����Position
		{
			Position p;
			p.x=x_;
			p.y=y_;
			return p;
		}

		bool isActive;						 //�Ƿ�Ϊ����
		bool isUnderAttack;				//�Ƿ����ܹ���
		FORWARD forward;			 //���������Եķ���
		BloodSlider *hp;				   //�洢Ѫ��
	protected:
		hgeSprite *spr;						//�洢ͼ��/����



	private:	
		float x_;
		float y_;
		
};


