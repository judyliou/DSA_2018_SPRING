#include <iostream>
#include <unordered_map>
#include <string>
//#include <bitset>
using namespace std;

// to do: 
// 1. alpha-beta pruning
// 2. unordered_map
unordered_map<int, int> map;

int Evaluate(long long board){	
	int score = 0;
	
	//count column
	for (int i = 0; i < 5; i++){
		int O = 0;
		for(int j = 0; j < 5; j++){
			if ((board >> (i*2+j*10) & 3LL) == 2) O += 1;
		}
		
		if (O >= 4) score += 1;
		else if (O <= 1) score -= 1;
	}
	
	//count row
	for (int i = 0; i < 5; i++){
		int O = 0;
		for(int j = 0; j < 5; j++){
			if ((board >> (i*10+j*2) & 3LL) == 2) O += 1;
		}
		if (O >= 4) score += 1;
		else if (O <= 1) score -= 1;
	}

	//count cross
	int O = 0;
	for (int i = 0; i < 5; i++){
		if ((board >> i*12 & 3LL) == 2) O += 1;
	}
	if (O >= 4) score += 1;
	else if (O <= 1) score -= 1;

	O = 0;
	for (int i = 0; i < 5; i++){
		if ((board >> 8*(i+1) & 3LL) == 2) O += 1;
	}
	if (O >= 4) score += 1;
	else if (O <= 1) score -= 1;

	if (score > 0) return 1;
	else if (score == 0) return 0;
	else return -1;
}

int WhoWin(long long board, int round){
		
	//find whether in map
	unordered_map<int, int>::iterator it;
    if ((it = map.find(board)) != map.end()) { 
		return it->second;	
	}
    

	int can_choose = (12 - round) * 2 + 3; 
	int blank_pos[25] = {0};

	//find left blank
	int c = 0;
	for (int i = 0; i < 25; i++){
		if (((board >> i*2) & 3LL) == 0) {
			blank_pos[c] = i;
			c++;
		}
	}
	
	if (round ==13) {
		int result = Evaluate(board);
		return result;	
	}
	
	if (round == 12) {
		long long preboard = board;
		long long X = 1;
		
		for (int i = 0; i < 3; i++) {
			
			board = (board | (X << blank_pos[i]*2));
		}
		int result = Evaluate(board);
		map.insert(make_pair(preboard,result));
		
		return result;	
	}
	
	//round: even for X; odd for O
	/// X's round: nextR beta
	if (round % 2 == 0){    
		int result = 1;
		
		for (int i = 0; i < can_choose; i++){
			for (int j = i+1; j < can_choose; j++){
				long long newboard = board;

				//add two place with X
				long long X = 1;
				newboard = (newboard | (X << blank_pos[i]*2));
				newboard = (newboard | (X << blank_pos[j]*2));	
			
				int nextResult = WhoWin(newboard, round+1);
				// alpha >= beta??
				// when alpha >= beta return 
				///cout << "round:" << round << " X next: " << nextResult << endl;
				if (nextResult == -1) {
					result = -1;
					map.insert(make_pair(board, nextResult));
					return result;
				}
				else if (nextResult == 0) result = 0;
			}
		}
		map.insert(make_pair(board, result));
		
		return result;
	}
	
	/// O's round
	if (round % 2 == 1){
		int result = -1;
		
		for (int i = 0; i < can_choose; i++){
			for (int j = i+1; j < can_choose; j++){
				long long newboard = board;
				///cout << "round:" << round << " i j: " << i << "/" << j << endl;
				
				//add two place with O
				long long O = 2;
				newboard = (newboard | (O << blank_pos[i]*2));
				newboard = (newboard | (O << blank_pos[j]*2));	
				
				int nextResult = WhoWin(newboard, round+1);
				
				if (nextResult == 1) {
					result = 1;
					map.insert(make_pair(board, nextResult)); 
					return result;
				}
				else if (nextResult == 0) result = 0;
			}
		}
		map.insert(make_pair(board, result));
		return result;
	}
}


int main(){
	int num = 0;
	cin >> num;
	
	for (int i = 0; i < num; i++){
		long long board = 0;
		int blank = 0;
		for (int j = 0; j < 5; j++){
			long long tmp = 0;
			string c;
			cin >> c;
			
			for (int k = 0; k < 5; k++){
				if (c[k] == 'O') tmp = 2;
				else if (c[k] == 'X') tmp = 1;
				else {
					tmp = 0;
					blank++;
				}
				board = (board | (tmp << j*10+k*2));
			}	
		}
		
		int round = -1;
		
	
		if (blank > 0) round = 12 - (blank - 3) / 2;
		else round = 13;
		
		int x = WhoWin(board, round);

		if (x == 1) cout << "O win";
		else if (x == 0) cout << "Draw";
		else cout << "X win";
		
		if (i != num-1) cout << endl;
	} 

	
	return 0;	
}
