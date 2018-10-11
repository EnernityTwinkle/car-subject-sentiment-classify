import sys
import jieba

#segmentation
#@param : sentence  list
#@return : sen      str
def segmentation(sentence):
    seg_sentence = jieba.cut(sentence)           #type : Generator
    #print(type(seg_sentence))
    sen = " ".join(seg_sentence)                            #type : str
    #print(type(sen))
    return sen
#build keys table where idf's value > 0.01
#@return : keys_table   list[][]
def build_keys_table(file_names):
   i = 0
   keys_table = []
   while(i < len(file_names)):
       try:
            file_in = open(file_names[i], "r", encoding='utf-8')
       except IOError:
           print("Open " + file_names[i] + " error!")
           sys.exit(1)
       lines = file_in.readlines()
       single_keys = []
       if(i == 0):                                                  #人工添加的关键字
           single_keys.append("发动机")
           single_keys.append("性能")
       if(i == 1):
           single_keys.append("便宜")
       if(i == 3):
            single_keys.append("高配")
       if(i == 4):
           single_keys.append("可靠性")
       if(i == 5):
           single_keys.append("颜值")
       if(i == 6):
           single_keys.append("性能")
           single_keys.append("四驱")
       j = 0
       while(j < len(lines)):
           cut_ = lines[j].split()
           if(float(cut_[1]) > 0.01):
               single_keys.append(cut_[0])
           else:
               break
           j += 1
       keys_table.append(single_keys)
       file_in.close()
       i += 1
   return keys_table
#人工建立用于分句的词表
def artificial_cut_sentence_keys_table():
    keys_table = []
    temp = ["动力", "发动机", "性能", "机油"]
    keys_table.append(temp)
    temp = ["价格", "便宜", "优惠"]
    keys_table.append(temp)
    temp = ["内饰", "座椅", "材料", "做工", "细节"]
    keys_table.append(temp)
    temp = ["配置", "高配", "导航", "中控", "雷达"]
    keys_table.append(temp)
    temp = ["安全性", "可靠性", "安全", "气囊"]
    keys_table.append(temp)
    temp = ["外观", "颜值", "车身", "车漆", "前脸", "好看", "丑", "车尾", "难看", "颜色"]
    keys_table.append(temp)
    temp = ["操控", "性能", "启停", "四驱", "底盘", "方向"]
    keys_table.append(temp)
    temp = ["油耗", "省油", "费油"]
    keys_table.append(temp)
    temp = ["空间", "后备", "后排", "宽敞", "轴距"]
    keys_table.append(temp)
    temp = ["舒适性", "噪音", "空调", "舒适", "风噪"]
    keys_table.append(temp)
    print(len(keys_table))
    return keys_table
    # keys_table = []
    # temp = ["动力", "发动机", "性能", "机油"]
    # keys_table.append(temp)
    # temp = ["价格", "便宜", "优惠", "落地", "保险"]
    # keys_table.append(temp)
    # temp = ["内饰", "座椅", "材料", "做工", "细节", "用料"]
    # keys_table.append(temp)
    # temp = ["配置", "高配", "导航", "中控", "雷达", "车载"]
    # keys_table.append(temp)
    # temp = ["安全性", "可靠性", "安全", "气囊", "刹车油", "刹车盘"]
    # keys_table.append(temp)
    # temp = ["外观", "颜值", "车身", "车漆", "前脸", "好看", "丑", "车尾", "难看", "颜色", "漂亮", "色"]
    # keys_table.append(temp)
    # temp = ["操控", "性能", "启停", "四驱", "底盘", "方向", "全时"]
    # keys_table.append(temp)
    # temp = ["油耗", "省油", "费油", "排量", "个油"]
    # keys_table.append(temp)
    # temp = ["空间", "后备箱", "后排", "宽敞", "轴距"]
    # keys_table.append(temp)
    # temp = ["舒适性", "噪音", "空调", "舒适", "风噪", "声音", "响"]
    # keys_table.append(temp)
    # print(len(keys_table))
    # return keys_table
