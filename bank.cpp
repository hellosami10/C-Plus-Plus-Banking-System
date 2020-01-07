/* BANKING SYSTEM
AUTHOR : SAMI, ADNAN

*/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <dirent.h>
#include <stdio.h>

using namespace std;

int x;

class user {
    string usr_name;
    string usr_id;
    string usr_dob;
    double usr_deposit;
    double usr_withdraw;
    double total_amount = 0.00;

    public:
        /* CREATE USER */
        void create_usr() {
            system("CLS");
            cout << " -----------------" << endl;
            cout << " :: CREATE USER ::" << endl;
            cout << " -----------------" << endl << endl;
            cout << " Applicant Name: ";
            cin >> usr_name;

            cout << " ID: ";
            cin >> usr_id;

            cout << " Date of Birth [D/M/Y]: ";
            cin >> usr_dob;

            /* CREATING FILE -> USR_ID */
            ofstream usr_file;
            usr_file.open(("my_database\\usr_\\" + usr_id).c_str());
            usr_file << " | Applicant Name: " << usr_name << endl;
            usr_file << " | ID: " << usr_id << endl;
            usr_file << " | Date of Birth [D/M/Y]: " << usr_dob << endl;
            usr_file.close();

            /* CREATING FILE -> USR_TEMP (WITH INITIAL VALUE, total_amount = 0.00) */
            ofstream usr_temp_file;
            usr_temp_file.open(("my_database\\usr_temp\\" + usr_id).c_str());
            usr_temp_file << total_amount; /* total_amount = 0.00 (GLOBAL) */
            usr_temp_file.close();

            /* CREATING FILE -> USR_BALANCE (ONLY A LINE OF STRING) */
            ofstream usr_balance_file;
            usr_balance_file.open(("my_database\\usr_balance\\" + usr_id).c_str());
            usr_balance_file << endl << " N/G" << endl << " BALANCE: 0.00" << " BDT" << endl << endl;
            usr_balance_file.close();

            system("CLS");
            cout << " -----------------" << endl;
            cout << " :: CREATE USER ::" << endl;
            cout << " -----------------" << endl << endl;

            cout << " | Applicant Name: " << usr_name<< endl;
            cout << " | ID: " << usr_id << endl;
            cout << " | Date of Birth [D/M/Y]: "<< usr_dob << endl << endl;
            cout << " USER HAS BEEN CREATED ! PRESS ANY KEY TO BACK .. ";

            getch();
            system("CLS");
            return;
        }


        /* DELETE USER */
        void delete_usr() {
            system("CLS");
            cout << " -----------------" << endl;
            cout << " :: DELETE USER ::" << endl;
            cout << " -----------------" << endl << endl;

            cout << " Enter ID : ";
            cin >> usr_id;
            show_info();

            cout << endl; /* LINE BREAK */

            char opt;
            cout << " Confirm? [y/n]: ";
            cin >> opt;

            if (opt == 'y' || opt == 'Y') {
                int usr_status, usr_temp_status, usr_balance_status;

                usr_status = remove(("my_database\\usr_\\" + usr_id).c_str());
                usr_temp_status = remove(("my_database\\usr_temp\\" + usr_id).c_str());
                usr_balance_status = remove(("my_database\\usr_balance\\" + usr_id).c_str());


                /* CHECK IF FILE EXISTS --> "my_database\\usr_\\", "my_database\\usr_temp\\", "my_database\\usr_balance\\" */
                if(usr_status == 0 && usr_temp_status ==0 && usr_balance_status == 0) {
                    cout << endl << " USER" << " [" << "ID: " << usr_id << "] " << "HAS BEEN DELETED" << " SUCCESSFULLY !" << endl << endl;
                    cout << " PRESS ANY KEY TO CONTINUE .. ";
                    getch();
                    system("CLS");
                    return;

                }
            }
            else if (opt == 'n' || opt == 'N'){
                system("CLS");
                return;
            }

        }

