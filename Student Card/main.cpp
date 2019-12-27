//
//  main.cpp
//  Student Card
//
//  Created by Rockabye Saw on 21/12/2019.
//  Copyright © 2019 Rockabye Saw. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>

class Student
{
    int rollno;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    double per;
    char grade;
    void calculate(); // function to calculate grade
    
public:
    void getdata(); // function to accept data from user
    void showdata() const; // function to show data on screen
    void show_tabular() const;
    int retrollno() const;
};

void Student::calculate()
{
    per = (p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
    
    if(per >= 60)
        grade = 'A';
    else if(per >= 50)
        grade = 'B';
    else if (per >= 33)
        grade = 'C';
    else
        grade = 'F';
}

void Student::getdata()
{
    std::cout<<"\nEnter The roll number of student ";
    std::cin>>rollno;
    std::cout<<"\n\nEnter The Name of student ";
    std::cin.ignore();
    std::cin.getline(name,50);
    std::cout<<"\nEnter The marks in physics out of 100 : ";
    std::cin>>p_marks;
    std::cout<<"\nEnter The marks in chemistry out of 100 : ";
    std::cin>>c_marks;
    std::cout<<"\nEnter The marks in maths out of 100 : ";
    std::cin>>m_marks;
    std::cout<<"\nEnter The marks in english out of 100 : ";
    std::cin>>e_marks;
    std::cout<<"\nEnter The marks in computer science out of 100 : ";
    std::cin>>cs_marks;
    calculate();
}

void Student::showdata() const
{
    std::cout<<"\nRoll number of student : "<<rollno;
    std::cout<<"\nName of student : "<<name;
    std::cout<<"\nMarks in Physics : "<<p_marks;
    std::cout<<"\nMarks in Chemistry : "<<c_marks;
    std::cout<<"\nMarks in Maths : "<<m_marks;
    std::cout<<"\nMarks in English : "<<e_marks;
    std::cout<<"\nMarks in Computer Science :"<<cs_marks;
    std::cout<<"\nPercentage of student is  :"<<per;
    std::cout<<"\nGrade of student is :"<<grade;
}

void Student::show_tabular() const
{
    std::cout<<rollno<<std::setw(6)<<" "<<name<<std::setw(10)<<p_marks<<std::setw(4)<<c_marks<<std::setw(4)<<m_marks<<std::setw(4)
    <<e_marks<<std::setw(4)<<cs_marks<<std::setw(8)<<per<<std::setw(6)<<grade<<std::endl;
}

int Student::retrollno() const
{
    return rollno;
}

void write_student(); // write student in binary file
void display_all(); // read all record from binary file
void display_sp(int); // accept rollno and read record from binary file
void modify_student(int); // accept rollno and update student of binary file
void delete_student(int); // accept rollno and delete student of binary file
void class_result(); // display all records in tabular from binary file
void result(); // display result menu
void intro(); //display welcome screen
void entry_menu(); //display entry menu on screen

int main(int argc, const char * argv[]) {
    char ch;
    std::cout.setf(std::ios::fixed | std::ios::showpoint); // fixed and show decimal points
    std::cout<< std::setprecision(2); // 2 decimal places
    
    intro();
    
    do
    {
        system("cls");
        std::cout<<"\n\n\n\tMAIN MENU";
        std::cout<<"\n\n\t01. RESULT MENU";
        std::cout<<"\n\n\t02. ENTRY/EDIT MENU";
        std::cout<<"\n\n\t03. EXIT";
        std::cout<<"\n\n\tPlease Select Your Option (1-3) ";
        std::cin>>ch;
        switch (ch)
        {
            case '1':
                result();
                break;
            case '2':
                entry_menu();
                break;
            case '3':
                break;
            default: std::cout<<"\a";
        }
    }
    while (ch != 3);
    return 0;
}

void write_student()
{
    Student st;
    std::ofstream outFile;
    outFile.open("student.bin", std::ios::binary|std::ios::app);
    st.getdata();
    outFile.write((char *)&st, sizeof(Student));
    outFile.close();
    std::cout<<"\n\nStudent record Has Been Created ";
    std::cin.ignore();
    std::cin.get();
}

void display_all()
{
    Student st;
    std::ifstream inFile;
    inFile.open("student.bin", std::ios::binary);
    
    if (!inFile) {
        std::cout<<"File could not be open !! Press any Key...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    while (inFile.read((char *)&st, sizeof(Student))) {
        st.showdata();
        std::cout<<"\n\n====================================\n";
    }
    inFile.close();
    std::cin.ignore();
    std::cin.get();
}

void display_sp(int n)
{
    Student st;
    std::ifstream inFile;
    inFile.open("student.bin", std::ios::binary);
    if (!inFile) {
        std::cout<<"File could not be open !! Press any Key...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    bool flag = false;
    while (inFile.read((char *)&st, sizeof(Student))) {
        if (st.retrollno() == n) {
            st.showdata();
            flag = true;
        }
    }
    
    inFile.close();
    if(flag==false)
        std::cout<<"\n\nrecord not exist";
    std::cin.ignore();
    std::cin.get();
}

void modify_student(int n)
{
    bool found = false;
    Student st;
    std::fstream File;
    File.open("student.bin",std::ios::binary|std::ios::in|std::ios::out);
    if(!File)
    {
        std::cout<<"File could not be open !! Press any Key...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    while (!File.eof() && found == false) // eof end of file
    {
        File.read((char *)&st, sizeof(Student));
        if(st.retrollno() == n)
        {
            st.showdata();
            std::cout<<"\n\nPlease Enter The New Details of student"<<std::endl;
            st.getdata();
            int pos = (-1)*static_cast<int>(sizeof(st));
            File.seekp(pos, std::ios::cur);
            File.write((char *)&st, sizeof(Student));
            std::cout<<"\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if(found==false)
        std::cout<<"\n\n Record Not Found ";
    std::cin.ignore();
    std::cin.get();
}

void delete_student(int n)
{
    Student st;
    std::ifstream inFile;
    inFile.open("student.bin", std::ios::binary);
    if(!inFile)
    {
        std::cout << "File could not be open !! Press any Key...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::ofstream outFile;
    outFile.open("temp.bin", std::ios::binary);
    inFile.seekg(0, std::ios::beg);
    while (inFile.read((char *)&st, sizeof(Student)))
    {
        if(st.retrollno() != n)
        {
            outFile.write((char *)&st, sizeof(Student));
        }
    }
    outFile.close();
    inFile.close();
    remove("student.bin");
    rename("temp.bin","student.bin");
    std::cout<<"\n\n\tRecord Deleted ..";
    std::cin.ignore();
    std::cin.get();
}

void class_result()
{
    Student st;
    std::ifstream inFile;
    inFile.open("student.bin", std::ios::binary);
    if(!inFile)
    {
        std::cout<<"File could not be open !! Press any Key...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
    std::cout<<"==========================================================\n";
    std::cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<std::endl;
    std::cout<<"==========================================================\n";
    while (inFile.read((char *)&st, sizeof(Student)))
    {
        st.show_tabular();
    }
    std::cin.ignore();
    std::cin.get();
    inFile.close();
}

void result()
{
    char ch;
    int rno;
    system("cls");
    std::cout<<"\n\n\n\tRESULT MENU";
    std::cout<<"\n\n\n\t1. Class Result";
    std::cout<<"\n\n\t2. Student Report Card";
    std::cout<<"\n\n\t3. Back to Main Menu";
    std::cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
    std::cin>>ch;
    system("cls");
    switch(ch)
    {
        case '1' :
            class_result();
            break;
        case '2' :
            std::cout<<"\n\n\tEnter Roll Number Of Student : "; std::cin>>rno;
            display_sp(rno);
            break;
        case '3' :
            break;
        default:    std::cout<<"\a";
    }
}

void intro()
{
    std::cout<<"\n\n\n\t\t  STUDENT";
    std::cout<<"\n\n\t\tREPORT CARD";
    std::cout<<"\n\n\t\t  PROJECT";
    std::cin.get();
}

void entry_menu()
{
    char ch;
    int num;
    system("cls");
    std::cout<<"\n\n\n\tENTRY MENU";
    std::cout<<"\n\n\t1.CREATE STUDENT RECORD";
    std::cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    std::cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    std::cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    std::cout<<"\n\n\t5.DELETE STUDENT RECORD";
    std::cout<<"\n\n\t6.BACK TO MAIN MENU";
    std::cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    std::cin>>ch;
    system("cls");
    switch(ch)
    {
        case '1':    write_student(); break;
        case '2':    display_all(); break;
        case '3':    std::cout<<"\n\n\tPlease Enter The roll number "; std::cin>>num;
            display_sp(num); break;
        case '4':    std::cout<<"\n\n\tPlease Enter The roll number "; std::cin>>num;
            modify_student(num);break;
        case '5':    std::cout<<"\n\n\tPlease Enter The roll number "; std::cin>>num;
            delete_student(num);break;
        case '6':    break;
        default:    std::cout<<"\a"; entry_menu();
    }
}
