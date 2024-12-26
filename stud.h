#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED

#include "mylib.h"

class Zmogus {
protected:
    string vardas;
    string pavarde;

    public:
    Zmogus(const string& vardas, const string& pavarde)
        : vardas(vardas), pavarde(pavarde) {}

    virtual ~Zmogus() {}

    const string& getVardas() const { return vardas; }
    const string& getPavarde() const { return pavarde; }

virtual void abstraktas() const = 0;
};

template <typename Container>
class Stud : public Zmogus {
private:
    Container ND;
    double egz;
    double vid;
    double med;
    double rezvid;
    double rezmed;
    bool suMediana;
    bool locked;

public:

    void abstraktas() const override {}

    Stud() : Zmogus("", ""), egz(0), vid(0), med(0), suMediana(false), locked(false) {}

    Stud(const string& vard, const string& pav)
        : Zmogus(vard, pav), egz(0), vid(0), med(0), suMediana(false), locked(false) {}

    Stud(const Stud& source) : Zmogus(source){
        vardas = source.vardas;
        pavarde = source.pavarde;
        egz = source.egz;
        ND = source.ND;
        rezmed = source.rezmed;
        rezvid = source.rezvid;
        suMediana = source.suMediana;
        locked = source.locked;
    }


Stud& operator=(const Stud& source) {
    if (this == &source) return *this;

    Zmogus::operator=(source);
    ND = source.ND;
    egz = source.egz;
    vid = source.vid;
    med = source.med;
    rezvid = source.rezvid;
    rezmed = source.rezmed;
    suMediana = source.suMediana;
    locked = source.locked;

    return *this;
}

~Stud() {
    val();
}

    Container& getND() { return ND; }
    double getEgz() const { return egz; }
    double getVid() const { return vid; }
    double getMed() const { return med; }
    bool getSuMediana() const { return suMediana; }
    double getRezmed() const { return rezmed; }
    double getRezvid() const { return rezvid; }

    void setRezVid(double r) { rezvid = r; }
    void setRezMed(double r) { rezmed = r; }

    void setVardas(const string& vard) {
        if (locked) throw runtime_error("Cannot modify 'vardas' after locking.");
        vardas = vard;
    }

    void setPavarde(const string& pav) {
        if (locked) throw runtime_error("Cannot modify 'pavarde' after locking.");
        pavarde = pav;
    }

    void addND(double grade) {
        if (locked) {
        throw runtime_error("Cannot modify 'ND' after locking.");
    }
    if constexpr (is_same<Container, vector<typename Container::value_type>>::value ||
                  is_same<Container, list<typename Container::value_type>>::value) {
        if (grade >= 0 && grade <= 10) {
            ND.push_back(grade);
        } else {
            throw runtime_error("Grade out of range.");
        }
    } else {
        throw runtime_error("Unsupported container type for adding grades.");
        }
    }

    void setEgz(double e) {
        if (e >= 0 && e <= 10) {
            egz = e;
        } else {
            throw runtime_error("Exam grade out of range.");
        }
    }

    void setSuMediana(bool value) { suMediana = value; }


    void vidurkis();
    void mediana();
    void galutinismed();
    void galutinisvid();

    void ived();
    void autom();

    void lock() { locked = true; }
    void unlock() { locked = false; }
    bool isLocked() const { return locked; }


    void val();

};

class FileManager {
public:
    static void genfailas(const string& filename, int numStudents) {

    auto start = steady_clock::now();

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    file << "Vardas Pavarde ";
    for (int i = 1; i <= 10; ++i) {
        file << "ND" << i << " ";
    }
    file << "Egzaminas" << endl;

    srand(time(0));

    for (int i = 1; i <= numStudents; ++i) {
        file << "Vardas" << i << " Pavarde" << i << " ";

        for (int j = 0; j < 10; ++j) {
            file << rand() % 10 + 1 << " ";
        }

        file << rand() % 10 + 1 << endl;
    }

    file.close();

    auto end = steady_clock::now();
    duration<double> diff = duration_cast<duration<double>>(end - start);

    cout << "File " << filename << " created in " << diff.count() << " s." << endl;
};
template <typename Container>
static void nuskaitymas(Container& students, const string& filename) {
    using StudType = typename Container::value_type;

    auto start = steady_clock::now();

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Error opening file: " + filename);
    }

