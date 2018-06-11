#include <iostream>
#include <string> 
#include <map>
#include <unordered_map>
#include <deque>
#include <cmath>
using namespace std;

int main(){
	string s;
	int num;
	cin >> s >> num;
	int x = 29;
	int M = 1000000007;
	
	// pow(x, ) preprocessing
	int pow_x[200000] = {1};
	long long p = 1;
	for (int i = 1; i < 200000; i++){
		p = (p * x) % M;
		pow_x[i] = p;
	}
	
	deque<int> all;
	for (int i = 0; i < s.length(); i++){
		all.push_back((int(s[i])- 96));
	}
	
	//hash table
	unordered_map<int, int> table;
	for (int i = 0; i < all.size(); i++){
		long long hash = all[i];
		table[hash] += 1;
		for (int j = 1; j < 10; j++){
			if (i + j >= all.size())
				break;
			else{
				int r = i + j;
				hash = ((hash * x) % M + all[r]) % M;
				table[hash] += 1;
			}
		}
	}

	for (int i = 0; i < num; i++){
		int type = 0;
		cin >> type;
		
		if (type == 1){    
			char add;
			cin >> add;
			all.push_front(int(add) - 96);
			
			//maintain hash table
			long long tmp = 0;
			for (int j = 0; j < 10 && j < all.size(); j++){
				tmp = ((tmp * x) % M + all[j]) % M;
				table[tmp] += 1;
			}	
		}
		else if (type == 2){ 
			char add;
			cin >> add;
			all.push_back(int(add)- 96);
			
			//maintain hash table
			int last_idx = all.size() - 1;
			for (int j = 0; j < 10 && j < all.size(); j++){
				long long tmp = 0;
				for (int k = 0; k <= j; k++){
					tmp += ((long long)all[last_idx - k] * pow_x[k]) % M; 
				}
				tmp = tmp % M;
				table[tmp] += 1;
			}	
		}
		// count
		else {
			string tmp;
			cin >> tmp; 
			int len = tmp.length();
			int count = 0;
			if (all.size() >= len){ 
				//hash
				long long query = (int(tmp[0])- 96) % M;
				for (int j = 1; j < len; j++) 
					query = (query * x + int(tmp[j]) - 96) % M;

				//Subtask 3
				if (len > 10){
					deque<int> all_hash;
					all_hash.push_back(0);
					for (int j = 0; j < all.size(); j++){
						long long h = ((long long)all_hash[j] * x + all[j]) % M;
						all_hash.push_back(h);
					}
					  
					for (int k = 0; k < all.size()-len+1; k++){
						long long sub = ((long long)all_hash[len+k] - ((long long)all_hash[k] * pow_x[len]) % M + M) % M;
						if (sub == query)
							count ++;
					}
					cout << count << endl;
				}
				//Subtask 4
				else{
					count = table[query];
					cout << count << endl;
				}	
			}
			else{
				cout << count << endl; 
			}
		}
	}
	return 0;
}
