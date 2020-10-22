#include <bits/stdc++.h>

using namespace std;


bool solve(string s1, string s2, long long int len)
{

	long long int h1 = 0,h2 = 0;
	long long int prime=7; // Base prime to calculate hash
	map<string, long long int> st_hash; // To store hash values of strings
	string dummy="";
	dummy=s1.substr(0,len);
	long long int i,val;
	for(i=0;i<len;i++)
	{
		val=(long long int)pow(prime,i);
		val=(long long int)(s1[i]-'a')*val;
		h1 = h1 + val;
	}
	st_hash[dummy]=h1; //Calculation of first hash of string of length len of first string

	for(i=len;i<s1.length();i++)  // This will calculate rolling hash, remove last char and append new character
	{
		dummy = s1.substr(i-len+1,len);
		h1 = h1-(long long int)(s1[i-len]-'a');
		val = (long long int)pow(prime,len-1);
		h1 = h1/prime + (long long int)(s1[i]-'a')*val;
		st_hash[dummy] = h1; // Storing all other lenlength hashes of string 1.
	}

	// Now for string 2 same process
	dummy=s2.substr(0,len);
	for(i=0;i<len;i++)
	{
		val=(long long int)pow(prime,i);
		val=(long long int)(s2[i]-'a')*val;
		h2 = h2 + val;
	}
	// Instead of storing we will now compare if the hash value is present or not.

	if(st_hash[dummy]==h2)
		return true;

	for(i=len;i<s2.length();i++)  // This will calculate rolling hash, remove last char and append new character
	{
		dummy = s2.substr(i-len+1,len);
		h2 = h2-(long long int)(s2[i-len]-'a');
		val = (long long int)pow(prime,len-1);
		h2 = h2/prime + (long long int)(s2[i]-'a')*val;
		if(st_hash[dummy]==h2) // Checking if hash matches
			return true;
	}
	return false; // No hash matches hence no common substring of length len
}

int main()
{
	string s1,s2;
	s1 = "111111112222222222229999999999shourabh0000000000000009999999999999999";
	s2 = "3333333333333333333333rabh8888888888888888";
	long long int l1=s1.length();
	long long int l2=s2.length();

	long long int r=min(l1,l2),l=0,mid;
	
	

	while(l<=r)
	{
		mid=l + (r-l)/2;
		if(solve(s1,s2,mid))
			l=mid+1;
		else
			r=mid-1;
	}
	cout<<"Length of longest common substring is "<<l-1<<endl;
	return 0;
}
