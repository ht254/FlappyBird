import os
import sys

sys.stdout = file("../Classes/Path.h", "w")
R = "../Resources/"

print '#ifndef __PATH_H__'
print '#define __PATH_H__'
print
print '#define FONTS_DIR  "fonts/"'
print '#define MUSICS_DIR "musics/"'
print '#define IMAGES_DIR "images/"'
print
print '#define FNT_FONT    FONTS_DIR"font.fnt"'
print '#define FNT_SCORE   FONTS_DIR"number_score.fnt"'
print
for platform, extension in [('CC_PLATFORM_WIN32', '.wav'), ('CC_PLATFORM_ANDROID', '.ogg'), ('CC_PLATFORM_IOS', '.wav')]:
    print '#if (CC_TARGET_PLATFORM == %s)' % platform
    for f in os.listdir(R + "musics/"):
        base, ext = os.path.splitext(f)
        if ext == extension:
            print "    #define", base.upper().ljust(14), 'MUSICS_DIR"%s"' % f
    print '#endif'
print
for f in os.listdir(R + "images/"):
    base, ext = os.path.splitext(f)
    if ext == ".png":
        print "#define", "IMG_" + base.upper().ljust(18), 'IMAGES_DIR"%s"' % f
print
print '#endif // __PATH_H__'

sys.stdout.flush()
sys.stdout.close()
