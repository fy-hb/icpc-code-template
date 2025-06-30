import sys # 用法: python ./cmp.py ./a.out ./a.ans
get = lambda name : [float(i) for i in open(name, 'r').read().split()]
if __name__ == "__main__":
	a, b = get(sys.argv[1]), get(sys.argv[2])
	assert len(a) == len(b)
	for x, y, i in zip(a, b, range(len(a))):
		assert abs(x - y) / max(1, abs(y)) <= 1E-4, f"Wrong at {i+1}-th"
