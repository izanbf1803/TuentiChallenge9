import os
import base64

DIR = "./evilcorppubkeys"

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

shanaehudson_key = None

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
	if user == "shanaehudson":
		shanaehudson_key = key

fact = []

for key in keys:
	n1 = shanaehudson_key[0]
	n2 = key[0]
	g = gcd(n1, n2)
	if g != 1 and g != n1 and g != n2:
		fact.append(g)
		# print("\n---\n".join(map(repr,[n1, n2, g])), "\n\n\n")

p, q = fact


# for i in range(len(keys)):
# 	for j in range(i+1,len(keys)):
# 		ni = keys[i][0]
# 		nj = keys[j][0]
# 		g = gcd(ni, nj)
# 		if g != 1 and g != ni and g != nj:
# 			print("\n---\n".join(map(repr,[ni, nj, g])), "\n\n\n")