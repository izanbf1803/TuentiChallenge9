import codecs

fin = codecs.open("in.txt", "r", "utf-8")
fout = codecs.open("out.txt", "w", "utf-8")

d = {}
d['一'] = 1;
d['二'] = 2;
d['三'] = 3;
d['四'] = 4;
d['五'] = 5;
d['六'] = 6;
d['七'] = 7;
d['八'] = 8;
d['九'] = 9;
m = {}
m['十'] = 10
m['百'] = 100
m['千'] = 1000
m['万'] = 10000

n = int(fin.readline())
for test in range(n):
    line = fin.readline().replace(" ","")
    a, bc = line.split("OPERATOR")
    b, c = bc.split("=")
    fout.write(a+" "+b+" "+c)

fin.close()
fout.close()