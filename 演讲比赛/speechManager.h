#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<string>
#include<numeric>
#include<fstream>
class SpeechManager
{
public:
	//���캯��
	SpeechManager();
	//�˵�����
	 void show_Menu();
	 //�˳�ϵͳ
	 void exitSystem();
	 //��������
	~SpeechManager();
	//��ʼ������
	void initSpeech();
	//����ѡ��
	void createSpeaker();

	//����
	void startSpeech();

	//��ǩ
	void speechDraw();
	
	//������ʼ
	void speechContest();

	//�ɼ���ʾ
	void showScore();

	//����ɼ�
	void  saveScore();

	//��ȡ�ļ�
	void ReadFile();

	//��ʾ�ļ���Ϣ
	void ShowFile();

	//����ļ���Ϣ
	void ClearFile();
	//�ļ�״̬
	bool fileIsEmpty;

	//�洢�ļ�������Ϣ
	map<int, vector<string>>m_Reader;

	//��һ��ѡ�� 12
	vector<int> v1;
	//�ڶ���ѡ�� 6
	vector<int> v2;
	//ʤ����ѡ�� 3
	vector<int> vVector;

	//��ű���Լ���Ӧ����ѡ����Ϣ
	map<int, Speaker>m_Speaker;

	//��¼��������
	int m_Index;
	
private:

};