        /* UPDATE USER */
        void update_usr() {
            system("CLS");

            cout << " -----------------------------" << endl;
            cout << " :: UPDATE USER INFORMATION ::" << endl;
            cout << " -----------------------------" << endl << endl;

            cout << " Enter ID: ";
            cin >> usr_id;

            show_info();
            cout << endl;
            cout << " Change Name: ";
            cin >> usr_name;

            cout << " Change Date of Birth [D/M/Y]: ";
            cin >> usr_dob;

            /* CREATING FILE -> USR_ID */
            ofstream usr_file;
            usr_file.open(("my_database\\usr_\\" + usr_id).c_str());
            usr_file << " | Applicant Name: " << usr_name << endl;
            usr_file << " | ID: " << usr_id << endl;
            usr_file << " | Date of Birth [D/M/Y]: " << usr_dob << endl;
            usr_file.close();

            system("CLS");
            cout << " -----------------------------" << endl;
            cout << " :: UPDATE USER INFORMATION ::" << endl;
            cout << " -----------------------------" << endl << endl;
            cout << " | Applicant Name: " << usr_name<< endl;
            cout << " | ID: " << usr_id << endl;
            cout << " | Date of Birth [D/M/Y]: " << usr_dob << endl << endl;

            cout << " INFORMATION IS UPDATED ! PRESS ANY KEY TO BACK .. ";

            getch();
            system("CLS");
            return;
        }

        void show_balance() {
            /* list data of the applicant */
            cout << endl;

            string line;
            ifstream file(("my_database\\usr_balance\\" + usr_id).c_str());

            while(getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }

        /* SEARCH USER BY ID */
        void search_id() {
            system("CLS");
            cout << " -----------------------" << endl;
            cout << " :: SEARCH USER BY ID ::" << endl;
            cout << " -----------------------" << endl << endl;

            string usr_id;
            cout << " ENTER ID: ";
            cin >> usr_id;

            cout << endl; /* LINE BREAK */

            ifstream fin(("my_database\\usr_\\" + usr_id).c_str());
            if(fin.is_open()){

                string line;
                ifstream file(("my_database\\usr_\\" + usr_id).c_str());

                while(getline(file, line)) {
                    cout << line << endl;
                }
                file.close();

                /* SHOW BALANCE */
                cout << endl;

                string line2;
                ifstream file2(("my_database\\usr_balance\\" + usr_id).c_str());

                while(getline(file2, line2)) {
                    cout << line2 << endl;
                }
                file.close();

                cout << endl;
                cout << " PRESS ANY KEY TO BACK .. ";
                getch();
                system("CLS");
                return;

            } else{
                cout<<" USER " << "[" << usr_id << "]" << " NOT FOUND !"<<endl;
                cout << " PRESS ANY KEY TO CONTINUE ..";
                getch();
                system("CLS");
                return;
            }
        }

        /* PRINT ALL USERS */
        void list_usr() {

            /* BLOCK */
            system("CLS");
            int i;
            cout << " -------------------" << endl;
            cout << " :: LIST OF USERS ::" << endl;
            cout << " -------------------" << endl;

            DIR *pDIR;
            struct dirent *entry;
            if( pDIR=opendir("my_database\\usr_\\") ){
                i = 1; /* PRINTS NUMBER LINE */

                while(entry = readdir(pDIR)) {

                    if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
                        /* cout << endl << "\t" << i << ". " << "\t" << entry->d_name << endl; */
                        cout << endl << " " << i << ". " << endl;
                        string x = entry->d_name;

                        string line;
                        ifstream file(("my_database\\usr_\\" + x).c_str());

                        while(getline(file, line)) {
                        cout << line << endl;
                        }
                        file.close();

                        i = i + 1;
                    }
                }
                closedir(pDIR);
            }
            /* BLOCK */
            cout << endl << " :: THE END ::" << endl;
            cout << endl << endl << " PRESS ANY KEY TO BACK.. ";
        }

