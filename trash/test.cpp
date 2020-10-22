#include<iostream>
#include<vector>
#include <stdlib.h>
#include <sys/types.h>
       #include <unistd.h>
using namespace std;

int main()
{	
	char a = 'a';
	void  *p = &a;
	cout<<p<<endl;
	cout<<((char *)p)<<endl;
}
