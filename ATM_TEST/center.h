#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<conio.h>
#include<iomanip>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

class User;

class ATM {
private:

public:
	ATM();

	~ATM();

	void getID(User&);

	int getInfo(User&);//检索该用户的信息

	int getPasswd();

	int checkPasswd(User&);

	int writeTxt(User&);

	void menu(User&);

	void changePasswd(User&);

	void fetchMoney(User&);

	void drawMoney(User&);

	void transfer(User&);

	int Exit() {
		exit(0);
	}
};

class User {
private:
	string name;
	int id;
	int pw;
	double Mon;
	int statue;
public:
	User();
	int count;
	friend class ATM;
};

ATM::ATM(){//ATM构造函数
}
ATM::~ATM() {//ATM析构函数

}

User::User() {//User构造函数
}

void ATM::getID(User& x) {
	User&user = x;
	int _inid;
	cout << "Please input ID:" << endl;
	cin >> _inid;
	user.id = _inid;//将输入的_inid暂时赋值给实例的id
}

int ATM::getInfo(User& x) {
	User& user = x;
	string _name;
	int _id;
	int _pw;
	double _Mon;
	int _statue;

	ifstream infile("sql.txt", std::ios::in,std::ios::binary);
	if (infile.fail()) {
		std::cerr << "FAIL_TO_OPEN";
		return -1;
	}

	user.count = 0;
	while (infile) {
		infile >> _name >> _id >> _pw >> _Mon >> _statue;
		//cout << _name << '\t' << _id << '\t' << _pw << '\t' << _Mon << '\t' << _statue << endl;//测试能否正常读取
		user.count++;
		if (_id == user.id) {
			user.name = _name;
			user.pw = _pw;
			user.Mon = _Mon;
			user.statue = _statue;
			cout << "The user is:" <<" "<< user.name << " " << user.id << endl;

			//count = infile.tellg();
			//cout << count << endl;
			//infile.seekg(count-count1, std::ios::cur);
			//count = infile.tellg();//记录这一行开头的位置
			infile.close();
			return 1;
		}
	}
	cerr << "Without this account!" << endl;
	system("pause");
	infile.close();
	exit(-1);
}

int ATM::getPasswd() {
	char pin[6];
	int temp = 0;
	cout << "Please input the password:" << endl;
	for (int i = 0; i < 6; i++) {
		pin[i] = _getch();
		cout << "*";
		temp *= 10;
		temp += pin[i] - '0';
	}
	_getch();
	 return temp;//返回之前输入的pw
}

int ATM::checkPasswd(User& x) {
	User&user = x;
	for (int i = 0; i < 3; i++) {
		int _pw = getPasswd();

		if (_pw == user.pw) {
			cout << "\nLogin successed!" << endl;
			return 0;
		}
		else if(i<2){
			cout << "\nWrong password! Try to input again." << endl;
		}
	}
	std::cerr << "Your account has been freazed!" << endl;
	user.statue = 1;
	writeTxt(x);
	exit(1);
}

int ATM::writeTxt(User& x) {
	User& user = x;
	fstream file("sql.txt",std::ios::in);
	ofstream outfile("sql2.txt",std::ios::out|std::ios::trunc);

	if (file.fail()) {
		std::cerr << "FAIL_TO_OPEN";
		return -1;
	}
	if (outfile.fail()) {
		std::cerr << "FAIL_TO_OPEN";
		return -1;
	}

	string line;
	int n = 0;
	while (!file.eof()) {
		getline(file, line);//读取sql中一行
		if (n != user.count - 1) {
			outfile << line << endl;//将非指定行输出到一个临时文件中去
		}
		else if (n == user.count - 1) {
			outfile << user.name << " " << user.id << " " << user.pw << " " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << user.Mon << " " << user.statue << endl;//向临时文件中写入指定行
		}
		n++;
	}
	outfile.close();
	file.close();

	ofstream outfile2("sql.txt", std::ios::out | std::ios::trunc);
	fstream file1("sql2.txt",std::ios::in);
	if (file1.fail()) {
		std::cerr << "FAIL_TO_OPEN";
		return -1;
	}
	if (outfile2.fail()) {
		std::cerr << "FAIL_TO_OPEN";
		return -1;
	}
	
	while (!file1.eof()) {
		getline(file1, line);
		outfile2 << line << endl;
	}
	outfile2.close();
	file1.close();
	system("del sql2.txt");
	cout << user.id<<"'s DATA＿UPDATED" << endl;
}

void ATM::changePasswd(User& x) {
	User&user = x;
	char temp1[6];
	char temp2[6];
	bool a = true;
	cout << "Please input the new passwords: " << endl;
	for (int i = 0; i < 6; i++) {
		temp1[i] = _getch();
		cout << "*";
	}
	_getch();

	cout << "Input the new passwords again:" << endl;
	for (int i = 0; i < 6; i++) {
		temp2[i] = _getch();
		cout << "*";
	}
	_getch();

	//检查匹配
	for (int i = 0; i < 6; i++) {
		if (temp1[i] != temp2[i]) {
			a = false;
		}
	}
	if (!a) {
		cout << "Two passwords  do not match!" << endl;
		cout << "Fail to change the passwords!" << endl;
	}
	else {
		int pin[6];
		int temp = 0;
		for (int i = 0; i < 6; i++) {
			temp *= 10;
			temp += pin[i];
		}
		user.pw = temp;
		writeTxt(user);
		cout << "Change passwords successed!" << endl;
	}
	menu(user);
}

void ATM::fetchMoney(User& x) {
	User&user = x;
	cout << "Please input how much money do you wang to fetch: ";
	int temp;
	cin >> temp;
	if (temp > user.Mon) {
		cout << " Without enough money!" << endl;
	}
	else {
		user.Mon -= temp;
	}
	writeTxt(user);
	cout << "YOU have fetch: " << temp << endl;
	menu(user);
}

void ATM::drawMoney(User& x) {
	User&user = x;
	cout << "Please input how much money do you wang to draw: " << endl;
	int temp;
	cin >> temp;
	user.Mon += temp;
	writeTxt(user);
	cout << "YOU have withdraw: " << temp << endl;
	menu(user);
}

void ATM::transfer(User& x) {
	User&user = x;
	User user2;
	cout << "Try to transfer money!" << endl;
	getID(user2);
	getInfo(user2);
	
	cout << "How much money do you want to transfer:" << endl;
	int temp;
	cin >> temp;
	if (temp > user.Mon) {
		cout << " Without enough money!" << endl;
	}
	else {
		user.Mon -= temp;
		user2.Mon += temp;
		writeTxt(user);
		writeTxt(user2);
		cout << "Transfer successed!" << endl;
	}
	menu(user);
}

void ATM::menu(User& x) {
	User&user = x;
	cout << "What do you want to do next ?" << endl;
	cout << "a -> changePasswd;\t b-> drawMoney;\n c-> fetchMoney; \t d->exit;\n e->tranfer;\n";
	char a;
	cin >> a;
	switch (a) {
	case 'a':
		changePasswd(user);
	case 'b':
		drawMoney(user);
	case 'c':
		fetchMoney(user);
	case 'd':
		Exit();
	case 'e':
		transfer(user);
	}
}