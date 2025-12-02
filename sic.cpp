#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define int long long
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define all(v) v.begin(), v.end()
map<string,string> mp1 = {
    {"ADD", "18"}, {"AND", "40"}, {"COMP", "28"}, {"DIV", "24"},
    {"J",   "3C"}, {"JEQ", "30"}, {"JGT", "34"}, {"JLT", "38"},
    {"JSUB","48"}, {"LDA", "00"}, {"LDCH","50"}, {"LDL", "08"},
    {"LDX", "04"}, {"MUL", "20"}, {"OR",  "44"}, {"RD",  "D8"},
    {"RSUB","4C"}, {"STA", "0C"}, {"STCH","54"}, {"STL", "14"},
    {"STSW","E8"}, {"STX", "10"}, {"SUB", "1C"}, {"TD",  "E0"},
    {"TIX", "2C"}, {"WD",  "DC"}
};// opcode table

map<string,int> mp2; // symbol table

struct Line {
    int address;
    string label;
    string opcode;
    string operand;
    string objectCode;
};

vector<Line> program;
void solve1()
{
    ifstream file("SIC.txt");
    string str,w1,w2,w3;
    int LOCCTR = 0;
    while(getline(file,str))
    {
        stringstream ss(str);
        Line line;
        ss>>w1;
        if(mp1.count(w1) or w1=="START" or w1=="END" or w1=="WORD" or w1=="RESW" or w1=="RESB" or w1=="BYTE")
        {
            line.label = "";
            line.opcode = w1;
            if(ss>>w2)line.operand = w2;
        }
        else
        {
            line.label = w1;
            if(ss>>w2)line.opcode = w2;
            if(ss>>w3)line.operand = w3;
        }
        line.address = LOCCTR;
        if(line.opcode == "START")
        {
            LOCCTR = stoi(line.operand, NULL, 16);
            line.address = LOCCTR;
        }
        else if (line.opcode!="END")
        {
            if(line.label!="")mp2[line.label] = LOCCTR;
            if(mp1.count(line.opcode)) LOCCTR += 3;
            else if(line.opcode=="WORD") LOCCTR += 3;
            else if(line.opcode=="RESW") LOCCTR += 3 * stoi(line.operand);
            else if(line.opcode=="RESB") LOCCTR += stoi(line.operand);
            else if(line.opcode=="BYTE") 
            {
                if(line.operand[0]=='C')
                {
                    LOCCTR += line.operand.size() - 3; 
                }
                else if(line.operand[0]=='X')
                {
                    LOCCTR += (line.operand.size() - 3 + 1) / 2; 
                }
            }
        }
        program.push_back(line);
    }

}

void solve2()
{
    for(auto&[address, label, opcode, operand, objectCode]:program)
    {
        if(mp1.count(opcode))
        {
            int add = 0;
            if(operand!="")
            {
                string s = operand;
                bool idx = 0;
                if(s.size()>2 and s.substr(s.size()-2) == ",X")
                {
                    idx = 1;
                    s = s.substr(0,s.size()-2);
                }   
                add = mp2[s];
                if(idx) add += 0x8000;
            }
            stringstream ss;
            ss << mp1[opcode]<< setfill('0') << setw(4) << hex << uppercase << add;
            opcode = ss.str();
        }
        else if (opcode =="WORD" or opcode == "BYTE")
        {
            if (opcode == "WORD") {
                stringstream ss;
                ss << setfill('0') << setw(6) << hex << stoi(operand);
                objectCode = ss.str();
            }
            else if (operand[0]=='C')
            {
                for(int i = 2 ;i<operand.size()-1;i++)
                {
                    stringstream ss;
                    ss << hex << uppercase << (int)operand[i];
                    objectCode += ss.str();
                }
            }
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*freopen("filename", "r", stdin);
    freopen("filename", "w", stdout);*/

    // int t = 1;
    // cin >> t;
    // while (t--)
    // {
    //     solve();
    // }
    solve1();
    cout<<"Finshed Pass 1\n";
    for(auto& line : program)
    {
        cout << line.opcode;
        if (!line.objectCode.empty()) cout << " " << line.objectCode;
        cout << endl;
    }
    solve2();
    // cout<<"Symbol Table:\n";
    // for(auto&[address, label, opcode, operand, objectCode]:program)
    // {
    //     cout<<hex<<uppercase<<setfill('0')<<setw(4)<<address<<" "<<setw(8)<<label<<" "<<setw(8)<<opcode<<" "<<setw(8)<<operand<<" "<<objectCode<<endl;
    // }
    cout<<"Finshed Pass 2\n";
     for(auto& line : program)
    {
        cout << line.opcode;
        if (!line.objectCode.empty()) cout << " " << line.objectCode;
        cout << endl;
    }
    return 0;
}