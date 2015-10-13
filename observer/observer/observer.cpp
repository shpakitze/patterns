#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

// 1. "Независимая" функциональность
class Subject {
	// 3. Связь только базовым классом Observer
	vector <class Observer*> views; 
	string value;
public:
	void attach(Observer *obs) {
		views.push_back(obs);
	}
	void setVal(string val) {
		value = val;
		notify();
	}
	string getVal() {
		return value;
	}
	void notify();
};

// 2. "Зависимая" функциональность
class Observer {
	Subject *model;
	char symbol;
public:
	Observer(Subject *mod, char smbl) {
		model = mod;
		symbol = smbl;
		// 4. Наблюдатели регистрируются у субъекта
		model->attach(this);
	}
	virtual void update() = 0;
protected:
	Subject *getSubject() {
		return model;
	}
	char getDivisor() {
		return symbol;  
	}
};

void Subject::notify() {
	// 5. Извещение наблюдателей
	for (int i = 0; i < views.size(); i++)
		views[i]->update();
}
//изменение порядка следования
class OrderObserver: public Observer {
public:
	OrderObserver(Subject *mod, char div): Observer(mod, div){}
	void update() {
		// 6. "Вытягивание" интересующей информации
		string v = getSubject()->getVal();
		char d = getDivisor();
		stack<int> pos;
		int prev=0;
		for (int i=0;i<v.size();++i)
			if (v[i]==d){
				random_shuffle(v.begin()+prev,v.begin()+i);
				prev=i+1;
			}
			//random_shuffle(v.begin(),v.end());
						
		cout << v << " string " << d << " char " << d << '\n';
	}
};

class UpcaseObserver: public Observer {
public:
	UpcaseObserver(Subject *mod, char div): Observer(mod, div){}
	void update() {
		string v = getSubject()->getVal();
		char d = getDivisor();
		for (string::iterator it=v.begin(); it!=v.end(); ++it)
			if (*it==d){
				*it=toupper(*it);
			}
			cout << "upper" <<'\n'<< v << '\n';

	}
};

int main() {
	Subject subj;
	OrderObserver divObs1(&subj, 'a'); // 7. Клиент настраивает число 
	OrderObserver divObs2(&subj, 'c'); //    и типы наблюдателей
	UpcaseObserver modObs3(&subj, 'b');
	subj.setVal("12345a123a456a789abla");
	}