    string header;
    getline(file, header);

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string vardas, pavarde;
        ss >> vardas >> pavarde;

        if (ss.fail()) {
            throw runtime_error("Error parsing student name and surname from line.");
        }

        StudType student(vardas, pavarde);

        double grade;
        while (ss >> grade) {
            if (ss.fail()) {
                throw runtime_error("Invalid grade format in file.");
            }
            if (grade >= 0 && grade <= 10) {
                student.addND(grade);
            } else {
                throw runtime_error("Grade out of range (0-10) in file.");
            }
        }

        if (!student.getND().empty()) {
            student.setEgz(student.getND().back());
            student.getND().pop_back();
        } else {
            throw runtime_error("No grades found for student: " + vardas + " " + pavarde);
        }

        student.lock();
        students.push_back(student);
    }

    file.close();

    auto end = steady_clock::now();
    duration<double> diff = duration_cast<duration<double>>(end - start);

    cout << "File " << filename << " read in " << diff.count() << " s." << endl;
}

    template <typename Container>
    static void ratefailas(const Container& students, const string& filename, const string& title){
    auto start = steady_clock::now();

    ofstream file(filename);
    if (file.is_open()) {
        file << title << ":\n";
        file << left << setw(20) << "Vardas"
             << setw(25) << "Pavardė"
             << setw(30) << "Galutinis (Vid.)/Galutinis (Med.)" << endl;
        file << "-----------------------------------------------------------------------" << endl;

        for (const auto& student : students) {
            file << left << setw(20) << student.getVardas()
                 << setw(25) << student.getPavarde()
                 << fixed << setprecision(2);
            if (student.getSuMediana()) {
                file << student.getRezmed() << endl;
            } else {
                file << student.getRezvid() << endl;
            }
        }

        file.close();
    } else {
        cout << "Unable to open " << filename << " file." << endl;
    }

    auto end = steady_clock::now();
    duration<double> diff = duration_cast<duration<double>>(end - start);
    cout << "File " << filename << " created in " << diff.count() << " s." << endl;
};
};

class Rusiavimas {
public:
    template <typename Container>
    static void sortabc(Container& students) {
    auto start = steady_clock::now();

    if constexpr (is_same<Container, vector<typename Container::value_type>>::value) {
            sort(students.begin(), students.end(), [](const typename Container::value_type& a, const typename Container::value_type& b) {
                double gradeA = a.getSuMediana() ? a.getRezmed() : a.getRezvid();
                double gradeB = b.getSuMediana() ? b.getRezmed() : b.getRezvid();

                if (gradeA != gradeB) {
                    return gradeA < gradeB;
                } else if (a.getVardas() != b.getVardas()) {
                    return toupper(a.getVardas()[0]) < toupper(b.getVardas()[0]);
                } else {
                    return toupper(a.getPavarde()[0]) < toupper(b.getPavarde()[0]);
                }
            });
        } else if constexpr (is_same<Container, list<typename Container::value_type>>::value) {
            students.sort([](const typename Container::value_type& a, const typename Container::value_type& b) {
                double gradeA = a.getSuMediana() ? a.getRezmed() : a.getRezvid();
                double gradeB = b.getSuMediana() ? b.getRezmed() : b.getRezvid();

                if (gradeA != gradeB) {
                    return gradeA < gradeB;
                } else if (a.getVardas() != b.getVardas()) {
                    return toupper(a.getVardas()[0]) < toupper(b.getVardas()[0]);
                } else {
                    return toupper(a.getPavarde()[0]) < toupper(b.getPavarde()[0]);
                }
            });
        }

    auto end = steady_clock::now();
    duration<double> diff = duration_cast<duration<double>>(end - start);
    cout << "Students sorted by grade and name in " << diff.count() << " s." << endl;
}

