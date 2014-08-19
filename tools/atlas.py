import Image
import os

atlas = './atlas/'
if not os.path.exists(atlas):
    os.mkdir(atlas)

png = Image.open("atlas.png")
for line in open("atlas.txt"):
    infos = line.split(" ")
    pos = int(float(infos[3]) * png.size[0]), int(
        float(infos[4]) * png.size[1])
    box = (pos[0], pos[1], pos[0] + int(infos[1]), pos[1] + int(infos[2]))
    png.crop(box).save(atlas + infos[0] + ".png")
