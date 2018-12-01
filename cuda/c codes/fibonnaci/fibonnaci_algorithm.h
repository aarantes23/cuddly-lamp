unsigned long long iterativeFibonnaci(int nSize) {
    unsigned long long nMinus2 = 0;
    unsigned long long nMinus1 = 1;
    unsigned long long n;
    int counter = nSize;

    for (int x = 2; x <= counter; x++){
        n = nMinus2 + nMinus1;
        nMinus2 = nMinus1;
        nMinus1 = n;
    }

    if (nSize == 0)
        return 0;
    else if (nSize == 1)
        return 1;
    else
        return n;
}

unsigned long long recursiveFibonnaci(int nSize) {
    switch (nSize){
        case 0:
            return 0;
            break;
        case 1:
            return 1;
            break;
        default:
            return recursiveFibonnaci( (nSize - 2) ) + recursiveFibonnaci( (nSize - 1) );
    }
}