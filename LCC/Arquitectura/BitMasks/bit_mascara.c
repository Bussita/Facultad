int is_one(long n, int b){
    if((n>>b-1)&1) return 1;
    return 0;
}

