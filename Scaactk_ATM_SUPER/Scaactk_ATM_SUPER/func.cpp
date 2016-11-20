#include"func.h"
#include"scaactk.h"
#include<iostream>
//#include<cstdlib>
#include<fstream>
#include<iomanip>
#include<cstdio>
#include<string>
#include<time.h>
#include<Windows.h>

using std::cin;
using std::fstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;
using std::ifstream;

func::func(User& _user) :user(_user) {

}

void func::Welcome() {
	while (1) {//�����ظ�����˽���
		int choose;
		system("cls");//����
		ATM::firstlogo();//����
		cout << "\t\t\t\t\t";
		cin >> choose;
		if (choose == 1) {
			Sign_Up();
		}
		else if (choose == 2) {
			Sign_In();
		}
		else if (choose == 3) {
			system("pause");
			exit(0);//�����˳�����
		}
	}
}

//ע��
void func::Sign_Up() {
	User user1;
	system("cls");
	cout << "Please input the name: " << endl;
	cin >> user1.name;
	system("cls");
	cout << "Please input your ID(six number): " << endl;
	cin >> user1.id;
	system("cls");
	if (Scaactk::Check_ID(user1.id)) {//���ID�Ƿ��ظ�
		//system("cls");
		cout << "Please input the passwords:" << endl;
		user1.pw = Scaactk::Get_Passwords();
		system("cls");
		cout << "Please input the passwords again:" << endl;
		int temp_pw = Scaactk::Get_Passwords();
		if (Scaactk::Compare(user1.pw, temp_pw)) {//������������Ƿ�ƥ��
			system("cls");
			cout << "How much money do you want to deposit first: " << endl;
			cin >> user1.Mon;
			if (Scaactk::Check_Mon(user1.Mon)) {
				fstream append("sql.txt", std::ios::out | std::ios::app);
				if (append.fail()) {
					std::cerr << "FAIL_TO_OPEN";
					system("pause");
					return;
				}
				else {
					system("cls");
					cout << std::flush;//ˢ��stdin
					append << user1.name << " " << user1.id << " " << user1.pw << " " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << user1.Mon << " " << 0 << endl;//����ʱ�ļ���д��ָ����
					//cout << user1.name << " " << user1.id << " " << user1.pw << " " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << user1.Mon << " " << 0 << endl;//����
					cout << "This User has been build!" << endl;
					append.close();

					//��¼����
					string rec = Scaactk::Int_To_String(user1.id);
					time_t nowtime;
					nowtime = time(NULL);
					ofstream record(rec.c_str(), std::ios::out|std::ios::app);
					record << user1.name << " " << nowtime << " sign up" << endl;
					record.close();

					system("pause");
					return;
				}
			}
		}
		else {
			cerr << "Two passwords do not match!" << endl;
			system("pause");
			return;
		}
	}
	cerr << "Fail to sign up!" << endl;
	system("pause");
	return;
}

//��¼
void func::Sign_In() {
	system("cls");
	user.id = Scaactk::Get_ID();
	if (!Get_Info(user)) {//ƥ��ID
		system("pause");
		return;
	}

	Check_Passwords(user);//�������

	cout << "\nLogin in successed!" << endl;\

	//��¼����
	string rec = Scaactk::Int_To_String(user.id);
	time_t nowtime;
	nowtime = time(NULL);
	fstream record(rec.c_str(), std::ios::out|std::ios::app);
	record << user.name << " " << nowtime << " SIGN IN" << endl;
	record.close();

	system("pause");
	while (1) {
		ATM::secondlogo();//���빦��ѡ�����
		int choose;
		cin >> choose;
		system("cls");
		if (choose == 1) {
			Fetch_Money(user);
		}
		if (choose == 2) {
			Deposit_Money(user);
		}
		if (choose == 3) {
			Transfer_Money(user);
		}
		if (choose == 4) {
			Change_Passwords(user);
		}
		if (choose == 5) {
			Check_Information(user);
		}
		if (choose == 6) {
			Print_Record(user);
		}
		if (choose == 7) {
			return;
		}
	}
}

