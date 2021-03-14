#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <complex>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <bitset>
#include <fstream>
using namespace std;

#define y0 y910831
#define y1 y923456
#define j0 j771912
#define j1 j442401
#define next next18181
#define prev prev18181
#define pack_bit_length 25
#define sample_num 38
#define target_img_id (sample_num)

using ll = long long;
using ul = unsigned long;
#define INF 1LL<<60
#define PRIME 1000000007
int dy[]={0, 0, 1, -1, 1, 1, -1, -1};
int dx[]={1, -1, 0, 0, 1, -1, 1, -1};
#define REP(i,n) for(ll i=0, i##_len=(n); i<i##_len; ++i)
#define ALL(x) (x).begin(),(x).end()
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}


// a,b unsigned_int[pack_bit_length]
int distance(unsigned int *a,unsigned int *b){
    int res = 0;
    REP(i,pack_bit_length){
        res += bitset<32>(a[i]^b[i]).count();
    }
    return res;
}

unsigned int *merge(unsigned int *a, unsigned int *b){
    unsigned int* result = new unsigned int[pack_bit_length];
    REP(i, pack_bit_length){
        result[i] = a[i] | b[i];
    }
    return result;
}

unsigned int *inverse_merge(unsigned int *a, unsigned int *b){
    unsigned int* result = new unsigned int[pack_bit_length];
    REP(i, pack_bit_length){
        result[i] = a[i] & (~b[i]);
    }
    return result;
}

void show(unsigned int *a){
    int x = 0;

    REP(i, pack_bit_length){
        REP(j, 32){
            cout << ((a[i] & (1<<(32-j))) > 0)?'1':'0';
            x++;
            if(x==20){
                x=0;
                cout << endl;
            }
        }
    }
}

int main(){
	// cin.tie(0);
	// ios::sync_with_stdio(false);

    int imgs[sample_num+1][40][20];
    unsigned int img_ui[sample_num+1][pack_bit_length];
    
    unsigned int target_img_ui[pack_bit_length];

    ifstream in("pattern.csv");
    cin.rdbuf(in.rdbuf());
    ifstream in2("target.csv");

    int tmp;
    for(int i=0; i<sample_num+1; i++){
        if (i==target_img_id){
            cin.rdbuf(in2.rdbuf());
        }

        for(int j=0; j<40; j++){
            for(int k=0; k<20; k++) cin >> imgs[i][j][k] ;
        }
        cin.ignore();
    }
    REP(i,40){
        REP(j,20){
            cout << imgs[target_img_id][i][j];
        }
        cout << endl;
    }
    REP(i, sample_num+1) {
        int ky=0;
        REP(j, 40){
            REP(k, 20){
                img_ui[i][ky/32] |= imgs[i][j][k] << (32-(ky%32));
                ky++;
            }
        }
    }

    for(int j=0;j<40;j++){
        for(int k=0;k<20;k++){
            cout << imgs[7][j][k];
        }
        cout << endl;
    }
    REP(j,pack_bit_length){
        printf("%016x", img_ui[7][j]);

    }
    cout << endl;

    int min_dist = 800;
    REP(i, sample_num){
        int i_target_dist = distance(img_ui[target_img_id], img_ui[i]);
        if(min_dist > i_target_dist) {
            min_dist = i_target_dist;
            cout << "D:" << min_dist << " only " << i <<  endl;

            show(img_ui[i]);
        }
    }
    REP(i,sample_num){
        REP(j, sample_num){
            if (i==j) continue;
            int i_target_dist = distance(img_ui[target_img_id], inverse_merge(img_ui[i], img_ui[j]));

            if(min_dist > i_target_dist) {
                min_dist = i_target_dist;
                cout << "D:" << min_dist << " " << i << " minus " << j <<  endl;
                show(inverse_merge(img_ui[i], img_ui[j]));
            }
        }
    }

    REP(i,sample_num){
        REP(j, sample_num){
            if (i==j) continue;
            int i_target_dist = distance(img_ui[target_img_id], merge(img_ui[i], img_ui[j]));
            if(min_dist > i_target_dist) {
                min_dist = i_target_dist;
                cout << "D:" << min_dist << " " << i << " plus " << j <<  endl;
                show(merge(img_ui[i], img_ui[j]));
            }
        }
    }

	return 0;
}
