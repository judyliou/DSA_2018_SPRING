#include <iostream>
#include <fstream>
#include <string> 
#include <vector> 
#include <algorithm>
#include <cstdlib>


using namespace std;

typedef struct Data{
	string date;
	string currency;
	string exchange;
	float low;
	float high;
	long long int cap;
}trans;


bool compare1(trans* t1, trans* t2){
	if (t1->date != t2->date)
		return (t1->date < t2->date);
	else if (t1->currency != t2->currency)
		return (t1->currency < t2->currency);
	else
		return (t1->exchange < t2->exchange);
}

bool compare2(trans* t1, trans* t2){
	if (t1->date != t2->date)
		return (t1->date < t2->date);
	else
		return (t1->exchange < t2->exchange);
}


void query(vector<trans*> &order, string date, string currency, string exchange, int left, int right){
	if (order[left]->date > date || order[right]->date < date){
		cout << "none" << endl;
		return;
	}
	while (left <= right){
		int mid = (left + right) / 2;
		
		if (order[mid]->date == date){
			
			//find the start point
			while (order[mid-1]->date == date){
				mid -= 1;
				if (mid == 0)
					break;
			}
			
			//find currency
			while (order[mid]->currency < currency){
				mid += 1;
				if (order[mid]->date != date){
					cout << "none" << endl;
					return;
				}
			}
			if (currency != order[mid]->currency){  //avoid not in the data set
				cout << "none" << endl;
				return;				
			}
			
			//find exchange
			while (order[mid]->exchange < exchange){
				mid += 1;
				if (order[mid]->currency != currency){
					cout << "none" << endl;
					return;
				}
			}
			if (exchange != order[mid]->exchange){  //avoid not in the data set
				cout << "none" << endl;
				return;				
			}
			printf("%.4f %.4f %lli\n", order[mid]->low, order[mid]->high, order[mid]->cap);
			return;
		}
		
		else if (order[mid]->date < date)
			left = mid + 1;
		
		else
			right = mid - 1;
	}
	cout << "none" << endl;
	return;
}

void price(vector<trans*> &order,string m, string date, string currency,int left, int right){
	int num = right;
	if (date < order[left]->date|| date > order[right]->date){
		cout << "none" << endl;
		return;
	}

	while (left <= right){
		int mid = (left + right) / 2;
		
		if (order[mid]->date == date){
			//find the start point
			if (mid != 0){
				while (order[mid-1]->date == date){
					mid -= 1;
					if (mid == 0)
						break;
				}
			}
			//find currency	
			while (order[mid]->currency < currency){
				mid += 1;
				if (mid > num){
					cout << "none" << endl;
					return;
				}
				if (order[mid]->date != date){
					cout << "none"  << endl;
					return;
				}
			}
			if (currency != order[mid]->currency){
				cout << "none" << endl;
				return;
			}
			
			//find max/min
			if (m == "max"){
				float price = order[mid]->high;
				
				while (mid < num){
					mid += 1;
					if (order[mid]->currency != currency || order[mid]->date != date)
					 	break;
					if (order[mid]->high > price)
						price = order[mid]->high;
				}

				printf("%.4f\n", price);
				return;
			}
			else if (m == "min"){
				float price = order[mid]->low;
			
				while (mid < num){
					mid += 1;
					if (order[mid]->currency != currency || order[mid]->date != date)
					 	break;
					if (order[mid]->low < price)
						price = order[mid]->low;
				}
				printf("%.4f\n", price);
				return;				
			}
		}
		
		else if (order[mid]->date < date)
			left = mid + 1;
		
		else
			right = mid - 1;
	}
	cout << "none" << endl;
	return;
}

void cap(vector<trans*> &order, string date, string exchange,int left, int right){
	int num = right;
	if (date < order[left]->date || date > order[right]->date){
		cout << "none" << "\n";
		return;
	}

	while (left <= right){
		int mid = (left + right) / 2;

		if (order[mid]->date == date){
			
			//find the start point
			while (order[mid-1]->date == date){
				mid -= 1;
				if (mid == 0)
					break;
			}
			
			//find exchange	
			while (order[mid]->exchange < exchange){
				mid += 1;
				if (order[mid]->date != date){
					cout << "none" << endl;
					return;
				}
			}
			if (exchange != order[mid]->exchange){
				cout << "none" << endl;
				return;
			}
			
			//count cap
			long long int total = order[mid]->cap;
			mid += 1;
			while (order[mid]->exchange == exchange){
				total += order[mid]->cap;
				mid += 1;
				if (mid == num)
			        break;
			}
			cout << total << endl;
			return;
		}
		
		else if (order[mid]->date < date)
			left = mid + 1;
		
		else
			right = mid - 1;
	}
	cout << "none" << endl;
	return;
}



int main(int argc, char** argv)
{
	ifstream inFile(argv[1]);
	vector<trans> allTrans;
	trans buffer;
	int count = 0;

	while (inFile >> buffer.date){		
		inFile >> buffer.currency;
		inFile >> buffer.exchange;
		inFile >> buffer.low;
		inFile >> buffer.high;
		inFile >> buffer.cap;

		allTrans.push_back(buffer);
		count += 1;		
	}
	inFile.close();

	vector<trans*> order1;
	vector<trans*> order2;
	
	for (int i = 0; i < count; i++){
		order1.push_back(&allTrans[i]);
		order2.push_back(&allTrans[i]);
	}
	
	//Sorting 1
	stable_sort(order1.begin(), order1.end(), compare1);

	//Sorting 2
	stable_sort(order2.begin(), order2.end(), compare2);
	
	
	string a;
	string date, currency, exchange, m;
	trans* t;
	cin >> a;
	while (a != "end"){
		if (a == "query"){
			cin >> date >> currency >> exchange;
			query(order1, date, currency, exchange, 0, count-1);
		}
		else if (a == "price"){
			cin >> m >> date >> currency;
			price(order1, m, date, currency, 0, count-1);
		}
		else{
			cin >> date >> exchange;
			cap(order2, date, exchange, 0, count-1);
		}
	
		cin >> a;
	}
	exit(0);
	
	return 0;
}
