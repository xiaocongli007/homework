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


/*
    以下是binary版的扩展欧几里得算法实现思路：
    因为扩展欧几里德算法的计算过程中，还会像辗转相除法一样需要mod的计算，所以我需要先用位计算实现mod，这就又要求我先用位计算实现减法，
而位运算实现减法又需要我先用位运算实现加法。
    所以需要做的工作是：
    （1）位计算实现加法
    （2）位计算实现加法后，在此基础上实现位计算的减法
    （3）位计算实现减法后，在此基础上实现基于位运算的mod(思路同naive的除法算法)
    （4）在（3）的基础实现基于位运算的扩展欧几里得。
 */

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

int binary_EX_GCD(int a,int b,int *x,int *y){
    if(b==0){
        *x=1,*y=0;
        return a;
    }
    int r = binary_EX_GCD(b,mod(a,b),x,y);          //等价于int r = binary_EX_GCD(b,a%b,x,y);
    int t = *x;
    *x = *y;
    *y = subtract(t,multiply(Divide(a,b),*y));      //等价于*y = t-a/b**y;
    return r;
}




/*Demo展示*/
int main(){
    cout<<"Demo展示:"<<endl;
    cout<<"使用simple Multiplication计算:-2*256="<<multiply(-2,256)<<endl;
    cout<<"使用BinaryGCD算法计算出：12345和678的最大公因数是:"<<binaryGCD(12345,678)<<endl;
    int x=0,y=0;
    cout<<"使用Binary_EX_GCD算法计算出：12345和678的最大公因数是:"<<binary_EX_GCD(12345,678,&x,&y)<<",系数是:"<<x<<","<<y<<endl;
    return 0;
}