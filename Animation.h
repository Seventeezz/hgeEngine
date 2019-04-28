#include "hgeanim.h"

/*****************************
此类为动画类,管理实体的动画
******************************/

class Animation
{
public:
	Animation(HTEXTURE moveTex,HTEXTURE attackTex);
	~Animation();
	void SetHotSpot();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	void AttackRight();
	void AttackLeft();
	void AttackUp();
	void AttackDown();
	
	void KeepPlaying();
	void Play();
	void Stop();
	void Update(float dt);
	hgeAnimation* GetAnimation();
private:
	hgeAnimation *animation;
	hgeAnimation *moveRight,*moveLeft,*moveUp,*moveDown;
	hgeAnimation *attackRight,*attackLeft,*attackUp,*attackDown;

};