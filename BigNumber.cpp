#include <iostream>
#include <string>
int length(std::string s)
{
	int i=0;
	while(s[i]>='0' && s[i]<='9')
	{
		i++;
	}
	return i;
}
class BigNum
{

private:
	friend std::ostream& operator<<(std::ostream& os,const BigNum& n);
	friend std::istream& operator>>(std::istream& os, BigNum& n);
	friend bool operator>(const BigNum& n1,const BigNum& n2);
	friend bool operator==(const BigNum& n1,const BigNum& n2);
	int* values;
	int count;
public:
	BigNum(std::string str="0")
	{
		int len=length(str);
		this->count=len;
		this->values=new int[len];
		for(int i=0;i<len;i++)
		{
			this->values[i]=str[i]-'0';
		}
	}

	virtual ~BigNum()
	{
		delete[] values;
	}
	BigNum operator+(const BigNum& other)
	{
		int i=other.count;
		int j=this->count;
		int carry,a0,a1;
		
		int max=(i>=j)?i:j;
		
		char* result=new char[max+1];
		char *pointer=&result[max];
		i--;
		j--;
		while(j>=0 || i>=0)
		{
			if(i==-1)
			{
				a0=0;
				a1=this->values[j];
				j--;
			}
			else if(j==-1)
			{
				a0=other.values[i];
				a1=0;
				i--;
			}
			else{
				a0=other.values[i];
				a1=this->values[j];
				i--;
				j--;
			}
			*pointer=((a0+a1+carry)%10)+'0';
			pointer--;
			carry=(a0+a1)/10;
		}
		result[0]='0'+carry;
		BigNum res=BigNum(result);
		delete[] result;
		return res;
		
		
	}
};
//TODO:mutipie 
std::ostream& operator<<(std::ostream& os,const BigNum& n)
{
	int start=0;
	while(n.values[start]==0){
		start++;
	}
	for(int i=start;i<n.count;i++)
	{
		std::cout<<n.values[i];
	}
	return os;
}
std::istream& operator>>(std::istream& os,BigNum& n)
{
	std::string s;
	os>>s;
	int length=s.length();
	int* array=new int[length];
	for(int i=0;i<length;i++)
	{
		array[i]=s[i]-'0';
	}
	delete n.values;
	n.values=array;
	n.count=length;
	return os;
}

	bool operator==(const BigNum& n1,const BigNum& n2)
	{
		int len1=n1.count;
		int len2=n2.count;
		if(len2!=len1)
		{
			return false;
		}
		for(int i=0;i<len1;i++)
		{
			if(n1.values[i]!=n2.values[i])
			{
				return false;
			}
			
		}
		return true;
	}
	bool operator>(const BigNum& n1,const BigNum& n2)
	
	{
		int len1=n1.count;
		int len2=n2.count;
		if(len1>len2 || len2>len1)
		{
			return len1>len2;
		}
		for(int i=0;i<len1;i++)
		{
			if(n1.values[i]>n2.values[i]){
				return true;
			}
			else if(n1.values[i]<n2.values[i])
			{
				return false;
			}
		}
		return false;
	}

int main()
{
	BigNum a=BigNum("2");
	BigNum b;
	std::cin>>b;
	BigNum c=a+b;
	std::cout <<c;
	
}