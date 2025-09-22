#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <cctype>
#include <locale>

using namespace std;

class Pipe {
private:
    string name;
    double length;
    double diameter;
    bool under_repair;

public:
    Pipe() : name(""), length(0.0), diameter(0.0), under_repair(false) {}

    void inputFromConsole() {
        cout << "\n=== Добавление трубы ===" << endl;

        // Исправлено: проверка, что километровая отметка — только цифры
        while (true) {
            cout << "Введите километровую отметку: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            bool isNumber = true;
            for (char c : name) {
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            if (isNumber && !name.empty()) {
                break;
            }
            else {
                cout << "Ошибка! Километровая отметка должна быть числом (например, '123')!" << endl;
            }
        }

        // Длина
        while (true) {
            cout << "Введите длину трубы (км): ";
            if (cin >> length && length > 0) {
                if (cin.peek() == '\n' || cin.peek() == EOF) {
                    break;
                }
                else {
                    cout << "Ошибка! После числа обнаружены лишние символы (например, буквы)." << endl;
                }
            }
            else {
                cout << "Ошибка! Длина должна быть положительным числом." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Диаметр
        while (true) {
            cout << "Введите диаметр трубы (мм): ";
            if (cin >> diameter && diameter > 0) {
                if (cin.peek() == '\n' || cin.peek() == EOF) {
                    break;
                }
                else {
                    cout << "Ошибка! После числа обнаружены лишние символы (например, буквы)." << endl;
                }
            }
            else {
                cout << "Ошибка! Диаметр должен быть положительным числом." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Ремонт
        char repair_input;
        while (true) {
            cout << "Труба в ремонте? (y/n): ";
            cin >> repair_input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            repair_input = tolower(repair_input);
            if (repair_input == 'y' || repair_input == 'n') {
                break;
            }
            cout << "Ошибка! Введите 'y' или 'n'." << endl;
        }
        under_repair = (repair_input == 'y');
    }

    void display() const {
        cout << "\n=== Труба: " << name << " ===" << endl;
        cout << "Километровая отметка: " << name << endl;
        cout << "Длина: " << fixed << setprecision(2) << length << " км" << endl;
        cout << "Диаметр: " << fixed << setprecision(1) << diameter << " мм" << endl;
        cout << "В ремонте: " << (under_repair ? "Да" : "Нет") << endl;
    }

    void toggleRepair() {
        under_repair = !under_repair;
        cout << "Труба '" << name << "' "
            << (under_repair ? "поставлена в ремонт" : "выведена из ремонта") << endl;
    }

    void saveToFile(ofstream& file) const {
        file << "PIPE|" << name << "|" << length << "|" << diameter << "|" << under_repair << endl;
    }

    bool loadFromFile(const string& line) {
        size_t pos = 0;
        string token;
        string delimiter = "|";
        vector<string> tokens;

        string tempLine = line;
        while ((pos = tempLine.find(delimiter)) != string::npos) {
            token = tempLine.substr(0, pos);
            tokens.push_back(token);
            tempLine.erase(0, pos + delimiter.length());
        }
        tokens.push_back(tempLine);

        if (tokens.size() == 5 && tokens[0] == "PIPE") {
            name = tokens[1];
            try {
                length = stod(tokens[2]);
                diameter = stod(tokens[3]);
                under_repair = (tokens[4] == "1");
                return true;
            }
            catch (const exception& e) {
                cout << "Ошибка загрузки трубы: неверный формат данных" << endl;
                return false;
            }
        }
        return false;
    }

    bool exists() const {
        return !name.empty();
    }
};

class CompressorStation {
private:
    string name;
    int total_workshops;
    int working_workshops;
    int station_class;

public:
    CompressorStation() : name(""), total_workshops(0), working_workshops(0), station_class(1) {}

    void inputFromConsole() {
        cout << "\n=== Добавление КС ===" << endl;
        cout << "Введите название КС: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        // Общее количество цехов
        while (true) {
            cout << "Введите общее количество цехов: ";
            if (cin >> total_workshops && total_workshops > 0) {
                if (cin.peek() == '\n' || cin.peek() == EOF) {
                    break;
                }
                else {
                    cout << "Ошибка! После числа обнаружены лишние символы (например, буквы)." << endl;
                }
            }
            else {
                cout << "Ошибка! Количество цехов должно быть положительным числом." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Работающие цехи
        while (true) {
            cout << "Введите количество работающих цехов: ";
            if (cin >> working_workshops && working_workshops >= 0 &&
                working_workshops <= total_workshops) {
                if (cin.peek() == '\n' || cin.peek() == EOF) {
                    break;
                }
                else {
                    cout << "Ошибка! После числа обнаружены лишние символы (например, буквы)." << endl;
                }
            }
            else {
                cout << "Ошибка! Количество работающих цехов должно быть от 0 до "
                    << total_workshops << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Класс станции
        while (true) {
            cout << "Введите класс станции (1-5): ";
            if (cin >> station_class && station_class >= 1 && station_class <= 5) {
                if (cin.peek() == '\n' || cin.peek() == EOF) {
                    break;
                }
                else {
                    cout << "Ошибка! После числа обнаружены лишние символы (например, буквы)." << endl;
                }
            }
            else {
                cout << "Ошибка! Класс станции должен быть от 1 до 5." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void display() const {
        cout << "\n=== КС: " << name << " ===" << endl;
        cout << "Название: " << name << endl;
        cout << "Общее количество цехов: " << total_workshops << endl;
        cout << "Работающих цехов: " << working_workshops << endl;
        cout << "Класс станции: " << station_class << endl;
        cout << "Эффективность: " << fixed << setprecision(1)
            << (total_workshops > 0 ? (working_workshops * 100.0 / total_workshops) : 0)
            << "%" << endl;
    }

    void startWorkshop() {
        if (working_workshops < total_workshops) {
            working_workshops++;
            cout << "Запущен цех. Теперь работает " << working_workshops
                << " из " << total_workshops << " цехов." << endl;
        }
        else {
            cout << "Ошибка! Все цехи уже работают." << endl;
        }
    }

    void stopWorkshop() {
        if (working_workshops > 0) {
            working_workshops--;
            cout << "Остановлен цех. Теперь работает " << working_workshops
                << " из " << total_workshops << " цехов." << endl;
        }
        else {
            cout << "Ошибка! Нет работающих цехов для остановки." << endl;
        }
    }

    void saveToFile(ofstream& file) const {
        file << "STATION|" << name << "|" << total_workshops << "|"
            << working_workshops << "|" << station_class << endl;
    }

    bool loadFromFile(const string& line) {
        size_t pos = 0;
        string token;
        string delimiter = "|";
        vector<string> tokens;

        string tempLine = line;
        while ((pos = tempLine.find(delimiter)) != string::npos) {
            token = tempLine.substr(0, pos);
            tokens.push_back(token);
            tempLine.erase(0, pos + delimiter.length());
        }
        tokens.push_back(tempLine);

        if (tokens.size() == 5 && tokens[0] == "STATION") {
            name = tokens[1];
            try {
                total_workshops = stoi(tokens[2]);
                working_workshops = stoi(tokens[3]);
                station_class = stoi(tokens[4]);

                if (total_workshops <= 0 || working_workshops < 0 ||
                    working_workshops > total_workshops || station_class < 1 || station_class > 5) {
                    cout << "Ошибка загрузки КС: неверные данные" << endl;
                    return false;
                }

                return true;
            }
            catch (const exception& e) {
                cout << "Ошибка загрузки КС: неверный формат данных" << endl;
                return false;
            }
        }
        return false;
    }

    bool exists() const {
        return !name.empty();
    }
};

class PipelineSystem {
private:
    Pipe pipe;
    CompressorStation station;

    int getMenuChoice() {
        int choice;
        while (true) {
            cout << "\n=== Меню управления трубопроводом ===" << endl;
            cout << "1. Добавить трубу" << endl;
            cout << "2. Добавить КС" << endl;
            cout << "3. Просмотр всех объектов" << endl;
            cout << "4. Редактировать трубу" << endl;
            cout << "5. Редактировать КС" << endl;
            cout << "6. Сохранить данные" << endl;
            cout << "7. Загрузить данные" << endl;
            cout << "8. Показать содержимое файла" << endl;
            cout << "0. Выход" << endl;
            cout << "Выберите действие: ";

            if (cin >> choice) {
                if (choice >= 0 && choice <= 8) {
                    if (cin.peek() == '\n' || cin.peek() == EOF) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        return choice;
                    }
                    else {
                        cout << "Ошибка! После числа обнаружены лишние символы." << endl;
                    }
                }
                else {
                    cout << "Ошибка! Введите число от 0 до 8." << endl;
                }
            }
            else {
                cout << "Ошибка! Введите корректное число." << endl;
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void editPipeMenu() {
        if (!pipe.exists()) {
            cout << "Ошибка! Труба не создана." << endl;
            return;
        }

        int choice;
        while (true) {
            cout << "\n=== Редактирование трубы ===" << endl;
            cout << "1. Переключить статус ремонта" << endl;
            cout << "2. Вернуться в меню" << endl;
            cout << "Выберите действие: ";

            if (cin >> choice) {
                if (cin.peek() == '\n' || cin.peek() == EOF) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (choice) {
                    case 1:
                        pipe.toggleRepair();
                        return;
                    case 2:
                        return;
                    default:
                        cout << "Ошибка! Неверный выбор." << endl;
                    }
                }
                else {
                    cout << "Ошибка! После числа обнаружены лишние символы." << endl;
                }
            }
            else {
                cout << "Ошибка! Введите число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void editStationMenu() {
        if (!station.exists()) {
            cout << "Ошибка! КС не создана." << endl;
            return;
        }

        int choice;
        while (true) {
            cout << "\n=== Редактирование КС ===" << endl;
            cout << "1. Запустить цех" << endl;
            cout << "2. Остановить цех" << endl;
            cout << "3. Вернуться в меню" << endl;
            cout << "Выберите действие: ";

            if (cin >> choice) {
                if (cin.peek() == '\n' || cin.peek() == EOF) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (choice) {
                    case 1:
                        station.startWorkshop();
                        return;
                    case 2:
                        station.stopWorkshop();
                        return;
                    case 3:
                        return;
                    default:
                        cout << "Ошибка! Неверный выбор." << endl;
                    }
                }
                else {
                    cout << "Ошибка! После числа обнаружены лишние символы." << endl;
                }
            }
            else {
                cout << "Ошибка! Введите число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void saveData() {
        ofstream file("pipeline_data.txt");
        if (!file) {
            cout << "Ошибка при создании файла!" << endl;
            return;
        }

        if (pipe.exists()) {
            pipe.saveToFile(file);
            cout << "Труба сохранена." << endl;
        }
        if (station.exists()) {
            station.saveToFile(file);
            cout << "КС сохранена." << endl;
        }

        file.close();
        cout << "Данные успешно сохранены в файл 'pipeline_data.txt'" << endl;
    }

    void loadData() {
        ifstream file("pipeline_data.txt");
        if (!file) {
            cout << "Ошибка при открытии файла или файл не существует!" << endl;
            return;
        }

        Pipe loadedPipe;
        CompressorStation loadedStation;
        string line;
        bool pipeLoaded = false;
        bool stationLoaded = false;

        while (getline(file, line)) {
            if (line.find("PIPE|") == 0) {
                if (loadedPipe.loadFromFile(line)) {
                    pipeLoaded = true;
                }
            }
            else if (line.find("STATION|") == 0) {
                if (loadedStation.loadFromFile(line)) {
                    stationLoaded = true;
                }
            }
        }

        file.close();

        if (pipeLoaded) {
            pipe = loadedPipe;
            cout << "Труба загружена успешно." << endl;
        }
        if (stationLoaded) {
            station = loadedStation;
            cout << "КС загружена успешно." << endl;
        }

        if (!pipeLoaded && !stationLoaded) {
            cout << "В файле нет корректных данных." << endl;
        }
    }

    void showFileContent() {
        ifstream file("pipeline_data.txt");
        if (!file) {
            cout << "Файл не существует или не может быть открыт!" << endl;
            return;
        }

        cout << "\n=== Содержимое файла pipeline_data.txt ===" << endl;
        string line;
        int lineNumber = 1;
        while (getline(file, line)) {
            cout << lineNumber++ << ": " << line << endl;
        }
        file.close();

        if (lineNumber == 1) {
            cout << "Файл пуст." << endl;
        }
    }

public:
    void run() {
        setlocale(LC_ALL, "Russian");
        cout << "=== Система управления трубопроводным транспортом ===" << endl;

        while (true) {
            int choice = getMenuChoice();

            switch (choice) {
            case 0:
                cout << "Выход из программы..." << endl;
                return;
            case 1:
                pipe.inputFromConsole();
                break;
            case 2:
                station.inputFromConsole();
                break;
            case 3:
                if (pipe.exists()) pipe.display();
                if (station.exists()) station.display();
                if (!pipe.exists() && !station.exists()) {
                    cout << "Нет созданных объектов." << endl;
                }
                break;
            case 4:
                editPipeMenu();
                break;
            case 5:
                editStationMenu();
                break;
            case 6:
                saveData();
                break;
            case 7:
                loadData();
                break;
            case 8:
                showFileContent();
                break;
            }
        }
    }
};

int main() {
    PipelineSystem system;
    system.run();
    return 0;
}