def artificial_build_keys_table():
    keys_table = []
    temp = ["动力", "发动机", "性能", "机油"]
    keys_table.append(temp)
    temp = ["价格", "便宜", "优惠", "落地", "保险"]
    keys_table.append(temp)
    temp = ["内饰", "座椅", "材料", "做工", "细节", "用料"]
    keys_table.append(temp)
    temp = ["配置", "高配", "导航", "中控", "雷达", "车载"]
    keys_table.append(temp)
    temp = ["安全性", "可靠性", "安全", "气囊", "刹车油", "刹车盘"]
    keys_table.append(temp)
    temp = ["外观", "颜值", "车身", "车漆", "前脸", "好看", "丑", "车尾", "难看", "颜色", "漂亮", "色"]
    keys_table.append(temp)
    temp = ["操控", "性能", "启停", "四驱", "底盘", "方向", "全时"]
    keys_table.append(temp)
    temp = ["油耗", "省油", "费油", "排量", "个油"]
    keys_table.append(temp)
    temp = ["空间", "后备箱", "后排", "宽敞", "轴距"]
    keys_table.append(temp)
    temp = ["舒适性", "噪音", "空调", "舒适", "风噪", "声音", "响"]
    keys_table.append(temp)
    print(len(keys_table))
    return keys_table
#将词表写出到文件中
#keys_table是一个二维列表；out_name是文件名
def print_keys_table(keys_table, out_name):
    try:
        file_out = open(out_name, "w", encoding='utf-8')
    except IOError:
        print("Open " + out_name + " error!")
        sys.exit(1)
    i = 0
    while i < len(keys_table):
        j = 0
        while j <len(keys_table[i]):
            file_out.write(keys_table[i][j] + '\n')
            j += 1
        i += 1
#删除含有subject关键字的内容
#sen_list里存放的是按照‘,’分开后的句子
#keys_table是关键字参照表
def delete_subject(sen_list, subject, keys_table, keys_current):
    sen_copy = sen_list[1]
    subjects = ["动力", "价格", "内饰", "配置", "安全性", "外观", "操控", "油耗", "空间", "舒适性"]
    i = subjects.index(subject)
    punc = {'，', '。', '？', '！', '、'}
    index = 0
    str = ""
    ing = 0
    #进行分句
    sentences = []
    sen_list[1] = sen_list[1].strip()
    while index < len(sen_list[1]):
        str += sen_list[1][index]
        if (sen_list[1][index] in punc):  # 遇到标点
            sentences.append(str)
            str = ""
            sen_list[1] = sen_list[1][index + 1:]
            index = 0
            continue
        index += 1
    if(len(str) > 0):
        sentences.append(str)
    str = ""
    flag = 0
    if(sen_copy.find(subject) == -1):                       #判断是否含有subject，如动力
        j = 0
        while j < len(keys_table[i]):
            if(sen_copy.find(keys_table[i][j]) != -1):
                break
            j += 1
        for sen in sentences:
            if(j >= len(keys_table[i])):
                str += sen
            elif (sen.find(keys_table[i][j]) == -1):          #没找到的句子留下
                str += sen
            else:                                              #找到的，应该只能含有一个，多个的只能删除关键词
                num = 0
                for word in keys_current:
                    if(sen.find(word) != -1):
                        num += 1
                if(num > 1):
                    sen = sen.replace(keys_table[i][j], "")
                    str += sen
    else:
        for sen in sentences:
            if(sen.find(subject) == -1):
                str += sen
            else:
                num = 0
                for word in keys_current:
                    if (sen.find(word) != -1):
                        num += 1
                if (num > 1):
                    sen = sen.replace(subject, "")
                    str += sen
    if(len(str) == 0):
        if(sen_copy.find(subject) == -1):
            j = 0
            while j < len(keys_table[i]):
                if (sen_copy.find(keys_table[i][j]) != -1):
                    break
                j += 1
            if(j < len(keys_table[i])):                                #在该句中找到特征词
                sen_copy = sen_copy.replace(keys_table[i][j], "")
        else:
            sen_copy.replace(subject, "")
        str += sen_copy
    return str.strip()
