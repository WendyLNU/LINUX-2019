from PIL import Image

im = Image.open('35.png').convert('RGBA')
_, _, _, alpha = im.split()
alpha = alpha.point(lambda i: 255)
im.putalpha(alpha)

im.save('luozi.png')