        void show_info() {
            /* list data of the applicant */
            cout << endl;

            string line;
            ifstream file(("my_database\\usr_\\" + usr_id).c_str());

            while(getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }


        void setusr_deposit() {
            top:
            system("CLS");

            cout << " -------------" << endl;
            cout << " :: DEPOSIT ::" << endl;
            cout << " -------------" << endl << endl;

            cout << " Enter ID: ";
            cin >> usr_id;
            show_info();

            show_balance();

            cout << " DEPOSIT: ";
            cin >> usr_deposit;

            /* retrive data from temp file and put the value in global variable "x" */
            ifstream infile(("my_database\\usr_temp\\" + usr_id).c_str());
            infile >> x;
            x = (x + usr_deposit);
            infile.close();

            /* save value to usr_temp*/
            ofstream temp_totalAmount;
            temp_totalAmount.open(("my_database\\usr_temp\\" + usr_id).c_str());
            temp_totalAmount << x << endl;
            temp_totalAmount.close();

            /* save value to usr_balance*/
            ofstream app_totalAmount;
            app_totalAmount.open(("my_database\\usr_balance\\" + usr_id).c_str());
            cout << " DATE OF DEPOSIT: ";
            string temp_date = "N/G";
            cin >> temp_date;
            app_totalAmount << endl << " DATE: " << temp_date << endl << " BALANCE: " << x << " BDT" << endl << endl;
            app_totalAmount.close();

            system("CLS");
            cout << " -------------" << endl;
            cout << " :: DEPOSIT ::" << endl;
            cout << " -------------" << endl << endl;

            cout << " ----------------------" << endl;
            cout << " DEPOSIT IS SUCCEEDED !" << endl;
            cout << " ----------------------" << endl;
            show_info();
            show_balance();

            cout << " DO YOU WANT TO DEPOSIT AGAIN? (Y/N) : ";

            char opt;
            cin >> opt;
            if (opt == 'y' || opt == 'Y') {
                system("CLS");
                goto top;
            }
            else {
                system("CLS");
                return;
            }
        }

        void setusr_withdraw() {
            top:
            system("CLS");

            cout << " --------------" << endl;
            cout << " :: WITHDRAW ::" << endl;
            cout << " --------------" << endl << endl;

            cout << " Enter ID: ";
            cin >> usr_id;

            show_info();
            show_balance();

            /* export deposit amount to temp file */
            cout << " WITHDRAW: ";
            cin >> usr_withdraw;

            ifstream rfile(("my_database\\usr_temp\\" + usr_id).c_str());
            rfile >> x;
            x = (x - usr_withdraw);
            rfile.close();

            ofstream temp_totalAmount;
            temp_totalAmount.open(("my_database\\usr_temp\\" + usr_id).c_str());
            temp_totalAmount << x << endl;
            temp_totalAmount.close();

            /* save value to usr_balance*/
            ofstream app_totalAmount;
            app_totalAmount.open(("my_database\\usr_balance\\" + usr_id).c_str());
            cout << " DATE OF WITHDRAW: ";
            string temp_date = "N/G";
            cin >> temp_date;
            app_totalAmount << endl << " DATE: " << temp_date << endl << " BALANCE: " << x << " BDT" << endl << endl;
            app_totalAmount.close();

            system("CLS");
            cout << " --------------" << endl;
            cout << " :: WITHDRAW ::" << endl;
            cout << " --------------" << endl << endl;
            cout << " -----------------------" << endl;
            cout << " WITHDRAW IS SUCCEEDED !" << endl;
            cout << " -----------------------" << endl;
            show_info();
            show_balance();

            cout << " DO YOU WANT TO WITHDRAW AGAIN? (Y/N) : ";

            char opt;
            cin >> opt;
            if (opt == 'y' || opt == 'Y') {
                system("CLS");
                goto top;
            }
            else {
                system("CLS");
                return;
            }
        }










};


void menu() {
    user usr;

    top:
    cout << " --------------------" << endl;
    cout << " :: BANKING SYSTEM ::" << endl;
    cout << " --------------------" << endl << endl;
    cout << " 1 --> Create User" << endl; // done
    cout << " 2 --> Delete User" << endl;
    cout << " 3 --> Update User Information" << endl; // done
    cout << " 4 --> Search User by ID" << endl; //done
    cout << " 5 --> Print All Users" << endl; //done
    cout << " 6 --> Deposit" << endl; //done
    cout << " 7 --> Withdraw" << endl << endl; //done

    int opt;
    cout << " >> ";
    cin >> opt;

    switch(opt) {
    case 1:
        usr.create_usr();
        goto top;
        break;
    case 2:
        usr.delete_usr();
        goto top;
        break;
    case 3:
        usr.update_usr();
        goto top;
        break;
    case 4:
        usr.search_id();
        goto top;
        break;
    case 5:
        usr.list_usr();
        getch();
        system("CLS");
        goto top;
        break;
    case 6:
        usr.setusr_deposit();
        goto top;
        break;
    case 7:
        usr.setusr_withdraw();
        goto top;
        break;
    default:
        break;
    }
}


int main() {
    menu();
}