#进行句子划分，将对应多个主题的句子分为多个句子
#keys_table是关键词参照表
#针对训练集
def cut_sentences_train(lines):
    subjects = ["动力", "价格", "内饰", "配置", "安全性", "外观", "操控", "油耗", "空间", "舒适性"]
    keys_table = artificial_build_keys_table()                  #得到人工构建的词表
    sentences = []
    flag = 0
    i = 0
    while i < len(lines):
        keys_current = []
        #判断是否进行分句
        cut_ = lines[i].split(',')  # 按照','分模块
        same_sen_subject = []
        j = 0
        num = 0
        #print(cut_[1])
        while j < len(keys_table):
            for word in keys_table[j]:
                if(cut_[1].find(word) != -1):
                    #print(word)
                    keys_current.append(word)
                    same_sen_subject.append(subjects[j])                    #应该分成哪些主题
                    num += 1
                    break
            j += 1
        if(num <= 1):
            sentences.append(lines[i])
        else:
            cut_copy = cut_
            k = 0
            while k < len(same_sen_subject):
                if (cut_[2] != same_sen_subject[k]):                        #删除其他主题词
                    cut_copy[1] = delete_subject(cut_copy, same_sen_subject[k], keys_table, keys_current)
                k += 1
            sentences.append(cut_copy[0] + ',' + cut_copy[1] + ',' + cut_copy[2] + ',' + cut_copy[3] + ',' + cut_copy[4])
        same_sen_subject.clear()
        i += 1
    print(len(sentences))
    return sentences
def cut_sentences_model(keys_table):                                              #只是为了找到合适的分句模型，不用于真正分句
    subjects = ["动力", "价格", "内饰", "配置", "安全性", "外观", "操控", "油耗", "空间", "舒适性"]
    file_name = "D:\\CCF\\train\\sort_train"
    try:
        fpi = open(file_name, "r", encoding='utf-8')  # read file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\keys_word_cut_sentence"
    try:
        fpo = open(file_name, "w", encoding='utf-8')  # read file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\cut_sentence_error"
    try:
        fpo2 = open(file_name, "w", encoding='utf-8')  # read file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    lines = fpi.readlines()
    sentences = []
    same_sen = []
    same_sen_subject = []
    flag = 0
    i = 0
    while i < len(lines):
        #print(i)
        flag = 0
        cut_ = lines[i].split(',')                  #按照','分模块
        if(len(same_sen) == 0):
            flag = 1
            same_sen.append(cut_)
            same_sen_subject.append(cut_[2])
        elif(same_sen[0][0] == cut_[0]):
            flag = 1
            same_sen.append(cut_)
            same_sen_subject.append(cut_[2])
        if(flag == 0):                              #需要对same_sen进行处理
            #计算句子中subject主题的关键词
            keys_current = []
            j = 0
            while j < len(same_sen_subject):
                if(same_sen[j][1].find(same_sen_subject[j]) != -1):
                    if(len(same_sen_subject) > 1):
                        fpo.write(same_sen_subject[j] + " " + same_sen_subject[j] + '\n')
                    keys_current.append(same_sen_subject[j])
                else:
                    key = subjects.index(same_sen_subject[j])
                    flag = 0
                    for word in keys_table[key]:
                        if(same_sen[j][1].find(word) != -1):
                            if(len(same_sen_subject) > 1):
                                fpo.write(word + " " + same_sen_subject[j] + '\n')
                            flag = 1
                            keys_current.append(word)
                            break
                    if(flag == 0 and len(same_sen_subject) > 1):
                        fpo2.write(same_sen[j][0] + ',' + same_sen[j][1] + ',' + same_sen[j][2] + ',' + same_sen[j][3] + ',' +
                same_sen[j][4])
                j += 1
            j = 0
            while j < len(same_sen_subject):        #将其他subject类型的关键词去掉
                k = 0
                while k < len(same_sen_subject):
                    if(k != j):
                        same_sen[j][1] = delete_subject(same_sen[j], same_sen_subject[k], keys_table, keys_current)
                    k += 1
                sentences.append(same_sen[j][0] + ',' + same_sen[j][1] + ',' + same_sen[j][2] + ',' + same_sen[j][3] + ',' + same_sen[j][4])
                j += 1
            same_sen.clear()
            same_sen_subject.clear()
            same_sen.append(cut_)
            same_sen_subject.append(cut_[2])
        i += 1
    if(len(same_sen) > 0):                              #对最后可能剩下的句子进行处理
        keys_current = []
        j = 0
        while j < len(same_sen_subject):
            if (same_sen[j][1].find(same_sen_subject[j]) != -1):
                keys_current.append(same_sen_subject[j])
            else:
                key = subjects.index(same_sen_subject[j])
                for word in keys_table[key]:
                    if (same_sen[j][1].find(word) != -1):
                        keys_current.append(word)
                        break
            j += 1
        j = 0
        while j < len(same_sen_subject):  # 将其他subject类型的关键词去掉
            k = 0
            while k < len(same_sen_subject):
                if (k != j):
                    same_sen[j][1] = delete_subject(same_sen[j], same_sen_subject[k], keys_table, keys_current)
                k += 1
            sentences.append(
                same_sen[j][0] + ',' + same_sen[j][1] + ',' + same_sen[j][2] + ',' + same_sen[j][3] + ',' +
                same_sen[j][4])
            j += 1
    print(len(sentences))
    fpi.close()
    fpo.close()
    fpo2.close()
    return sentences
