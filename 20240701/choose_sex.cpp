#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <conio.h>
#include "sexchoose.h"
//����߼���������ͼ��������һ����ͼ����ȷ����ť����Ӧ��gender����1�����������������߼�

Sex::Sex() {//initialize the position
	int genderHeight = 1;//С��ͼƬ�߶�
	int genderWidth = 1;//С��ͼƬ��ȣ�������Ҫ�����ֶ��޸�
	int checkWidth = 1;
	int checkHeight = 1;
	gender1_L = 1;//gender1x
	gender1_U = 1; // gender1y
	gender2_L = 1;
	gender2_U = 1;
	gender1_R = gender1_L + genderWidth;
	gender2_R = gender2_L + genderWidth;
	gender1_D = gender1_U + genderHeight;
	gender2_D = gender2_U + genderHeight;
	check_L = 1;//set by hand
	check_U = 1;//set by hand as well
	check_R = check_L + checkWidth;
	check_D = check_U + checkHeight;
}

void Sex::userclick() {
	float xx, yy;  
	while (!_kbhit()) { // ��û�а���������ʱ����ѭ��  
		POINT cursorPos; // ����POINT�ṹ�����ڴ洢�������  
		GetCursorPos(&cursorPos); // ��ȡ������Ļ����  
		xx = static_cast<float>(cursorPos.x);
		yy = static_cast<float>(cursorPos.y);
		Sleep(10);
	}
	if (xx > gender1_L && xx<gender1_R && yy >gender1_U && yy < gender1_D) {//�����������ͼ1��Χ��
		gender1 = 1;//ѡ���˵�һ���Ա�
		gender2 = 0;
	}
	else if (xx > gender2_L && xx<gender2_R && yy >gender2_U && yy < gender2_D) {//��ͼ2
		gender2 = 1;//ѡ���˵ڶ����Ա�
		gender1 = 0;
	}
}

int Sex::checktwice() {
	float xx, yy;
	while (!_kbhit()) { // ��û�а���������ʱ����ѭ��  
		POINT cursorPos; // ����POINT�ṹ�����ڴ洢�������  
		GetCursorPos(&cursorPos); // ��ȡ������Ļ����  
		xx = static_cast<float>(cursorPos.x);
		yy = static_cast<float>(cursorPos.y);
		Sleep(10);
	}
	if (xx > check_L && xx<check_R && yy >check_U && yy < check_D) {//�����������ͼ1��Χ��
		return true;
	}
}

void Sex::sexChoose() {
	while (1) {//һֱ��ȡ
		userclick();
		Print();
		if (Sex::checktwice()) {
			break;//�����Ա��ȡ
		}
	}
	//�������������߼�
}

void Sex::Print() {
	if (gender1 == 1) {
		//��ʾһ����д�š�male�����쵼дһ�°��Ҳ�֪����д�ĵ�
		//Ҳ����ʶ����ͣ��ʲô�ģ����õ�����ͼ��Ӧ��Ҳ���ԷŴ���Сʲô��
	}
	else if (gender2 == 1) {
		//ͬ��
	}
}

int main() {
	Sex s;
	s.sexChoose();
	return 0;
}