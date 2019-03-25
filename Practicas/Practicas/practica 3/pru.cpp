#include <cstring>
#include <cstdio>
#include <iostream>
#include <tgmath.h>

using namespace std;

#define aureo 1.6680889885
#define tam 120

int lalo(char cad[]){
	int mul=1, i, tamCad = sizeof(&cad), dif=0, dif2=0;
	double res;
	float temp;

	for(i=0; i<tamCad; i++){
		mul = mul * cad[i];
		if(i%2==0)
			dif = dif + cad[i];
		if(i%3 == 0)
			dif2 = dif2 +1;
	}
	mul = mul*aureo;
	mul = mul/dif+tamCad;
	mul = mul%250;

	res = exp(mul)/dif2+dif;
	while(res>3500){
		res = res/exp(aureo);
		// res = res + dif2*exp(dif);
	}

	temp = (float)res+tamCad*aureo;
	mul=0;
	mul = ((int)temp)%tam;

	return mul;
}

int pao(char cad[]){
	int i, s, o, p;
	float mul;
	i=0;
	s=0;
	o=0;
	p = (int)cad[0];

	for(i=0; i<strlen(cad); i=i+1){
		s = s + (int)cad[i];
	}

	mul = ((float)s*(float)aureo*(float)p);
	o = (int)mul;

	if(o<0){
		o = o*(-1);
	}

	o = o%tam;

	return o;
}

int main(){
	string s;
	int i;

	char pal[40];

	while(cin >> s){
		for(i=0; i<s.size(); i++){
			pal[i] = (char)s[i];
			cout << pal[i] << ": " << (int)pal[i] << "  " << endl;
		}
		pal[i] = '\0';
		cout << s << "\t" << lalo(pal) << "\t" << pao(pal) << endl;
	}

	return 0;
}