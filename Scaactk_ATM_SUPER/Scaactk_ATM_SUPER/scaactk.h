#pragma once
#include<iostream>
#include<fstream>
#include<conio.h>
#include<cstdlib>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::cin;

namespace Scaactk {
	int Check_ID(int);
	int Get_Passwords();
	int Compare(int, int);
	int Check_Mon(double);
	//int Append_User(User&);
	int Get_ID();
	//int Get_Info();
	void Print_Record(string);
	//void Record(string);
	string Int_To_String(int);
}

int Scaactk::Check_ID(int id) {
	string _name;
	int _id;
	int _pw;
	double _Mon;
	int _statue;

	ifstream infile("sql.txt", std::ios::in);
	if(infile.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}
	while (infile) {
		infile >> _name >> _id >> _pw >> _Mon >> _statue;//���ж�ȡ

		if (_id == id) {
			cerr << "This ID has been used!" << endl;
			infile.close();
			return false;
		}
	}
	cout << "This ID can be used!" << endl;
	infile.close();
	return true;
}

int Scaactk::Get_Passwords() {
	char pin[7];
	int temp = 0;
	for (int i = 0; i < 6; i++) {
		pin[i] = _getch();
		cout << "*";
		temp *= 10;
		temp += pin[i] - '0';
	}
	_getch();
	return temp;//����֮ǰ�����pw
}

int Scaactk::Compare(int t1, int t2) {
	if (t1 == t2) {
		return true;
	}
	else {
		return false;
	}
}

int Scaactk::Check_Mon(double m) {
	if (m < 0) {
		cerr << "Eroor Number!" << endl;
		return false;
	}
	else {
		return true;
	}
}
 
int Scaactk::Get_ID() {
	int _inid;
	cout << "Please input ID:" << endl;
	cin >> _inid;
	return _inid;
}

void Scaactk::Print_Record(string id) {
	ifstream record(id.c_str(), std::ios::in);
	//�����fstream ��������벻���Ĵ����Ʋ��ǻ���ͬʱ���ʺͶ�д�ĳ�ͻ
	string line;
	while (!record.eof()) {
		getline(record, line);
		std::cout << line << endl;
	}
	record.close();
}

string Scaactk::Int_To_String(int id) {
	char temp[100];
	_itoa_s(id, temp, 10);
	return (string)temp;
}