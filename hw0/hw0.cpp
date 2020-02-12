#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class cell{
public:
    int id, x, y, cons;
};


int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Error input format: ./hw0 XXX\n");
        return 0;
    }
    string str;

    ifstream file;
    string filename(argv[1]);
    file.open ("./testcase/" + filename + ".cfg", ifstream::in);
    int W_pp, W_scl, W_t;
    file>>W_pp>>W_scl>>W_t;
    file.close();
    // while(file.good()){
    file.open ("./testcase/" + filename + ".chn", ifstream::in);
    for(int i=0;i<10;i++){
        int x, y, z;
        // file>>str>>x>>y>>z;
        // cout<<str<<'-'<<x<<' '<<y<<' '<<z<<'-'<<endl;
        file>>str;
        cout<<str<<'-'<<endl;

    }
    file.colse()








    return 0;

}
