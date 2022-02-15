#include"speechManager.h"

SpeechManager::SpeechManager()
{
	//初始化容器以及属性
	this->initSpeech();

	//创建选手
	this->createSpeaker();
	
	//加载文件
	this->ReadFile();
}
//菜单函数
void SpeechManager::show_Menu()
{
	cout << "******************************************" << endl;
	cout << "*************欢迎参加演讲比赛*************" << endl;
	cout << "*************1.开始演讲比赛***************" << endl;
	cout << "*************2.查看往界记录***************" << endl;
	cout << "*************3.清空比赛记录***************" << endl;
	cout << "*************0.退出比赛程序***************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}



//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//初始化属性
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVector.clear();
	this->m_Speaker.clear();

	this->m_Reader.clear();

	this->m_Index = 1;

}

//创建选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
			name += nameSeed[i];
			Speaker speaker;
			speaker.m_name = name;
			for (int j = 0; j < 2; j++)
			{
				speaker.m_Score[j] = 0;
			}
			this->v1.push_back(i + 10001);

			this->m_Speaker.insert(make_pair(i + 10001, speaker));
	}


}
//抽签
void SpeechManager::speechDraw()
{
	cout << "第" << this->m_Index << "轮比赛正在进行中" << endl;
	cout << "-----------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else 
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << endl;
		}
	}
	cout << "-----------------------------" << endl;
	system("pause");
	cout << endl;
}
//开始比赛
void SpeechManager::startSpeech()
{
	//    第一轮比赛
	// 1.抽签
	   this->speechDraw();
	//	  2.比赛
	   speechContest();
	//	  3.显示晋级结果
	   this->showScore();

	//	  第二轮比赛
	//	  1.抽签
	   this->m_Index++;
	   this->speechDraw();
	//	  2.比赛
	   speechContest();

	//	  3.显示晋级结果
	   this->showScore();
	//    4.保存分数到文件中
	   this->saveScore();
	   this->initSpeech();
	   this->createSpeaker();
	   this->ReadFile();
	   cout << "本届比赛结束" << endl;
	   system("pause");
	   system("cls");
}
//比赛开始
void SpeechManager::speechContest()
{
	vector<int>v_Src;
	multimap<double, int, greater<double>>groupScore;
	int num = 0;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score<<" ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//打印平均分
		//cout << "编号：" << *it << "姓名：" << this->m_Speaker[*it].m_name << "平均分：" << avg << endl;
		this->m_Speaker[*it].m_Score [this->m_Index-1]= avg;
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组得分如下：" << endl;
				for(multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
				{
					cout << "编号:" << it->second << "姓名:" << this->m_Speaker[it->second].m_name
						<< "成绩:" << it->first<<endl;
				}
			
				cout << endl;
				int cout = 0;
				for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && cout < 3; it++, cout++)
				{
					if (this->m_Index == 1)
					{
						v2.push_back((*it).second);
					}
					else
					{
						vVector.push_back((*it).second);
					}
				}
				groupScore.clear();
		}
	}
	cout << "第" << this->m_Index << "轮比赛结束"<<endl;
	system("pause");
}
//成绩显示
void SpeechManager::showScore()
{
	cout << "第" << this->m_Index << "轮晋级选手信息如下" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVector;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号：" << *it << "姓名：" << this->m_Speaker[*it].m_name 
			<<"得分："<<this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}
void  SpeechManager::saveScore()
{
	ofstream of;
	of.open("speech.csv",ios::out|ios::app);
	for(vector<int>::iterator it=vVector.begin();it!=vVector.end();it++)
	{
		of << *it << "," << this->m_Speaker[*it].m_name << "," << this->m_Speaker[*it].m_Score[1] <<",";
	}
	of << endl;
	of.close();
	cout << "记录已保存" << endl;
	this->fileIsEmpty = false;
}



//读取文件
void SpeechManager::ReadFile()
{
	ifstream ifs("speech.csv", ios::in);

	if(!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "文件为空" << endl;
			ifs.close();
			return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs >> data)

	{
		//cout << data << endl;
		vector<string> v;
		
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		index++;
		this->m_Reader.insert(make_pair(index, v));
		
	}
	ifs.close();	
}
//显示文件信息
void SpeechManager:: ShowFile()
{
	if (this->fileIsEmpty)
	{
		cout << "无往届记录" << endl;

	}
	else
	{
		for (map<int, vector<string>>::iterator it = this->m_Reader.begin(); it != this->m_Reader.end(); it++)
		{
			cout << "第" << it->first << "界比赛结果如下：" << endl;

			cout << "冠军编号：" << it->second[0] << " " << "冠军姓名:" << it->second[1] << "  " << "冠军分数：" << it->second[2] << endl;
			cout << "季军编号：" << it->second[3] << " " << "季军姓名:" << it->second[4] << "  " << "季军分数：" << it->second[5] << endl;
			cout << "亚军编号：" << it->second[6] << " " << "亚军姓名:" << it->second[7] << "  " << "亚军分数：" << it->second[8] << endl;
		}
	}
	system("pause");
	system("cls");
}
//清除文件信息
void SpeechManager::ClearFile()
{
	cout << "请您确定是否清楚所有信息？" << endl;
	cout << "1-确认" << endl;
	cout << "2-取消" << endl;
	int chose;
	cin >> chose;
	if (chose == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeaker();
		this->ReadFile();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager()
{


}
