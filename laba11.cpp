#include <iostream>

using namespace std;
struct Tube {
	string name;
	float dlina;
	int diametr;
	bool check;
};

struct Ks {
	string name;
	int ceh;
	int workceh;
	string klass;
};

void menu() {




	while (true) {
		cout << "1. Добавить трубу" << endl;
		cout << "2. Добавить КС" << endl;
		cout << "3. Просмотр всех объектов" << endl;
		cout << "4. Редактировать трубу" << endl;
		cout << "5. Редактировать КС" << endl;
		cout << "6. Сохранить данные" << endl;
		cout << "7. Загрузить данные" << endl;
		cout << "8. Выход" << endl;
		break;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	Tube T;
	Ks K;
	menu();
	return 0;
}

