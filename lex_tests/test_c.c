main() {
    if(1 <= 0) {
        int a = 1;
        int k = 1;
        int i = 0;
        while (a <= 3) {
            a = a + 1;
            while (i < 10) {
                k = k + 1;
                i = i + 1;
            }
            i = 0;
        }
        print(a);
        print(k);
    } else {
        int i1 = 1;
        int i2 = 2;
        int i3 = 3;
        int i4 = 4;
        if(((i1 < i2) && ((i2 > i3) || (i4 > i1)))) {
            int a = 12;
            print(a);
        } else {
            int b = -(17*(14/2))/(1+2+3+4+((18/2)+1+(10-2))); // should be 4
            print(b);
            while(!(b >= 4)) {
               b = b + 1;
               print(b);
            }
            print(b);
        }
        int a = 1;
        print(a);
    }
    int m = 2;
    print(m);


    //k=1;
    //int k = 2;
    //while(a < 18) {
    //   k = k+1;
    //   print(k);
    //}
    //print(k);
}
