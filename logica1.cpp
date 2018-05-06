#include <bits/stdc++.h>
using namespace std;

#define jl(n) for(int abc = 0; abc < n; abc++) cout<<endl

string expr = "(P > ((~Q) < (Q < S)))";
int var[]={0,0,0,0};
vector<string> subexp;

bool comp(string a, string b){
    if(a.size()!=b.size())return a.size()<b.size();
    return a<b;
}

string space(int n){
    string s="";
    for(int i = 0; i < n; i++) s += " ";
    return s;
}

void rep(string &s, string old, string nova){
    size_t index = 0;
    while (1){
        index = s.find(old,index);
        if(index==string::npos)break;
        s.replace(index,old.size(),nova);
        index+=nova.size();
    }
}


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
    string aux=expr;

    if(strstr(expr.c_str(),"P"))  {subexp.push_back("P"); var[0]=1;}
    if(strstr(expr.c_str(),"Q"))  {subexp.push_back("Q"); var[1]=1;}
    if(strstr(expr.c_str(),"R"))  {subexp.push_back("R"); var[2]=1;}
    if(strstr(expr.c_str(),"S"))  {subexp.push_back("S"); var[3]=1;}
    //if(strstr(expr.c_str(),"~P")) subexp.push_back("~P");
    //if(strstr(expr.c_str(),"~Q")) subexp.push_back("~Q");
    //if(strstr(expr.c_str(),"~R")) subexp.push_back("~R");
    //if(strstr(expr.c_str(),"~S")) subexp.push_back("~S");


    while(1){
        pair<int,int> sub = nextsub(aux);
        if (sub.first==0&&sub.second==0)break;
        aux[sub.first] = aux[sub.second]='_';

        subexp.push_back(expr.substr(sub.first,sub.second-sub.first+1));
        //cout<<exp<<endl;
    }
    for(string &s : subexp){
        if(s[0] == '(' && s[s.size() - 1] == ')') s = s.substr(1, s.size() - 2);
    }
    sort(subexp.begin(),subexp.end(),comp);

}

int avaliarExp(string exp,int p, int q, int r, int s){
    //cout<<exp<<endl;
    rep(exp, " ","");
    //cout<<exp<<endl;
    replace(exp.begin(),exp.end(),'P',p?'1':'0');
    replace(exp.begin(),exp.end(),'Q',q?'1':'0');
    replace(exp.begin(),exp.end(),'R',r?'1':'0');
    replace(exp.begin(),exp.end(),'S',s?'1':'0');





    while(exp.size() > 1){
        //string aux = exp;
        rep(exp, "0&0","0");
        rep(exp, "0&1","0");
        rep(exp, "1&0","0");
        rep(exp, "1&1","1");

        rep(exp, "0v0","0");
        rep(exp, "0v1","1");
        rep(exp, "1v0","1");
        rep(exp, "1v1","1");

        rep(exp, "0>0","1");
        rep(exp, "0>1","1");
        rep(exp, "1>0","0");
        rep(exp, "1>1","1");

        rep(exp, "0<0","1");
        rep(exp, "0<1","0");
        rep(exp, "1<0","0");
        rep(exp, "1<1","1");

        rep(exp, "~0","1");
        rep(exp, "~1","0");
        rep(exp, "(0)","0");
        rep(exp, "(1)","1");

        //if(aux == exp) {cout<<aux<<endl; }
    }
    //jl(4);
    return exp!="0";
}

#define db if(1) cout

void gerarTabela(){
    int numvar = 0;

    for(int i = 0; i <4; i++) numvar += var[i];
    //cout<<numvar<<endl;
    bool separador = false;
    for(int i = 0; i <subexp.size();i++){
        if(subexp[i].size()>1&&separador==false){
            db<<"|";
            separador = true;
        }
        db<<  (subexp[i].size()==1?"":" ")   <<subexp[i]<<" \n"[i == subexp.size() - 1];
    }


    separador = false;


    for(int p=0;p<2;p++){
        if(!var[0]&&p==1)continue;
        for(int q=0;q<2;q++){
            if(!var[1]&&q==1)continue;
            for(int r=0;r<2;r++){
                if(!var[2]&&r==1)continue;
                for(int s=0;s<2;s++){
                    if(!var[3]&&s==1)continue;

                    for(int i = 0; i <subexp.size();i++){
                        string exp = subexp[i];
                        int res = avaliarExp(exp, p,q,r,s);
                        if(i<numvar) {
                            cout<<res<<" ";

                        }
                        else{

                            if(!separador){
                                db<<"|";
                                separador = true;
                            }
                            db<<" "<<space(exp.size()-1)<<res<<" \n"[i == subexp.size() - 1];
                        }
                    }

                    separador = false;
                }
            }
        }
    }


}
int main(){
    allsub();
    //for(string s: subexp) cout<<s<<endl;
    gerarTabela();
}
