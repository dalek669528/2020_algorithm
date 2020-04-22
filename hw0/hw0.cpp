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
#include <omp.h>
using namespace std;

float W_pp, W_scl, W_t;

class Cell{
public:
    int id, x, y, sum, count;
    double cons, std, mean;
    vector<bool> patterns;
    Cell(){
        id = x = y = sum = count = 0;
        cons = std = mean = 0.0;
    }
    void display(){
        // cerr<<"Cell "<<id<<"\t<"<<x<<",\t"<<y<<">\t"<<setprecision(15)<<cons<<endl;
        cerr<<"Cell "<<setw(5)<<id<<setw(5)<<(sum/count)<<"\t"<<setprecision(15)<<cons<<endl;
    }
    int distance(const Cell& ob2){
        int dis = 0;
        for(int i=0;i<patterns.size();i++){
            dis += (int)(this->patterns[i] ^ ob2.patterns[i]);
        }
        dis += (abs(this->x - ob2.x) + abs(this->y - ob2.y))*W_scl*0.1;
        return dis;
    }
    bool operator<(const Cell& ob2){
        // if(abs(this->mean - ob2.mean) < range){
        //     return this->std < ob2.std; 
        // }
        // else{
        //     return this->mean < ob2.mean;
        // }
        // return (this->sum/(double)this->count) < (ob2.sum/(double)ob2.count);
        return this->cons < ob2.cons;
    }
};

int main(int argc, char *argv[]){
    if(argc!=7){
        printf("Error input format: ./hw0 XXX\n");
        return 0;
    }
    fstream file;
    string path("");
    string filename(argv[3]);
    file.open (path + filename , ifstream::in);
    file>>W_pp>>W_scl>>W_t;
    file.close();

    filename = argv[1];
    file.open (path + filename, ifstream::in);
    int cell_n = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
    file.seekg(0);
    file.clear();
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
    // cerr<<"Readed "<<cell_n<<" cells."<<endl;
    double all_cons[cell_n] = {c[0].cons};
    int scan_chain_L = 0;
    for(int i=1;i<cell_n;i++){
        all_cons[i] = c[i].cons;
        scan_chain_L = scan_chain_L + abs(c[i].x - c[i-1].x) + abs(c[i].y - c[i-1].y);
    }

    filename = argv[2];
    file.open (path + filename, ifstream::in);
    int pattern_n = 0;
    bool d_p[cell_n*2] = {0};
    bool last_state = 0;
    double max_PP = 0;

    // cerr<<"|";
    while(!file.eof()){
        string str;
        getline(file,str);
        if(str == "")
            break;
        int k = 0;
        #pragma omp parallel for
        for(int j=0;j<str.length();j++){
            bool curr_state;
            if (str[j] == '\\'){
                getline(file,str);
                if(str == "")
                    break;
                else{
                    j = -1;
                    continue;
                }
            }
            else if (str[j] == '0'){
                c[k].patterns.push_back(0);
                curr_state = 0;
                k++;
            }
            else if (str[j] == '1'){
                c[k].patterns.push_back(1);
                c[k].sum += pattern_n;
                c[k].count += 1;
                curr_state = 1;
                k++;
            }
            else if (str[j] == '\r'){
                break;
            }
            else{
                cerr<<"Error src input. line:"<<pattern_n<<" j:"<<j<<" -"<<str[j]<<"-"<<endl;
                break;
            }
            d_p[k + cell_n - 1] = curr_state ^ last_state;
            last_state = curr_state;
            // cerr<<curr_state;
            // cerr<<d_p[k + cell_n - 1];
        }
        // cerr<<endl;
        // cerr<<"Pattern "<<i<<" finish.\n";

        for(int j=0;j<cell_n;j++){
            double pp = 0;
            for(int k=0;k<cell_n;k++){
                // cerr<<all_cons[k]<<" * "<<d_p[j + cell_n - k - 1]<<endl;
                pp = pp + all_cons[k] * d_p[j + cell_n - k - 1];
            }
            // cerr<<" = "<<pp<<endl<<endl;
            d_p[j] = d_p[j + cell_n];
            if(max_PP < pp){
                max_PP = pp;
            }
        }
        pattern_n++;
        // cerr<<"Pattern "<<pattern_n<<" finish.\n";
        // cerr<<"-";
    }
    // cerr<<"|"<<endl;
    file.close();

    cout<<"Scan-chain Length: "<<scan_chain_L<<endl;
    cout<<"Max Peak Power: "<<max_PP<<endl;
    double ori_pp = max_PP; 
    int ori_SCL = scan_chain_L;

    cerr<<"\n";
    // sort(c+1, c+cell_n-1);
    for(int i=0;i<cell_n-2;i++){
        // cerr<<i<<" - ";
        int index = i+1;
        int min_dis = c[i].distance(c[i+1]);
        for(int j=i+2;j<cell_n-1;j++){
            // cerr<<j<<" ";
            int dis = c[i].distance(c[j]);
            if(dis<min_dis){
                min_dis = dis;
                index = j;
            }
        }
        if(i+1 != index){
            // cerr<<"swap -- "<<i+1<<" / "<<index<<"\t\t"<<c[i+1].id<<" / "<<c[index].id<<endl;
            swap(c[i+1], c[index]);
        }
    }

    scan_chain_L = 0;
    last_state = 0;
    max_PP = 0;
    for(int i=0;i<cell_n;i++){
        d_p[i] = 0;
    }
    for(int i=1;i<cell_n;i++){
        all_cons[i] = c[i].cons;
        scan_chain_L = scan_chain_L + abs(c[i].x - c[i-1].x) + abs(c[i].y - c[i-1].y);
    }
    // cerr<<"|";
    #pragma omp parallel for
    for(int i=0;i<pattern_n;i++){
        // cerr<<"-";
        for(int j=0;j<cell_n;j++){
            d_p[j + cell_n - 1] = c[j].patterns[i] ^ last_state;
            last_state = c[j].patterns[i];
            // cout<<c[j].patterns[i]<<" ^ "<<last_state<<" = ";
            // cout<<d_p[j + cell_n - 1]<<endl;
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
    // cerr<<"|"<<endl;
    cout<<"Scan-chain Length: "<<scan_chain_L<<endl;
    cout<<"Max Peak Power: "<<max_PP<<endl;



    filename = argv[4];
    file.open (path + filename, ofstream::out);
    for(int i=0;i<cell_n;i++){
        file<<"SCANCELL"<<c[i].id<<"\t<"<<c[i].x<<",\t"<<c[i].y<<">\t"<<setprecision(15)<<c[i].cons<<endl;
    }
    file.close();

    filename = argv[5];
    file.open (path + filename, ofstream::out);
    for(int j=0;j<pattern_n;j++){
        for(int i=0;i<cell_n;i++){
            file<<c[i].patterns[j];
        }
        file<<endl;
    }
    file.close();
    
    filename = argv[6];
    file.open (path + filename, ofstream::out);
    file<<"Original:\n";
    file<<"Scan-Chain Length = "<<ori_SCL<<endl;
    file<<"Max Peak Power = "<<ori_pp<<endl<<endl;
    file<<"Reordered:\n";
    file<<"Scan-Chain Length = "<<scan_chain_L<<endl;
    file<<"Max Peak Power = "<<max_PP;
    file.close();
    
    cout<<endl<<"The program took "<<(((float)clock())/CLOCKS_PER_SEC)<<" seconds."<<endl;
    return 0;

}
