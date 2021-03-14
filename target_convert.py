from imageio import imread, imwrite


a = imread(uri='yi.png')

height = len(a)  #20
width = len(a[0]) #40

small_img = []
for i in range(0, height, 1):
    line = []
    for j in range(0, width, 1):
        a[i][j][1]=128
        line.append(a[i][j])
    small_img.append(line)
    
for ii in range(0,40):
    img_elem_line = []
    for jj in range(0,20):
        img_elem_line.append(1 if small_img[ii][jj][0] < 128 else 0)
    print(' '.join([str(i) for i in img_elem_line]))