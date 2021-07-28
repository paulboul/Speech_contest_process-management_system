#include "speechManager.h"
//建構子
SpeechManager::SpeechManager() {

	//初始化容器和屬性
	this->initSpeech();

	//創建12名選手
	this->createSpeaker();


	//加載往屆紀錄
	this->loadRecord();
}
//展示菜單
void SpeechManager::show_Menu() {
	cout << "*******************************************" << endl;
	cout << "**************歡迎參加演講比賽*************" << endl;
	cout << "**************1.開始演講比賽***************" << endl;
	cout << "**************2.查看往屆紀錄***************" << endl;
	cout << "**************3.清空比賽紀錄***************" << endl;
	cout << "**************0.退出比賽程序***************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}
//退出系統
void  SpeechManager::exitSystem() {

	cout << "歡迎下次使用" << endl;
	system("pause");
	exit(0);
}
//初始化容器和屬性
void  SpeechManager::initSpeech() {
	//容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比賽輪數
	this->m_Index = 1;

	//將紀錄容器清空
	this->m_Record.clear();

}
//創建12名選手
void  SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "選手";
		name += nameSeed[i];

		//創建具體選手
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		//創建選手編號，並且放入到v1容器中
		this->v1.push_back(i + 10001);

		//選手編號以及對應選手，放入map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}

}
//開始比賽 比賽整個流程控制函數
void SpeechManager::startSpeech() {
	//第一輪開始比賽

	//1.抽籤
	this->speechDraw();
	//2.比賽
	this->speechContest();
	//3.顯示晉級結果
	this->showScore();
	//第二輪開始比賽
	this->m_Index++;
	//1.抽籤
	this->speechDraw();
	//2.比賽
	this->speechContest();
	//3.顯示最終結果
	this->showScore();

	//重置比賽，獲取紀錄
	//4.保存分數到文件中
	this->saveRecord();

	//初始化容器和屬性
	this->initSpeech();

	//創建12名選手
	this->createSpeaker();


	//加載往屆紀錄
	this->loadRecord();



	cout << "本屆比賽完畢" << endl;
	system("pause");
	system("cls");
}
//抽籤
void SpeechManager::speechDraw() {
	cout << "第<<" << this->m_Index << ">>輪比賽選手正在抽籤" << endl;
	cout << "----------------------------------" << endl;
	cout << "抽籤後演講順序如下: " << endl;

	if (this->m_Index == 1) {
		//第一輪比賽
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;

	}
	else {
		//第二輪比賽
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;

	}

	cout << "----------------------------------" << endl;
	system("pause");
	cout << endl;


}
//比賽
void SpeechManager::speechContest() {
	cout << "--------------第" << this->m_Index << " 輪比賽正式開始----------------" << endl;

	//準備臨時容器 存放小組成績
	multimap<double, int, greater<double>> groupScore;

	int num = 0;//紀錄人員6人一組

	vector<int>v_Src;//比賽人員的容器

	if (this->m_Index == 1) {
		v_Src = v1;

	}
	else {
		v_Src = v2;

	}

	//遍歷所有選手進行比賽
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {

		num++;

		//評委打分
		deque<double> d;
		for (int i = 0; i < 10; i++) {

			double score = (rand() % 401 + 600) / 10.f; //600~1000
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());//排序降序分數
		d.pop_front();//去除最高分
		d.pop_back();//去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//加總分數
		double avg = sum / (double)d.size();//平均分

		//打印平均分
		//cout << "編號: " << *it << " 姓名: " << this->m_Speaker[*it].m_Name << "  平均分: " << avg << endl;
	

		//將平均分放入到map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//將打分數據 放入到臨時小組容器中
		groupScore.insert(make_pair(avg, *it));//key是得分，value是選手編號
		//每六人取出前3名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小組比賽名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {

				cout << "編號: " << it->second << " 姓名: " << this->m_Speaker[it->second].m_Name << " 成績: "
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;

			}
			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {

				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}

			}
			groupScore.clear();
			cout << endl;

		}

	}
	cout << "--------------------第" << this->m_Index << "輪比賽完畢-------------------" << endl;
	system("pause");

}
//顯示得分
void SpeechManager::showScore() {
	cout << "---------------------第" << this->m_Index << "輪晉級選手信息如下:---------------------" << endl;

	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "選手編號: " << *it << " 姓名: " << this->m_Speaker[*it].m_Name << " 得分: " <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();


}
void SpeechManager::saveRecord() {

	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用追加方式寫文件

	//將每個選手數據寫入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//關閉
	ofs.close();
	cout << "紀錄已經保存" << endl;

	//更改文件不為空了
	this->fileIsEmpty = false;


}
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);//讀文件

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	

	//文件清空狀況
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件為空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	///文件不為空
	this->fileIsEmpty = false;
	ifs.putback(ch);//將上面讀取的單個字符放回來

	string data;
	int index = 0;

	while (ifs>>data) {
		//cout << data;

		vector<string>v;//存放6個string字串
		v.clear();
		int pos = -1;//查到"，"位置的變量
		int start = 0;


		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//沒有找到情況
				break;

			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;

		}

		this->m_Record.insert(make_pair(index, v));
		index++;
		
	}

	ifs.close();
	
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {

		cout << it->first << "冠軍編號: " << it->second[0] << " 分數: " << it->second[0] << endl;
		
	}*/
	

}
//顯示往屆紀錄
void SpeechManager::showRecord() {

	if (this->fileIsEmpty) {
		cout << "文件為空或文件不存在" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "第" << i + 1 << "屆" << " 冠軍編號: " << this->m_Record[i][0] << " 得分: " << this->m_Record[i][1] << " "
				<< " 亞軍編號: " << this->m_Record[i][2] << " 得分: " << this->m_Record[i][3] << " "
				<< " 季軍編號: " << this->m_Record[i][4] << " 得分: " << this->m_Record[i][5] << endl;
		}
	}


	system("pause");
	system("cls");
}
//清空文件
void SpeechManager::clearRecord() {
	
	cout << "是否確定清空文件?" << endl;
	cout << "1. 是" << endl;
	cout << "2. 否" << endl;
	int select = 0;

	cin >> select;

	if (select == 1) {
		//確認清空
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和屬性
		this->initSpeech();

		//創建12名選手
		this->createSpeaker();


		//加載往屆紀錄
		this->loadRecord();

		cout << "清空成功" << endl;
	}

	system("pause");
	system("cls");
}
//解構子
SpeechManager::~SpeechManager() {

}