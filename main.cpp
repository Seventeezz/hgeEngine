#include "Declaration.h"
#pragma comment(lib,"hge.lib")

bool FrameFunc()
{
	dt=hge->Timer_GetDelta();
	world->HandleInput();
	world->Update();
	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	world->Render();
	hge->Gfx_EndScene();

	return false;
}



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR ,int)
{
	hge=hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC,FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC,RenderFunc);
	hge->System_SetState(HGE_TITLE, "曹操传");
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate())
	{

		if(Initiate() == false) return 0; //如果初始化失败，结束进程
		hge->System_Start();  
		Release();
	

	}
	else MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;	

}