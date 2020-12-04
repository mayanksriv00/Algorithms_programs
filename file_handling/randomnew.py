import random
col=int((input("enter the size of each instance ")))
fh = open('./sample.txt','w')
Mat = []
for i in range (0,20):
    l = random.sample(range(0,4294967295),col)
    out=""
    for ele in l:
        out = out + str(ele)+" "
    fh.write(out+"\n") 
fh.close()
