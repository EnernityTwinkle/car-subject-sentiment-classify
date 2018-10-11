// Copyright 2018 YH
// License(GPL)
// Author: YH
// This is calculate word table.
#ifndef BUILD_WORD_TABLE_H_
#define BUILD_WORD_TABLE_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

struct WordIDF {			// Storage word and it's idf
	string word;
	double idf;
};

class WordTable {
public:
	// ����ȫ�ִʱ�idf,�������Ϊ�ļ���
	vector<WordIDF> BuildGlobalIDF(string file_name);
	//��idf�ʱ�д�����ļ���
	//word_frequency ��ŵ��Ǵʱ����string�� idfֵ(double)
	// file_name ����ļ�����
	void Print(vector<WordIDF> word_frequency, string file_name);
	// �ʵ�idfͳ��,�������̬�����Ĳ�ͬͳ��ÿ�����Ĵʵ�idf�ֲ�
	// sentences���ŵ��Ǵ�ͳ�Ƶ����о��ӣ�
	// type�����̬�ȵ���𣬿���Ϊ"0" "1" "-1"
	vector<WordIDF> CalculateIDFSentiment(vector<string> sentences, string type);
	// �ʵ�idfͳ�ƣ�ͳ��subject�е�
	// sentences���ŵ��Ǵ�ͳ�Ƶ����о��ӣ�
	// type�����̬�ȵ����ȡֵ��ΧΪ0--9��
	// ���������۸����Ρ����á���ȫ�ԡ���ۡ��ٿء��ͺġ��ռ䡢������ʮ�����
	vector<WordIDF> CalculateIDFSubject(vector<string> sentences, int type);
	// ��Ƶѡ������
	void SelectSort(vector<WordIDF> &word_idf);
	// ��Ƶ��������
	void QuickSort(vector<WordIDF> &word_idf, int begin, int end);
	//���㲻ͬ���̬�������еĸ�������
	// �����ʱֱ��д���ļ���
	void CalSentimentFeature();
	//���㲻ͬ���������еĸ�������
	// �����ʱֱ��д���ļ���
	// file_names	��Ų�ͬ������������дʵ��ĵ���
	void CalSubjectFeature(vector<string> file_names);
	// ���������ͳһ�Ĵʱ����ڱȽϼ������ƶ�
	void BuildAllCategoryWordTable();
};

#endif