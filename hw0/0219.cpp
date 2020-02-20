#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <vector> 
using namespace std;
class Cell{
public:
    int id, x, y, sum;
    double cons, std, mean;
    vector<bool> patterns;
    Cell(){
        id = x = y = sum = 0;
        cons = std = mean = 0.0;
    }
    void display(){
        cout<<"Cell "<<id<<"\t<"<<x<<",\t"<<y<<">\t"<<setprecision(15)<<cons<<endl;
    }

    bool operator< (const Cell& ob2){
        if(abs(this->mean - ob2.mean) < range){
            return this->std < ob2.std; 
        }
        else{
            return this->mean < ob2.mean; 
        }
    }
    /*
    data_for_sort columns[cell_n-2];
    for(int j=1;j<cell_n-1;j++){
        int data[pattern_n] = {0}, length = pattern_n;
        double mean = 0, std = 0, sum = 0, range = 0;
        for(int i=0;i<length;i++){
            if(patterns[i][j] == '1'){
                data[i] = i;
                sum += i;
            }
        }
        mean = sum/length;
        for(int i=0;i<length;i++){
            std += pow(data[i] - mean, 2);
        }
        std = sqrt(std / length);
        columns[j].init(mean, std, sum, 0.5*std, length, j);
    }
    sort(columns, columns+sizeof(columns)/sizeof(data_for_sort));
    */


};

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Error input format: ./hw0 XXX\n");
        return 0;
    }
    ifstream file;
    string filename(argv[1]);

    file.open ("./testcase/" + filename + ".cfg", ifstream::in);
    int W_pp, W_scl, W_t;
    file>>W_pp>>W_scl>>W_t;
    file.close();

    file.open ("./testcase/" + filename + ".chn", ifstream::in);
    int cell_n = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
    cout<<cell_n<<" cells."<<endl;
    file.clear();
    file.seekg(0);
    Cell c[cell_n];
    // while(!file.eof()){
    for(int i=0;i<cell_n;i++){
        // Cell c;
        int pos1, pos2;
        string str;
        getline(file,str);
        if(str == "")
            break;
        pos1 = str.find('\t', 8);
        c[i].id = atoi(str.substr(8,pos1-8).c_str());
        pos1 = str.find('<', pos1);
        pos2 = str.find(',', pos1);
        c[i].x = atoi(str.substr(pos1+1,pos2-pos1).c_str());
        pos1 = str.find('\t', pos2);
        pos2 = str.find('>', pos1);
        c[i].y = atoi(str.substr(pos1+1,pos2-pos1).c_str());
        pos1 = str.find('\t', pos2);
        c[i].cons = strtod(str.substr(pos1+1).c_str(), NULL);
        // c.display();
    }
    file.close();
    double all_cons[cell_n] = {c[0].cons};
    int scan_chain_L = 0;
    for(int i=1;i<cell_n;i++){
        all_cons[i] = c[i].cons;
        scan_chain_L = scan_chain_L + abs(c[i].x - c[i-1].x) + abs(c[i].y - c[i-1].y);
    }

    file.open ("./testcase/" + filename + ".src", ifstream::in);
    int pattern_n = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
    cout<<pattern_n<<" patterns."<<endl;
    file.clear();
    file.seekg(0);

    bool d_p[cell_n*2] = {0};
    bool last_state = 0;
    double max_PP = 0;

    for(int i=0;i<pattern_n;i++){
        if(i%(pattern_n/5) == 0)
            cerr<<'|';
        else if(i%(pattern_n/50) == 0)
            cerr<<'-';

        string str;
        getline(file,str);
        if(str == "")
            break;
        for(int j=0;j<cell_n;j++){
            bool curr_state;
            if (str[j] == '0'){
                c[j].patterns.push_back(0);
                curr_state = 0;
            }
            else if (str[j] == '1'){
                c[j].patterns.push_back(1);
                c[j].sum += i;
                curr_state = 1;
            }
            else{
                continue;
            }
            d_p[j + cell_n - 1] = curr_state ^ last_state;
            last_state = curr_state;
            // cout<<d_p[j + cell_n - 1];
        }
        // cout<<endl;
        // cout<<"Pattern "<<i<<" finish.\n";

        for(int j=0;j<cell_n;j++){
            double pp = 0;
            for(int k=0;k<cell_n;k++){
                // cout<<all_cons[k]<<" * "<<d_p[j + cell_n - k - 1]<<endl;
                pp = pp + all_cons[k] * d_p[j + cell_n - k - 1];
            }
            // cout<<" = "<<pp<<endl<<endl;
            d_p[j] = d_p[j + cell_n];
            if(max_PP < pp){
                max_PP = pp;
            }
        }
    }
    cerr<<"|"<<endl;
    file.close();

    cout<<"Max Peak Power: "<<max_PP<<endl;
    cout<<"Scan-chain Length: "<<scan_chain_L<<endl;

    // sort(columns, columns+sizeof(columns)/sizeof(data_for_sort));

     cout<<"The program took "<<(((float)clock())/CLOCKS_PER_SEC)<<" seconds."<<endl;
    return 0;

}
