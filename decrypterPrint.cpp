#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string asciiConvt(string s, int shift){
    int asciiBef,asciiAft;
    string result;
    for (int i = 0; i < s.length(); ++i){
        asciiBef = (int)s[i];
        asciiAft = asciiBef;
        if((asciiBef >= 65 && asciiBef <= 90) || (asciiBef >= 97 && asciiBef <= 122)){
            asciiAft = asciiBef + shift;
            if(asciiBef >= 97 && asciiAft <= 90){
                asciiAft -= 6;
            }
            while(asciiAft>122){
                asciiAft = 65 + (asciiAft-122) - 1;
            }
            while(asciiAft<65){
                asciiAft = 122 - abs(65-asciiAft) + 1;
            }
            while(asciiAft > 90 && asciiAft < 97){
                asciiAft = 90 - abs(97 - asciiAft) + 1;
            }
        }
        result += (char)asciiAft;
    }
    return result;
}

int getID(){
    ifstream r("ID.dat",ios::binary);
    int x = 0;
    r.read((char*)&x,sizeof(x));
    r.close();

    ofstream w("ID.dat",ios::binary);
    if(x == 0){
        x = 1;
    }
    else{
        x += 1;
        if(x > 31){
            x = 1;
        }
    }
    w.write((char*)&x,sizeof(x));
    w.close();
    return x;
}

bool argLen(int x)
{
    if (x == 3){
        return true;
    }
    throw std::invalid_argument("Only 3 arguments please");
}



int main(int argc, char* argv[]){

    try{
        argLen(argc);
    }
    catch(std::invalid_argument){
        cout << "Please put 2 filenames to be converted as quotes!" << endl;
        return -1;
    }

    int id = getID();

    string temp,temp2;

    string input1 = argv[1];
    string input2 = argv[2];
    //cout << "INPUT1:" << input1 << endl;
    //cout << "INPUT2:" << input2 << endl;

    ifstream r(input1);
    ifstream r2(input2);

    cout << "------------------------" << endl;

    for (int i = 1; i <= 31; ++i){
        int shift = i*-1;
        getline(r,temp);
        getline(r2,temp2);
        temp = asciiConvt(temp,shift);
        temp2 = asciiConvt(temp2,shift);
        if(i == id){
            for (int i = 0; i < temp.length(); ++i){
                if(temp[i] == '^'){
                    cout << "\n";
                }
                else{
                    cout << temp[i];
                }
            }
            cout << endl << "------------------------";
            cout << endl;
            for (int i = 0; i < temp2.length(); ++i){
                if(temp2[i] == '^'){
                    cout << "\n";
                }
                else{
                    cout << temp2[i];
                }
            }
        }
    }
    cout << endl << endl;
    r.close();

}
