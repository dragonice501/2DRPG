#include "Engine/Engine.h"

int main(int argc, char* argv[])
{

	if (Engine::Instance().Init())
	{
		Engine::Instance().Run();
	}
	Engine::Instance().Destroy();

    return 0;
}