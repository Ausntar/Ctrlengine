#include <iostream>
#include <string>
using namespace std;
int main(int argc, char *argv[]){
    string s = argv[0];
    if(!s.find("F")!=string::npos) return -1;
    if(!s.find("B")!=string::npos) return -1;
    if(!s.find("L")!=string::npos) return -1;
    if(s.find("K")==string::npos) return -1;
    if(s.find("O")==string::npos) return -1;
    if(s.find("D")==string::npos) return -1;

    int a=0;
    for(int i=0;i<s.size();i++){
        if(s[i]>='0' && s[i]<='9') a+=s[i]-'0';
        else a--;
    }
    if(a==0) {
        if(s.find("0")==string::npos) return -1;
        cout<<"Verified by"<<endl;
        return 0;
    }
    
    else return -1;
}