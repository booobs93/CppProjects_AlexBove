#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
vector<T> AddVectors(const vector<T>& v1, const vector<T>& v2) {
	vector<T> v3;
	if (v1.size == v2.size()) {
		for (int i = 0; i < v1.size(); ++i) {
			v3.push_back(v1(i) + v2(i));
		}
	}
	return v3;
}

template <typename T>
vector<T> ConcatVectors(const vector<T>& v1, const vector<T>& v2){
	vector<T> v3;
	for (int i = 0; i < v1.size(); ++i) {
		v3.push_back(v1(i));
	}
	for (int i = 0; i < v2.size(); ++i) {
		v3.push_back(v2(i));
	}
	return v3;
}

void shiftRight(vector<int>& v) {
	for (int i = v.size() - 1; i >= 0; --i) {
		v[i] = v[i - 1];
	}
	srand(time(NULL));
	v[0] = rand() * 100;
}

template <typename T>
void Rotteleft(vector<T>& v) {
	T aux = v[0];
	for (int i = 0; i < v.size(); ++i) {
		v[i] = v[i + 1];
	}
	v[v.size() - 1] = aux;
}

void searchAdjacent(vector<int>& v) {
	for (int i = 0; i < v.size() - 2; ++i) {
		if (v[i] == v[i + 1] == v[i + 2]) {
			for (int j = i + 2; j > 2; --j) {
				v[j] = v[j - 3];
			}
			srand(time(NULL));
			v[0] = rand() * 100;
			v[1] = rand() * 100;
			v[2] = rand() * 100;
		}
	}
}

int main(){

	vector<int> v1(5);
	vector<int> v2(10, 0);
	vector<int> v3 = { 10,9,8,7,6,5,4,3,2,1 };
	vector<string> v4 = { "Gertrudiz","Pancracia","Anacleto","Hipolito","Eustaquio","Fulgencia" };	vector<int> v5 = v3;	struct Persona 	{
		string nombre;
		string fecha;
		string dni;
	};	vector<Persona> v6 = { Persona{"pepe", "0101200", "123456789A"},		Persona{"tete","02012001","234567991B"},		Persona{"tito", "03012003", "456123798C"}};
}

