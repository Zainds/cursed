﻿#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

string days[5] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница" };

class WorkshopBuilder {

private:
    string name;
    string workshopName;
    int detailsCreated[5];


public:
    WorkshopBuilder(string n, string wname, int d[5]) {
        name = n;
        workshopName = wname;
        for (int i = 0; i < 5; i++) {
            detailsCreated[i] = d[i];
        }
    }

    void setName(string _name) { name = _name; };
    void setWorkshopName(string _wName) { workshopName = _wName; };
    void setDetailsCreated(int* _detailsCr) { for (int i = 0; i < 5; i++) detailsCreated[i] = _detailsCr[i]; };
    string getName() { return name; };
    string getWorkshopName() { return workshopName; };
    int* getDetailsCreated() { return detailsCreated; };
    int getAllDetailsCreated() {
        int detailSum = 0;
        for (int x : detailsCreated) {
            detailSum += x;
        }
        return detailSum;
    };

    void printBuilder() {

        cout << "ФИО: " << name << " \t " << "ЦЕХ: " << workshopName << " \t "
            << "Изготовлено деталей: " << detailsCreated[0] << " "
            << detailsCreated[1] << " " << detailsCreated[2] << " "
            << detailsCreated[3] << " " << detailsCreated[4] << endl;

    }
    void printBuilderMaxDetail() {
        int day, details = -999;
        for (int i = 0; i < 5; i++) {
            if (detailsCreated[i] > details) {
                details = detailsCreated[i];
                day = i;
            }
        }
        cout << "ФИО: " << name << " \t " << days[day] << " " << details << " д" << endl;
    }

};

void updateInputFile(vector<WorkshopBuilder>& workers) {
    ofstream fout("input.txt");

    if (!fout)
    {
        cout << "Файл не открыт\n\n";
    }
    else
    {
        for (int i = 0; i < workers.size(); i++) {
            WorkshopBuilder x = workers[i];
            auto dt = x.getDetailsCreated();
            fout << x.getName() << " " << x.getWorkshopName() << " " << dt[0] << " " << dt[1]
                << " " << dt[2] << " " << dt[3] << " " << dt[4];
            if (i != workers.size() - 1) fout << endl;
        }
    }
}

void readWorkersFromConsole(vector<WorkshopBuilder>& workers) {
    ofstream out("input.txt");

    int count;
    string name, workshopName;
    int detailsCreated[5];
    cout << "Введите количество рабочих: "; cin >> count;
    cin.ignore();
    for (int i = 0; i < count; i++) {
        cout << "Введите имя: "; getline(cin >> ws, name);
        cout << "Введите цех: "; getline(cin >> ws, workshopName);

        cout << "Введите количество деталей по дням(через пробел) : ";

        for (int i = 0; i < 5; i++) {
            int x;
            cin >> x; cout << " ";
            detailsCreated[i] = x;
        }
        cout << endl;
        WorkshopBuilder WB(name, workshopName, detailsCreated);
        workers.push_back(WB);
    }
    updateInputFile(workers);
}

void readWorkersFromFile(vector<WorkshopBuilder>& workers) {
    ifstream fin("input.txt");

    if (!fin)
    {
        
        cout << "Файл не найден. Создаем новый файл\n\n";
        system("pause");
        readWorkersFromConsole(workers);
    }
    else
    {
        //cout << "Все ОК! Файл открыт!\n\n";
        for (string line; getline(fin, line); )
        {
            string name;
            string wname;
            string mynum = "";
            int dArr[5];
            int arrPos = 0;
            int spaceCounter = 0;

            for (int i = 0; i <= line.length(); i++)
            {
                if (line[i] == ' ') spaceCounter += 1;
                if (spaceCounter <= 2)name += line[i];
                if (spaceCounter > 2 && spaceCounter < 4 && line[i] != ' ')wname += line[i];
                if (spaceCounter >= 4) {
                    if (line[i] != ' ') {
                        mynum += line[i];

                    }
                    else {
                        if (spaceCounter != 4) {

                            dArr[arrPos] = stoi(mynum);
                            arrPos++;
                            mynum = "";
                        }
                    }
                    if (i == line.length())dArr[arrPos] = stoi(mynum);
                }
            }
            WorkshopBuilder WB(name, wname, dArr);
            workers.push_back(WB);
        }
    }
}

void writeWorkersFromFile(vector<WorkshopBuilder>& workers) {
    ofstream fout("output.txt");

    if (!fout)
    {
        cout << "Файл не открыт\n\n";
    }
    else
    {
        for (int i = 0; i < workers.size(); i++) {
            WorkshopBuilder x = workers[i];
            fout << x.getName() << " " << x.getAllDetailsCreated();
            if (i != workers.size() - 1) fout << endl;
        }
    }
}
void printAllBuilders(vector<WorkshopBuilder>& workers) {
    for (WorkshopBuilder x : workers) {
        x.printBuilder();
    }
}
//Вывести всех рабочих заданного цеха и день недели в который он собрал наибольшее кол-во деталей
void printFromCurWS(vector<WorkshopBuilder>& workers) {
    string workshopName;
    cout << "Введите цех: "; getline(cin >> ws, workshopName);
    for (WorkshopBuilder x : workers) {
        if (x.getWorkshopName() == workshopName) {
            x.printBuilderMaxDetail();
        }
    }
}
void printAllBuildersOutputFormat(vector<WorkshopBuilder>& workers) {
    for (WorkshopBuilder x : workers) {
        cout << x.getName() << " " << x.getAllDetailsCreated() << endl;
    }
    writeWorkersFromFile(workers);
}
void printAllBuildersFromInputFile() {
    vector<WorkshopBuilder> localWorkers;
    readWorkersFromFile(localWorkers);
    printAllBuilders(localWorkers);
}