#测试集：进行句子划分，将对应多个主题的句子分为多个句子
def cut_sentences_test(lines):
    subjects = ["动力", "价格", "内饰", "配置", "安全性", "外观", "操控", "油耗", "空间", "舒适性"]
    keys_table = artificial_build_keys_table()  # 得到人工构建的词表
    cut_sentence_keys_table = artificial_cut_sentence_keys_table()
    sentences = []
    flag = 0
    i = 0
    while i < len(lines):
        # 判断是否进行分句
        cut_ = lines[i].split(',')  # 按照','分模块
        same_sen_subject = []
        keys_current = []
        j = 0
        num = 0
        while j < len(cut_sentence_keys_table):
            for word in cut_sentence_keys_table[j]:
                if (cut_[1].find(word) != -1):
                    keys_current.append(word)
                    same_sen_subject.append(subjects[j])  # 应该分成哪些主题
                    num += 1
                    break
            j += 1
        if (num <= 1):
            sentences.append(lines[i])
        else:
            j = 0
            while j < len(same_sen_subject):  # 将其他subject类型的关键词去掉
                cut_copy = lines[i].split(',')
                k = 0
                while k < len(same_sen_subject):
                    if (k != j):
                        cut_copy[1] = delete_subject(cut_copy, same_sen_subject[k], keys_table, keys_current)
                    k += 1
                sentences.append(cut_copy[0] + ',' + cut_copy[1])
                j += 1
            same_sen_subject.clear()
        i += 1
    print(len(sentences))
    return sentences
