
Shraddha Koli <shraddhakoli.me@gmail.com>
Fri, Feb 28, 10:13 PM (17 hours ago)
to me

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <typeinfo>
#include <algorithm>
using namespace std;

class node {
public:
map<string, string> attr;
node *lnode;
string name;
};


void getData(vector<string> &data, string str)
{
while(!str.empty()){
int pos = str.find(' ');
if (pos == string::npos){
data.push_back(str);
break;
}
data.push_back(str.substr(0,pos));
str.erase(0, pos+1);
}
}

void getInputData(vector<string> &data, string &attr, string str)
{
while(!str.empty()){
int pos = str.find('.');
if (pos == string::npos){
data.push_back(str);
break;
}
data.push_back(str.substr(0,pos));
str.erase(0, pos+1);
}
int pos = data.back().find('~');
if(pos != string::npos){
string temp=data.back();
data.back()=data.back().substr(0,pos);
temp.erase(0,pos+1);
attr=temp;}

}

string& remove_char(string &s, const string &chars)
{
s.erase(remove_if(s.begin(), s.end(), [&chars](const char &c){return chars.find(c) != string::npos;} ),s.end());
return s;
}

void addnode(node *nobj, string data)
{
vector<string> strTok;
getData(strTok,data);
string str;
strTok[0] = remove_char(strTok[0], "<");
nobj->name=strTok[0];
cout<<nobj->name;
if (strTok.at(2) == "="){
nobj->attr.insert(pair<string,string>(strTok[1], strTok[3]));}
while(true)
{
getline(cin, str);
strTok.clear();

getData(strTok,str);
if (strTok[0].find("/") != string::npos){
return;}

nobj->lnode = new node;
addnode(nobj->lnode, str);

}
}

void printNames(node* n)
{
cout<<"name is "<<n->name;
if (n->lnode != NULL){

printNames(n->lnode);}
else{
return;
}

}

void printValue(node* n, vector<string> lnames, string attr)
{

while(n!=NULL)
{

if (lnames.back() == n->name)
{
cout<<n->attr[attr];
break;
}
else{
n=n->lnode;
}
}
cout<<"None";

}


int main()
{

node *n;
string str;
getline(cin, str);
if (str[0] == '<')
{
n = new node;
cout<<n;
cout<<"here"<<n->name;
addnode(n, str);
}

vector<string> lnames;
string attr;
printNames(n);
// Enter query
getline(cin,str);
getInputData(lnames, attr, str);
printValue(n,lnames, attr);
return 0;
}



