import os
import base64

DIR = "./evilcorppubkeys"
USER = "shanaehudson"

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def minv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

def gcd(a, b):
	if a > b:
		a, b = b, a
	while a != 0:
		a, b = b%a, a
	return b

def process_formated_key(key):
	hexval = base64.b64decode(key).hex()
	hexarr = [hexval[i:i+2] for i in range(0, len(hexval), 2)]
	offset = 11
	e_size = int(''.join(hexarr[offset:offset+4]), 16)
	offset += 4
	e = int(''.join(hexarr[offset:offset+e_size]), 16)
	offset += e_size
	n_size = int(''.join(hexarr[offset:offset+4]), 16)
	offset += 4
	n = int(''.join(hexarr[offset:offset+n_size]), 16)
	return (n, e)

user_key = None

files = [val for sublist in [[os.path.join(i[0], j) for j in i[2]] for i in os.walk(DIR)] for val in sublist]
keys = []
for filename in files:
	file = open(filename, "r")
	words = ''.join(file.readlines()).split()
	key = words[1]
	user = words[2]
	n, e = process_formated_key(key)
	key = (n, e, user)
	keys.append(key)
	if user == USER:
		user_key = key
	file.close()
fact = []

for key in keys:
	n1 = user_key[0]
	n2 = key[0]
	g = gcd(n1, n2)
	if g != 1 and g != n1 and g != n2:
		fact.append(g)
		# print("\n---\n".join(map(repr,[n1, n2, g])), "\n\n\n")

n = user_key[0]
e = user_key[1]
p, q = fact
phi = (p-1)*(q-1)
d = minv(e, phi)
e1 = d%(p-1)
e2 = d%(q-1)
coeff = minv(q, p)

print(e,d,n,"\n\n")

s = f"""asn1=SEQUENCE:rsa_key

[rsa_key]
version=INTEGER:0
modulus=INTEGER:{n}
pubExp=INTEGER:{e}
privExp=INTEGER:{d}
p=INTEGER:{p}
q=INTEGER:{q}
e1=INTEGER:{e1}
e2=INTEGER:{e2}
coeff=INTEGER:{coeff}"""

file = open("key_spec.txt", "w")
file.write(s)
file.close()

os.system("openssl asn1parse -genconf key_spec.txt -out newkey.der")
os.system("openssl rsa -in newkey.der -inform der -text -check")

# Then save private key and use: 
# >> ssh shanaehudson@52.49.91.111 -p 2222 -i rsa_priv.txt