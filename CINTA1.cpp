#include<iostream>
using namespace std;
int add(int a,int b);

/*以下是基于位运算的乘法*/
int multiply(int a, int b) {
    //使用flag计算结果的符号
    int flag = 1;
    if((a^b)<0)
        flag=-1;
    //将a和b取绝对值再进行计算
    a=a<0?-a:a;
    b=b<0?-b:b;
    int result = 0;
    while(b > 0) {
        if((b & 0x1) > 0) {             // 每次考察乘数的最后一位　　　　
            result = add(result,a);     //等价于result=result+a,  add是基于位运算的加法。
        }
        a = a << 1;// 每运算一次，a*2　　　
        b = b >> 1;// 每运算一次,b右移一位，从而在下一轮循环中检查b的最后一位。　
    }
    if(flag==-1)
        return -result;
    return result;
}



/*以下是基于位运算的GCD实现,思路同stein算法*/
int binaryGCD(int u,int v){
    int count;

    if (u == 0) {
        return v;
    }

    if (v == 0) {
        return u;
    }
    //当两数均为偶数时将其同时除以2至至少一数为奇数为止，记录除掉的所有公因数2的乘积,即2的count次方,这部分就是公因数中含偶数因子的部分
    for (count = 0; ((u | v) & 1) == 0; ++count) {
        u >>= 1;
        v >>= 1;
    }
    //下面用普通的欧几里得算法（辗转相减法）计算公因数中不为偶数因子的部分
    while ((u & 1) == 0) {
        u >>= 1;
    }

    do {

        while ((v & 1) == 0) {
            v >>= 1;
        }

        if (u > v) {
            int t = v;
            v = u;
            u = t;
        }

        v = v - u;

    } while (v != 0);

    //最大公因数即为（最大公因数中含偶数因子的部分）乘以（最大公因数中不含偶数因子的部分）
    return u << count;
}




int add(int a, int b) {
    if (b == 0) { return a; }
    int temp = a ^ b;
    b = (a & b) << 1;
    a = temp;
    return add(a, b);
}

int subtract(int a, int b) {
    a = add(a, ~b + 1);
    return a;
}
int Divide(int a,int b){
    int q=0;
    while(a>=b){
        a=subtract(a,b);
        q=add(q,1);
    }
    return q;
}
int mod(int a,int b){
    int r=0;
    while(a>=b){
        a=subtract(a,b);
    }
    r=a;
    return r;
}

//binary-egcd的递归版本
int binary_EX_GCD_recurse(int a,int b,int *x,int *y){
    if(b==0){
        *x=1,*y=0;
        return a;
    }
    int r = binary_EX_GCD_recurse(b,mod(a,b),x,y);          //等价于int r = binary_EX_GCD(b,a%b,x,y);
    int t = *x;
    *x = *y;
    *y = subtract(t,multiply(Divide(a,b),*y));      //等价于*y = t-a/b**y;
    return r;
}


//binary-egcd的迭代版本
int Binary_EX_GCD_iteration(int a,int b,int &s0,int &t0){
    s0=1;t0=0;
    int s1=0,t1=1;
    int temp,s_temp,t_temp;
    while(b){
        int q = Divide(a,b);

        temp=a;
        a=b;
        b=mod(temp,b);          //b=temp%b;

        s_temp=s0;
        s0=s1;
        s1=subtract(s_temp,multiply(q,s1)); //s1=s_temp-q*s1;

        t_temp=t0;
        t0=t1;
        t1=subtract(t_temp,multiply(q,t1)); //t1=t_temp-q*t1;

    }
    return a;

}

/*Demo展示*/
int main(){
    cout<<"Demo展示:"<<endl;
    cout<<"使用simple Multiplication计算:-2*256="<<multiply(-2,256)<<endl;
    cout<<"使用BinaryGCD算法计算出：12345和678的最大公因数是:"<<binaryGCD(12345,678)<<endl;
    int x=0,y=0;
    cout<<"使用Binary_EX_GCD_recurse算法计算出：12345和678的最大公因数是:"<<binary_EX_GCD_recurse(12345,678,&x,&y)<<",系数是:"<<x<<","<<y<<endl;
    int s=0,t=0;
    cout<<"使用Binary_EX_GCD_iteration算法计算出：12345和678的最大公因数是:"<<Binary_EX_GCD_iteration(12345,678,s,t)<<",系数是:"<<s<<","<<t<<endl;
    return 0;
}
