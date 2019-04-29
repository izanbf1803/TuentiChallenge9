import codecs

def bin2hex(s):
    ans = ""
    for c in s:
        h = hex(ord(c))[2:]
        if len(h) == 1:
            h = "0"+h
        ans += h
    return ans

auth_cookie = "0c82c312c766e23720b76cd1255aa5ae"
empty_str_md5 = "d41d8cd98f00b204e9800998ecf8427e"

userMd5 = codecs.decode(empty_str_md5, "hex")
result = ""
for i in range(len(userMd5)):
    for c in range(256): # find solution for each byte
        if bin2hex(chr((c + userMd5[i]) % 256)) == auth_cookie[2*i:2*i+2]:
            result += bin2hex(chr(c))
    # result += bin2hex(chr((authKey[i] + userMd5[i]) % 256)) # original operation

print(result, codecs.decode(result, "hex"))