//2016.11.12
//把進位就往後找經過7的4寫成函數 find4after7
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
string ans;
bool carry= false;//進位了沒
int len, n4=0, n7=0;
void find4after7(int i){
	bool pass7=false;
	for(int j=i-1; j>=0; j--){
		if(ans[j]=='7'){
			pass7=true;
			ans.erase(ans.begin()+j);
			n7++;
		}
		else{//ans[j]=4
			if(pass7){
				ans[j]='7'; 
				n7--; n4++;
				carry=true;//進位～～
				break;//find the 4 which has passed 7
			}
			else{
				ans.erase(ans.begin()+j);
				n4++;
			}
		}	
	}
}
int main(){
	string input;
	while(cin>>input){
	len=input.size();
	//增加位數
	if(len%2==1){
		len++;
		n4=n7=len/2;
		for(int i=0; i<n4; i++) cout<<4;
		for(int i=0; i<n7; i++) cout<<7;
	}
	else{
		bool inc=false;//如果已經是某位數的最大值 就要增加位數
		bool all7=true;
		bool all4=true;
		int count4=0, count7=0;
		for(int i=0; i<len; i++){
			char* c=new char[2];
			c[0]=input[i];
			c[1]='\0';
			int n = atoi(c);
			if(i<len/2){
				if(n!=7) all7=false;
				if(n<7){inc=false; break;}
				else if(n>7){inc=true; break;}
			}
			else{ 
				if(all7==true){
					if(n!=4) all4=false;
					if(n<4){inc=false; break;}
					else if(n>4){inc=true; break;}
				}
			}
		}
		//=7744
		if(all7 && all4 && inc==false){ 
			cout<<input;
		}
		//>7744
		else if(inc==true){
			len+=2;
			n4=n7=len/2;
			for(int i=0; i<n4; i++) cout<<4;
			for(int i=0; i<n7; i++) cout<<7;
		}
		//<7744
		else{
			len=input.size();
			ans.clear();
			n4=n7=len/2;
			carry= false;//進位了沒
			for(int i=0; i<len && carry==false; i++){
				char* c=new char[2];
				c[0]=input[i];
				c[1]='\0';
				int n=atoi(c);
				if(i==0){//first character
					if(n<4){ n4--; ans+='4'; break;}
					else if(n==4){ n4--; ans+='4'; continue;}
					else if(n<7){ n7--; ans+='7'; break;}
					else if(n==7){ n7--; ans+='7'; continue;}
				}
				if(n<4){
					if(n4>0){
						n4--; ans+='4';
						break;	
					}
					else break;
				}
				else if(n==4){
					if(n4>0){
						n4--; ans+='4';
					}
					else break;
				}
				else if(n<7){
					if(n7>0){
						n7--; ans+='7';
						break;
					}
					//7用完了 找經過7的4進位
					else find4after7(i);
				}
				else if(n==7){
					if(n7>0){
						n7--; ans+='7';
					}
					//7用完了 找經過7的4進位
					else find4after7(i);
				}
				else{
					//7尚未用完 直接找4進位
					if(n7>0){
						for(int j=i-1; j>=0; j--){
							if(ans[j]=='4'){
								ans[j]='7';
								n7--; n4++;
								carry=true;
								break;
							}
							else{//ans[j]=7
								ans.erase(ans.begin()+j);
								n7++;	
							}
						}
					}
					//7用完了 找經過7的4進位
					else find4after7(i);
				}
			}
			//ans+=' ';
			for(int i=0; i<n4; i++) ans+='4';
			for(int i=0; i<n7; i++) ans+='7';
			cout<<ans;
		}
	}
	cout<<"\n";
	}
	return 0;
}
