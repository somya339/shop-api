#include <bits/stdc++.h>
    using namespace std;
class subject
{
protected:
    int subID, credit, semester, attndCutoff;

public:
    subject()
    {
        int x;
        x = rand() % 10000 + 10000;
        subID = x;
        x = rand() % 8 + 1;
        semester = x;
    }
    int returnCredit() { return credit; }
    int prntSubID() { return subID; }
    virtual int scoreMarks() = 0;
    virtual int debarStatus(int x) = 0;
    void printDetails()
    {
        cout << subID << "\t\t";
        cout << credit << "\t";
        cout << semester << "\t\t";
        cout << attndCutoff << "\n";
    }
};
class Elective : public subject
{
public:
    Elective()
    {
        credit = 3;
        attndCutoff = 70;
    }
    int debarStatus(int x)
    {
        if (x >= attndCutoff)
            return 1;
        else
            return 0;
    }
    int scoreMarks()
    {
        int T1, T2, T3, TA;
        T1 = rand() % 21;
        T2 = rand() % 21;
        T3 = rand() % 36;
        TA = rand() % 26;
        return T1 + T2 + T3 + TA;
    }
};
class core : public subject
{
public:
    core() {}
};
class Theory : public core
{
public:
    Theory()
    {
        credit = 4;
        attndCutoff = 70;
    }
    int debarStatus(int x)
    {
        int tutorialAttnd;
        tutorialAttnd = rand() % 90 + 10;
        if ((x + tutorialAttnd) >= attndCutoff)
            return 1;
        else
            return 0;
    }
    int scoreMarks()
    {
        int T1, T2, T3, TA, Tutorial;
        T1 = rand() % 21;
        T2 = rand() % 21;
        T3 = rand() % 36;
        TA = rand() % 16;
        Tutorial = rand() % 11;
        return T1 + T2 + T3 + TA + Tutorial;
    }
};
class Lab : public core
{
public:
    Lab()
    {
        credit = 1;
        attndCutoff = 80;
    }
    int debarStatus(int x)
    {
        if (x >= attndCutoff)
            return 1;
        else
            return 0;
    }
    int scoreMarks()
    {
        int LT1, LT2, Assgn;
        int T, MiniPrj;
        LT1 = rand() % 21;
        LT2 = rand() % 21;
        MiniPrj = rand() % 11;
        Assgn = rand() % 51;
        T = LT1 + LT2 + Assgn + MiniPrj;
        return T;
    }
};
class student
{
protected:
    int semester, *attendance, *marks;
    subject *sub[6];
    float CGPA;

public:
    int stdID;
    student()
    {
        stdID = rand() % 100000 + 100000;
        semester = rand() % 8 + 1;
        CGPA = 0.0;
    }
    int getSemester() { return semester; }
    virtual void printDetails() = 0;
    virtual void computeCGPA() = 0;
    virtual void giveExam() = 0;
    virtual void registerSubject(subject *o) = 0;
    virtual int tellMarks(int sub_id) = 0;
    virtual bool dbar(int sub_id) = 0;
    int getCG()
    {
        return CGPA;
    }
};
class UGStudent : public student
{
public:
    UGStudent()
    {
        if (semester % 2 == 0)
        {
            marks = new int[6];
            attendance = new int[6];
            for (int i = 0; i < 6; i++)
                sub[i] = NULL;
        }
        else
        {
            marks = new int[5];
            attendance = new int[5];
            for (int i = 0; i < 6; i++)
                sub[i] = NULL;
        }
    }
    void registerSubject(subject *o)
    {
        int j, i = 0;
        if (semester % 2 == 0)
            j = 6;
        else
            j = 5;
        while (sub[i] != NULL && i < j)
            i++;
        if (i == j)
            cout << "\nCan not register more than " << j << " subjects";
        else
            sub[i] = o;
    }
    void giveExam()
    {
        int j, i;
        if (semester % 2 == 0)
            j = 6;
        else
            j = 5;
        for (i = 0; (i < j) && (sub[i] != NULL); i++)
            attendance[i] = rand() % 101;
        for (i = 0; (i < j) && (sub[i] != NULL); i++)
        {
            if (sub[i]->debarStatus(attendance[i]))
                marks[i] = sub[i]->scoreMarks();
            else
                marks[i] = 0;
        }
    }
    void computeCGPA()
    {
        int j, i, credit, creditTotal = 0, gradePoint = 0;
        if (semester % 2 == 0)
        {
            j = 6;
        }
        else
        {
            j = 5;
        }
        for (i = 0; (i < j) && (sub[i] != NULL); i++)
        {
            credit = sub[i]->returnCredit();
            creditTotal = creditTotal + credit;
            if (marks[i] >= 90)
            {
                gradePoint = gradePoint + credit * 10;
            }
            if (marks[i] >= 80 && marks[i] < 90)
            {
                gradePoint = gradePoint + credit * 9;
            }
            if (marks[i] >= 70 && marks[i] < 80)
            {
                gradePoint = gradePoint + credit * 8;
            }
            if (marks[i] >= 60 && marks[i] < 70)
            {
                gradePoint = gradePoint + credit * 7;
            }
            if (marks[i] >= 50 && marks[i] < 60)
            {
                gradePoint = gradePoint + credit * 6;
            }
            if (marks[i] >= 40 && marks[i] < 50)
            {
                gradePoint = gradePoint + credit * 5;
            }
            if (marks[i] >= 30 && marks[i] < 40)
            {
                gradePoint = gradePoint + credit * 4;
            }
            if (marks[i] < 30)
            {
                gradePoint = gradePoint + credit * 0;
            }
        }
        CGPA = gradePoint / creditTotal;
    }
    void printDetails()
    {
        cout << "\nStudent ID: " << stdID << "\n";
        for (int k = 0; sub[k] != NULL; k++)
        {
            cout << "\tSubID = " << sub[k]->prntSubID() << "\n";
            cout << "\t\tAttendance = " << attendance[k] << "\n";
            cout << "\t\tMarks = " << marks[k] << "\n";
        }
        cout << "\tCGPA = " << CGPA;
    }
    int tellMarks(int sub_id)
    {
        int i = 0;
        bool flag = 0;
        while (sub[i] != NULL)
        {
            if (sub[i]->prntSubID() == sub_id)
            {
                flag = 1;
                return marks[i];
            }
            i++;
        }
        if (flag == 0)
            return -1;
    }
    bool dbar(int sub_id)
    {
        for (int i = 0; sub[i] != NULL; i++)
        {
            if ((sub[i]->prntSubID() == sub_id) && (sub[i]->debarStatus(attendance[i])))
                return 1;
        }
        return 0;
    }
};
void listSubjects(subject *s[], int no_of_subs)
{
    cout << "\nSubjects Listed in the college:\n";
    cout << "Subject ID\tCredits\tSemester\tAttendance Cutoff\n";
    for (int i = 0; i < no_of_subs; i++)
        s[i]->printDetails();
}
void listStudents(student *st[], int no_of_stud)
{
    cout << "\n\nDetails of all students: \n\n";
    for (int i = 0; i < no_of_stud; i++)
    {
        st[i]->printDetails();
        cout << "\n";
    }
}
void query1(student *st[], int no_of_stud)
{
    int i, sub_id, mx = INT8_MIN;
    student *topper;
    cout << "\nEnter the Subject ID for which you want to know topper: ";
    cin >> sub_id;
    bool flag = 0;
    for (i = 0; i < no_of_stud; i++)
    {
        if ((st[i]->tellMarks(sub_id) != -1) && (st[i]->tellMarks(sub_id) > mx))
        {
            mx = st[i]->tellMarks(sub_id);
            topper = st[i];
            flag = 1;
        }
    }
    if (flag)
        cout << "\nTopper's ID: " << topper->stdID << "\n";
    else
        cout << "\nSubject not found!!\n";
}
void query2(student *st[], int no_of_stud)
{
    cout << "\nEnter the subjectID for which you want to see debarred students: ";
    int sub_id;
    cin >> sub_id;
    bool flag = 0;
    for (int i = 0; i < no_of_stud; i++)
    {
        if (st[i]->dbar(sub_id))
        {
            cout << "\t" << st[i]->stdID << "\n";
            flag = 1;
        }
    }
    if (flag == 0)
        cout << "\nSubject not found!!\n";
}
void query3(student *st[], int no_of_stud)
{
    int sem;
    cout << "\nEnter the semester (1-8): ";
    cin >> sem;
    if (sem < 1 || sem > 8)
    {
        cout << "\nWrong Entry!!\n";
        return;
    }
    bool flag = 0;
    student *topper = NULL;
    float maxcg = 0;
    for (int i = 0; i < no_of_stud; i++)
    {
        if ((st[i]->getSemester() == sem) && (st[i]->getCG() >= maxcg))
        {
            maxcg = st[i]->getCG();
            topper = st[i];
            flag = 1;
        }
    }
    if (flag)
    {
        cout << "\nTopper's ID: " << topper->stdID << "\n";
        cout << "CGPA: " << maxcg << "\n\n";
    }
    else
        cout << "\nNo student is currently in this semester!!\n";
}
int main()
{
    int i;
    subject *s[8];
    s[0] = new Theory;
    s[1] = new Theory;
    s[2] = new Theory;
    s[3] = new Theory;
    s[4] = new Lab;
    s[5] = new Lab;
    s[6] = new Elective;
    s[7] = new Elective;
    student *st[6];
    for (i = 0; i < 6; i++)
        st[i] = new UGStudent;
    //subject registration
    for (i = 0; i < 6; i += 2)
    {
        st[i]->registerSubject(s[0]);
        st[i]->registerSubject(s[2]);
        st[i]->registerSubject(s[4]);
        st[i]->registerSubject(s[6]);
    }
    for (i = 1; i < 6; i += 2)
    {
        st[i]->registerSubject(s[1]);
        st[i]->registerSubject(s[3]);
        st[i]->registerSubject(s[5]);
        st[i]->registerSubject(s[7]);
    }
    //exams:
    for (i = 0; i < 6; i++)
    {
        st[i]->giveExam();
        st[i]->computeCGPA();
    }
    int choice;
    while (1)
    {
        cout << "Data is already feed in the code";
        cout << "\n\t1. Query 1 : Print the ID of the topper of a subject";
        cout << "\n\t2. Query 2 : Print the list of the students who are debarred in a subject";
        cout << "\n\t3. Query 3 : Print the ID of the topper of a semester";
        cout << "\n\t4. Print the details of all subjects";
        cout << "\n\t5. Print the details of all students";
        cout << "\n\t6. Exit the program";
        cout << "\n\nEnter your choice(1-4): ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            query1(st, 6);
            break;
        case 2:
            query2(st, 6);
            break;
        case 3:
            query3(st, 6);
            break;
        case 4:
            listSubjects(s, 8);
            break;
        case 5:
            listStudents(st, 6);
            break;
        case 6:
            exit(0);
        default:
            cout << "\nWrong choice entered!!";
        }
        cout << endl;
    }
}
