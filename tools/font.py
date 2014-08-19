import Image
import os

p = "./atlas/"
d = "../Resources/fonts/"

def generate_fnt(name):
    fonts = []
    for f in os.listdir(p):
        if f.startswith("%s_" % name):
            fonts.append(Image.open(p + f))
    h = fonts[0].size[1]
    gap = 1
    x = gap
    img = Image.new("RGBA", (x + sum(map(lambda m: m.size[0] + gap, fonts)), h))
    for m in fonts:
        img.paste(m, (x, 0))
        x += m.size[0] + gap
    img.save(d + "%s.png" % name)

    text = """\
info face="Arial" size=32 bold=0 italic=0 charset="" unicode=1 stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=1,1 outline=0
common lineHeight=32 base=26 scaleW=256 scaleH=45 pages=1 packed=0 alphaChnl=1 redChnl=0 greenChnl=0 blueChnl=0
page id=0 file="%s"
chars count=%d
""" % ("%s.png" % name, len(fonts))

    i = 48
    x = gap
    y = 0
    for m in fonts:
        w, h = m.size
        text += """\
char id=%d   x=%d     y=%d     width=%d    height=%d    xoffset=0     yoffset=0     xadvance=%d    page=0  chnl=15
""" % (i, x, y, w, h, w + gap)
        x += w + gap
        i += 1
    open(d + "%s.fnt" % name, "w").write(text)

generate_fnt("font")
generate_fnt("number_score")
