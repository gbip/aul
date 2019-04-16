main() {

	int a = 1;
	int b_ = 4;
	const c = 2;
	int d = 3;//(a + b_) / (c*(c+(10*2))); // should be 2
	//int dd = (a<b_)+(a==b)-(a>=b);
	print(d);
	if(a<b_) {
	   if(c == d) {
	       print(c);
	   } else {
            print(a);
        }
	}
	else {
	    c = 3;
	    print(b_);
	}
    //int k = 2;
    //while(a < 18) {
     //   k = k+1;
     //   print(k);
    //}
    //print(k);
}
