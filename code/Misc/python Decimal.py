from decimal import Decimal, getcontext, localcontext
getcontext().prec = 1000 # 全局环境 精度为 1000
with localcontext() as ctx:
	ctx.prec = 1000 # 临时环境
a = Decimal("1.14514") # a.sqrt(), a.ln(), a.exp(), ...
