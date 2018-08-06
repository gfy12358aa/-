#include"Show.h"
//使用windows获取系统时间，初始化随机树
#include<Windows.h>

int main()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	e.seed(sys.wHour+ sys.wMinute+ sys.wSecond+sys.wMilliseconds);

	WindowsPlayer player;
	player.start();
	return 0;
}