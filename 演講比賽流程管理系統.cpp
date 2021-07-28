#include<iostream>

using namespace std;
#include "speechManager.h"
int main() {

	//隨機數種子
	srand((unsigned)time(NULL));

	//創建管理對象
	SpeechManager sm;
	//測試12名選手創建
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "選手編號: " << it->first << " 姓名: " << it->second.m_Name << " 分數: " << it->second.m_Score[0] << endl;

	}*/

	int choice = 0;//存取用戶輸入

	while (true) {

		sm.show_Menu();

		cout << "請輸入你的選擇:" << endl;
		cin >> choice;

		switch (choice) {

		case 1://開始演講比賽
			sm.startSpeech();

			break;
		case 2://查看往屆紀錄
			sm.showRecord();

			break;
		case 3://清空比賽紀錄
			sm.clearRecord();
			break;

		case 0://退出系統
			sm.exitSystem();
			break;
		default:
			break;



		}




	}
	




	return 0;
}