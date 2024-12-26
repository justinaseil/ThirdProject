#include "stud.h"

    void generuotifailus() {
    FileManager::genfailas("studentai1000.txt", 1000);
    FileManager::genfailas("studentai10000.txt", 10000);
    FileManager::genfailas("studentai100000.txt", 100000);
    FileManager::genfailas("studentai1000000.txt", 1000000);
    FileManager::genfailas("studentai10000000.txt", 10000000);
}

void RuleOfThree() {
    Stud<vector<double>> studentas1("Justina", "Seiliunaite");
    studentas1.addND(8.0);
    studentas1.addND(7.5);
    studentas1.setEgz(9.0);

    studentas1.galutinisvid();

    Stud<vector<double>> studentas2(studentas1);
    studentas2.galutinisvid();

    Stud<vector<double>> studentas3("Juste", "Sei");
    studentas3 = studentas1;
    studentas3.galutinisvid();

    cout << "Studentas 2: " << studentas2 << endl;
    cout << "Studentas 3: " << studentas3 << endl;

    studentas1.val();
    studentas2.val();
    studentas3.val();
}
