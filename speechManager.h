#pragma once
#include<iostream>
#include<vector>
using namespace std;
#include<map>
#include<algorithm>
#include<fstream>
#include<deque>
#include<functional>
#include<string>
#include<numeric>
#include "speaker.h"


//設計演講管理類
class SpeechManager {
public:
	//建構子
	SpeechManager();

	//展示菜單
	void show_Menu();

	//退出系統
	void exitSystem();

	//解構子
	~SpeechManager();

	//初始化容器和屬性
	void initSpeech();

	//創建12名選手
	void createSpeaker();

	//開始比賽 比賽整個流程控制函數
	void startSpeech();

	//抽籤
	void speechDraw();

	//比賽
	void speechContest();

	//顯示得分
	void showScore();

	//保存紀錄
	void saveRecord();

	//讀取紀錄
	void loadRecord();

	//判斷文建是否為空
	bool fileIsEmpty;

	//存放往屆紀錄得容器
	map<int, vector<string>>m_Record;

	//顯示往屆紀錄
	void showRecord();

	//清空文件
	void clearRecord();

	//成員屬性
	//保存第一輪選手編號
	vector<int> v1;

	//第一輪競級選手編號容器
	vector<int> v2;

	//勝出前三名
	vector<int>vVictory;

	//存放編號以及對應具體選手容器
	map<int, Speaker>m_Speaker;

	//存取比賽輪數
	int m_Index;

	

};


