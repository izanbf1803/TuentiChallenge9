import codecs
import itertools

fin = codecs.open("in.txt", "r", "utf-8")
fout = codecs.open("out.txt", "w", "utf-8")

D = {}
D['一'] = 1;
D['二'] = 2;
D['三'] = 3;
D['四'] = 4;
D['五'] = 5;
D['六'] = 6;
D['七'] = 7;
D['八'] = 8;
D['九'] = 9;
M = {}
M['十'] = 10
M['百'] = 100
M['千'] = 1000
M['万'] = 10000
K = {}
V = {}
for key in D:
    K[D[key]] = key
    V[key] = D[key]
for key in M:
    K[M[key]] = key
    V[key] = M[key]
for dkey in D:
    if D[dkey] == 1: continue
    for mkey in M:
        K[M[mkey]*D[dkey]] = dkey+mkey
K[10000] = "一万" # special case


def kanji_decode(s):
    if len(s) == 0:
        return None
    lastd = -1
    ans = 0
    for c in s:
        x = V[c]
        if c in D: # digit
            if lastd == -1:
                lastd = x
            else:
                return None
        else: # multiple
            if lastd == -1:
                if x == 10000 and lastd == -1:
                    return None
                else:
                    ans += x
            else:
                if lastd == 1 and x != 10000:
                    return None
                else:
                    ans += x*lastd
            lastd = -1
    if lastd != -1:
        ans += lastd
    return ans

def kanji_encode(n):
    if n == 0:
        return None
    ans = []
    pot = 0
    if n % 10 != 0:
        ans.append(K[n%10])
    n //= 10
    while n > 0:
        pot += 1
        k = n % 10
        if k != 0:
            ans.append(K[k*10**pot])
        n //= 10
    return ''.join(reversed(ans))

def backtrack(v, i, ans):
    if i == 2:
        # fout.write(' '.join([repr(i), repr(ans)])+"\n")
        x = ans[0]*ans[1]
        if x >= 1 and x <= 99999 and sorted(kanji_encode(x)) == sorted(v[2]):
            return ('*', ans[0], ans[1], x)
        x = ans[0]+ans[1]
        if x >= 1 and x <= 99999 and sorted(kanji_encode(x)) == sorted(v[2]):
            return ('+', ans[0], ans[1], x)
        x = ans[0]-ans[1]
        if x >= 1 and x <= 99999 and sorted(kanji_encode(x)) == sorted(v[2]):
            return ('-', ans[0], ans[1], x)
    else:
        valid = {}
        for k in itertools.permutations(v[i]):
            n = kanji_decode(k)
            if n != None:
                valid[n] = True
        for n in valid: # avoid repeating the same number
            ans[i] = n
            res = backtrack(v, i+1, ans)
            if res != None: return res
    return None


### TESTS: ###
TESTK = [
    "十一",
    "四十八",
    "百五十一",
    "三百二",
    "四百六十九",
    "二千二十五",
    "千百十",
    "二千三百四十五",
    "一万百十四",
    "五万四千七百三十二",
]
TESTN = [
    11,
    48,
    151,
    302,
    469,
    2025,
    1110,
    2345,
    10114,
    54732,
]
assert len(TESTK) == len(TESTN)
for i in range(len(TESTK)):
    assert kanji_encode(TESTN[i]) == TESTK[i]
    assert kanji_decode(TESTK[i]) == TESTN[i]
for i in range(1, 99999+1):
    if kanji_decode(kanji_encode(i)) != i:
        print (i)
        assert False 
### END TESTS ###

n = int(fin.readline())
for test in range(n):
    line = fin.readline().replace(" ","").replace("\n","").replace("\r","")
    a, bc = line.split("OPERATOR")
    b, c = bc.split("=")

    ################
    # s = {}
    # for x in itertools.permutations(b):
    #     x = ''.join(x)
    #     if kanji_decode(x) != None:
    #         fout.write(x+" "+repr(kanji_decode(x))+"\n")
    #         s[kanji_decode(x)] = 1
    # for e in s:
    #     print(e)
    # print(len(s))
    ################

    sol = backtrack([a, b, c], 0, [-1, -1, -1])
    print(sol)
    if sol == None:
        fout.write(f"Case #{test+1}: ERR\n\r")
    else:
        fout.write(f"Case #{test+1}: {sol[1]} {sol[0]} {sol[2]} = {sol[3]}\n")
        # fout.write(f"Case #{test+1}: {kanji_encode(sol[1])} {sol[0]} {kanji_encode(sol[2])} = {kanji_encode(sol[3])}\n")
fin.close()
fout.close()

# kanji = "五万四千七百三十二"
# n = 10114
# fout.write(' '.join([ repr(kanji), repr(kanji_decode(kanji)) ])+"\n")
# fout.write(' '.join([ repr(n), repr(kanji_encode(n)) ]) +"\n")