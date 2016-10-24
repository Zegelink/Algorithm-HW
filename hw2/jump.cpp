/*
 Author: Chongxian Chen
 DATE: October 23, 2016
 */

#include <iostream>
#include <fstream>
#include <utility>  //pair
#include <cmath>
using namespace std;

void extractData(pair<int,int>* array, ifstream* file,int size);
int jump(pair<int,int>* p,int pstart,int pend, pair<int,int>* q,int qstart, int qend, double l, int** memory_jump);
double distanceTo(pair<int,int> p, pair<int,int> q);

int main(){

   ifstream file;
   file.open("5.txt");
    
    int sizep;
    file>>sizep;
    /*char c;
    while(file.get(c)){
        cout<<c;
    }*/
    
   pair<int,int>* p = new pair<int,int> [sizep];
    extractData(p,&file,sizep);
    /*for(int i = 0; i < sizep; i++){
        cout<<"("<<p[i].first<<","<<p[i].second<<")"<<endl;
    }*/
    
    int sizeq;
    file>>sizeq;
    pair<int,int>* q = new pair<int,int> [sizeq];
    extractData(q,&file,sizeq);
    /*for(int i = 0; i < sizeq; i++){
        cout<<"("<<q[i].first<<","<<q[i].second<<")"<<endl;
    }*/
    int** memory_jump = new int* [sizep];
    for(int i = 0; i < sizep; i++){
        memory_jump[i] = new int [sizeq];
        for(int j = 0; j<sizeq;j++){
            memory_jump[i][j] = -1;
        }
    }
    
    int result = jump(p,0,sizep-1,q,0,sizeq-1,226,memory_jump);
    
    cout<<"the result is "<<result<<endl;
    
    //write result into file
    ofstream outputfile;
    outputfile.open("output.txt");
    outputfile<<result;
    outputfile.close();
    
   delete[] p;
   delete[] q;
    for (int i = 0; i < sizep; i++){
        delete[] memory_jump[i];
    }
    delete[] memory_jump;
    
   file.close();
   return 0;
}

//This function extracts data into the array for the specific format of the input file
void extractData(pair<int,int>* array, ifstream* file,int size){
    char c;
    //file->get(c);
    file->get(c);
    for (int i = 0; i < size-1; i++){
        file->get(c);
        (*file)>>array[i].first;
        file->get(c);
        (*file)>>array[i].second;
        file->get(c);
        file->get(c);
    }
    file->get(c);
    (*file)>>array[size-1].first;
    file->get(c);
    (*file)>>array[size-1].second;
    file->get(c);
}

int jump(pair<int,int>* p,int pstart,int pend, pair<int,int>* q,int qstart, int qend, double l, int **memory_jump){
    
    if(memory_jump[pstart][qstart] != -1){
        return memory_jump[pstart][qstart];
    }
    
    //if the distance is greater then the leash at current point, return 0
    if ( distanceTo(p[pstart],q[qstart]) > l){
        /*cout<<distanceTo(p[pstart],q[qstart]);
        cout<<"  pstart:"<<pstart<<"  qstart:"<<qstart<<endl;*/
        memory_jump[pstart][qstart] = 0;
        return 0;
    }
    //three special case;
    if( (pend-pstart == 0) && (qend-qstart == 0) ){
        memory_jump[pstart][qstart] = 1;
        return 1;
    }
    else if(pend-pstart == 0){
        if(jump(p,pstart,pend,q,qstart+1,qend,l,memory_jump)){
            memory_jump[pstart][qstart] = 1;
            return 1;
        }
        else{
            memory_jump[pstart][qstart] = 1;
            return 0;
        }
    }
    else if(qend-qstart == 0){
        if(jump(p,pstart+1,pend,q,qstart,qend,l,memory_jump)){
            memory_jump[pstart][qstart] = 1;
            return 1;
        }
        else{
            memory_jump[pstart][qstart] = 0;
            return 0;
        }
    }
    else{
        //three valid ways for frogs to jump
        int a,b,c;
        a = jump(p,pstart+1,pend,q,qstart,qend,l,memory_jump);
        b = jump(p,pstart,pend,q,qstart+1,qend,l,memory_jump);
        c = jump(p,pstart+1,pend,q,qstart+1,qend,l,memory_jump);
        
        if(a||b||c){
            memory_jump[pstart][qstart] = 1;
            return 1;
        }
        else{
            memory_jump[pstart][qstart] = 0;
            return 0;
        }
    }
}

double distanceTo(pair<int,int> p, pair<int,int> q){
    int d = pow(p.first-q.first,2)+pow(p.second-q.second,2);
    return sqrt(d);
}
