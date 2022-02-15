#include"speechManager.h"

SpeechManager::SpeechManager()
{
	//��ʼ�������Լ�����
	this->initSpeech();

	//����ѡ��
	this->createSpeaker();
	
	//�����ļ�
	this->ReadFile();
}
//�˵�����
void SpeechManager::show_Menu()
{
	cout << "******************************************" << endl;
	cout << "*************��ӭ�μ��ݽ�����*************" << endl;
	cout << "*************1.��ʼ�ݽ�����***************" << endl;
	cout << "*************2.�鿴�����¼***************" << endl;
	cout << "*************3.��ձ�����¼***************" << endl;
	cout << "*************0.�˳���������***************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}



//�˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ʼ������
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVector.clear();
	this->m_Speaker.clear();

	this->m_Reader.clear();

	this->m_Index = 1;

}

//����ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
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
//��ǩ
void SpeechManager::speechDraw()
{
	cout << "��" << this->m_Index << "�ֱ������ڽ�����" << endl;
	cout << "-----------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

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
//��ʼ����
void SpeechManager::startSpeech()
{
	//    ��һ�ֱ���
	// 1.��ǩ
	   this->speechDraw();
	//	  2.����
	   speechContest();
	//	  3.��ʾ�������
	   this->showScore();

	//	  �ڶ��ֱ���
	//	  1.��ǩ
	   this->m_Index++;
	   this->speechDraw();
	//	  2.����
	   speechContest();

	//	  3.��ʾ�������
	   this->showScore();
	//    4.����������ļ���
	   this->saveScore();
	   this->initSpeech();
	   this->createSpeaker();
	   this->ReadFile();
	   cout << "�����������" << endl;
	   system("pause");
	   system("cls");
}
//������ʼ
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
		//��ӡƽ����
		//cout << "��ţ�" << *it << "������" << this->m_Speaker[*it].m_name << "ƽ���֣�" << avg << endl;
		this->m_Speaker[*it].m_Score [this->m_Index-1]= avg;
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��÷����£�" << endl;
				for(multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
				{
					cout << "���:" << it->second << "����:" << this->m_Speaker[it->second].m_name
						<< "�ɼ�:" << it->first<<endl;
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
	cout << "��" << this->m_Index << "�ֱ�������"<<endl;
	system("pause");
}
//�ɼ���ʾ
void SpeechManager::showScore()
{
	cout << "��" << this->m_Index << "�ֽ���ѡ����Ϣ����" << endl;
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
		cout << "��ţ�" << *it << "������" << this->m_Speaker[*it].m_name 
			<<"�÷֣�"<<this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
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
	cout << "��¼�ѱ���" << endl;
	this->fileIsEmpty = false;
}



//��ȡ�ļ�
void SpeechManager::ReadFile()
{
	ifstream ifs("speech.csv", ios::in);

	if(!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�Ϊ��" << endl;
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
//��ʾ�ļ���Ϣ
void SpeechManager:: ShowFile()
{
	if (this->fileIsEmpty)
	{
		cout << "�������¼" << endl;

	}
	else
	{
		for (map<int, vector<string>>::iterator it = this->m_Reader.begin(); it != this->m_Reader.end(); it++)
		{
			cout << "��" << it->first << "�����������£�" << endl;

			cout << "�ھ���ţ�" << it->second[0] << " " << "�ھ�����:" << it->second[1] << "  " << "�ھ�������" << it->second[2] << endl;
			cout << "������ţ�" << it->second[3] << " " << "��������:" << it->second[4] << "  " << "����������" << it->second[5] << endl;
			cout << "�Ǿ���ţ�" << it->second[6] << " " << "�Ǿ�����:" << it->second[7] << "  " << "�Ǿ�������" << it->second[8] << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ļ���Ϣ
void SpeechManager::ClearFile()
{
	cout << "����ȷ���Ƿ����������Ϣ��" << endl;
	cout << "1-ȷ��" << endl;
	cout << "2-ȡ��" << endl;
	int chose;
	cin >> chose;
	if (chose == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeaker();
		this->ReadFile();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager()
{


}
