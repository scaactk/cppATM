#include<iostream>
#include"center.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	system("color AD");
	User A;
	ATM B;
	B.getID(A);
	B.getInfo(A);
	B.checkPasswd(A);
	system("ds");
	B.menu(A);
	system("pause");
}