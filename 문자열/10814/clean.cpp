    #include <iostream>
    #include <vector>
    #include <string>
    #include <algorithm>
    using namespace std;

    struct Person{
        int age;
        string name;
        
    };

    int main() {

        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int N;
        cin >> N;

        vector<Person> v;
        v.reserve(N);

        for (int i=0; i < N; i++){
            int age;
            string name;
            cin >> age >>name;
            v.push_back(Person{age, std::move(name)});

        }

        stable_sort(v.begin(), v.end(),[](const Person& a, const Person& b) { return a.age < b.age;});
        for (const auto& p : v){
            cout << p.age << " " << p.name << '\n';

        }
        return 0;

    }