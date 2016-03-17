import subprocess


def run(args):
	return subprocess.Popen(args, stdout=subprocess.PIPE).communicate()[0].decode("utf8")


def test(n, t):
	res = run(["./prime", str(n), str(t)]).split("\n")

	try:
		if (len(res) != 5):
			raise Exception("Not 5 lines")
		if (res[0] != res[2]):
			raise Exception("Not same answer")

		return int(res[1]), int(res[3])
	except:
		print(n, t, res)

def bench(n, t, s):
	single = 0
	thread = 0

	for i in range(0, s):
		(st, tt) = test(n, t)
		single += st
		thread += tt

	return single / s, thread / s

print(bench(99194853094755499, 4, 1))
