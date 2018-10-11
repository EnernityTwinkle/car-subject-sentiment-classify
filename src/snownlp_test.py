import sys
import jupyter
from snownlp import SnowNLP
from snownlp import sentiment

#对测试集进行预测
def predict_test():
    file_name = "D:\\CCF\\libsvm-3.23\\windows\\data\\result_sentiment"         #打开写出结果的文件
    try:
        fpo = open(file_name, "w", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    file_name = "D:\\CCF\\train\\segment_test"                                      #读入测试集的文本
    try:
        fpi1 = open(file_name, "r", encoding='utf-8')  # write file
    except IOError:
        print("Open " + file_name + "error!")
        sys.exit(1)
    contents = fpi1.readlines()
    i = 0
    count = 0
    while i < len(contents):
        # v = SnowNLP(contents[i]).sentiments
        # if (v > 0.99):
        #     #fpo.write(str(v) + " " + "1" + "\n")
        #     fpo.write("1\n")
        # elif (v < 0.01):
        #     fpo.write("-1\n")
        #     #fpo.write(str(v) + " -1\n")
        # else:
        #     fpo.write("0\n")
        #     count += 1
        #     #fpo.write(str(v) + " 0\n")
        fpo.write("0\n")
        i += 1
    print(count)
    fpo.close()
    fpi1.close()

if __name__=="__main__":
    # sentiment.train("D:\\neg.txt", "D:\\pos.txt")
    # sentiment.save('C:\\Users\\Jiayonghui\\Anaconda3.4\\Lib\\site-packages\\snownlp\\sentiment\\sentiment.marshal')
    # file_name = "D:\\content.txt"
    # try:
    #     fpi1 = open(file_name, "r", encoding='utf-8')  # write file
    # except IOError:
    #     print("Open " + file_name + "error!")
    #     sys.exit(1)
    # file_name = "D:\\sentiment.txt"
    # try:
    #     fpi2 = open(file_name, "r", encoding='utf-8')  # write file
    # except IOError:
    #     print("Open " + file_name + "error!")
    #     sys.exit(1)
    # contents = fpi1.readlines()
    # sentiments = fpi2.readlines()
    # step = 0.000001
    # threshold = 0.99999
    # while(threshold <= 1):
    #     print(threshold)
    #     i = 0
    #     count = 0
    #     count2 = 0
    #     while i < len(contents):
    #         #print(content)
    #         v = SnowNLP(contents[i]).sentiments
    #         # if(v > threshold):                                  #阈值为0.999999994
    #         #     print(v)
    #         #     if(sentiments[i].strip() == "1"):
    #         #         print(str(v) + "true")
    #         #         count += 1
    #         # elif(v < 0.00000001):                          #1e-08
    #         #     if(sentiments[i].strip() == "-1"):
    #         #         count += 1
    #         # elif(sentiments[i].strip() == "0"):
    #         #     count += 1
    #         if (v > threshold):  # 阈值为0.999999994
    #             print(v)
    #             if (sentiments[i].strip() == "1"):
    #                 print(str(v) + "true")
    #                 count += 1
    #         elif (sentiments[i].strip() == "0"):
    #                 count += 1
    #         i += 1
    #     print(count)
    #     print(count * 1.0 /len(contents))
    #     threshold += step
    predict_test()

