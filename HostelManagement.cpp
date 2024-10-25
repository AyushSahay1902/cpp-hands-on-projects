#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Hostel {
private:
  string name;
  int rent;
  int bed;

public:
  Hostel(string name, int rent, int bed) {
    this->name = name;
    this->rent = rent;
    this->bed = bed;
  }
  string getName() { return name; }
  int getRent() { return rent; }
  int getBed() { return bed; }

  void reserve() {
    ifstream in("./hostel.txt");
    ofstream out("./temp.txt");
    string line;

    while (getline(in, line)) {
      int pos = line.find("3star");
      if (pos != string::npos) {
        int bed = bed - 1;
        bed = bed < 0 ? 0 : bed;
        stringstream ss;
        ss << bed;
        string strBed = ss.str();

        int pos1 = line.find(":");
        line.replace(pos1 + 1, string::npos, strBed);
      }
      out << line << endl;
    }
    in.close();
    out.close();
    remove("./hostel.txt");
    rename("./temp.txt", "./hostel.txt");
    cout << "\tBed reserved successfully" << endl;
  }
};

class Student {
private:
  string Name, Roll, Address;

public:
  Student() : Name(""), Roll(""), Address("") {}
  void setName(string Name) { this->Name = Name; }
  void setRoll(string Roll) { this->Roll = Roll; }
  void setAddress(string Address) { this->Address = Address; }
  string getName() { return Name; }
  string getRoll() { return Roll; }
  string getAddress() { return Address; }
};

int main() {
  Hostel h1("Hostel 1", 5000, 10);
  Student s;
  ofstream out("./hostel.txt", ios::app);
  out << "\t" << h1.getName() << "\t:" << h1.getRent() << "\t:" << h1.getBed()
      << endl
      << endl;
  cout << "Hostel 1 added successfully" << endl;
  out.close();
  bool exit = false;
  while (!exit) {
    system("cls");
    int val;
    cout << "\t Welcome to Hostel Management System" << endl;
    cout << "1. Make Reservation" << endl;
    cout << "2. Show Student" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> val;

    if (val == 1) {
      system("cls");
      string name, roll, address;
      cout << "\tEnter your name: ";
      cin >> name;
      s.setName(name);
      cout << "\tEnter your roll: ";
      cin >> roll;
      s.setRoll(roll);
      cout << "\tEnter your address: ";
      cin >> address;
      s.setAddress(address);

      if (h1.getBed() == 0) {
        cout << "\tNo bed available" << endl;
      } else {
        h1.reserve();
      }

      ofstream out("./student.txt", ios::app);
      out << "\t" << s.getName() << "\t:" << s.getRoll()
          << "\t:" << s.getAddress() << endl
          << endl;
      cout << "Student added successfully" << endl;
      out.close();
    } else if (val == 2) {
      system("cls");
      ifstream in("./student.txt");
      string line;
      cout << "\tName\tRoll\tAddress" << endl;
      while (getline(in, line)) {
        cout << line << endl;
      }
      in.close();
      system("pause");
    } else if (val == 3) {
      exit = true;
    }
  }
};