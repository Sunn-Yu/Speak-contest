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
	//构造函数
	SpeechManager();
	//菜单函数
	 void show_Menu();
	 //退出系统
	 void exitSystem();
	 //析构函数
	~SpeechManager();
	//初始化属性
	void initSpeech();
	//创建选手
	void createSpeaker();

	//比赛
	void startSpeech();

	//抽签
	void speechDraw();
	
	//比赛开始
	void speechContest();

	//成绩显示
	void showScore();

	//保存成绩
	void  saveScore();

	//读取文件
	void ReadFile();

	//显示文件信息
	void ShowFile();

	//清除文件信息
	void ClearFile();
	//文件状态
	bool fileIsEmpty;

	//存储文件读出信息
	map<int, vector<string>>m_Reader;

	//第一轮选手 12
	vector<int> v1;
	//第二轮选手 6
	vector<int> v2;
	//胜利的选手 3
	vector<int> vVector;

	//存放编号以及对应具体选手信息
	map<int, Speaker>m_Speaker;

	//记录比赛轮数
	int m_Index;
	
private:

};

