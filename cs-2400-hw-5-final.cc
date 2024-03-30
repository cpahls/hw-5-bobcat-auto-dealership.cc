/**
*   @file: homework_5_experimental.cc
* @author: Christian Pahls
*   @date: 03/26/2024
*  @brief: This program is used to show us how to use vectors and arrays in our program
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;


int display_opt(vector<string> vMod, vector<string> vOpt, vector<int> vModPrice, vector<int> vOptPrice) {

    string sOptPrice1, sOptPrice2, sOptPrice3;

    //Display for models and prices
    cout << endl << "Prices for model E, L, & X: ";
    for (int i = 0; i < vModPrice.size(); ++i) {
        if (i < vModPrice.size()-1){
            cout << "$" << vModPrice[i] << ", ";
        }
        else {cout << "$" << vModPrice[i];}
    }
    cout << endl;
    cout << "Available Options" << endl << endl;

    //Displays for options and prices
    for (int i = 0; i < vOpt.size(); i += 3) {
        sOptPrice1 = vOpt[i] + " ($" + to_string(vOptPrice[i]) + ")";
        sOptPrice2 = vOpt[i+1] + " ($" + to_string(vOptPrice[i+1]) + ")";
        sOptPrice3 = vOpt[i+2] + " ($" + to_string(vOptPrice[i+2]) + ")";
        cout << left << setw(28) << sOptPrice1 << setw(28) << sOptPrice2 << setw(28) << sOptPrice3 << endl;
    }
    cout << endl << endl;

    return 0;
} //End display_opt() 


std::string set_lower(string sInput, vector<string> vToCompare) {
    //Function is used to convert input to lower case

    vector<string> vLower;
    string str, strRet;

    //Converts sInput to lower-case
    for(int i = 0; i < sInput.length(); i++) {
        if(sInput[i]>='A' && sInput[i]<='Z') {
            sInput[i]=sInput[i]+32;
        }
    }


    //Copys vToCompare to vLower
    for (int i = 0; i < vToCompare.size(); ++i) {
        str = vToCompare[i];
        for(int j = 0; j < str.length(); j++) {
            if(str[j]>='A' && str[j]<='Z') {
                str[j]=str[j]+32;
            }
        }
        vLower.push_back(str);
    }

    //Compares sInput to vLower
    for (int i = 0; i < vLower.size(); ++i) {
        if(sInput == vLower[i]) {
            strRet = vToCompare[i];
        }
    }

    return strRet;
} //End opt_match() 


bool check_mod(vector<string> vModSel) {
    //Function checks to see if a vehicle has been selected

    bool exists=false;

    if (vModSel[0] != "") {
        exists=true;
    } 
    return exists;
} //End check_mod


int calc_total(vector<string> vModSel, vector<string> vMod, vector<int> vModPrice, vector<string> vOptSel, vector<string> vOpt, vector<int> vOptPrice) {

    int iTotal=0;

    //Grabs base vehicle price
    for (int i = 0; i < vMod.size(); ++i) {
        if (vModSel[0] == vMod[i]){
            iTotal = iTotal + vModPrice[i];
        }
    }

    //Add price of selected option(s)
    for (int i = 0; i < vOptSel.size(); ++i) {
        for (int j = 0; j < vOpt.size(); ++j) {
            if (vOptSel[i] == vOpt[j]){
                iTotal = iTotal + vOptPrice[j];
            }
        }
    }

    return iTotal;   
} //End calc_total()


int main() {
    
    //Declare variables
    vector<string> vMod, vOpt, vModSel(1), vOptSel(6);
    vector<int> vModPrice, vOptPrice, vModSelPrice(1), vOpSelPrice(6);
    int iSel, iOptPrice, iTotal, iCtOpt;
    string sFile, line, sModSel, sOpt, sOptSel, sOptList, sLower;
    bool inputExists, modSel;

    //Bring in data from options text file
    sFile = "options.txt";
    fstream fIn;
    fIn.open(sFile, fstream::in);

    if (fIn.fail()) {
        cout << sFile << " failed to open." << endl;
        return 1;
    }

    while (getline(fIn, line)) {
        // isolate option price
        size_t spc1 = line.find(' ');
        iOptPrice = stoi(line.substr(0,spc1));
        // isolate option description
        sOpt = line.substr(spc1 + 1, line.size());

        vOptPrice.push_back(iOptPrice);     //adds price into the vOptPrice vector (last position)
        vOpt.push_back(sOpt);               //adds description into the vOpt vector (last position)
    }

    fIn.close();

    //Assign values to model vectors 
    vMod = {"E", "L", "X"};
    vModPrice = {10000, 12000, 18000};

     //Display Menu 
    do {
        cout << "1. Select a model (E, L, X)" << endl;
        cout << "2. Display available options and prices" << endl;
        cout << "3. Add an option" << endl;
        cout << "4. Remove an option" << endl;
        cout << "5. Cancel order" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter choice: ";
        cin >> iSel;
        
        switch (iSel) {
        
            case 1:
            do {
            cout << "Enter the model: (E, L, X): ";
            cin >> sModSel;     //Get user model input
            sLower = set_lower(sModSel, vMod);  //Converts to lower-case
            } while (sLower == "");
            vModSel[0] = sLower;
            //See if exists in model options
            iTotal = calc_total(vModSel, vMod, vModPrice, vOptSel, vOpt, vOptPrice);    //calcs total

            //Generate options list
            if (vOptSel[0] == "") {
                sOptList = "None";
            }
            else {
                for (int i = 0; i < vOptSel.size(); ++i) {
                    if (vOptSel[i] != ""){
                        sOptList = sOptList + ", " + vOptSel[i];
                    }
                }
            }
            cout << endl << "Model: " << vModSel[0] << ", $" << iTotal << ", Options: " << sOptList << endl << endl;       //output current selections
            break;  //End case 1

            case 2:
            display_opt(vMod, vOpt, vModPrice, vOptPrice);
            break; //End case 2

            case 3:
            if(check_mod(vModSel)==false) {
                cout << endl << "NO MODEL SELECTED" << endl << endl;
            }
            else {
                do {
                    cout << "Enter option: ";
                    cin.ignore();
                    getline(cin,sOptSel);       //Get user option input
                    sLower = set_lower(sOptSel, vOpt);  //Converts to lower-case
                } while (sLower == "");
                //Add to vector of selected options
                for (int i = 0; i < vOptSel.size(); ++i) {
                    if(vOptSel[i]=="") {
                        vOptSel[i] = sLower;
                        break;
                    }
                }
                iTotal = calc_total(vModSel, vMod, vModPrice, vOptSel, vOpt, vOptPrice);    //Calcs total

                //Generate options list
                if (vOptSel[0] == "") {
                    sOptList = "None";
                }
                else {
                    sOptList = "";
                    iCtOpt = 0;
                    for (int i = 0; i < vOptSel.size(); ++i) {
                        if (vOptSel[i] != ""){
                            iCtOpt = iCtOpt + 1;
                            sOptList = sOptList + vOptSel[i] + ", ";
                        }
                    }
                }
                cout << endl << "Model: " << vModSel[0] << ", $" << iTotal << ", Options: " << sOptList << endl << endl;       //output current selections
            }
            break; //End case 3

            case 4:
            if(check_mod(vModSel)==false) {
                cout << endl << "NO MODEL SELECTED" << endl << endl;
            }
            else {
                do {
                    cout << "Enter option to remove: ";
                    cin.ignore();
                    getline(cin,sOptSel);       //Get user option input
                    sLower = set_lower(sOptSel, vOpt);  //Converts to lower-case
                } while (sLower == "");
                //Remove from vector of selected options
                for (int i = 0; i < vOptSel.size(); ++i) {
                    if(vOptSel[i]==sLower) {
                        vOptSel[i] = "";
                        break;
                    }
                }
                iTotal = calc_total(vModSel, vMod, vModPrice, vOptSel, vOpt, vOptPrice);    //Calcs total

                //Generate options list
                if (vOptSel[0] == "") {
                    sOptList = "None";
                }
                else {
                    sOptList = "";
                    iCtOpt = 0;
                    for (int i = 0; i < vOptSel.size(); ++i) {
                        if (vOptSel[i] != ""){
                            iCtOpt = iCtOpt + 1;
                            sOptList = sOptList + vOptSel[i] + ", ";
                        }
                    }
                }
                cout << endl << "Model: " << vModSel[0] << ", $" << iTotal << ", Options: " << sOptList << endl << endl;       //output current selections
            }
            break; //End case 4

            case 5:
            vModSel.clear();    //Clears vModSel vector
            vOptSel.clear();    //Clears vOptSel vector
            iTotal = 0;         //Sets iTotal = 0 (zero)
            cout << endl << "Model: None, $" << iTotal << ", Options: None" << endl << endl;
            break;  //End case 5
        }

    } while (iSel != 6);

    return 0;
}