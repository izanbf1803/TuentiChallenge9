import binascii
from PIL import Image

def gen_image(w, h, bits):
    img = Image.new("RGB", (w,h), (255,255,255))
    pixel = img.load()
    for x in range(w):
        for y in range(h):
            c = 255*(bits[x*w+y]=="1")
            pixel[x,y] = (c,c,c)
    img.save(f"{w}x{h}.png")

FILE = "artifact.jar"
f = open(FILE, "rb")
data = binascii.hexlify(f.read())
data = [data[2*i:2*i+2] for i in range(len(data)//2)]
bits = ""
for byte in data:
    bits += "{:08b}".format(int(byte,16))

n = len(bits)
k = 1
while k*k <= n:
    if n % k == 0:
        gen_image(k, n//k, bits)
    k += 1