//ȡ��
void func::Fetch_Money(User& _user) {
	system("cls");
	User& user = _user;
	cout << "Please input how much money do you wang to fetch: " << endl;
	int temp;
	cin >> temp;
	if (temp >= user.Mon) {
		cout << " Without enough money!" << endl;
		system("pause");
		return;
	}
	else if (temp < 0) {
		cout << "Wrong number!" << endl;
		system("pasuse");
		return;
	}
	else {
		user.Mon -= temp;
		Write_TXT(user);
		cout << "You have fetched :" << temp << endl;

		//��¼����
		string rec = Scaactk::Int_To_String(user.id);
		time_t nowtime;
		nowtime = time(NULL);
		fstream record(rec.c_str(), std::ios::out|std::ios::app);
		record << user.name << " " << nowtime << " Fetched " << temp << endl;
		record.close();

		system("pause");
		return;
	}
}

//���
void func::Deposit_Money(User& _user) {
	system("cls");
	User& user = _user;
	cout << "Please input how much money do you wang to draw: " << endl;
	int temp;
	cin >> temp;
	if (temp < 0) {
		cout << "Wrong number!" << endl;
		system("pasuse");
		return;
	}
	else {
		user.Mon += temp;
		Write_TXT(user);
		cout << "YOU have deposited : " << temp << endl;

		//��¼����
		string rec = Scaactk::Int_To_String(user.id);
		time_t nowtime;
		nowtime = time(NULL);
		fstream record(rec.c_str(), std::ios::out|std::ios::app);
		record << user.name << " " << nowtime << " Deposited " << temp << endl;
		record.close();

		system("pause");
		return;
	}
}

//ת��
void func::Transfer_Money(User& _user) {
	system("cls");
	User& user = _user;
	User user2;

	cout << "You try to transfer money!" << endl;
	user2.id = Scaactk::Get_ID();
	if (!Get_Info(user2)) {
		system("pause");
		return;
	}
	
	if (user2.id == user.id) {
		cerr<<"You cannot transfer to yourself!" << endl;
		system("pause");
		return;
	}

	cout << "How much money do you want to transfer:" << endl;
	int temp;
	cin >> temp;
	if (temp <= 0) {
		cerr << "Error money!" << endl;
		system("pause");
		return;
	}
	else if (temp > user.Mon) {
		cout << " Without enough money!" << endl;
		system("pause");
		return;
	}
	else {
		user.Mon -= temp;
		user2.Mon += temp;
		Write_TXT(user);
		Write_TXT(user2);
		cout << "Transfer successed!" << endl;
		cout << "You have transfered:" << temp << endl;

		//��¼����
		string rec = Scaactk::Int_To_String(user.id);
		time_t nowtime;
		nowtime = time(NULL);
		fstream record(rec.c_str(), std::ios::out|std::ios::app);
		record << user.name << " " << nowtime << " Transfered " << temp << " to " << user2.name << endl;
		record.close();

		system("pause");
		return;
	}
}

//����
void func::Change_Passwords(User& _user) {
	system("cls");
	User&user = _user;
	char temp1[7];
	char temp2[7];
	bool a = true;

	cout << "Please input the old passwords to confirm your identity!" << endl;
	Check_Passwords(user);//У�������

	cout << "\nPlease input the new passwords: " << endl;
	for (int i = 0; i < 6; i++) {
		temp1[i] = _getch();
		cout << "*";
	}
	_getch();

	cout << "\nInput the new passwords again:" << endl;
	for (int i = 0; i < 6; i++) {
		temp2[i] = _getch();
		cout << "*";
	}
	_getch();

	//���ƥ��
	for (int i = 0; i < 6; i++) {
		if (temp1[i] != temp2[i]) {
			a = false;
		}
	}
	if (!a) {
		cout << "Two passwords  do not match!" << endl;
		cout << "Fail to change the passwords!" << endl;
		system("pause");
		return;
	}
	else {
		int pin[6];
		int temp = 0;
		for (int i = 0; i < 6; i++) {
			temp *= 10;
			temp += pin[i];
		}
		if (temp == user.pw) {
			cerr << "The new passwords is similiar to the old one!" << endl;
			system("pause");
			return;
		}
		user.pw = temp;
		Write_TXT(user);
		cout << "Change passwords successed!" << endl;

		//��¼����
		string rec = Scaactk::Int_To_String(user.id);
		time_t nowtime;
		nowtime = time(NULL);
		fstream record(rec.c_str(), std::ios::out|std::ios::app);
		record << user.name << " " << nowtime << " Changed  the Passwords " << endl;
		record.close();

		system("pause");
		return;
	}
}

//�鿴��Ϣ
void func::Check_Information(User& _user) {
	User& user = _user;
	system("cls");
	cout << "\t\t\t\t Your information: " << endl;
	cout << "\t\t ID: " << user.id;
	cout << "\t\t\t\t Name: " << user.name;
	cout << "\t\t\t\t Money: " << user.Mon;
	system("pause");
	return;
}

