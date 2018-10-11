// Copyright 2018 YH
// License(GPL)
// Author: YH
// This is calculate word table.
#include "build_word_table.h"

// ����ȫ�ִʱ�idf,�������Ϊ�ļ���
vector<WordIDF> WordTable::BuildGlobalIDF(string file_name) {
	int position;
	string content;
	map<string, int> word_frequency;
	vector<string> sentences;								//����ļ���ľ���
	ifstream in;
	in.open(file_name);
	if(!in) {
		cout<<"Open "<<file_name<<" error"<<endl;
	}
	string str;
	while(getline(in,str)) {								//��ȡ�ļ�����
		sentences.push_back(str);
	}
	for(int i = 0; i < sentences.size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		position = sentences[i].find(',');
		if(position != string::npos) {							//������ǩID
			sentences[i].erase(0, position + 1);
		}
		position = sentences[i].find(',');
		content = sentences[i].erase(position);					//�õ���������
		map<string,int> temp;
		while(1) {												//����һ�������г��ֵĴ���
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
		for(iter = temp.begin(); iter != temp.end(); iter++) {		//��һ����������ֵĴ�����뵽�ܴ��������
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
	for(iter = word_frequency.begin(); iter != word_frequency.end(); iter++) {		//��map�������ת��vector��
		WordIDF temp;
		temp.word = iter->first;
		temp.idf = iter->second * 1.0 / sentences.size();
		word_idf.push_back(temp);
	}
	return word_idf;
}
// ��idf�ʱ�д�����ļ���
// word_frequency ��ŵ��Ǵʱ����string�� idfֵ(double)
// file_name ����ļ�����
void WordTable::Print(vector<WordIDF> word_frequency, string file_name) {
	ofstream out;
	out.open(file_name);
	for(int i = 0; i < word_frequency.size(); i++) {
		out<<word_frequency[i].word<<'\t'<<word_frequency[i].idf<<endl;
	}
	out.close();
}
// �ʵ�idfͳ��,�������̬�����Ĳ�ͬͳ��ÿ�����Ĵʵ�idf�ֲ�
// sentences���ŵ��Ǵ�ͳ�Ƶ����о��ӣ�
// type�����̬�ȵ���𣬿���Ϊ"0" "1" "-1"
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
		content = sentences[i].erase(position);					//�õ���������
		position = sentiment_word.find(',');
		sentiment_word = sentiment_word.erase(0, position + 1);
		position = sentiment_word.find(',');
		sentiment_word = sentiment_word.substr(0, position);	//�õ����ֵ
		if(sentiment_word == type) {
			count++;
			map<string,int> temp;
			while(1) {												//����һ�������д����Ƿ����
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
			for(iter = temp.begin(); iter != temp.end(); iter++) {		//��һ��������Ĵʼ��뵽�ܵ�����
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
	for(iter = word_frequency.begin(); iter != word_frequency.end(); iter++) {		//��map�������ת��vector��
		WordIDF temp;
		temp.word = iter->first;
		temp.idf = iter->second * 1.0 / count;
		word_idf.push_back(temp);
	}
	return word_idf;
}
// �ʵ�idfͳ�ƣ�ͳ��subject�е�
// sentences���ŵ��Ǵ�ͳ�Ƶ����о��ӣ�
// type����������ȡֵ��ΧΪ0--9
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
		content = sentences[i].erase(position);					//�õ���������
		position = sub.find(',');
		sub.erase(position);
		if(sub == subject[type]) {
			count++;
			map<string,int> temp;
			while(1) {												//����һ�������д����Ƿ����
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
			for(iter = temp.begin(); iter != temp.end(); iter++) {		//��һ��������Ĵʼ��뵽�ܵ�����
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
	for(iter = word_frequency.begin(); iter != word_frequency.end(); iter++) {		//��map�������ת��vector��
		WordIDF temp;
		temp.word = iter->first;
		temp.idf = iter->second * 1.0 / count;
		word_idf.push_back(temp);
	}
	return word_idf;
}
// �Դ�Ƶ����ѡ������
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
// ��Ƶ��������
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
// ���㲻ͬ���̬�������еĸ�������
// �����ʱֱ��д���ļ���
void WordTable::CalSentimentFeature() {
	vector<vector<WordIDF>> types_idf;					//��Ų�ͬ���͵������ʣ���all
	ifstream in;
	vector<string> type_name;
	type_name.push_back("0");
	type_name.push_back("1");
	type_name.push_back("-1");
	string file_name = "D:\\CCF\\train\\idf_type";
	for(int i = 0; i < type_name.size(); i++) {					//��ȡ���еĴ���
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
	//���㲻ͬ������͵������ʵķ���һ��һ������ĳһ����г��ֵĴ�����࣬�����ڸ����
	//for(int key = 0; key < N; key++) {							//һ��ѭ�����һ���������ʹʵĹ���
	//	double m = 0, n = 0;
	//	ofstream out;
	//	out.open(file_name + type_name[key] + "keys");							
	//	for(int i = 0; i < types_idf[key].size(); i++) {		//һ��ѭ�����һ���ʵĹ���
	//		if(types_idf[key][i].idf > 0.001) {
	//			vector<double> idf_temp;						//��¼�����������ʹʵĶ��ձ�
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
	//			for(j = 0; j < idf_temp.size(); j++) {					//�жϸô��Ƿ��Ǹ�����������
	//				if(types_idf[key][i].idf <= idf_temp[j]) {			//�жϹ����ǣ�һ������ĳһ����г��ֵĴ�����࣬�����ڸ����
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
	//�жϸô��Ƿ��Ǹ����������ʵĵڶ��ַ�����һ������ĳһ����г��ֵĴ�����������������г��ֵĴ���֮��
	//�������̬��Ϊ0ʱ��������
	int key = 0;
	double m = 0, n = 0;
	ofstream out;
	out.open(file_name + type_name[key] + "keys");
	for(int i = 0; i < types_idf[key].size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		for(int j = 0; j < types_idf[key + 1].size(); j++) {		//������1�г��ֵ�Ƶ��
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
	//�������̬��Ϊ1ʱ��������
	key = 1;
	m = n = 0;
	out.open(file_name + type_name[key] + "keys");
	for(int i = 0; i < types_idf[key].size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		for(int j = 0; j < types_idf[key + 1].size(); j++) {		//������1�г��ֵ�Ƶ��
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
	//�������̬��Ϊ-1ʱ��������
	key = 2;
	m = n = 0;
	out.open(file_name + type_name[key] + "keys");
	for(int i = 0; i < types_idf[key].size(); i++) {
		if(i % 1000 == 0)
			cout<<i<<endl;
		for(int j = 0; j < types_idf[key - 2].size(); j++) {		//������0�г��ֵ�Ƶ��
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
// ���㲻ͬ���������еĸ�������
// �����ʱֱ��д���ļ���
// file_names	��Ų�ͬ������������дʵ��ĵ���
void WordTable::CalSubjectFeature(vector<string> file_names) {
	vector<vector<WordIDF>> types_idf;					//��Ų�ͬ���͵������ʣ���all
	vector<string> type_name;
	ifstream in;
	in.open("D:\\CCF\\train\\subject.txt");
	string s;
	while(getline(in,s)) {								//��ȡʮ���������ʹ�
		type_name.push_back(s);
	}
	in.close();
	for(int i = 0; i < file_names.size(); i++) {					//��ȡ���еĴ���
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
	//���㲻ͬ�������͵�������
	ofstream out_all;
	out_all.open("D:\\subject_word.txt");
	for(int key = 0; key < 10; key++) {							//һ��ѭ�����һ���������ʹʵĹ���
		double m = 0, n = 0;
		ofstream out;
		out.open(file_names[key] + "keys");							
		for(int i = 0; i < types_idf[key].size(); i++) {		//һ��ѭ�����һ���ʵĹ���
			if(types_idf[key][i].idf > 0.001) {
				vector<double> idf_temp;							//��¼�����������ʹʵĶ��ձ�
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
				//Ѱ�����idfֵ��Ϊһ����������ֵ
				/*int j;
				for(j = 0; j < idf_temp.size(); j++) {
					if(types_idf[key][i].idf <= idf_temp[j]) {
						break;
					}
				}
				if(j >= idf_temp.size()) {
					out<<types_idf[key][i].word<<' '<<types_idf[key][i].idf<<endl;
				}*/
				// ѡȡһ������idfֵԶ�����������Ĵ���Ϊ����ֵ
				double sum = 0;									//׼ȷ�ʣ�0.351586
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
// ���������ͳһ�Ĵʱ����ڱȽϼ������ƶ�
void WordTable::BuildAllCategoryWordTable() {
	ifstream in_IDF("D:\\CCF\\train\\GlobalIDF");
	if(!in_IDF)
		cout<<"Open GlobalIDF error"<<endl;
	map<string,double> global_idf;									//���ȫ��idf��
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
	//����ͳһ�����̬�ȱ�
	vector<string> file_names;
	file_names.push_back("D:\\CCF\\train\\idf_type0");
	file_names.push_back("D:\\CCF\\train\\idf_type1");
	file_names.push_back("D:\\CCF\\train\\idf_type-1");
	vector<vector<WordIDF>> word_idf_table;
	for(int i = 0; i < 3; i++) {								//��ȡ�������ʱ�
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
		for(int j = 0; j < word_idf_table[i].size(); j++) {			//��ʽ���������ͬ���Ĵʱ�
			map<string,double>::iterator iter;
			if(word_idf_table[i][j].idf > 0.0005) {
				double sum = 0;
				for(int k = 0; k < file_names.size(); k++) {		//����ô����������idfֵ���ܺ�
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
				if(word_idf_table[i][j].idf > sum) {							//�ô�������������
					if(iter != global_idf.end()) {
						out<<word_idf_table[i][j].word<<" "<<iter->second<<endl;
					}
					for(int k = 0; k < file_names.size(); k++) {		//ɾ���������ʱ��еĸô�
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
	//����ͳһ�������
	file_names.clear();
	file_names.push_back("D:\\CCF\\train\\idf_subject����");
	file_names.push_back("D:\\CCF\\train\\idf_subject�۸�");
	file_names.push_back("D:\\CCF\\train\\idf_subject����");
	file_names.push_back("D:\\CCF\\train\\idf_subject����");
	file_names.push_back("D:\\CCF\\train\\idf_subject��ȫ��");
	file_names.push_back("D:\\CCF\\train\\idf_subject���");
	file_names.push_back("D:\\CCF\\train\\idf_subject�ٿ�");
	file_names.push_back("D:\\CCF\\train\\idf_subject�ͺ�");
	file_names.push_back("D:\\CCF\\train\\idf_subject�ռ�");
	file_names.push_back("D:\\CCF\\train\\idf_subject������");
	word_idf_table.clear();
	for(int i = 0; i < file_names.size(); i++) {								//��ȡ�������ʱ�
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
		for(int j = 0; j < word_idf_table[i].size(); j++) {			//��ʽ���������ͬ���Ĵʱ�
			map<string,double>::iterator iter;
			if(word_idf_table[i][j].idf > 0.001) {
				double sum = 0;
				for(int k = 0; k < file_names.size(); k++) {		//����ô����������idfֵ���ܺ�
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
				if(word_idf_table[i][j].idf > sum) {							//�ô�������������
					if(iter != global_idf.end()) {
						out<<word_idf_table[i][j].word<<" "<<iter->second<<endl;
					}
					for(int k = 0; k < file_names.size(); k++) {		//ɾ���������ʱ��еĸô�
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