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
	// 建立全局词表idf,传入参数为文件名
	vector<WordIDF> BuildGlobalIDF(string file_name);
	//将idf词表写出到文件中
	//word_frequency 存放的是词表：词语（string） idf值(double)
	// file_name 输出文件名称
	void Print(vector<WordIDF> word_frequency, string file_name);
	// 词的idf统计,根据情感态度类别的不同统计每个类别的词的idf分布
	// sentences里存放的是待统计的所有句子；
	// type是情感态度的类别，可以为"0" "1" "-1"
	vector<WordIDF> CalculateIDFSentiment(vector<string> sentences, string type);
	// 词的idf统计，统计subject中的
	// sentences里存放的是待统计的所有句子；
	// type是情感态度的类别，取值范围为0--9，
	// 代表动力、价格、内饰、配置、安全性、外观、操控、油耗、空间、舒适性十大类别
	vector<WordIDF> CalculateIDFSubject(vector<string> sentences, int type);
	// 词频选择排序
	void SelectSort(vector<WordIDF> &word_idf);
	// 词频快速排序
	void QuickSort(vector<WordIDF> &word_idf, int begin, int end);
	//计算不同情感态度所具有的各特征词
	// 结果暂时直接写入文件中
	void CalSentimentFeature();
	//计算不同主题所具有的各特征词
	// 结果暂时直接写入文件中
	// file_names	存放不同主题里面的所有词的文档名
	void CalSubjectFeature(vector<string> file_names);
	// 建立各类别统一的词表，便于比较计算相似度
	void BuildAllCategoryWordTable();
};

#endif