    template <typename Container>
        static void rusiavimas(Container& students, Container& vargsiukai, bool suMediana) {
        auto start = steady_clock::now();

        if constexpr (is_same<Container, vector<typename Container::value_type>>::value) {
            auto it = partition(students.begin(), students.end(), [suMediana](auto& student) {
                if (suMediana) {
                    student.galutinismed();
                } else {
                    student.galutinisvid();
                }
                return suMediana ? student.getRezmed() >= 5.0 : student.getRezvid() >= 5.0;
            });

            vargsiukai.insert(vargsiukai.end(), it, students.end());
            students.erase(it, students.end());

        } else if constexpr (is_same<Container, list<typename Container::value_type>>::value) {
            for (auto it = students.begin(); it != students.end();) {
                if (suMediana) {
                    it->galutinismed();
                } else {
                    it->galutinisvid();
                }

                if ((suMediana && it->getRezmed() < 5.0) || (!suMediana && it->getRezvid() < 5.0)) {
                    vargsiukai.push_back(std::move(*it));
                    it = students.erase(it);
                } else {
                    ++it;
                }
            }
        }
        auto end = steady_clock::now();
        duration<double> diff = duration_cast<duration<double>>(end - start);
        cout << "Students sorted into 'vargsiukai' and remaining 'kietekai' in " << diff.count() << " s." << endl;
    }
};

template <typename Container>
void testavimas(Container& students, const string& filename, int numStudents) {

    auto start = steady_clock::now();

    Container vargsiukai;

    FileManager::nuskaitymas(students, filename);

    bool suMediana = false;
    for (auto& student : students) {
        student.vidurkis();
        student.mediana();

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

    students.clear();

    auto end = steady_clock::now();
    duration<double> diff = duration_cast<duration<double>>(end - start);
    cout << "Testing time for " << filename << ": " << diff.count() << " s." << endl;
    cout << "File testing done. " << endl;
    cout << endl;
}

template <typename Container>
void Stud<Container>::vidurkis() {
    if (!ND.empty()) {
        vid = accumulate(ND.begin(), ND.end(), 0.0) / ND.size();
    } else {
        vid = 0.0;
    }
}

template <typename Container>
void Stud<Container>::mediana() {
    if (!ND.empty()) {
        if constexpr (is_same<Container, vector<typename Container::value_type>>::value) {
            sort(ND.begin(), ND.end());

            int size = ND.size();
            auto it = ND.begin();
            advance(it, size / 2);

            if (size % 2 == 0) {
                auto it_prev = std::prev(it);
                med = (*it_prev + *it) / 2.0;
            } else {
                med = *it;
            }
        }

        else if constexpr (is_same<Container, list<typename Container::value_type>>::value) {
            ND.sort();
            int size = ND.size();
            auto it = ND.begin();
            advance(it, size / 2);

            if (size % 2 == 0) {
                auto it_prev = prev(it);
                med = (*it_prev + *it) / 2.0;
            } else {
                med = *it;
            }
        } else {
            med = 0.0;
        }
    } else {
        med = 0.0;
    }
}

template <typename Container>
void Stud<Container>::galutinisvid() {
    vidurkis();
    rezvid = 0.4 * vid + 0.6 * egz;
}

template <typename Container>
void Stud<Container>::galutinismed() {
    mediana();
    rezmed = 0.4 * med + 0.6 * egz;
}

template <typename Container>
istream& operator>>(istream& is, Stud<Container>& obj) {
    string vardas, pavarde;
    double egz;
    is >> vardas >> pavarde;

    Stud<Container> temp(vardas, pavarde);

    if (is >> egz && egz >= 0 && egz <= 10) {
        temp.setEgz(egz);
    }

    double grade;
    while (is >> grade) {
        if (grade < 0 || grade > 10) break;
        temp.addND(grade);
    }

    obj = move(temp);

    return is;
}

template <typename Container>
ostream& operator<<(ostream& os, const Stud<Container>& obj) {
    os << left << setw(18) << obj.getVardas()
       << setw(18) << obj.getPavarde()
       << fixed << setprecision(2);

    if (obj.getSuMediana()) {
        os << obj.getRezmed();
    } else {
        os << obj.getRezvid();
    }
     os << endl;

    return os;
}

template <typename Container>
void Stud<Container>::autom() {
    cout << "Input Name, Surname: ";
    cin >> vardas >> pavarde;

    srand(time(0));
    egz = rand() % 10 + 1;

    for (int j = 0; j < 12; ++j) {
        ND.push_back(rand() % 10 + 1);
    }
}

template <typename Container>
void Stud<Container>::val() {
    vardas.clear();
    pavarde.clear();
    ND.clear();
    vid = 0;
    med = 0;
    rezmed = 0;
    rezvid = 0;
    suMediana = false;
}

void generuotifailus();
void RuleOfThree();

template <typename Container>
void programLoop(Container& students);

template <typename Container>
class Stud;




#endif // STUD_H_INCLUDED
