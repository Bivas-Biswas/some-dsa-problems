#include<bits/stdc++.h>

using namespace std;

#define endl       '\n'

#define int        long long

#define sz(v)       (int)(v.size())



string s;

int dp[5001];



int rec(int level){

               

               // base case

               if(level<0)return 1;

               // cache check

               if(dp[level]!=-1)return dp[level];

               // transition

               int ans=0;

               // decode as 1 letter

               if(s[level]!='0')ans+=rec(level-1);

               // decode as 2 letters

               if(level-1>=0){

                         int value = (s[level-1]-'0')*10 + (s[level]-'0');

                         if(value>=10 and value<=26)ans+=rec(level-2);

               }

               // save & return

               return dp[level]=ans;



}

void sigmale(string &s){

            memset(dp,-1,sizeof(dp));

            cout << rec(sz(s)-1) << endl;

     

}



signed main(){    

    ios_base::sync_with_stdio(0);

    cin.tie(0);cout.tie(0);  

   

    while(cin>>s){

        if(s=="0")break;    

        sigmale(s);

    }

}