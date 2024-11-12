import os
changepath='E:\\dopython\\山火\\Wildfire Smoke.v1-raw.coco\\labels\\valid'


path_list=os.listdir(changepath)
for i in path_list:
    data=''
    with open(changepath+"\\"+i,'r') as f:
        textline=f.readlines()
        for j in textline:
            line=j.split(' ')
            line[0]='0'
            data+=' '.join(line)
            data+='\n'

    with open(changepath+"\\"+i,'w') as f:
        f.write(data)

