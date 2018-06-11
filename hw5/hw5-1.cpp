#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
	int M = 1000000007;
	int days;
	cin >> days;
	int* fries;
	fries = new int[days];
	for (int i = 0; i < days; i++){
		cin >> fries[i];
	}

	// initial the first one
	int* len, *cnt, *pre;
	len = new int[days];
	cnt = new int[days];
	pre = new int[days];
	len[0] = 1;
	cnt[0] = 1;
	pre[0] = -1;

	int len_a = 0;
	long long cnt_a = 0;
	int last_day = 0;
	
	//fill all len, cnt, pre
	for (int i = 1; i < days; i++){
		int maxlen = 0;
		long long count = 1;
		int pre_day = -1;
		for (int j = 0; j < i; j++){
			if (fries[j] <= fries[i] && len[j] > maxlen){
				maxlen = len[j];
				count = cnt[j];
				pre_day = j;
			}
			else if (fries[j] <= fries[i] && len[j] == maxlen){
				count = (count + cnt[j]) % M;
			}
		}
		
		len[i] = maxlen + 1;
		cnt[i] = count;
		pre[i] = pre_day; 
		if (len[i] > len_a){
			len_a = len[i];
			last_day = i;
			cnt_a = cnt[i];
		}
		else if (len[i] == len_a){
			cnt_a = (cnt_a + cnt[i]) % M;
		}
	}
	
//		cout << "fries ";
//		for (int i = 0; i < days; i++){
//			cout << fries[i] << " ";
//		}
//		cout << endl << "len   ";
//		for (int i = 0; i < days; i++){
//			cout << len[i] << " ";
//		}
//		cout << endl << "cnt   ";
//		for (int i = 0; i < days; i++){
//			cout << cnt[i] << " ";
//		}
//		cout << endl << "pre   ";
//		for (int i = 0; i < days; i++){
//			cout << pre[i] << " ";
//		}
//		cout << endl;
	
	

	//fill in and print out
	vector <int> record;
	record.push_back(last_day);
	record.push_back(pre[last_day]);
	while(record.back() != -1){
		record.push_back(pre[record.back()]);
	}
	
	
	//print
	//cout << last_day << endl;
	cout << len_a << endl;
	cout << cnt_a << endl;
	for (int i = 0; i < len_a; i++){
		cout << record[record.size() - i - 2] + 1;
		if (i != len_a - 1)
			cout << " ";
	}
	
	
	delete [] fries;
	delete [] len;
	delete [] cnt;
	delete [] pre;
}
 
