from imageio import imread, imwrite


a = imread(uri='black.png')
# print(type( a))
# print(len(a), len(a[0]))
height = len(a) 
width = len(a[0])

small_img = []
for i in range(0, height, 8):
    line = []
    for j in range(0, width, 8):
        a[i][j][1]=128
        line.append(a[i][j])
    small_img.append(line)
imwrite(uri='res.png',im=small_img)
# print(len(small_img), len(small_img[0]))

splited_img=[]
idx = 0
for i in range(0,8):
    for j in range(0,5):
        img_element = []
        if idx not in [15, 34]:
            for ii in range(0,40):
                img_elem_line = []
                for jj in range(0,20):
                    img_elem_line.append(1 if small_img[i*40+ii][j*20+jj][3] > 128 else 0)
                img_element.append(img_elem_line)
                print(' '.join([str(i) for i in img_elem_line]))
            print()

        idx += 1
        #imwrite(uri=f'res{i}{j}.png',im=img_element)

        #splited_img.append(img_element)
