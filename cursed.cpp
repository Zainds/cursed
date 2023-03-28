#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string days[5] = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница"};

class WorkshopBuilder {
    string name;
    string workshopName;
    int detailsCreated[5];

    WorkshopBuilder(string n, string wname, int d[5]) {
        name = n;
        workshopName = wname;
        for (int i = 0; i < 5; i++) {
            detailsCreated[i] = d[i];
        }
    }
    void printBuilder(){
        cout << "ФИО: " << name << "  " << "ЦЕХ: " << workshopName << "  " 
            <<"Изготовлено деталей: "<< detailsCreated[0] << " " 
            <<detailsCreated[1]<<" "<<detailsCreated[2] << " "  
            <<detailsCreated[3]<< " "<< detailsCreated[4]<<endl;
    }
};

int main()
{
    setlocale(LC_ALL, "");

    vector<WorkshopBuilder> workers;
    ifstream fin("input.txt");

    if (!fin)
    {
        cout << "Файл не открыт\n\n";
        
    }
    else
    {
        cout << "Все ОК! Файл открыт!\n\n";
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
                if (spaceCounter<=2)name += line[i];
                if (spaceCounter > 2 && spaceCounter <4 && line[i] != ' ')wname += line[i];
                if (spaceCounter >= 4 ) {
                    if (line[i] != ' ' ) {
                        mynum += line[i];

                    }
                    else {
                        if (spaceCounter != 4) {

                            dArr[arrPos] = stoi(mynum);
                            arrPos++;
                            mynum = "";
                        }
                        
                    }
                    if(i == line.length())dArr[arrPos] = stoi(mynum);
                    
                    
                }
                
                
                cout << line[i];
            }
            cout << endl <<name <<" "<< wname<< " " << 
                dArr[0] << " " << dArr[1] << " " << dArr[2] << " " << dArr[3] << " " << dArr[4] << endl;
            
        }
        
    }
}

