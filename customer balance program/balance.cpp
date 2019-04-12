#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

struct PERSON{
    char Name[22];
    float Balance;
};

void printmenu() {
    cout << "Please enter a choice:" << endl;
    cout << "1. Display records" << endl;
    cout << "2. Deposit funds" << endl;
    cout << "3. Find highest balance" << endl;
    cout << "4. Update records" << endl;
    cout << "5. Exit the program" << endl;
}

PERSON * readData(int & N){
    ifstream data;
    data.open("data.txt");
    if(!data){
        cout << "Error data.txt could not be found" << endl;
        exit(0);
    }
    if(data){
        string line;
        while(getline(data, line)){
            N++;
        }
    }
    data.close();

    ifstream data1;
    data1.open("data.txt");
    PERSON * PTperson = NULL;
    PTperson = new PERSON[N];

    string firstName;
    string lastName;
    string fullName;
    if(data1){
        for(int x = 0; x < N; x++){
            data1 >> firstName >> lastName;
            data1 >> PTperson[x].Balance;
            fullName = firstName + " " + lastName;
            strcpy(PTperson[x].Name, fullName.c_str());
        }
    }
    data.close();
    return PTperson;
}

void FindRichest(PERSON * list, int & size){
    string Richest = list[0].Name;
    int price = list[0].Balance;
    for(int x = 1; x < size; x++){
        if(price < list[x].Balance){
            Richest = list[x].Name;
            price = list[x].Balance;
        }
    }
    cout << "Highest Balance: " << Richest << endl << endl;
}//

void update(PERSON * list, int size){
    string text = "data.txt";
    ofstream file;
    file.open(text);
    cout << "Updating..." << endl;
    cout << "Press any character then enter" << endl;
    for (int x = 0; x < size; x++){
        file << list[x].Name << " " << list[x].Balance << endl;
        cin >> ws;
    }
    cout << "Finished updating!" << endl
        << "End of program" << endl;
    file.close();
}

void Deposit(PERSON * arr, int & N, string custName, float amount){
    for(int x = 0; x < N; x++){
        if (arr[x].Name == custName){
            arr[x].Balance += amount;
            cout << "New Balance: " << arr[x].Balance << endl << endl;
            return;
        }
        else if(x == N){
            cout << "Could not find name closing program" << endl;
        }
    }
    return;
}

void display(PERSON * arr, int &N){
    for(int x = 0; x < N; x++){
        cout << arr[x].Name << " " << arr[x].Balance << endl;
    }
}

int main() {
    PERSON * arrayPtr = NULL;
    int size = 0;
    arrayPtr = readData(size);
    int choice;
    do{
        string CustomerName;
        float amount = 0;
        printmenu();
        cin >> choice;
        switch(choice){
            case 1:

                cout << endl;
                display(arrayPtr, size);
                break;

            case 2:

                cout << endl;
                cout << "Enter your full name to deposit money: ";
                getline(cin, CustomerName);
                cout << CustomerName << ", how much would you like to deposit? ";
                cin >> amount;
                Deposit(arrayPtr, size, CustomerName, amount);
                break;

            case 3:

                cout << endl;
                FindRichest(arrayPtr,size);
                break;

            case 4:

                cout << endl;
                update(arrayPtr, size);
                break;
            case 5:
                
                cout << endl;
                update(arrayPtr, size);
                break;

            default:
                cout << "Invalid" << endl;
                break;
        }
        cout << endl;
    }
    while(choice != 5);
    return 0;
}
