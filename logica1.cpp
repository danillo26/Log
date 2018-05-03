#include <bits/stdc++.h>
using namespace std;

string expr = "((P&Q)vB)";
vector<string> subexp;
pair <int,int> nextsub(string exp){
    int pos = exp.find_first_of(")");
    for(int i = pos-1; i>=0; i--){
        if(exp[i]=='(') {

            return make_pair(i,pos);
        }
    }
    return make_pair(0,0);
}
void allsub(){
    string exp=expr;
    while(1){
        pair<int,int> sub = nextsub(exp);
        if (sub.first==0&&sub.second==0)break;
        exp[sub.first] = exp[sub.second]='_';

        subexp.push_back(expr.substr(sub.first,sub.second-sub.first+1));
        //cout<<exp<<endl;
    }

}

int main(){
    allsub();
    for(string s : subexp) cout<<s<<endl;
}