//��ӡ��¼
void func::Print_Record(User& _user) {
	User& user = _user;
	string temp = Scaactk::Int_To_String(user.id);
	Scaactk::Print_Record(temp);
	system("pause");
	return;
}


//�����ϲ�
//void func::Return_Before() {
//	system("cls");
//	return;
//}



/*            ������ѡ����֮��ĵײ����                */

//����ID��Ӧ��Ϣ
int func::Get_Info(User& _user) {

	User& user = _user;
	string _name;
	int _id;
	int _pw;
	double _Mon;
	int _statue;

	ifstream infile("sql.txt", std::ios::in);
	if (infile.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}

	user.count = 0;
	while (infile) {
		infile >> _name >> _id >> _pw >> _Mon >> _statue;
		//cout << _name << '\t' << _id << '\t' << _pw << '\t' << _Mon << '\t' << _statue << endl;//�����ܷ�������ȡ
		user.count++;
		if (_id == user.id) {
			if (_statue == 1) {
				cerr << "Your account has been freazed!" << endl;
				return false;
			}
			user.name = _name;
			user.pw = _pw;
			user.Mon = _Mon;
			user.statue = _statue;
			cout << "The user is:" << " " << user.name << " " << user.id << endl;

			//count = infile.tellg();
			//cout << count << endl;
			//infile.seekg(count-count1, std::ios::cur);
			//count = infile.tellg();//��¼��һ�п�ͷ��λ��
			infile.close();
			return true;
		}
	}
	cerr << "Without this account!" << endl;
	infile.close();
	return false;
}

//�����û�����
int func::Write_TXT(User& _user) {
	User& user = _user;
	ifstream file("sql.txt", std::ios::in);
	ofstream outfile("sql2.txt", std::ios::out | std::ios::trunc);

	if (file.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}
	if (outfile.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}

	string line;
	int n = 1;
/*
�����и������ص�bug, file�ڶ�ȡ���ļ�ĩβ(EOF)��ʱ�򣬲�������������true,
�����ٶ�һ��,��ʱeofdbit�ű�����,
��������������bit,��goodbit,
���´ε���eofʱ�ŷ���true
Ҳ����˵,���������Ļ��з��ᱻ��ȡ����

��Ȼ֪���������ڣ��Ǿͺð���
*/
	while (getline(file, line)) {
		////�������֮һ,���һ���ж�,���Ǻ���ûʲôЧ��23333
		//if (file.fail()) {
		//	break;
		//}
		//getline(file, line);//��ȡsql��һ��
		if (n != user.count ) {
			outfile << line << endl;//����ָ���������һ����ʱ�ļ�sql2��ȥ
		}
		else if (n == user.count ) {
			outfile << user.name << " " << user.id << " " << user.pw << " " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << user.Mon << " " << user.statue << endl;//����ʱ�ļ���д��ָ����
			cout << std::flush;
		}
		n++;
	}
	outfile.close();
	file.close();

	ofstream outfile2("sql.txt", std::ios::out | std::ios::trunc);
	ifstream file2("sql2.txt", std::ios::in);
	if (file2.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}
	if (outfile2.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}

	while (getline(file2, line)) {
		//���������:ֱ����while���ж�
		outfile2 << line << endl;
	}
	outfile2.close();
	file2.close();
	system("del sql2.txt");//ɾ����ʱ�ļ�
	cout << endl << user.name << "'s DATA��UPDATED" << endl;
	return true;
}

//��������
int func::Check_Passwords(User& _user) {
	User& user = _user;
	for (int i = 0; i < 3; i++) {
		cout << "Please input the passwords:" << endl;
		int temp_pw = Scaactk::Get_Passwords();
		if (temp_pw != user.pw) {//ƥ������
			cout << "\nWrong Passwords!" << endl;
		}
		else {
			return true;
		}

		if (i == 2) {
			user.statue = 1;
			Write_TXT(user);
			cerr << "The account has been freezed!" << endl;

			//��¼����
			string rec = Scaactk::Int_To_String(user.id);
			time_t nowtime;
			nowtime = time(NULL);
			fstream record(rec.c_str(), std::ios::out);
			record << user.name << " " << nowtime << " Has been Freezed "  << endl;
			record.close();

			system("pause");
			exit(-1);
		}
	}
	return false;
}

//��¼����