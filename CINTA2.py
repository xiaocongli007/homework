#求乘法逆元要用到EGCD
def EX_GCD(a,b):
    s0=1;t0=0;s1=0;t1=1

    while(b):
        q = a//b;

        temp=a;
        a=b;
        b=temp%b;

        s_temp=s0;
        s0=s1;
        s1=s_temp-q*s1;

        t_temp=t0;
        t0=t1;
        t1=t_temp-q*t1;


    return a,s0,t0;

#求乘法逆元
def multipy_inverse(a,n):
    EX_list = EX_GCD(a,n);
    if EX_list[0]!= 1:
        print("无解")
    else:
        a_inverse = EX_list[1];
    return a_inverse;




def fun(a,b,m):


    EX_list = EX_GCD(a, m);

    #a的逆存在时，方程两边同乘a逆
    if(EX_GCD(a,m)[0]==1):
        a_inverse=EX_list[1];
        return (b*a_inverse)%m;

    #a的逆不存在时，暴力法
    else:
        resultList = []
        for num in range(1,m-1):
            if((a*num-b)%m==0):
                resultList.append(num);
        if(resultList!=[]):
            return resultList;


print(multipy_inverse(3,11));   #输出4
print(fun(3,2,11));     #输出8
print(fun(7,3,13));     #输出6
print(fun(7,3,14))      #输出None，代表无解
print(fun(6,12,24));    #输出【2，6，10，14，18，22】