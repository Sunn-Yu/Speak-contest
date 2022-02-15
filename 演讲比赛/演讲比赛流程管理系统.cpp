#include<iostream>
using namespace std;
#include"speechManager.h"

int main()
{
	SpeechManager SM;
	int chose;
	srand((unsigned int)time(NULL));
	//for (map<int, Speaker>::iterator it = SM.m_Speaker.begin(); it != SM.m_Speaker.end(); it++)
	//{
	//	cout << "选手编号" << it->first << "姓名" << it->second.m_name << "分数" << it->second.m_Score[0]<< endl;
	//}
	while (true)
	{
		SM.show_Menu();
		
		cout << "请输入您的选择" << endl;
		cin >> chose;
		switch (chose)
		{
		case 1://开始演讲
			SM.startSpeech();
			break;
		case 2://查看系统记录
			SM.ShowFile();
			break;
		case 3://清空记录
			SM.ClearFile();
			break;
		case 0://退出系统
			SM.exitSystem();
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}