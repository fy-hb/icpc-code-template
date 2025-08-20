from fractions import Fraction
a = Fraction(3, 4)    # 3/4
print(f.numerator, f.denominator) # 3 4
# 找到最接近的分数，分母不超过指定值
Fraction('3.1415926535897932').limit_denominator(10)  # 22/7
Fraction('3.1415926535897932').limit_denominator(100)  # 311/99
