#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>
#include<math.h>
#include "build_word_table.h"

using namespace std;

//划分训练集和测试集
void divide_train_test();
//将分好词的句子拆分成词
void cut_word( vector<string> content, vector<vector<string>> &content_word );
//计算词频tf，每一行存放一行中词语的tf
void calculate_tf( vector<vector<string>> content_word, vector< map<string,WordIDF> > &tf);
// 读取idf词表
void ReadIDFTable(vector<string> file_names, vector<map<string, double>> &idf_table);
//计算余弦相似度	与三个词表的
void calculate_cos( vector< map<string, WordIDF> > tf, vector<map<string,double>> idf, string out_name);
//计算余弦相似度 训练集 subject	与多个词表+重点词
void calculate_cos_keys( vector< map<string, WordIDF> > tf, vector<map<string,double>> idf, string out_name);
//计算余弦相似度,训练集	与三个词表的
void calculate_cos_train( vector< map<string, WordIDF> > tf, vector<map<string,double>> idf, string out_name);
//整合，将特征和向量结合
void combine();
void combine2();
//测试集里面的整合
void combine3();
// 测试集里面的整合主题
void CombinePredictSubject();
//得到结果
void GetResult();
//总流程
void test();
// 计算情感词表
void CalSentimentTable();
// 计算主题词表
void CalSubjectTable();
// 计算训练情感的向量
void CalTrainSentiment();
// 计算训练主题的向量
void CalTrainSubject();
// 计算测试情感的向量
void CalPredictSentiment();
// 计算测试主题的向量
void CalPredictSubject();
int main() {
	//divide_train_test();
	string global_name = "D:\\CCF\\train\\segment_train";
	WordTable word_table;
	vector<WordIDF> word_frequency;
	/*word_frequency = word_table.BuildGlobalIDF(global_name);
	word_table.QuickSort(word_frequency, 0, word_frequency.size() - 1);
	word_table.Print(word_frequency, "D:\\CCF\\train\\GlobalIDF");*/
	CalSentimentTable();				// 计算情感词表  基础表和keys
	CalSubjectTable();				// 计算主题词表  基础表和keys
	//word_table.BuildAllCategoryWordTable();
	//CalTrainSentiment();				// 计算训练情感的向量
	//CalTrainSubject();				// 计算训练主题的向量
	////combine();						//整合，将情感特征和向量结合,训练
	//combine2();						//整合，将主题特征和向量结合，训练
	////CalPredictSentiment();				// 计算测试情感的向量
	//CalPredictSubject();				// 计算测试主题的向量
	////combine3();							//测试集里面的整合情感
	//CombinePredictSubject();			//测试集里面的整合主题
	//GetResult();
	return 0;
}
//划分训练集和测试集
void divide_train_test() {
	ifstream in;
	string file_name = "D:\\CCF\\train\\train.csv";
	in.open(file_name);
	if(!in)
		cout<<"Open train.csv error"<<endl;
	ofstream out1;
	out1.open("D:\\train_defined");
	ofstream out2;
	out2.open("D:\\test_defined");
	string str;
	int i =0;
	while(getline(in, str)) {
		if(i % 4 == 0) {
			out2<<str<<endl;
		}
		else {
			out1<<str<<endl;
		}
		i++;
	}
	in.close();
	out1.close();
	out2.close();
}
// 计算情感词表
void CalSentimentTable() {
	string in_name = "D:\\CCF\\train\\segment_train";
	vector<string> file_names;
	file_names.push_back("D:\\CCF\\train\\idf_type0");
	file_names.push_back("D:\\CCF\\train\\idf_type1");
	file_names.push_back("D:\\CCF\\train\\idf_type-1");
	ifstream in;
	in.open(in_name);
	if(!in)
		cout<<"Open "<<in_name<<"error"<<endl;
	string str;
	vector<string> sentences;
	while(getline(in, str)) {
		sentences.push_back(str);
	}
	vector<string> types;
	types.push_back("0");
	types.push_back("1");
	types.push_back("-1");
	WordTable word_table;
	for(int i = 0; i < file_names.size(); i++) {
		vector<WordIDF> word_idf;
		word_idf = word_table.CalculateIDFSentiment(sentences, types[i]);						//构建idf表
		//word_idf = CalculateIDFSubject(sentences);						//构建idf表
		word_table.SelectSort(word_idf);
		word_table.Print(word_idf, file_names[i]);								//输出idf表
	}
	word_table.CalSentimentFeature();
}
// 计算主题词表
void CalSubjectTable() {
	string in_name = "D:\\CCF\\train\\segment_train";
	vector<string> file_names;
	file_names.push_back("D:\\CCF\\train\\idf_subject动力");
	file_names.push_back("D:\\CCF\\train\\idf_subject价格");
	file_names.push_back("D:\\CCF\\train\\idf_subject内饰");
	file_names.push_back("D:\\CCF\\train\\idf_subject配置");
	file_names.push_back("D:\\CCF\\train\\idf_subject安全性");
	file_names.push_back("D:\\CCF\\train\\idf_subject外观");
	file_names.push_back("D:\\CCF\\train\\idf_subject操控");
	file_names.push_back("D:\\CCF\\train\\idf_subject油耗");
	file_names.push_back("D:\\CCF\\train\\idf_subject空间");
	file_names.push_back("D:\\CCF\\train\\idf_subject舒适性");
	ifstream in;
	in.open(in_name);
	if(!in)
		cout<<"Open "<<in_name<<"error"<<endl;
	string str;
	vector<string> sentences;
	while(getline(in, str)) {
		sentences.push_back(str);
	}
	/*vector<string> types;
	types.push_back("0");
	types.push_back("1");
	types.push_back("-1");*/
	WordTable word_table;
	for(int i = 0; i < file_names.size(); i++) {
		vector<WordIDF> word_idf;
		word_idf = word_table.CalculateIDFSubject(sentences, i);						//构建idf表
		word_table.SelectSort(word_idf);
		word_table.Print(word_idf, file_names[i]);								//输出idf表
	}
	word_table.CalSubjectFeature(file_names);
}
// 计算训练情感的向量
void CalTrainSentiment() {
	string in_name = "D:\\CCF\\train\\segment_train";
	ifstream in;
	in.open(in_name);
	if(!in)
		cout<<"Open "<<in_name<<"error"<<endl;
	string str;
	vector<string> sentences;
	while(getline(in, str)) {
		sentences.push_back(str);
	}
	vector<vector<string>> content_word;
	cut_word(sentences, content_word);
	vector<map<string,WordIDF>> tf;
	calculate_tf(content_word, tf);										//计算tf
	vector<string> file_names;
	file_names.push_back("D:\\CCF\\train\\idf_type0cos");
	file_names.push_back("D:\\CCF\\train\\idf_type1cos");
	file_names.push_back("D:\\CCF\\train\\idf_type-1cos");
	file_names.push_back("D:\\CCF\\train\\idf_type0keys");
	file_names.push_back("D:\\CCF\\train\\idf_type1keys");
	file_names.push_back("D:\\CCF\\train\\idf_type-1keys");
	vector<map<string,double>> idf_table;
	ReadIDFTable(file_names, idf_table);
	calculate_cos(tf, idf_table, "D:\\CCF\\train\\features_value");
}
// 计算训练主题的向量
void CalTrainSubject() {
	string in_name = "D:\\CCF\\train\\segment_train";
	ifstream in;
	in.open(in_name);
	if(!in)
		cout<<"Open "<<in_name<<"error"<<endl;
	string str;
	vector<string> sentences;
	while(getline(in, str)) {
		sentences.push_back(str);
	}
	vector<vector<string>> content_word;
	cut_word(sentences, content_word);
	vector<map<string,WordIDF>> tf;
	calculate_tf(content_word, tf);										//计算tf
	vector<string> file_names;
	file_names.push_back("D:\\CCF\\train\\idf_subject动力cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject价格cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject内饰cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject配置cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject安全性cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject外观cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject操控cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject油耗cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject空间cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject舒适性cos");
	/*file_names.push_back("D:\\CCF\\train\\idf_subject动力keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject价格keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject内饰keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject配置keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject安全性keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject外观keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject操控keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject油耗keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject空间keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject舒适性keys");*/
	vector<map<string,double>> idf_table;
	ReadIDFTable(file_names, idf_table);
	calculate_cos_keys(tf, idf_table, "D:\\CCF\\train\\features_value2");
}
// 计算测试情感的向量
void CalPredictSentiment() {
	string in_name = "D:\\CCF\\train\\segment_test";
	ifstream in;
	in.open(in_name);
	if(!in)
		cout<<"Open "<<in_name<<"error"<<endl;
	string str;
	vector<string> sentences;
	while(getline(in, str)) {
		sentences.push_back(str);
	}
	vector<vector<string>> content_word;
	cut_word(sentences, content_word);
	vector<map<string,WordIDF>> tf;
	calculate_tf(content_word, tf);										//计算tf
	vector<string> file_names;
	file_names.push_back("D:\\CCF\\train\\idf_type0cos");
	file_names.push_back("D:\\CCF\\train\\idf_type1cos");
	file_names.push_back("D:\\CCF\\train\\idf_type-1cos");
	file_names.push_back("D:\\CCF\\train\\idf_type0keys");
	file_names.push_back("D:\\CCF\\train\\idf_type1keys");
	file_names.push_back("D:\\CCF\\train\\idf_type-1keys");
	vector<map<string,double>> idf_table;
	ReadIDFTable(file_names, idf_table);
	calculate_cos(tf, idf_table, "D:\\CCF\\train\\test_features_value");
}
// 计算测试主题的向量
void CalPredictSubject() {
	string in_name = "D:\\CCF\\train\\segment_test";
	ifstream in;
	in.open(in_name);
	if(!in)
		cout<<"Open "<<in_name<<"error"<<endl;
	string str;
	vector<string> sentences;
	while(getline(in, str)) {
		sentences.push_back(str);
	}
	vector<vector<string>> content_word;
	cut_word(sentences, content_word);
	vector<map<string,WordIDF>> tf;
	calculate_tf(content_word, tf);										//计算tf
	vector<string> file_names;
	file_names.push_back("D:\\CCF\\train\\idf_subject动力cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject价格cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject内饰cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject配置cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject安全性cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject外观cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject操控cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject油耗cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject空间cos");
	file_names.push_back("D:\\CCF\\train\\idf_subject舒适性cos");
	/*file_names.push_back("D:\\CCF\\train\\idf_subject动力keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject价格keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject内饰keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject配置keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject安全性keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject外观keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject操控keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject油耗keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject空间keys");
	file_names.push_back("D:\\CCF\\train\\idf_subject舒适性keys");*/
	vector<map<string,double>> idf_table;
	ReadIDFTable(file_names, idf_table);
	calculate_cos_keys(tf, idf_table, "D:\\CCF\\train\\test_features_value2");
}
//将分好词的句子拆分成词
void cut_word( vector<string> sentences, vector<vector<string>> &content_word ){
	int position;
	string content;
	for( int i = 0; i < sentences.size(); i++){
		position = sentences[i].find(',');
		if(position != string::npos) {
			sentences[i].erase(0, position + 1);
		}
		else
			cout<<"error"<<endl;
		//position = sentences[i].find(',');
		//content = sentences[i].erase(position);					//得到句子内容
		content = sentences[i];										//测试数据里的方法
		string str;
		vector<string> temp;
		for( int j = 0; j < content.size(); j++ ){
			if( content[j] != ' ' )
				str += content[j];
			else{
				temp.push_back( str );
				str.clear();
			}
		}
		if(str.size() > 0)
			temp.push_back(str);
		content_word.push_back( temp );
	}
}
//计算词频tf，每一行存放一行中词语的tf
void calculate_tf( vector<vector<string>> content_word, vector< map<string,WordIDF> > &tf ){
	map<string, WordIDF>::iterator word_iter;
	for( int i = 0; i < content_word.size(); i++ ){								//第i个句子
		map<string,WordIDF> blank;
		tf.push_back( blank );
		//int num_word = 0;														//计算每一句含有的词语个数
		for( int j = 0; j < content_word[i].size(); j++ ){						//第i个句子的第j个词
			word_iter = tf[i].find( content_word[i][j] );
			if( word_iter != tf[i].end() ){										//当该词已经存在时
				word_iter->second.idf += 1;
			}
			else{																//如果该词不存在，则添加进去
				WordIDF temp;
				temp.idf = 1;
				tf[i].insert( pair<string,WordIDF>(content_word[i][j], temp) );
			}
		}
		map<string, WordIDF>::iterator iter;
		for ( iter = tf[i].begin(); iter != tf[i].end(); iter++ ){						//得到tf
			iter->second.idf = iter->second.idf * 1.0 / content_word[i].size();
		}
	}
	//*********************************测试***********************************************
	/*for( int i = 0; i < tf.size(); i++ ){
		for( word_iter = tf[i].begin(); word_iter != tf[i].end(); word_iter++ ){
			cout<<word_iter->second.frequency<<'\t';
		}
	}*/
}
// 读取idf词表
// file_names 存放多个词表的路径名
void ReadIDFTable(vector<string> file_names, vector<map<string, double>> &idf_table) {
	ifstream in;
	for(int i = 0; i < file_names.size(); i++) {					//读取所有的词语
		in.open(file_names[i]);
		if(!in)
			cout<<"Open "<<file_names[i]<<" error"<<endl;
		map<string,double> single_idf;
		WordIDF temp;
		string str;
		while(getline(in, str)) {
			istringstream sin(str);
			sin>>temp.word;
			sin>>temp.idf;
			if(str[0] == ' ')
				cout<<temp.word<<' '<<temp.idf<<endl;
			temp.idf = log(1.0 / temp.idf);
			single_idf.insert(pair<string,double>(temp.word, temp.idf));
		}
		idf_table.push_back(single_idf);
		in.close();
	}
}
//计算余弦相似度	情感态度 与三个词表的
void calculate_cos( vector< map<string, WordIDF> > tf, vector<map<string,double>> idf, string out_name){
	ofstream out;
	out.open(out_name);
	if(!out)
		cout<<"Open features_value error"<<endl;
	map<string,double>::iterator iter_idf;													//计算idf的模
	vector<double> idf_model;
	for(int i = 0; i < idf.size(); i++) {
		double sum = 0;
		for(iter_idf = idf[i].begin(); iter_idf != idf[i].end(); iter_idf++) {
			sum = sum + iter_idf->second * iter_idf->second;
		}
		idf_model.push_back(sqrt(sum));
	}
	vector<string> file_keys_name;
	file_keys_name.push_back("D:\\CCF\\train\\sentiment_word_table.txt");
	vector<map<string,double>> idf_keys;
	ReadIDFTable(file_keys_name, idf_keys);
	for(int i = 0; i < tf.size(); i++) {
		map<string, WordIDF>::iterator iter;
		int j = 0;
		for(j = 0; j < idf.size(); j++) {
			double sum = 0;
			double tf_model = 0;
			for(iter = tf[i].begin(); iter != tf[i].end(); iter++) {
				tf_model += iter->second.idf * iter->second.idf;
				iter_idf = idf[j].find(iter->first);
				if(iter_idf != idf[j].end()) {
					sum = sum + iter->second.idf * iter_idf->second;
				}
			}
			sum = sum / (sqrt(tf_model) * idf_model[j]);
			out<<j+1<<":"<<sum<<" ";
		}
		map<string,double>::iterator iter_keys;
		for(iter_keys = idf_keys[0].begin(); iter_keys != idf_keys[0].end(); iter_keys++) {			//一次循环计算一个词的相关度
			iter = tf[i].find(iter_keys->first);
			if(iter != tf[i].end()) {
				out<<j + 1<<":"<<iter_keys->second * iter->second.idf<<" ";
				j++;
			}
			else {
				out<<j+1<<":"<<0<<" ";
				j++;
			}
		}
		out<<endl;
	}


	/*for(int i = 0; i < tf.size(); i++) {
		map<string, WordIDF>::iterator iter;
		for(int j = 0; j < idf.size(); j++) {
			double sum = 0;
			double tf_model = 0;
			for(iter = tf[i].begin(); iter != tf[i].end(); iter++) {
				tf_model += iter->second.idf * iter->second.idf;
				iter_idf = idf[j].find(iter->first);
				if(iter_idf != idf[j].end()) {
					sum = sum + iter->second.idf * iter_idf->second;
				}
			}
			sum = sum / (sqrt(tf_model) * idf_model[j]);
			out<<j+1<<":"<<sum<<" ";
		}
		out<<endl;
	}*/
}
//计算余弦相似度 训练集 subject	与多个词表+重点词
void calculate_cos_keys( vector< map<string, WordIDF> > tf, vector<map<string,double>> idf, string out_name) {
	ofstream out;
	out.open(out_name);
	if(!out)
		cout<<"Open features_value error"<<endl;
	map<string,double>::iterator iter_idf;													//计算idf的模
	vector<double> idf_model;
	for(int i = 0; i < idf.size(); i++) {
		double sum = 0;
		for(iter_idf = idf[i].begin(); iter_idf != idf[i].end(); iter_idf++) {
			sum = sum + iter_idf->second * iter_idf->second;
		}
		idf_model.push_back(sqrt(sum));
	}
	vector<string> file_keys_name;
	file_keys_name.push_back("D:\\CCF\\train\\subject_word72.txt");
	vector<map<string,double>> idf_keys;
	ReadIDFTable(file_keys_name, idf_keys);
	for(int i = 0; i < tf.size(); i++) {
		map<string, WordIDF>::iterator iter;
		int j = 0;
		for(j = 0; j < idf.size(); j++) {
			double sum = 0;
			double tf_model = 0;
			for(iter = tf[i].begin(); iter != tf[i].end(); iter++) {
				tf_model += iter->second.idf * iter->second.idf;
				iter_idf = idf[j].find(iter->first);
				if(iter_idf != idf[j].end()) {
					sum = sum + iter->second.idf * iter_idf->second;
				}
			}
			//cout<<sum<<endl;
			sum = sum / (sqrt(tf_model) * idf_model[j]);

			out<<j+1<<":"<<sum<<" ";
		}
		map<string,double>::iterator iter_keys;
		for(iter_keys = idf_keys[0].begin(); iter_keys != idf_keys[0].end(); iter_keys++) {			//一次循环计算一个词的相关度
			iter = tf[i].find(iter_keys->first);
			if(iter != tf[i].end()) {
				out<<j + 1<<":"<<iter_keys->second * iter->second.idf<<" ";
				j++;
			}
			else {
				out<<j+1<<":"<<0<<" ";
				j++;
			}
		}
		out<<endl;
	}
	out.close();
}
//计算余弦相似度,训练集	与三个词表的
void calculate_cos_train( vector< map<string, WordIDF> > tf, vector<map<string,double>> idf) {
	
}
//整合，将情感特征和向量结合
void combine() {
	string in_name = "D:\\CCF\\train\\segment_train";
	ifstream in;
	in.open(in_name);
	if(!in)
		cout<<"Open "<<in_name<<"error"<<endl;
	string str;
	vector<string> sentences;
	//getline(in, str);
	while(getline(in, str)) {
		sentences.push_back(str);
	}
	ifstream in2;
	in2.open("D:\\CCF\\train\\features_value");
	vector<string> sen2;
	while(getline(in2,str)) {
		sen2.push_back(str);
	}
	int position;
	ofstream out;
	out.open("D:\\CCF\\train\\train_sentiment");
	string sentiment_word;
	vector<vector<string>> sentiment_vec;
	vector<string> temp;
	sentiment_vec.push_back(temp);
	sentiment_vec.push_back(temp);
	sentiment_vec.push_back(temp);
	for(int i = 0; i < sentences.size(); i++) {
		/****************************************************************/
		position = sentences[i].find(',');
		if(position != string::npos) {
			sentences[i].erase(0, position + 1);
		}
		position = sentences[i].find(',');
		sentiment_word = sentences[i].substr(position + 1);
		sentences[i].erase(position);					//得到句子内容
		//out<<content<<endl;
		position = sentiment_word.find(',');
		sentiment_word = sentiment_word.erase(0, position + 1);
		position = sentiment_word.find(',');
		sentiment_word = sentiment_word.substr(0, position);	//得到情感值
		out<<sentiment_word<<" "<<sen2[i]<<endl;
		/*************************进行均衡化****************/
		if(sentiment_word == "0")
			sentiment_vec[0].push_back(sentiment_word + " " + sen2[i]);
		if(sentiment_word == "1")
			sentiment_vec[1].push_back(sentiment_word + " " + sen2[i]);
		if(sentiment_word == "-1")
			sentiment_vec[2].push_back(sentiment_word + " " + sen2[i]);
		/******************************************************************/

	}
	/*for(int i = 0; i >= sentiment_vec[0].size() && i >= sentiment_vec[1].size() && i >= sentiment_vec[2].size(); i++) {
		out<<sentiment_vec[0][i % sentiment_vec[0].size()]<<endl;
		out<<sentiment_vec[1][i % sentiment_vec[1].size()]<<endl;
		out<<sentiment_vec[2][i % sentiment_vec[2].size()]<<endl;
	}*/
	in.close();
	in2.close();
	out.close();
}
//整合，将主题特征和向量结合
void combine2() {
	vector<vector<string>> subject_vec;
	vector<string> temp;
	vector<string> subject;
	ifstream in3;
	in3.open("D:\\CCF\\train\\subject.txt");
	string s;
	while(getline(in3,s)) {
		subject_vec.push_back(temp);
		subject.push_back(s);
	}
	string in_name = "D:\\CCF\\train\\segment_train";
	ifstream in;
	in.open(in_name);
	if(!in)
		cout<<"Open "<<in_name<<"error"<<endl;
	string str;
	vector<string> sentences;
	//getline(in, str);
	while(getline(in, str)) {
		sentences.push_back(str);
	}
	ifstream in2;
	in2.open("D:\\CCF\\train\\features_value2");
	vector<string> sen2;
	while(getline(in2,str)) {
		sen2.push_back(str);
	}
	int position;
	ofstream out;
	out.open("D:\\CCF\\train\\train_subject");
	string sentiment_word;
	for(int i = 0; i < sentences.size(); i++) {
		position = sentences[i].find(',');
		if(position != string::npos) {
			sentences[i].erase(0, position + 1);					//删除id标签
		}
		position = sentences[i].find(',');
		string sub;
		sub = sentences[i].substr(position + 1);					//截取主题及主题之后的内容
		position = sub.find(',');
		sub.erase(position);										//得到主题
		for(int j = 0; j < subject.size(); j++) {
			if(sub == subject[j]) {
				ostringstream os;
				os <<j;
				subject_vec[j].push_back(os.str() + " " + sen2[i]);
				//out<<j<<" "<<sen2[i]<<endl;
				break;
			}
		}
	}
	int i = 0;
	while(1) {
		int j;
		for(j = 0; j < 10; j++) {						//判断数目是否大于最小数目
			if(i < subject_vec[j].size())
				break;
		}
		if(j < 10) {
			for(int k = 0; k < 10; k++) {
				out<<subject_vec[k][i % subject_vec[k].size()]<<endl;
			}
		}
		else
			break;
		i++;
	}
	in.close();
	in2.close();
	out.close();
}
//测试集里面的整合
void combine3() {
	ifstream in2;
	in2.open("D:\\CCF\\train\\test_features_value");
	vector<string> sen2;
	string str;
	while(getline(in2,str)) {
		sen2.push_back(str);
	}
	int position;
	ofstream out;
	out.open("D:\\CCF\\train\\test_sentiment");
	for(int i = 0; i < sen2.size(); i++) {
		out<<"1 "<<sen2[i]<<endl;
	}
	in2.close();
	out.close();
}
// 测试集里面的整合主题
void CombinePredictSubject() {
	ifstream in2;
	in2.open("D:\\CCF\\train\\test_features_value2");
	vector<string> sen2;
	string str;
	while(getline(in2,str)) {
		sen2.push_back(str);
	}
	int position;
	ofstream out;
	out.open("D:\\CCF\\train\\test_subject");
	for(int i = 0; i < sen2.size(); i++) {
		out<<"1 "<<sen2[i]<<endl;
	}
	in2.close();
	out.close();
}
//得到结果
void GetResult() {
	vector<string> subject;
	ifstream in_;
	in_.open("D:\\CCF\\train\\subject.txt");
	string s;
	while(getline(in_,s)) {
		subject.push_back(s);
	}
	string str1 = "D:\\CCF\\train\\segment_test";
	string str2 = "D:\\CCF\\libsvm-3.23\\windows\\data\\result_sentiment";
	string str3 = "D:\\CCF\\libsvm-3.23\\windows\\data\\result_subject";
	ifstream in;
	in.open(str1);								//测试数据集
	ifstream in2;
	in2.open(str2);								//情感预测
	ifstream in3;
	in3.open(str3);								//主题预测
	string str4 = "D:\\CCF\\libsvm-3.23\\windows\\data\\FinalResult.csv";
	ofstream out;
	out.open(str4);
	out<<"content_id,subject,sentiment_value,sentiment_word"<<endl;
	string str;
	int pos;
	while(getline(in, str)) {
		pos = str.find(',');
		str.erase(pos);
		out<<str<<',';
		string sub;
		int a;
		getline(in3,sub);
		istringstream ss(sub);
		ss>>a;
		out<<subject[a]<<",";
		getline(in2, str);
		out<<str<<","<<""<<endl;
	}
	in.close();
	in2.close();
	in3.close();
	out.close();
}