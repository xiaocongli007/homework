//模指数运算迭代法
int modexp_iteration(int x,int y,int N){
    int result = 1 ;
    int count = 0;
    while(y>0){
        if(y& 1>0){
            result=int(result*pow(x,pow(2,count)))%N;
        }
        count++;
        y=y>>1;
    }
    if(result<0)
        return result+N;
    return result;
}
