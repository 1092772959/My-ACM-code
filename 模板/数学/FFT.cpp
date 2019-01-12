#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 2e5 + 10;
const double PI = acos(-1.0);
struct Complex{
    double x, y;
    inline Complex operator+(const Complex b) const {
        return (Complex){x +b.x,y + b.y};
    }
    inline Complex operator-(const Complex b) const {
        return (Complex){x -b.x,y - b.y};
    }
    inline Complex operator*(const Complex b) const {
        return (Complex){x *b.x -y * b.y,x * b.y + y * b.x};
    }
} va[MAXN * 2 + MAXN / 2], vb[MAXN * 2 + MAXN / 2];
int lenth = 1, rev[MAXN * 2 + MAXN / 2];
int N, M;   // f 和 g 的数量
    //f g和 的系数
    // 卷积结果
    // 大数乘积
int f[MAXN],
g[MAXN];
vector<LL> conv;
vector<LL> multi;
//f g
void init()
{
    int tim = 0;
    lenth = 1;
    conv.clear(), multi.clear();
    memset(va, 0, sizeof va);
    memset(vb, 0, sizeof vb);
    while (lenth <= N + M - 2)
        lenth <<= 1, tim++;
    for (int i = 0; i < lenth; i++)
        rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (tim - 1));
}
void FFT(Complex *A, const int fla)
{
    for (int i = 0; i < lenth; i++){
        if (i < rev[i]){
            swap(A[i], A[rev[i]]);
        }
    }
    for (int i = 1; i < lenth; i <<= 1){
        const Complex w = (Complex){cos(PI / i), fla * sin(PI / i)};
        for (int j = 0; j < lenth; j += (i << 1)){
            Complex K = (Complex){1, 0};
            for (int k = 0; k < i; k++, K = K * w){
                const Complex x = A[j + k], y = K * A[j + k + i];
                A[j + k] = x + y;
                A[j + k + i] = x - y;
            }
        }
    }
}
void getConv()
{
    init();
    for (int i = 0; i < N; i++)
        va[i].x = f[i];
    for (int i = 0; i < M; i++)
        vb[i].x = g[i];
    FFT(va, 1), FFT(vb, 1);
    for (int i = 0; i < lenth; i++)
        va[i] = va[i] * vb[i];
    FFT(va, -1);
    for (int i = 0; i <= N + M - 2; i++)
        conv.push_back((LL)(va[i].x / lenth + 0.5));
}
void getMulti()
{
    getConv();
    multi = conv;
    reverse(multi.begin(), multi.end());
    multi.push_back(0);
    for (int i = 0; i < multi.size() - 1; i++){
        multi[i + 1] += multi[i] / 10;
        multi[i] %= 10;
    }
    while (!multi.back() && multi.size() > 1)
        multi.pop_back();
    reverse(multi.begin(), multi.end());
}
//事先需要设置系数 f 和 g 和数组大小 N 和 M
//卷积结果保存 conv, 乘法结果保存 multi

char s1[MAXN], s2[MAXN];
