#pragma once
#ifndef SEXCHOOSE_H
#define SEXCHOOSE_H

class Sex {
private:
	int gender1 = 0, gender2 = 0;
public:
	Sex();
	int gender1_L, gender1_R, gender1_U, gender1_D;//�Ա�һ����ͼ���귶Χ
	int gender2_L, gender2_R, gender2_U, gender2_D;//�Ա������ͼ���귶Χ
	int check_L, check_R, check_U, check_D;//ȷ����ť����ͼ���귶Χ
	void sexChoose();//ѡ��ͼ
	void userclick();//ʶ�����������û��������Ա�ѡ�˹���ȫ��1
	int checktwice();//��ȷ��
	void Print();
};
#endif