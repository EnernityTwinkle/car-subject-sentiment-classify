// Copyright 2018 YH
// License(GPL)
// Author: YH
// This is calculate word table.
#include "build_word_table.h"

// 建立全局词表idf,传入参数为文件名
vector<WordIDF> WordTable::BuildGlobalIDF(string file_name) {
	int position;
	string content;
	map<string, int> word_frequency;
	vector<string> sentences;								//存放文件里的句子
	ifstream in;
	in.open(file_name);
	if(!in) {
		cout<<"Open "<<file_name<<" error"<<endl;
	}
	string str;
	while(getline(in,str)) {								//读取文件内容
		sentences.push_back(str);
	}
	for(int i = 0; i < sentences.size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		position = sentences[i].find(',');
		if(position != string::npos) {							//丢弃标签ID
			sentences[i].erase(0, position + 1);
		}
		position = sentences[i].find(',');
		content = sentences[i].erase(position);					//得到句子内容
		map<string,int> temp;
		while(1) {												//计算一个句子中出现的词语
			string word;
			position = content.find(' ');
			if(position != string::npos) {
				word = content.substr(0, position);
				content.erase(0, position + 1);
				temp.insert(pair<string, int>(word, 1));
			}
			else {
				temp.insert(pair<string, int>(content, 1));
				break;
			}
		}
		map<string,int>::iterator iter;
		map<string,int>::iterator iter_all;
		for(iter = temp.begin(); iter != temp.end(); iter++) {		//将一个句子里出现的词语加入到总词语的里面
			iter_all = word_frequency.find(iter->first);
			if(iter_all != word_frequency.end()) {
				iter_all->second += 1;
			}
			else {
				word_frequency.insert(pair<string,int>(iter->first, 1));
			}
		}
	}
	vector<WordIDF> word_idf;
	map<string,int>::iterator iter;
	for(iter = word_frequency.begin(); iter != word_frequency.end(); iter++) {		//将map里的数据转到vector中
		WordIDF temp;
		temp.word = iter->first;
		temp.idf = iter->second * 1.0 / sentences.size();
		word_idf.push_back(temp);
	}
	return word_idf;
}
// 将idf词表写出到文件中
// word_frequency 存放的是词表：词语（string） idf值(double)
// file_name 输出文件名称
void WordTable::Print(vector<WordIDF> word_frequency, string file_name) {
	ofstream out;
	out.open(file_name);
	for(int i = 0; i < word_frequency.size(); i++) {
		out<<word_frequency[i].word<<'\t'<<word_frequency[i].idf<<endl;
	}
	out.close();
}
// 词的idf统计,根据情感态度类别的不同统计每个类别的词的idf分布
// sentences里存放的是待统计的所有句子；
// type是情感态度的类别，可以为"0" "1" "-1"
vector<WordIDF> WordTable::CalculateIDFSentiment(vector<string> sentences, string type) {
	int position;
	string content;
	string sentiment_word;
	map<string, int> word_frequency;
	int count = 0;
	for(int i = 0; i < sentences.size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		position = sentences[i].find(',');
		if(position != string::npos) {
			sentences[i].erase(0, position + 1);
		}
		position = sentences[i].find(',');
		sentiment_word = sentences[i].substr(position + 1);
		content = sentences[i].erase(position);					//得到句子内容
		position = sentiment_word.find(',');
		sentiment_word = sentiment_word.erase(0, position + 1);
		position = sentiment_word.find(',');
		sentiment_word = sentiment_word.substr(0, position);	//得到情感值
		if(sentiment_word == type) {
			count++;
			map<string,int> temp;
			while(1) {												//计算一个句子中词语是否出现
				string word;
				position = content.find(' ');
				if(position != string::npos) {
					word = content.substr(0, position);
					content.erase(0, position + 1);
					if(word.size() > 0)
						temp.insert(pair<string, int>(word, 1));
				}
				else {
					temp.insert(pair<string, int>(content, 1));
					break;
				}
			}
			map<string,int>::iterator iter;
			map<string,int>::iterator iter_all;
			for(iter = temp.begin(); iter != temp.end(); iter++) {		//将一个句子里的词加入到总的里面
				iter_all = word_frequency.find(iter->first);
				if(iter_all != word_frequency.end()) {
					iter_all->second += 1;
				}
				else {
					word_frequency.insert(pair<string,int>(iter->first, 1));
				}
			}
		}
	}
	vector<WordIDF> word_idf;
	map<string,int>::iterator iter;
	for(iter = word_frequency.begin(); iter != word_frequency.end(); iter++) {		//将map里的数据转到vector中
		WordIDF temp;
		temp.word = iter->first;
		temp.idf = iter->second * 1.0 / count;
		word_idf.push_back(temp);
	}
	return word_idf;
}
// 词的idf统计，统计subject中的
// sentences里存放的是待统计的所有句子；
// type是主题的类别，取值范围为0--9
vector<WordIDF> WordTable::CalculateIDFSubject(vector<string> sentences, int type) {
	int position;
	string content;
	string sentiment_word;
	map<string, int> word_frequency;
	int count = 0;
	vector<string> subject;
	ifstream in;
	in.open("D:\\CCF\\train\\subject.txt");
	string s;
	while(getline(in,s)) {
		subject.push_back(s);
	}
	for(int i = 0; i < sentences.size(); i++) {
		position = sentences[i].find(',');
		if(position != string::npos) {
			sentences[i].erase(0, position + 1);
		}
		position = sentences[i].find(',');
		string sub;
		sub = sentences[i].substr(position + 1);
		content = sentences[i].erase(position);					//得到句子内容
		position = sub.find(',');
		sub.erase(position);
		if(sub == subject[type]) {
			count++;
			map<string,int> temp;
			while(1) {												//计算一个句子中词语是否出现
				string word;
				position = content.find(' ');
				if(position != string::npos) {
					word = content.substr(0, position);
					content.erase(0, position + 1);
					if(word.size() > 0)
						temp.insert(pair<string, int>(word, 1));
				}
				else {
					temp.insert(pair<string, int>(content, 1));
					break;
				}
			}
			map<string,int>::iterator iter;
			map<string,int>::iterator iter_all;
			for(iter = temp.begin(); iter != temp.end(); iter++) {		//将一个句子里的词加入到总的里面
				iter_all = word_frequency.find(iter->first);
				if(iter_all != word_frequency.end()) {
					iter_all->second += 1;
				}
				else {
					word_frequency.insert(pair<string,int>(iter->first, 1));
				}
			}
		}
	}
	vector<WordIDF> word_idf;
	map<string,int>::iterator iter;
	for(iter = word_frequency.begin(); iter != word_frequency.end(); iter++) {		//将map里的数据转到vector中
		WordIDF temp;
		temp.word = iter->first;
		temp.idf = iter->second * 1.0 / count;
		word_idf.push_back(temp);
	}
	return word_idf;
}
// 对词频进行选择排序
void WordTable::SelectSort(vector<WordIDF> &word_idf) {
	WordIDF temp;
	for(int i = 0; i < word_idf.size(); i++) {
		int k = i;
		for(int j = k + 1; j < word_idf.size(); j++) {
			if(word_idf[j].idf > word_idf[k].idf) {
				k = j;
			}
		}
		if(k != i) {
			temp = word_idf[k];
			word_idf[k] = word_idf[i];
			word_idf[i] = temp;
		}
	}
}
// 词频快速排序
void WordTable::QuickSort(vector<WordIDF> &word_idf, int begin, int end) {
	if(begin >= end)
		return;
	int i = begin, j = end;
	double x = word_idf[(i + j) >> 1].idf;
	WordIDF tmp;
	while(i <= j) {
		while(word_idf[i].idf > x)
			i++;
		while(word_idf[j].idf < x)
			j--;
		if(i <= j) {
			tmp = word_idf[i];
			word_idf[i] = word_idf[j];
			word_idf[j] = tmp;
			i++;
			j--;
		}
	}
	QuickSort(word_idf, begin, j);
	QuickSort(word_idf, i, end);
}
// 计算不同情感态度所具有的各特征词
// 结果暂时直接写入文件中
void WordTable::CalSentimentFeature() {
	vector<vector<WordIDF>> types_idf;					//存放不同类型的特征词，即all
	ifstream in;
	vector<string> type_name;
	type_name.push_back("0");
	type_name.push_back("1");
	type_name.push_back("-1");
	string file_name = "D:\\CCF\\train\\idf_type";
	for(int i = 0; i < type_name.size(); i++) {					//读取所有的词语
		in.open(file_name + type_name[i]);
		if(!in)
			cout<<"Open "<<type_name[i]<<" error"<<endl;
		vector<WordIDF> single_idf;
		WordIDF temp;
		string str;
		while(getline(in, str)) {
			istringstream sin(str);
			sin>>temp.word;
			sin>>temp.idf;
			single_idf.push_back(temp);
		}
		types_idf.push_back(single_idf);
		in.close();
	}
	int N = 3;
	//计算不同情感类型的特征词的方法一：一个词在某一类别中出现的次数最多，则属于该类别
	//for(int key = 0; key < N; key++) {							//一次循环完成一个主题类型词的构造
	//	double m = 0, n = 0;
	//	ofstream out;
	//	out.open(file_name + type_name[key] + "keys");							
	//	for(int i = 0; i < types_idf[key].size(); i++) {		//一次循环完成一个词的过滤
	//		if(types_idf[key][i].idf > 0.001) {
	//			vector<double> idf_temp;						//记录其他主题类型词的对照表
	//			if(i % 1000 == 0)
	//				cout<<i<<endl;
	//			for(int j = 0; j < types_idf.size(); j++) {
	//				if(j == key)
	//					continue;
	//				for(int k = 0; k < types_idf[j].size(); k++) {
	//					if(types_idf[key][i].word == types_idf[j][k].word) {
	//						idf_temp.push_back(types_idf[j][k].idf);
	//						break;
	//					}
	//				}
	//			}
	//			int j;
	//			for(j = 0; j < idf_temp.size(); j++) {					//判断该词是否是该类别的特征词
	//				if(types_idf[key][i].idf <= idf_temp[j]) {			//判断规则是：一个词在某一类别中出现的次数最多，则属于该类别
	//					break;
	//				}
	//			}
	//			if(j >= idf_temp.size()) {
	//				out<<types_idf[key][i].word<<' '<<types_idf[key][i].idf<<endl;
	//			}
	//		}
	//	}
	//	out.close();
	//}
	//判断该词是否是该类别的特征词的第二种方法：一个词在某一类别中出现的次数大于在其他类别中出现的次数之和
	//计算情感态度为0时的特征词
	int key = 0;
	double m = 0, n = 0;
	ofstream out;
	out.open(file_name + type_name[key] + "keys");
	for(int i = 0; i < types_idf[key].size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		for(int j = 0; j < types_idf[key + 1].size(); j++) {		//查找在1中出现的频率
			if(types_idf[key][i].word == types_idf[key + 1][j].word){
				m = types_idf[key + 1][j].idf;
				break;
			}
		}
		for(int j = 0; j < types_idf[key + 2].size(); j++) {
			if(types_idf[key][i].word == types_idf[key + 2][j].word){
				n = types_idf[key + 2][j].idf;
				break;
			}
		}
		if(m >= 0.001 && n >= 0.001) {
			if(types_idf[key][i].idf * 1.4 > m + n) {
				out<<types_idf[key][i].word<<' '<<types_idf[key][i].idf<<endl;
			}
			m = n = 0;
		}
		else {
			m = n = 0;
		}
	}
	out.close();
	//计算情感态度为1时的特征词
	key = 1;
	m = n = 0;
	out.open(file_name + type_name[key] + "keys");
	for(int i = 0; i < types_idf[key].size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		for(int j = 0; j < types_idf[key + 1].size(); j++) {		//查找在1中出现的频率
			if(types_idf[key][i].word == types_idf[key + 1][j].word){
				m = types_idf[key + 1][j].idf;
				break;
			}
		}
		for(int j = 0; j < types_idf[key - 1].size(); j++) {
			if(types_idf[key][i].word == types_idf[key - 1][j].word){
				n = types_idf[key - 1][j].idf;
				break;
			}
		}
		if(m >= 0.001 && n >= 0.001) {
			if(types_idf[key][i].idf > m + n) {
				out<<types_idf[key][i].word<<' '<<types_idf[key][i].idf<<endl;
			}
			m = n = 0;
		}
		else {
			m = n = 0;
		}
	}
	out.close();
	//计算情感态度为-1时的特征词
	key = 2;
	m = n = 0;
	out.open(file_name + type_name[key] + "keys");
	for(int i = 0; i < types_idf[key].size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		for(int j = 0; j < types_idf[key - 2].size(); j++) {		//查找在0中出现的频率
			if(types_idf[key][i].word == types_idf[key - 2][j].word){
				m = types_idf[key - 2][j].idf;
				break;
			}
		}
		for(int j = 0; j < types_idf[key - 1].size(); j++) {
			if(types_idf[key][i].word == types_idf[key - 1][j].word){
				n = types_idf[key - 1][j].idf;
				break;
			}
		}
		if(m >= 0.001 && n >= 0.001) {
			if(types_idf[key][i].idf > m + n) {
				out<<types_idf[key][i].word<<' '<<types_idf[key][i].idf<<endl;
			}
			m = n = 0;
		}
		else {
			m = n = 0;
		}
	}
	out.close();
}
// 计算不同主题所具有的各特征词
// 结果暂时直接写入文件中
// file_names	存放不同主题里面的所有词的文档名
void WordTable::CalSubjectFeature(vector<string> file_names) {
	vector<vector<WordIDF>> types_idf;					//存放不同类型的特征词，即all
	vector<string> type_name;
	ifstream in;
	in.open("D:\\CCF\\train\\subject.txt");
	string s;
	while(getline(in,s)) {								//读取十种主题类型词
		type_name.push_back(s);
	}
	in.close();
	for(int i = 0; i < file_names.size(); i++) {					//读取所有的词语
		in.open(file_names[i]);
		if(!in)
			cout<<"Open "<<file_names[i]<<" error"<<endl;
		vector<WordIDF> single_idf;
		WordIDF temp;
		string str;
		while(getline(in, str)) {
			istringstream sin(str);
			sin>>temp.word;
			sin>>temp.idf;
			single_idf.push_back(temp);
		}
		types_idf.push_back(single_idf);
		in.close();
	}
	//计算不同主题类型的特征词
	ofstream out_all;
	out_all.open("D:\\subject_word.txt");
	for(int key = 0; key < 10; key++) {							//一次循环完成一个主题类型词的构造
		double m = 0, n = 0;
		ofstream out;
		out.open(file_names[key] + "keys");							
		for(int i = 0; i < types_idf[key].size(); i++) {		//一次循环完成一个词的过滤
			if(types_idf[key][i].idf > 0.001) {
				vector<double> idf_temp;							//记录其他主题类型词的对照表
				if(i % 1000 == 0)
					cout<<i<<endl;
				for(int j = 0; j < types_idf.size(); j++) {
					if(j == key)
						continue;
					for(int k = 0; k < types_idf[j].size(); k++) {
						if(types_idf[key][i].word == types_idf[j][k].word) {
							idf_temp.push_back(types_idf[j][k].idf);
							break;
						}
					}
				}
				//寻找最大idf值作为一个类别的特征值
				/*int j;
				for(j = 0; j < idf_temp.size(); j++) {
					if(types_idf[key][i].idf <= idf_temp[j]) {
						break;
					}
				}
				if(j >= idf_temp.size()) {
					out<<types_idf[key][i].word<<' '<<types_idf[key][i].idf<<endl;
				}*/
				// 选取一个类别的idf值远大于其他类别的词作为特征值
				double sum = 0;									//准确率：0.351586
				for(int j = 0; j < idf_temp.size(); j++) {
					sum += idf_temp[j];
				}
				if(types_idf[key][i].idf * 1.5 > sum) {
					out<<types_idf[key][i].word<<' '<<types_idf[key][i].idf<<endl;
					out_all<<types_idf[key][i].word<<' '<<types_idf[key][i].idf<<endl;
				}
			}
		}
		out.close();
	}
	out_all.close();
}
// 建立各类别统一的词表，便于比较计算相似度
void WordTable::BuildAllCategoryWordTable() {
	ifstream in_IDF("D:\\CCF\\train\\GlobalIDF");
	if(!in_IDF)
		cout<<"Open GlobalIDF error"<<endl;
	map<string,double> global_idf;									//存放全局idf表
	string str;
	string word;
	double temp;
	while(getline(in_IDF, str)) {
		istringstream ss(str);
		ss>>word;
		ss>>temp;
		global_idf.insert(pair<string,double>(word, temp));
	}
	in_IDF.close();
	//建立统一的情感态度表
	vector<string> file_names;
	file_names.push_back("D:\\CCF\\train\\idf_type0");
	file_names.push_back("D:\\CCF\\train\\idf_type1");
	file_names.push_back("D:\\CCF\\train\\idf_type-1");
	vector<vector<WordIDF>> word_idf_table;
	for(int i = 0; i < 3; i++) {								//读取所有类别词表
		ifstream in;
		in.open(file_names[i]);
		if(!in)
			cout<<"Open "<<file_names[i]<<" error"<<endl;
		WordIDF word_idf;
		vector<WordIDF> single_idf;
		while(getline(in, str)) {
			istringstream ss(str);
			ss>>word_idf.word;
			ss>>word_idf.idf;
			single_idf.push_back(word_idf);
		}
		word_idf_table.push_back(single_idf);
		in.close();
	}
	for(int i = 0; i < file_names.size(); i++) {
		ofstream out;
		out.open(file_names[i] + "cos");
		if(!out)
			cout<<"Open cos error"<<endl;
		for(int j = 0; j < word_idf_table[i].size(); j++) {			//逐词进行制作不同类别的词表
			map<string,double>::iterator iter;
			if(word_idf_table[i][j].idf > 0.0005) {
				double sum = 0;
				for(int k = 0; k < file_names.size(); k++) {		//计算该词在其他类别idf值的总和
					if(k != i) {
						for(int m = 0; m < word_idf_table[k].size(); m++) {
							if(word_idf_table[i][j].word == word_idf_table[k][m].word) {
								sum += word_idf_table[k][m].idf;
								break;
							}
						}
					}
				}
				iter = global_idf.find(word_idf_table[i][j].word);
				if(word_idf_table[i][j].idf > sum) {							//该词是特殊特征词
					if(iter != global_idf.end()) {
						out<<word_idf_table[i][j].word<<" "<<iter->second<<endl;
					}
					for(int k = 0; k < file_names.size(); k++) {		//删除在其他词表中的该词
						if(k != i) {
							for(int m = 0; m < word_idf_table[k].size(); m++) {
								if(word_idf_table[i][j].word == word_idf_table[k][m].word) {
									word_idf_table[k].erase(word_idf_table[k].begin() + m);
									break;
								}
							}
						}
					}
				}
				else {
					if(iter != global_idf.end()) {
						out<<word_idf_table[i][j].word<<" "<<iter->second<<endl;
					}
				}
			}
		}
		out.close();
	}
	//建立统一的主题表
	file_names.clear();
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
	word_idf_table.clear();
	for(int i = 0; i < file_names.size(); i++) {								//读取所有类别词表
		ifstream in;
		in.open(file_names[i]);
		if(!in)
			cout<<"Open "<<file_names[i]<<" error"<<endl;
		WordIDF word_idf;
		vector<WordIDF> single_idf;
		while(getline(in, str)) {
			istringstream ss(str);
			ss>>word_idf.word;
			ss>>word_idf.idf;
			single_idf.push_back(word_idf);
		}
		word_idf_table.push_back(single_idf);
		in.close();
	}
	for(int i = 0; i < file_names.size(); i++) {
		ofstream out;
		out.open(file_names[i] + "cos");
		if(!out)
			cout<<"Open cos error"<<endl;
		for(int j = 0; j < word_idf_table[i].size(); j++) {			//逐词进行制作不同类别的词表
			map<string,double>::iterator iter;
			if(word_idf_table[i][j].idf > 0.001) {
				double sum = 0;
				for(int k = 0; k < file_names.size(); k++) {		//计算该词在其他类别idf值的总和
					if(k != i) {
						for(int m = 0; m < word_idf_table[k].size(); m++) {
							if(word_idf_table[i][j].word == word_idf_table[k][m].word) {
								sum += word_idf_table[k][m].idf;
								break;
							}
						}
					}
				}
				iter = global_idf.find(word_idf_table[i][j].word);
				if(word_idf_table[i][j].idf > sum) {							//该词是特殊特征词
					if(iter != global_idf.end()) {
						out<<word_idf_table[i][j].word<<" "<<iter->second<<endl;
					}
					for(int k = 0; k < file_names.size(); k++) {		//删除在其他词表中的该词
						if(k != i) {
							for(int m = 0; m < word_idf_table[k].size(); m++) {
								if(word_idf_table[i][j].word == word_idf_table[k][m].word) {
									word_idf_table[k].erase(word_idf_table[k].begin() + m);
									break;
								}
							}
						}
					}
				}
				else {
					if(iter != global_idf.end()) {
						out<<word_idf_table[i][j].word<<" "<<iter->second<<endl;
					}
				}
			}
		}
		out.close();
	}
}