#include <bits/stdc++.h>  
using namespace std;
typedef long long ll;
#define vll vector<ll>
#define db double
typedef pair<ll,ll> pll;
#define vll vector<ll>
#define pll pair<ll, ll>
#define vpll vector<pair<ll, ll>>
#define mxheap priority_queue<ll>
#define mnheap priority_queue<ll,vector<ll>,greater<ll> >
#define loop0(e,i) for(ll i = 0; i < e; i++)
#define loops(s,e,i) for(ll i = s; i < e; i++)
#define loopr0(s,i) for(ll i = s; i >= 0; i--)
#define loopre(s,e,i) for(ll i = s; i >= e; i--)
#define endl "\n"
#define dbg(x) cout<<#x<<" = "<<x<<ln
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF 2e18
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define MOD  1000000007;
 

float rfxyz(vector<float> sp){
    return ((2*pow(sp[0],2)) + (4*pow(sp[1],2)) - (3*sp[0]*sp[1]*sp[2]));
}

void sof(vector<vector<float>> &s){
    vector<float> fxyz;
    ll lll = 0;
    for(auto tp : s){
        ll a = rfxyz(tp);
        cout << "fitness value of " << ++lll << " = " << a << endl;
        loop0(3,i)cout << s[lll-1][i] << " ";
        cout << endl;
        fxyz.pb(a);
    }
    vector<float> fv = fxyz;
    float sum = 0;
    loop0(s.size(),i){
        if(fxyz[i] >= 0)fv[i] = 1.0/(1+fxyz[i]); 
        else fv[i] = 1 - 1.0/(1+fxyz[i]); 
        sum+= fv[i];
        cout << "fitness of " << i+1 << " " << fv[i] << endl;
    }
    cout << "Total : " << sum << endl; 
    vector<float> fp;
    lll = 0;
    for(auto f : fv){
        cout << "fitness probability of  " << ++lll << " " << f/sum << endl;
        fp.pb(f/sum);
    }
    vector<float> cumfp = fp;
    lll = 0;
    loops(1,s.size(), i){
        cumfp[i] = cumfp[i-1] + fp[i];
        cout << "cum probability of  " << ++lll << " " << cumfp[i] << endl;
    }

    vector<vector<float>> t = s;

    loop0(10,i){
        float rg = (int)((float) 100*rand()/RAND_MAX)/100.0;
        cout << "random number generated for " << i+1 << " is " << rg << endl;
        ll idx = -1;
        loop0(10,k){
            //cout << rg << " " << cumfp[k] << endl;
            if(rg <= cumfp[k] && idx == -1) idx = k;
        }
        cout << "corresponding sample space index : " << idx << endl;
        t[i] = s[idx];
    }
    s = t;
}

void crossover(vector<vector<float>> &s){
    float acpt = 0.33;
    vector<int> incrs;
    loop0(10,i){
        float rg = (int)((float) 100*rand()/RAND_MAX)/100.0;
        cout << i+1 << " " << rg << endl;
        if(rg > acpt){
            cout << "accepted\n";
            incrs.pb(i);
        }
    }
    vector<vector<float>> t = s;
    for(auto idx : incrs){
        if(incrs.size() == 1)break;
        float rg = idx;
        while(rg == idx){
            rg = incrs[rand()%incrs.size()];
        }
        cout << idx+1 << " x " << rg+1 << endl;
        loop0(3,i)cout << s[idx][i] << " ";
        cout << endl;
        loop0(3,i)cout << s[rg][i] << " ";
        cout << endl;

        ll l = rand()%3;
        cout << l << endl;
        if(l == 0)t[idx][0] = s[rg][0], t[idx][1] = s[rg][1],t[idx][2] = s[rg][2];
        else if(l == 1)t[idx][1] = s[rg][1],t[idx][2] = s[rg][2];
        else if(l == 2)t[idx][2] = s[rg][2];
        loop0(3,i)cout << t[idx][i] << " ";
        cout << endl;
    }
    s = t;
}

void mutation(vector<vector<float>> &s){
    ll rgidx = rand()%s.size();
    ll rgbit = rand()%3;
    cout << rgidx+1 << " " << rgbit+1 << endl;
    if(rgbit == 0)s[rgidx][rgbit] = rand()%11;
    if(rgbit == 1)s[rgidx][rgbit] = rand()%6;
    if(rgbit == 2)s[rgidx][rgbit] = rand()%9;
    loop0(3,i)cout << s[rgidx][i] << " ";
    cout << endl;
}

int main()
{
    fast;
    vector<vector<float>> samples(10, vector<float>(3));
    loop0(10,i)cin >> samples[i][0] >> samples[i][1] >> samples[i][2];
    loop0(3,i){
        cout << "Iteration " << i+1 << " : \n";
        cout << "SURVIVAL OF FITTEST : \n";
        sof(samples);
        cout << "NEW SAMPLE SPACE : \n";
        loop0(10,i){loop0(3,j){cout << samples[i][j] << " ";}cout << endl;}
        cout << "CROSSOVER : \n";
        crossover(samples);
        cout << "NEW SAMPLE SPACE : \n";
        loop0(10,i){loop0(3,j){cout << samples[i][j] << " ";}cout << endl;}
        cout << "MUTATION : \n";
        mutation(samples);
        cout << "NEW SAMPLE SPACE : \n";
        loop0(10,i){loop0(3,j){cout << samples[i][j] << " ";}cout << endl;}
    }
    sof(samples);
    return 0;
}