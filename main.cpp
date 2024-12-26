#include "mylib.h"
#include "stud.h"

int main() {
    char choice;
    bool useVector = true;
    RuleOfThree();
    //Zmogus zmogus ("Justina", "Seiliunaite");

    while (true) {
        cout << "Choose container type (V for vector, L for list): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 'V' || choice == 'v') {
            useVector = true;
            break;
        } else if (choice == 'L' || choice == 'l') {
            useVector = false;
            break;
        } else {
            cout << "Error. Please enter 'V' for vector or 'L' for list." << endl;
        }
    }
if (useVector) {
    vector<Stud<vector<double>>> students;
    programLoop(students);
} else {
    list<Stud<list<double>>> students;
    programLoop(students);
}

    return 0;
}

template <typename Container>
void programLoop(Container& students) {
    using StudType = typename Container::value_type;
    Container vargsiukai;
    StudType temp;
    vector<int> numStudents = {1000, 10000, 100000, 1000000, 10000000};
    char choice;
    bool suMediana = false;

    while (true) {
        cout << "Do you want to test the file? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 'Y' || choice == 'y') {

        cout << "Do you want to generate files (G) or you generated them before (B)?";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 'G' || choice == 'g') {
                for (int num : numStudents) {
                string filename = "studentai" + to_string(num) + ".txt";
        FileManager::genfailas(filename, num);
        cout << endl;
        }
        }else if (choice == 'B' || choice == 'b'){
        } else {
            cout << "Error.Try again" << endl;
        }

        for (int num : numStudents) {
        typename Container::value_type temp;
        string filename = "studentai" + to_string(num) + ".txt";
        cout << "Testing file: " << filename << endl;
        testavimas(students, filename, num);
        }

        cout << "Do you want to continue the program? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 'N' || choice == 'n') {
                return;
                } else if (choice == 'Y' || choice == 'y'){
                    break;
                } else {
                        cout << "Error.Try again" << endl;
                }
        } else if (choice == 'N' || choice == 'n') {
            break;
        } else {
            cout << "Error. Try again." << endl;
        }
    }

    while (true) {
        cout << "Do you want to read student data from a file? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n') {
            break;
        } else {
            cout << "Error. Try again." << endl;
        }
    }

    if (choice == 'Y' || choice == 'y') {
        string filename;
        cout << "Enter the filename: ";
        cin >> filename;
        FileManager::nuskaitymas(students, filename);


        while (true) {
            cout << "Do you want to calculate the final grade with median or with average? (M/A): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice == 'M' || choice == 'm') {
                suMediana = true;
                break;
            } else if (choice == 'A' || choice == 'a') {
                suMediana = false;
                break;
            } else {
                cout << "Error. Try again." << endl;
            }
        }

   for (auto& student : students) {
        student.setSuMediana(suMediana);
        if (suMediana) {
            student.galutinismed();
        } else {
            student.galutinisvid();
                }
            }

            Rusiavimas::rusiavimas(students, vargsiukai, suMediana);

        Rusiavimas::sortabc(students);
        Rusiavimas::sortabc(vargsiukai);

        FileManager::ratefailas(students, "kietekai_" + filename, "Kietekai");
        FileManager::ratefailas(vargsiukai, "vargsiukai_" + filename, "Vargšiukai");

    } else {

        while (true) {
        cout << "Do you want to generate student data files? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice == 'Y' || choice == 'y') {
                generuotifailus();
                return;
            } else if (choice == 'N' || choice == 'n') {
                break;
            } else {
                cout << "Error. Try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

            int n;
            while (true) {
                cout << "How many students do you have? ";
                if (cin >> n && n > 0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Error. Try again." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            for (int i = 0; i < n; i++) {
                typename Container::value_type temp;
                cout << "Please input user data for student " << endl;

                while (true) {
                    cout << "Do you want to generate random grades for this student? (Y/N): ";
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (choice == 'Y' || choice == 'y') {
                        temp.autom();
                        break;
                    } else if (choice == 'N' || choice == 'n') {
                        cin >> temp;
                        break;
                    } else {
                        cout << "Error. Try again." << endl;
                    }
                }

                 while (true) {
                    cout << "Do you want to calculate the final grade with median or with average? (M/A): ";
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (choice == 'M' || choice == 'm') {
                        suMediana = true;
                        break;
                    } else if (choice == 'A' || choice == 'a') {
                        suMediana = false;
                        break;
                    } else {
                        cout << "Error. Try again." << endl;
                    }
                }

                temp.setSuMediana(suMediana);
                if (suMediana) {
                        temp.galutinismed();
                } else {
                    temp.galutinisvid();
                    }

                    students.push_back(temp);
                    cout << "Memory address of the student in container: " << &students.back() << endl;
                    temp.val();
            }

            Rusiavimas::rusiavimas(students, vargsiukai, suMediana);
            Rusiavimas::sortabc(students);
            Rusiavimas::sortabc(vargsiukai);

            cout << "\nKietekai:\n";
            cout << left << setw(18) << "Vardas" << setw(18) << "Pavardė" << setw(25) << "Galutinis" << endl;
            cout << string(60, '-') << endl;
            for (const auto& student : students) {
                    cout << student;
            }

            cout << "\nVargšiukai:\n";
            cout << left << setw(18) << "Vardas" << setw(18) << "Pavardė" << setw(25) << "Galutinis" << endl;
            cout << string(60, '-') << endl;
            for (const auto& student : vargsiukai) {
                    cout << student;
            }

            FileManager::ratefailas(students, "kietekai.txt", "Kietekai");
            FileManager::ratefailas(vargsiukai, "vargsiukai.txt", "Vargšiukai");
    }

    char a;
    cout << "Press any key to exit..." << endl;
    cin >> a;


}