void addWorker(vector<WorkshopBuilder>& workers) {
    string name;
    string workshopName;
    int detailsCreated[5];
    cout << "Введите имя: "; getline(cin >> ws, name);
    cout << "Введите цех: "; getline(cin >> ws, workshopName);
    cout << "Введите количество деталей по дням(через пробел): ";
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x; cout << " ";
        detailsCreated[i] = x;
    }
    WorkshopBuilder WB(name, workshopName, detailsCreated);
    workers.push_back(WB);

    ofstream outfile;
    outfile.open("input.txt", std::ios_base::app); // append instead of overwrite
    outfile << endl << name << " " << workshopName << " " << detailsCreated[0] << " " << detailsCreated[1] << " "
        << detailsCreated[2] << " " << detailsCreated[3] << " " << detailsCreated[4];
}

void deleteWorkerByFio(vector<WorkshopBuilder>& workers) {
    string name;
    int flag = 0;
    cout << "Введите ФИО для удаления работника: "; getline(cin >> ws, name);
    for (int i = 0; i < workers.size(); i++) {
        if (workers[i].getName() == name) {
            flag = 1;
            workers.erase(workers.begin() + i);
            i--;
        }
    }
    if (flag == 1) {
        updateInputFile(workers);
    }
    else {
        cout << "Рабочий не найден\n";
        system("pause");
    }
    
}
void renameWorkerWorkshopByFio(vector<WorkshopBuilder>& workers) {
    int flag = 0;
    string name, workshopName;
    cout << "Введите ФИО работника для смены цеха: "; getline(cin >> ws, name);
    cout << "Введите новый цех: "; getline(cin >> ws, workshopName);
    for (int i = 0; i < workers.size(); i++) {
        if (workers[i].getName() == name) {
            flag = 1;
            cout << "!!\n";
            workers[i].setWorkshopName(workshopName);
        }
    }
    if (flag == 1) {
        updateInputFile(workers);
    }
    else {
        cout << "Рабочий не найден\n";
        system("pause");
    }
}
void showMenu(vector<WorkshopBuilder>& workers) {
    boolean isScanned = false;
    while (true) {
        if (!isScanned) {
            cout << endl <<
                "1. Считать содержимое из файла\n" <<
                "2. Заполнить рабочих через консоль\n";
        }

        else {
            cout << endl <<
                "3. Выдать на экран содержимое файла\n" <<
                "4. Выдать на экран список рабочих заданного цеха\n" <<
                "5. Распечатать файл упрощенной структуры\n" <<
                "6. Добавить данные нового рабочего\n" <<
                "7. Удалить все элементы записи определённого рабочего\n" <<
                "8. Изменить цех у определённого рабочего\n" <<
                "н. Назад\n" <<
                "в. Выход" << endl;
        }

        char choice;
        cin >> choice;
        switch (choice) {
        case '1':
            readWorkersFromFile(workers);
            system("cls");
            isScanned = true;
            break;
        case '2':
            system("cls");
            readWorkersFromConsole(workers);
            isScanned = true;
            break;
        case '3':
            system("cls");
            if (isScanned) printAllBuilders(workers);
            break;
        case '4':
            system("cls");
            if (isScanned) printFromCurWS(workers);
            break;
        case '5':
            system("cls");
            if (isScanned) printAllBuildersOutputFormat(workers);
            break;
        case '6':
            if (isScanned) addWorker(workers);
            system("cls");
            break;
        case '7':
            if (isScanned) deleteWorkerByFio(workers);
            system("cls");
            break;
        case '8':
            if (isScanned) renameWorkerWorkshopByFio(workers);
            system("cls");
            break;
        case 'в':
            exit(3);
            break;
        case 'н':
            system("cls");
            isScanned = false;
            workers.clear();
            break;
        default:
            cout << "Недопустимое значение!" << endl;
            break;
        }
    }

}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");
    vector<WorkshopBuilder> workers;

    showMenu(workers);

}
//Ангальдт Михаил Ильич цех2 12 34 123 5 2
//Алабин Никита Сергеевич цех1 11 0 34 10 93
//Моисеев Даниил Игоревич цех1 10 4 5 8 6
//Мелков Илья Игоревич цех4 7 85 2 6 3
//Михалков Никита Серый цех4 1 2 3 4 5
//Агафонов Петр Иванович цех1 1 2 3 4 5
//Скляров Олег Русанович цех1 2 3 4 5 6
//Земеров Егор Эдуардович цех2 23 45 64 12 55