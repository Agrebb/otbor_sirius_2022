#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

struct function{
    int n, m;
    vector <int> f;
    function(){
    }
    function(int _n){
        n = _n;
        f.resize(1<<_n);
    }
};

const int maxn = 13;
function summ [maxn];
int pw[maxn], numf = 4;
vector <int> func2{6, 8, 14, 9, 7, 1};

bool gen_random_and_compare(int n, int m, int depth, function & ideal, vector <pair<int, int>> b_start = {}, vector <int> fb_start = {}){
    vector <pair<int, int>> b(depth);
    vector <int> fb(depth);
    for (int i = 0; i < depth; i++){
        if (i < b_start.size()){
            b[i] = b_start[i];
            fb[i] = fb_start[i];
            continue;
        }
        int x1 = 0, x2 = 0;
        while (x1 == x2) {
            if (m == 1)  x1 = i < depth - 2 ? (rand() % (n + i)) : n+i-1;
            else x1 = (rand() % (n + i));
            x2 = (rand() % (n + i));
        }
        b[i] = {x1, x2};
        fb[i] = rand() % func2.size();
    }
    for (int mask = (1<<n) - 1; mask >= 0; mask--){
        int res = 0;
        vector <int> a(n + depth);
        for (int i = 0; i < n; i++) a[i] = (mask >> i) & 1;
        for (int i = 0; i < depth; i++){
            int x1 = a[b[i].first], x2 = a[b[i].second];
            a[n+i] = ((func2[fb[i]] >> (2*x1+x2)) & 1);
            if (i >= depth - m){
                res += (a[n+i] << (i - depth + m));
            }
        }
        if (mask < 7) cout << mask << endl;
        if (res != ideal.f[mask]) return false;
    }
    for (int i = 0; i < depth; i++){
        cout << b[i].first << " " << b[i].second << " " << fb[i] << endl;
    }
    return true;
}

void verify (function & ideal){
    freopen("../input.txt", "r", stdin);

    int n, k, m; cin >> n >> k >> m;
    for (int i = 0; i < n; i++){
        int a; cin >> a;
    }
    vector <int> u(k), v(k), func(k);
    for (int i = 0; i < k; i++){
        int ff = 0, tmp;
        cin >> tmp >> u[i] >> v[i] >> ff; u[i]--; v[i]--;
        func[i] = 0;
        int cur = 1;
        while (ff > 0){
            func[i] += cur * (ff % 10);
            ff /= 10;
            cur *= 2;
        }
    }
    vector <int> index(m);
    for (int i = 0; i < m; i++){
        cin >> index[i]; index[i]--;
    }
    for (int mask = 0; mask < (1<<n); mask++){
        int res = 0;
        vector <int> a(n);
        for (int i = 0; i < n; i++) a[i] = (mask >> i) & 1;
        for (int i = 0; i < k; i++){
            int x1 = a[u[i]], x2 = a[v[i]];
            int bit = (func[i] >> (2*(1-x1) + (1-x2))) & 1;
            a.push_back(bit);
        }
        for (int i = 0; i < m; i++){
            res += a[index[i]] << i;
        }
        if (res != ideal.f[mask]){
            cout << "BAD\n";
            cout << mask << " " << res << endl;
            for (int bit : a) cout << bit;
            cout << endl;
            return;
        }
    }
    cout << "OK\n";
}

#include <map>

