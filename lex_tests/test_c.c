main() {

	int a = 88;
	int b_ = 4;
	const c = 2;
	int d = (a + b_) / (c*(c+(10*2))); // should be 2
	//int dd = (a<b_)+(a==b)-(a>=b);
	if(a<b_) {
	   if(c == d) {
	       print(c);
	   } else {
            print(a);
        }
	}
	else {
	    print(b);
	}
    //int k = 2;
    //while(a < 18) {
     //   k = k+1;
     //   print(k);
    //}
    //print(k);
}
