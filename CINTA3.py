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

def eulersTotient(n):
    z = 1
    for i in range(2, n):
        if (EX_GCD(i, n)[0] == 1):
            z+=1
    return z

print(eulersTotient(19));  #18
print(eulersTotient(72)); #24