#寻找情态态度的关键词
def search_sentiment_keys():
    file_name = "D:\\CCF\\train\\sort_train"
    try:
        fpi = open(file_name, "r", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\keys0"
    try:
        fpo1 = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\keys1"
    try:
        fpo2 = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\keys-1"
    try:
        fpo3 = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    lines = fpi.readlines()
    for line in lines:
        cut_ = line.split(',')
        if(len(cut_[4]) > 0):
            if(cut_[3] == "0"):
                fpo1.write(cut_[4])
            if(cut_[3] == "1"):
                fpo2.write(cut_[4])
            if(cut_[3] == "-1"):
                fpo3.write(cut_[4])
    fpi.close()
    fpo1.close()
    fpo2.close()
    fpo3.close()
#根据情感态度的不同划分集合
def divide_sentence():
    file_name = "D:\\CCF\\train\\cut_train"
    try:
        fpi = open(file_name, "r", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\neg.txt"
    try:
        fpo1 = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\pos.txt"
    try:
        fpo2 = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    lines = fpi.readlines()
    for line in lines:
        cut_ = line.split(',')
        if(cut_[3] == "-1"):
            fpo1.write(cut_[1] + "\n")
        if(cut_[3] == "1"):
            fpo2.write(cut_[1] + '\n')
    fpi.close()
    fpo1.close()
    fpo2.close()
#单独划分出来内容和情感态度
def get_content_and_sentiment():
    file_name = "D:\\CCF\\train\\cut_test_train"
    try:
        fpi = open(file_name, "r", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\content.txt"
    try:
        fpo1 = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\sentiment.txt"
    try:
        fpo2 = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    lines = fpi.readlines()
    for line in lines:
        cut_ = line.split(',')
        # if(cut_[3] != "0"):
        #     fpo1.write(cut_[1] + '\n')
        #     fpo2.write(cut_[3] + '\n')
        fpo1.write(cut_[1] + '\n')
        fpo2.write(cut_[3] + '\n')
    fpi.close()
    fpo1.close()
    fpo2.close()

if __name__=="__main__":
    #get_content_and_sentiment()                                    #将内容和情感值写出到文件
    #divide_sentence()                                              #根据情感态度分出pos和neg文件
    #search_sentiment_keys()
    # file_names = []
    # file_names.append("D:\\CCF\\train\\idf_subject动力keys")
    # file_names.append("D:\\CCF\\train\\idf_subject价格keys")
    # file_names.append("D:\\CCF\\train\\idf_subject内饰keys")
    # file_names.append("D:\\CCF\\train\\idf_subject配置keys")
    # file_names.append("D:\\CCF\\train\\idf_subject安全性keys")
    # file_names.append("D:\\CCF\\train\\idf_subject外观keys")
    # file_names.append("D:\\CCF\\train\\idf_subject操控keys")
    # file_names.append("D:\\CCF\\train\\idf_subject油耗keys")
    # file_names.append("D:\\CCF\\train\\idf_subject空间keys")
    # file_names.append("D:\\CCF\\train\\idf_subject舒适性keys")
    #######################################寻找合适的训练集模型的分句################################################
    #keys_table = build_keys_table(file_names)                                  #建立关键词表
    #print_keys_table(keys_table, "D:\\CCF\\train\\keys_table")              #将词表写出到文件中
    #lines = cut_sentences_model(keys_table)                                       #寻找合适的训练集模型的分句
    #lines = cut_sentences_test(keys_table)                                  #测试集的分句
    ####################################进行训练集的分句##########################################################
    #file_name = "D:\\train_defined"
    file_name = "D:\\CCF\\train\\sort_train"
    try:
        fpi = open(file_name, "r", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    lines = fpi.readlines()
    lines = cut_sentences_train(lines)
    file_name = "D:\\CCF\\train\\segment_train"
    #file_name = "D:\\CCF\\train\\cut_train"
    try:
        fpo = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    i = 0
    while i < len(lines):
        cut_ = lines[i].split(',')                    #type : list
        cut_[1] = segmentation(cut_[1].strip())
        fpo.write(cut_[0] + "," + cut_[1].strip() + "," + cut_[2] + "," + cut_[3] + "," + cut_[4])
        i += 1
    fpo.close()
    #测试集分词
    file_name = "D:\\CCF\\train\\test_public"
    #file_name = "D:\\test_defined"
    try:
        fpi = open(file_name, "r", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    lines = fpi.readlines()
    lines = cut_sentences_test(lines)
    file_name = "D:\\CCF\\train\\segment_test"
    #file_name = "D:\\CCF\\train\\cut_test"                                     #仅用于提取出内容
    try:
        fpo = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    i = 0
    while i < len(lines):
        cut_ = lines[i].split(',')  # type : list
        cut_[1] = segmentation(cut_[1].strip())
        fpo.write(cut_[0] + "," + cut_[1].strip() + "\n")
        #fpo.write(cut_[1].strip() + '\n')                                      #仅用于提取出内容
        i += 1
    fpo.close()
