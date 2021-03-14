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

int* merge_min_index(unsigned int *target, unsigned int *current, unsigned int img_ui[][pack_bit_length]){
    int* min_index_and_dist = new int[2];
    min_index_and_dist[0] = -1;
    min_index_and_dist[1] = 800;
    REP(i, sample_num) {
      auto merge_result = merge(current, img_ui[i]);
      int target_dist = distance(target, merge_result);
      if(min_index_and_dist[1] > target_dist) {
        min_index_and_dist[0] = i;
        min_index_and_dist[1] = target_dist;
        cout << "merge_min_index: " << i << " " << target_dist << endl;
      }
      delete merge_result;
    }
    return min_index_and_dist;
}

int* inverse_merge_min_index(unsigned int *target, unsigned int *current, unsigned int img_ui[][pack_bit_length]){
    int* min_index_and_dist = new int[2];
    min_index_and_dist[0] = -1;
    min_index_and_dist[1] = 800;
    REP(i, sample_num) {
      auto inverse_merge_result = inverse_merge(current, img_ui[i]);
      int target_dist = distance(target, inverse_merge_result);
      if(min_index_and_dist[1] > target_dist) {
        min_index_and_dist[0] = i;
        min_index_and_dist[1] = target_dist;
        cout << "inverse_merge_min_index: " << i << " " << target_dist << endl;
        show(inverse_merge_result);
      }
      delete inverse_merge_result;
    }
    return min_index_and_dist;
}

int* both_min_index(unsigned int *target, unsigned int *current, unsigned int img_ui[][pack_bit_length]){
    int* min_indexes_and_dist = new int[3];
    min_indexes_and_dist[0] = -1;
    min_indexes_and_dist[1] = -1;
    min_indexes_and_dist[2] = 800;
    REP(i, sample_num){
        REP(j, sample_num){
            if (i==j) continue;
            auto merge_result = merge(current, img_ui[i]);
            auto ivm_result = inverse_merge(merge_result, img_ui[j]);
            int target_dist = distance(target, ivm_result);

            if(min_indexes_and_dist[2] > target_dist) {
                min_indexes_and_dist[0] = i;
                min_indexes_and_dist[1] = j;
                min_indexes_and_dist[2] = target_dist;
                cout << "both_min_index: " << i << " " << j << " " << target_dist << endl;
                show(ivm_result);
            }
            delete ivm_result;
            delete merge_result;
        }
    }
    return min_indexes_and_dist;
}

class Operation {
public:
  char op;
  int idx;

  Operation() {
    op = '\0';
    idx = -1;
  }

  Operation(char iop, int iidx) {
    op = iop;
    idx = iidx;
  }
};

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
    REP(i, sample_num+1) {
        int ky=0;
        REP(j, 40){
            REP(k, 20){
                img_ui[i][ky/32] |= imgs[i][j][k] << (32-(ky%32));
                ky++;
            }
        }
    }

    Operation* operations = new Operation[6];

    auto current = merge(img_ui[sample_num-1], img_ui[sample_num-1]);
    REP(i, 6) {
      auto merge_result = merge_min_index(img_ui[target_img_id], current, img_ui);
      auto inverse_merge_result = inverse_merge_min_index(img_ui[target_img_id], current, img_ui);
      auto both_merge_result = both_min_index(img_ui[target_img_id], current, img_ui);

      auto results = new int[3];
      results[0] = merge_result[1];
      results[1] = inverse_merge_result[1];
      results[2] = both_merge_result[2];

      int min_result = 800;
      int min_idx = -1;
      REP(j, 3) {
        if(min_result > results[j]) {
          min_result = results[j];
          min_idx = j;
        }
      }
      cout << "min_idx " << min_idx << " min_result " << min_result << endl;

      auto before_current = current;
      switch(min_idx) {
        case 0:
          current = merge(current, img_ui[merge_result[0]]);
          operations[i].op = 'F';
          operations[i].idx = merge_result[0];
          break;
        case 1:
          current = inverse_merge(current, img_ui[inverse_merge_result[0]]);
          operations[i].op = 'B';
          operations[i].idx = inverse_merge_result[0];
          break;
        case 2:
          auto merge_result = merge(current, img_ui[both_merge_result[0]]);
          current = inverse_merge(merge_result, img_ui[both_merge_result[1]]);
          operations[i].op = 'F';
          operations[i].idx = both_merge_result[0];
          delete merge_result;
          i++;
          operations[i].op = 'B';
          operations[i].idx = both_merge_result[1];
          break;
      }
      delete before_current;
    }
    
    cout << "current" << endl;
    show(current);

    cout << "operations" << endl;
    REP(i, 6) {
      cout << operations[i].op << " " << operations[i].idx << endl;
    }

    return 0;

}
