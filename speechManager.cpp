#include "speechManager.h"
//�غc�l
SpeechManager::SpeechManager() {

	//��l�Ʈe���M�ݩ�
	this->initSpeech();

	//�Ы�12�W���
	this->createSpeaker();


	//�[����������
	this->loadRecord();
}
//�i�ܵ��
void SpeechManager::show_Menu() {
	cout << "*******************************************" << endl;
	cout << "**************�w��ѥ[�t������*************" << endl;
	cout << "**************1.�}�l�t������***************" << endl;
	cout << "**************2.�d�ݩ�������***************" << endl;
	cout << "**************3.�M�Ť��ɬ���***************" << endl;
	cout << "**************0.�h�X���ɵ{��***************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}
//�h�X�t��
void  SpeechManager::exitSystem() {

	cout << "�w��U���ϥ�" << endl;
	system("pause");
	exit(0);
}
//��l�Ʈe���M�ݩ�
void  SpeechManager::initSpeech() {
	//�e�����m��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//��l�Ƥ��ɽ���
	this->m_Index = 1;

	//�N�����e���M��
	this->m_Record.clear();

}
//�Ы�12�W���
void  SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "���";
		name += nameSeed[i];

		//�Ыب�����
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		//�Ыؿ��s���A�åB��J��v1�e����
		this->v1.push_back(i + 10001);

		//���s���H�ι������A��Jmap�e����
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}

}
//�}�l���� ���ɾ�Ӭy�{������
void SpeechManager::startSpeech() {
	//�Ĥ@���}�l����

	//1.����
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ܮʯŵ��G
	this->showScore();
	//�ĤG���}�l����
	this->m_Index++;
	//1.����
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��̲ܳ׵��G
	this->showScore();

	//���m���ɡA�������
	//4.�O�s���ƨ���
	this->saveRecord();

	//��l�Ʈe���M�ݩ�
	this->initSpeech();

	//�Ы�12�W���
	this->createSpeaker();


	//�[����������
	this->loadRecord();



	cout << "�������ɧ���" << endl;
	system("pause");
	system("cls");
}
//����
void SpeechManager::speechDraw() {
	cout << "��<<" << this->m_Index << ">>�����ɿ�⥿�b����" << endl;
	cout << "----------------------------------" << endl;
	cout << "���ҫ�t�����Ǧp�U: " << endl;

	if (this->m_Index == 1) {
		//�Ĥ@������
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;

	}
	else {
		//�ĤG������
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
//����
void SpeechManager::speechContest() {
	cout << "--------------��" << this->m_Index << " �����ɥ����}�l----------------" << endl;

	//�ǳ��{�ɮe�� �s��p�զ��Z
	multimap<double, int, greater<double>> groupScore;

	int num = 0;//�����H��6�H�@��

	vector<int>v_Src;//���ɤH�����e��

	if (this->m_Index == 1) {
		v_Src = v1;

	}
	else {
		v_Src = v2;

	}

	//�M���Ҧ����i�����
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {

		num++;

		//���e����
		deque<double> d;
		for (int i = 0; i < 10; i++) {

			double score = (rand() % 401 + 600) / 10.f; //600~1000
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());//�Ƨǭ��Ǥ���
		d.pop_front();//�h���̰���
		d.pop_back();//�h���̧C��

		double sum = accumulate(d.begin(), d.end(), 0.0f);//�[�`����
		double avg = sum / (double)d.size();//������

		//���L������
		//cout << "�s��: " << *it << " �m�W: " << this->m_Speaker[*it].m_Name << "  ������: " << avg << endl;
	

		//�N��������J��map�e����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//�N�����ƾ� ��J���{�ɤp�ծe����
		groupScore.insert(make_pair(avg, *it));//key�O�o���Avalue�O���s��
		//�C���H���X�e3�W
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "�p�դ��ɦW��" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {

				cout << "�s��: " << it->second << " �m�W: " << this->m_Speaker[it->second].m_Name << " ���Z: "
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;

			}
			//�����e�T�W
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
	cout << "--------------------��" << this->m_Index << "�����ɧ���-------------------" << endl;
	system("pause");

}
//��ܱo��
void SpeechManager::showScore() {
	cout << "---------------------��" << this->m_Index << "���ʯſ��H���p�U:---------------------" << endl;

	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "���s��: " << *it << " �m�W: " << this->m_Speaker[*it].m_Name << " �o��: " <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();


}
void SpeechManager::saveRecord() {

	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//�ΰl�[�覡�g���

	//�N�C�ӿ��ƾڼg�J����
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//����
	ofs.close();
	cout << "�����w�g�O�s" << endl;

	//����󤣬��ŤF
	this->fileIsEmpty = false;


}
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);//Ū���

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "��󤣦s�b" << endl;
		ifs.close();
		return;
	}
	

	//���M�Ū��p
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "��󬰪�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	///��󤣬���
	this->fileIsEmpty = false;
	ifs.putback(ch);//�N�W��Ū������Ӧr�ũ�^��

	string data;
	int index = 0;

	while (ifs>>data) {
		//cout << data;

		vector<string>v;//�s��6��string�r��
		v.clear();
		int pos = -1;//�d��"�A"��m���ܶq
		int start = 0;


		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//�S����챡�p
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

		cout << it->first << "�a�x�s��: " << it->second[0] << " ����: " << it->second[0] << endl;
		
	}*/
	

}
//��ܩ�������
void SpeechManager::showRecord() {

	if (this->fileIsEmpty) {
		cout << "��󬰪ũΤ�󤣦s�b" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "��" << i + 1 << "��" << " �a�x�s��: " << this->m_Record[i][0] << " �o��: " << this->m_Record[i][1] << " "
				<< " �ȭx�s��: " << this->m_Record[i][2] << " �o��: " << this->m_Record[i][3] << " "
				<< " �u�x�s��: " << this->m_Record[i][4] << " �o��: " << this->m_Record[i][5] << endl;
		}
	}


	system("pause");
	system("cls");
}
//�M�Ť��
void SpeechManager::clearRecord() {
	
	cout << "�O�_�T�w�M�Ť��?" << endl;
	cout << "1. �O" << endl;
	cout << "2. �_" << endl;
	int select = 0;

	cin >> select;

	if (select == 1) {
		//�T�{�M��
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��l�Ʈe���M�ݩ�
		this->initSpeech();

		//�Ы�12�W���
		this->createSpeaker();


		//�[����������
		this->loadRecord();

		cout << "�M�Ŧ��\" << endl;
	}

	system("pause");
	system("cls");
}
//�Ѻc�l
SpeechManager::~SpeechManager() {

}