void bfs_bruteforce(int n, int threshold, function & ideal){

    long long id = 0;
    for (int j = 0; j < (1<<n); j++){
        id += (1ll<<j) * (ideal.f[j]);
    }

    map <vector <long long>, int> d;
    vector <vector <long long>> v(1);
    for (int i = 0; i < n; i++){
        v[0].resize(n, 0);
        for (int j = 0; j < (1<<n);  j++){
            v[0][i] += (1ll<<j) * ((j >> i) & 1);
        }
    }
    sort(v[0].begin(), v[0].end());
    d[v[0]] = 1;

    long long full_mask = (1ll<<(1<<n)) - 1;

    const int maxt = 1000000;
    for (int tt = 0; tt < maxt; tt++){
        int sz = v.size();
        auto k = v[rand() % sz];
        int i1 = rand() % n, i2 = rand() % n;
        if (i1 == i2) continue;

        int st_dist = d[k];
        int fb1 = rand() % 3, fb2 = rand() % 2;
        long long res = 0;
        if (fb1 == 0) res = k[i1] & k[i2];
        else if (fb1 == 1) res = k[i1] | k[i2];
        else if (fb1 == 2) res = k[i1] ^ k[i2];
        if (fb2) res = full_mask - res;

        k[i2] = res;
        // cout << res << " " << st_dist << endl;
        if (res == id){
            cout << st_dist << endl;
        }
        sort(k.begin(), k.end());

        int pr_dist = d[k];
        if (!pr_dist){
            d[k] = st_dist + 1;
            if (st_dist < threshold) v.push_back(k);
        }
        else{
            d[k] = min(pr_dist, st_dist + 1);
        }
    }
    cout << "size: " << v.size() << endl;
}

typedef long long ll;
const int n = 4, sz = (1<<n);
ll polymult(ll a, ll b){
    ll res = 0;
    for (int i = 0; i < sz; i++){
        int v1 = (a>>i)&1;
        if (!v1) continue;
        for (int j = 0; j < sz; j++){
            int v2 = (b>>j)&1;
            if (v2) res ^= (1ll<<(i|j));
        }
    }
    return res;
}

ll get_linear_form(int mask){
    ll res = 0;
    for (int i = 0; i < n; i++){
        int v = (mask>>i)&1;
        if (v) res |= (1ll<<(1<<i));
    }
    if ((mask>>n)&1) res |= 1;
    return res;
}

ll get_quadratic_form(int mask){
    ll res = 0;
    int cur = 0;
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if ((mask>>cur)&1) res |= (1ll<<((1<<i) + (1<<j)));
            cur++;
        }
    }
    for (int i = 0; i < n; i++){
        if ((mask>>cur)&1) res |= (1ll<<(1<<i));
        cur++;
    }
    if ((mask>>cur)&1) res |= 1;
    return res;
}

int get_cnt(int x){
    int cnt = 0;
    while (x > 0){
        cnt += (x&1);
        x /= 2;
    }
    return cnt;
}

void out_poly(ll a){
    for (int mask = 0; mask < sz; mask++){
        if ((a>>mask)&1){
            if (mask == 0){
                cout << "1+";
                continue;
            }
            for (int i = 0; i < n; i++){
                if ((mask>>i)&1) cout << i;
            }
            cout << "+";
        }
    }
    cout << "    ";
}

void factor_polynomial(){

    ll ideal = 0;
    for (int i = 0; i < sz; i++){
        int cnt = get_cnt(i);
        if (cnt == 2 || cnt == 4) ideal |= (1ll<<i);
    }

    vector <ll> qforms;
    for (int mask = 0; mask < (1<<(n*(n+1)/2+1)); mask++){
        qforms.push_back(get_quadratic_form(mask));
    }
    cout << qforms.size() << endl;

    for (int i = 0; i < qforms.size(); i++) {
        for (int j = 0; j < i; j++) {
            ll res = polymult(qforms[i], qforms[j]) ^ ideal;
            if (res == 0 || res == 1) {
                out_poly(qforms[i]);
                out_poly(qforms[j]);
                cout << endl;
            }
        }
    }
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < maxn; i++){
        pw[i] = pw[i-1] * numf;
        summ[i] = function(i);
        for (int mask = 0; mask < (1<<i); mask++){
            int m = mask, val = 0;
            while (m > 0){
                val += (m & 1);
                m /= 2;
            }
            summ[i].f[mask] = val;

            summ[i].m = max(summ[i].m, get_cnt(summ[i].f[mask]));
        }
    }

    // bfs_bruteforce(4, 7, summ[4]);

    // verify(summ[5]);

     factor_polynomial();

    return 0;
}