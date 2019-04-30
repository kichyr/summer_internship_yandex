#include<set>
#include<iostream>
#include<utility>
#include<string.h>
#include<vector>
#include<stdio.h>
#include<stdio.h>
#include<algorithm>


using namespace std;

typedef struct pattern {
    string number;
    string add_inf;
    int l_bracket = 0;
    int r_bracket = 0;


} pattern;
//std::sort(C.begin(), C.end().compare_without_case);

bool pattern_cmp(const pattern &a, const pattern &b) {
    if(a.number.length() > b.number.length())
        return true;
    if(a.number.length() == b.number.length() && a.number > b.number)
        return true;
    return false;
}

bool string_cmp(const string &a, const string &b) {
    if(a.length() > b.length())
        return true;
    if(a.length() == b.length() && a > b)
        return true;
    return false;
}



class data_base {
public:
    vector<string> numbers;
    vector<pattern> patterns;
    int n;
    int m;
    void input(int _n) {
        n = _n;
        set<char> ignore = {' ', '-', '+', '(', ')'};
        numbers.resize(n);
        for(int i = 0; i < n; i++) {
            char c;
            for(;(c = getchar()) != '\n';) {
                if(ignore.find(c) == ignore.end())
                    numbers[i].push_back(c);
                    //cout << c;
            }
        }
    }


    void print_base_nums() {
        for(auto i : numbers)
            cout << i << endl;
    }

    void print_base_patterns() {
        for(auto i : patterns) {
            cout << i.number << " - " << i.add_inf << endl;
            cout <<  i.l_bracket << " " << i.r_bracket << endl;
        }
    }
    

    void input_patterns(int _m) {
        m =_m;
        int k = 0, state = 0;
        numbers.resize(m);
        for(int i = 0; i < m; i++) {
            k = 0;
            state = 0;
            char c;
            pattern* p = new pattern;
            patterns.push_back(*p);
            for(;(c = getchar()) != '\n';) {
                if (state != 0) {
                    patterns.back().add_inf.push_back(c);
                    continue;
                }

                switch (c)
                {
                case ' ':
                    break;
                case '+':
                    break;
                case '-':
                    cin.ignore();
                    state = 1;
                    break;
                case '(':
                    patterns.back().l_bracket = k;
                    break;
                case ')':
                    patterns.back().r_bracket = k;
                    break;

                default:
                        patterns.back().number.push_back(c);
                        k++;
                    break;
                }
            }
        }
        std::sort(patterns.begin(), patterns.end(), pattern_cmp);
    }


    pattern& binary_seatch_pattern(int l, int r, string& desired) {
        if(l == r-1)
            return patterns[l];
        m = (l+r)/2;
        //cout << m << << r << endl;
        if(string_cmp(desired, patterns[m].number)) {
            //cout << "l" << desired << " " << patterns[m].number;
            binary_seatch_pattern(l, m, desired);
        }
        else {
            //cout << "l" << desired << " " << patterns[m].number << endl;
            binary_seatch_pattern(m, r, desired);
            //binary_seatch_pattern(l, m, desired);
        }
    }

    void print_patterns_for_nums() {;

        for(int i = 0; i < n; i++) {

            //cout << numbers[i] << endl;
            cout << binary_seatch_pattern(0, m, numbers[i]).number << endl;
        }
    }
    ~data_base(){
        patterns.clear();
        /* for(auto i : patterns) {
            delete[](i.add_inf);
            delete[]
        } */
    }
}; 


int main() {
    data_base data;
    int n, m;
    cin >> n;
    cin.ignore();
    data.input(n);
    //data.print_base_nums();
    cin >> m;
    cin.ignore();
    data.input_patterns(m);
    
    //data.print_base_patterns();
    //cout << string_cmp("118","117");
    //data.print_patterns_for_nums();
    pattern searched;
    for (int i = 0; i < n; i++) {
        cout << "+";
        searched = data.binary_seatch_pattern(0, m, data.numbers[i]);
        for(int j = 0; j < data.numbers[i].length(); j++) {
            if(j == searched.l_bracket) cout << " (";
            if(j == searched.r_bracket) cout << ") ";
            cout << data.numbers[i][j];
        }
        cout << " - " << searched.add_inf << endl;
    }

}