#include<map>
#include<iostream>
#include<utility>
#include<string.h>
#include<vector>
#include<stdio.h>


using namespace std;


class storage {
public:
    int SIGMA_LEN = 26;
    
    map<short, map<short, char>> arr;

    short get_hash(string& s, int start) {
        short code = 0;
        for (int i = 0; i < 3; i++) {
            code = code*SIGMA_LEN + (s[start + 2 - i]-'a');
        }
        return code;
    }

    void print_decode(short code) {
        for(int i = 2; i >=0; i--) {
            printf("%c", code%SIGMA_LEN+'a');
            code /= SIGMA_LEN;
        }
    }

    void print_all() {
        for(auto i : arr) {
            if(i.second[0] == 0) continue;
            for(auto j = i.second.begin(); j != i.second.end();) {
                j++;
                if((*j).second > 0) {
                    print_decode(i.first);
                    printf(" ");
                    print_decode((*j).first-1);
                    printf(" ");
                    printf("%i\n", (*j).second);
                }
        }
        }
    }
}; 


int main() {
    int v = 0, pairs = 0;
    storage st;
/*     string s = "abs";
    cout << st.get_hash(s, 0) << endl;
    st.print_decode(st.get_hash(s,0)); */
    int n;
    string in_s;
    cin >> n;
    int len, prev, code;
    for(int i = 0; i < n; i++) {
        cin >> in_s;
        len = in_s.length();
        prev = -1;
        code;
        for(int j = 0; j < len-2; j++) {
            code = st.get_hash(in_s, j);
            if(prev != -1) {
                if(st.arr[prev][code+1] == 0) pairs++;
                st.arr[prev][code+1]++;
            }
            if(st.arr[code][0] == 0) v++;
            st.arr[code][0] = 1;
            prev = code;
        }
    }
    cout << v << endl << pairs << endl;
    st.print_all();

}