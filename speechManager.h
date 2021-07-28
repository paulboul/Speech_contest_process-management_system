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


//�]�p�t���޲z��
class SpeechManager {
public:
	//�غc�l
	SpeechManager();

	//�i�ܵ��
	void show_Menu();

	//�h�X�t��
	void exitSystem();

	//�Ѻc�l
	~SpeechManager();

	//��l�Ʈe���M�ݩ�
	void initSpeech();

	//�Ы�12�W���
	void createSpeaker();

	//�}�l���� ���ɾ�Ӭy�{������
	void startSpeech();

	//����
	void speechDraw();

	//����
	void speechContest();

	//��ܱo��
	void showScore();

	//�O�s����
	void saveRecord();

	//Ū������
	void loadRecord();

	//�P�_��جO�_����
	bool fileIsEmpty;

	//�s�񩹩������o�e��
	map<int, vector<string>>m_Record;

	//��ܩ�������
	void showRecord();

	//�M�Ť��
	void clearRecord();

	//�����ݩ�
	//�O�s�Ĥ@�����s��
	vector<int> v1;

	//�Ĥ@���v�ſ��s���e��
	vector<int> v2;

	//�ӥX�e�T�W
	vector<int>vVictory;

	//�s��s���H�ι���������e��
	map<int, Speaker>m_Speaker;

	//�s�����ɽ���
	int m_Index;

	

};


