#include<iostream>

using namespace std;
#include "speechManager.h"
int main() {

	//�H���ƺؤl
	srand((unsigned)time(NULL));

	//�Ыغ޲z��H
	SpeechManager sm;
	//����12�W���Ы�
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "���s��: " << it->first << " �m�W: " << it->second.m_Name << " ����: " << it->second.m_Score[0] << endl;

	}*/

	int choice = 0;//�s���Τ��J

	while (true) {

		sm.show_Menu();

		cout << "�п�J�A�����:" << endl;
		cin >> choice;

		switch (choice) {

		case 1://�}�l�t������
			sm.startSpeech();

			break;
		case 2://�d�ݩ�������
			sm.showRecord();

			break;
		case 3://�M�Ť��ɬ���
			sm.clearRecord();
			break;

		case 0://�h�X�t��
			sm.exitSystem();
			break;
		default:
			break;



		}




	}
	




	return 0;
}