#include <iostream>
#include <string>
#include <fstream>

#include <exception>
#include <stdexcept>

using namespace std;

string asciiConvt(string s, int shift){
    int asciiBef,asciiAft;
    string result;
    //65-90 | 97-122
    for (int i = 0; i < s.length(); ++i){
        asciiBef = (int)s[i];
        asciiAft = asciiBef;
        if((asciiBef >= 65 && asciiBef <= 90) || (asciiBef >= 97 && asciiBef <= 122)){
            //asciiBef += shift;
            asciiAft = asciiBef + shift;
            if(asciiBef <= 90 && asciiAft >= 97){
                asciiAft += 6;
            }
            while(asciiAft>122){
                asciiAft = 65 + (asciiAft-122) - 1;
            }
            while(asciiAft > 90 && asciiAft < 97){
                asciiAft = 97 + abs(90 - asciiAft) - 1;
            }
            while(asciiAft<65){
                asciiAft = 122 - abs(65-asciiAft) + 1;
            }
        }
        result += (char)asciiAft;
    }
    return result;
}

bool argLen(int x)
{
	if (x == 2){
		return true;
	}
	throw std::invalid_argument("Only 2 arguments please");
}


int main(int argc, char* argv[]){

    string temp;
    int i = 1;

    try{
    	argLen(argc);
    }
    catch(std::invalid_argument){
    	cout << "Please put the filename to be converted as the second argument!" << endl;
    	return -1;
    }

    string inputname = argv[1];
    ifstream r(inputname); //input file is to be named input.txt
    string outputname = inputname.substr(0,inputname.size() - 4) + "C.txt";
    ofstream w(outputname); //crypted input exported into inputC.txt
    while(!r.eof()){
        getline(r,temp);
        temp = asciiConvt(temp,i);
        w << temp << endl;
        i++;
    }
    w.close();
    r.close();
}
