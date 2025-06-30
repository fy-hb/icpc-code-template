void gen(int a, int b, int c) {
    gen( a + 2 * b + 2 * c,  2 * a + b + 2 * c,  2 * a + 2 * b + 3 * c);
    gen(-a + 2 * b + 2 * c, -2 * a + b + 2 * c, -2 * a + 2 * b + 3 * c);
    gen( a - 2 * b + 2 * c,  2 * a - b + 2 * c,  2 * a - 2 * b + 3 * c);
} // 用法: gen(3, 4, 5) 遍历所有 a < b 的素勾股数
