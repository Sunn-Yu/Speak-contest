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
	//	cout << "ѡ�ֱ��" << it->first << "����" << it->second.m_name << "����" << it->second.m_Score[0]<< endl;
	//}
	while (true)
	{
		SM.show_Menu();
		
		cout << "����������ѡ��" << endl;
		cin >> chose;
		switch (chose)
		{
		case 1://��ʼ�ݽ�
			SM.startSpeech();
			break;
		case 2://�鿴ϵͳ��¼
			SM.ShowFile();
			break;
		case 3://��ռ�¼
			SM.ClearFile();
			break;
		case 0://�˳�ϵͳ
			SM.exitSystem();
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}