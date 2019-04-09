main() {

	int a = 88;
	int b_ = 4;
	const c = 2;
	int d = (a + b_) / (c*(c+(10*2))); // should be 2
	int dd = (a<b_)+(a==b)-(a>=b);
	print(d);
	if(a+b) {
		print(a);
		if((a == b)) {
		    a = b;
		}
	} else {
		b = 2*b;
	}
}
