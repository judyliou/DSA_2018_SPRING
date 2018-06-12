#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double A = pow(10,-10);
vector<pair<double, double>> loc;

pair<double, double> cal_coef(double x1, double y1, double x2, double y2){
	double a ,b;
	a = ((x1*y2/x2) - y1) / (x1*x2 - x1*x1);
	b = (y1 - a*x1*x1) / x1;
	//printf("%f %f ", a, b);
	return make_pair(a, b);
}

bool lag_cal(int x1, int y1, int x2, int y2, int x, int y){
	long long right = y1 * (x-x2) * x * x2 - y2 * (x-x1) * x * x1;
	long long left = (x1-x2) * x1 * x2 * y;
	if (right == left)
 		return true;
 	else
 		return false;
} 

bool on_curve(int j, int k, int t){
	pair<double, double> pig1 = loc[j];
	pair<double, double> pig2 = loc[k];
	pair<double, double> pig3 = loc[t];
	
	return lag_cal(pig1.first, pig1.second, pig2.first, pig2.second, pig3.first, pig3.second);
}


int main(){
	
	int T = 0;
	cin >> T;
	
	for (int i = 0; i < T; i++){
		int n = 0;
		cin >> n;
	
		
		for (int j = 0; j < n; j++){   //save location 
			double x, y;
			cin >> x >> y;
			loc.push_back(make_pair(x, y));
		}
		
		double** para = new double*[n];
		for (int j = 0; j < n; j++){
			para[j] = new double[n];
		}
		//calculate every para-curve
		for (int j = 0; j < n; j++){
			for (int k = 0; k < n; k++){
				double a = cal_coef(loc[j].first, loc[j].second, loc[k].first, loc[k].second).first;
				//printf("a: %f \n", a);
				if (loc[j].first == loc[k].first){ // same x 
					para[j][k] = 1 << j;
					continue;
				}
				else if (abs((loc[j].first / loc[j].second) - (loc[k].first / loc[k].second)) < pow(10,-10)){  // three points on a line
					para[j][k] = 1 << j;
					continue;
				}
				else if (a > 0){  // not downward curve
					para[j][k] = 1 << j;
					continue;
				}
				para[j][k] = (1 << j) + (1 << k);  //2^j + 2^k
				for (int t = 0; t < n; t++){
					if (on_curve(j, k, t) && t != j && t != k){
						para[j][k] += (1 << t);
					}
				}
			}
		}
		
		int B = pow(2, n);
		vector<int> dp(B, 1000);
		dp[0] = 0;
		dp[1] = 1;
		dp[2] = 1;

		for (int l = 3; l < B; l++){
			for (int j = 0; j < n; j++){
				if (((1 << j) & l) == 0) continue; 
				
				for (int k = 0; k < n; k++){
					if (((1 << k) & l) == 0) continue;
					
					int p = para[j][k];
					int s_ = l & (~p); //l - p

					dp[l] = min(dp[s_] +1, dp[l]);
				}
				break;
			}
		}
		
		cout << dp[B-1];
		if (i != T - 1)
			cout << endl;

		
		for (int j = 0; j < n; j++){
			delete[] para[j];
		}
		delete[] para;
		loc.clear();
	}
		
	return 0;
} 
