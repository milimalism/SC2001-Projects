def PreprocessCase1(P):
    length = len(P)
    bpos= [0 for i in range(length + 1)]
    shift = [0 for i in range(length + 1)]
    i = len(P)
    j= len(P) + 1
    bpos[i] = j
    while(i > 0):
        while(j <= len(P) and P[i-1] != P[j-1]):
            if(shift[j] == 0):
                shift[j] = j - i
    
        j = bpos[j] 
    i=-1
    j=-1
    bpos [i] = j


def main():
    P = "wowwow"

    PreprocessCase1(P)


main()