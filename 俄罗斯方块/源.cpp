#include"Show.h"
//ʹ��windows��ȡϵͳʱ�䣬��ʼ�������
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