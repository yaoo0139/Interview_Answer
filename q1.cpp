#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
vector<char *> vs = {
  "aa",
  "ccc",
  "eeeee",
  "gggggg",
  "zzzz",
};

// Q1
// 完成用 binary serach 搜尋vector vs, 回傳字串str在vs中的位置, 若未發現則回傳 -1
// 不限使用 C或C++的function 
// 但請注意c++ string 與 c char*轉換的消耗, 盡可能以最有效率的方式完成工作, 

int bin_search(const string &str) {
	const char* s = str.c_str();
	int L = 0, R = vs.size() - 1;
	while(L <= R){
		int mid = (L+R) / 2;
		int ret = strcmp(s, vs[mid]);
		if(ret < 0){
			R = mid - 1;
		}
		else if(ret > 0){
			L = mid + 1;
		}
		else
			return mid;

	}
	return -1;
}
int main(){
	string str;
	while(cin>> str)
		cout<< bin_search(str)<< endl;
}
// Q2
// 若要insert "111"到vs內, 應該放在哪最為合適.

// 根據strcmp的判定，111是在此vector裡應該為最小的元素，因此他應該放在aa前面，以維護binary_search的正確性
