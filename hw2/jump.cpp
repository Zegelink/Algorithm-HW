/*
 Author: Chongxian Chen
 DATE: October 23, 2016
 */

#include <iostream>
#include <fstream>
#include <utility>  //pair
#include <cmath>
#include <algorithm>
using namespace std;

void extractData(pair<int,int>* array, ifstream* file,int size);
int jump(pair<int,int>* p,int pstart,int pend, pair<int,int>* q,int qstart, int qend, double l, int** memory_jump);
double distanceTo(pair<int,int> p, pair<int,int> q);
int jump_iterative(pair<int,int>* p,int pstart,int pend, pair<int,int>* q,int qstart, int qend, double l, int **memory_jump);
int binary_search_jump(int *arr, int left, int right,pair<int,int>* p,int pstart,int pend, pair<int,int>* q,int qstart, int qend, double l, int **memory_jump);

int main(){

   ifstream file;
   file.open("1.txt");
    
    int sizep;
    file>>sizep;
    
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
    
    int sizel;
    file>>sizel;
    int* l = new int[sizel];
    for (int i = 0; i < sizel; i++){
        file>>l[i];
        //eliminate the , symbol
        file.get();
    }
    //sort l in preparation for binary search
    sort(l,l+sizel);

    int** memory_jump = new int* [sizep];
    for(int i = 0; i < sizep; i++){
        memory_jump[i] = new int [sizeq];
        for(int j = 0; j<sizeq;j++){
            memory_jump[i][j] = -1;
        }
    }
    //int result = jump(p,0,sizep-1,q,0,sizeq-1,225,memory_jump);
    //int result = jump_iterative(p,0,sizep-1,q,0,sizeq-1,1,memory_jump);
    int result = binary_search_jump(l,0,sizel-1,p,0,sizep-1,q,0,sizeq-1,23,memory_jump);
    cout<<"the result is "<<result<<endl;
    
    //write result into file
    ofstream outputfile;
    outputfile.open("output.txt");
    outputfile<<result;
    outputfile.close();
    
   delete[] p;
   delete[] q;
    delete[] l;
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
    //the format for input 1,2,3 needs the following line, weird format of input file the prof has provided to us!
    while(file->peek() != '('){
        file->get(c);
    }

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
    double d = sqrt( pow(p.first-q.first,2)+pow(p.second-q.second,2) );
    return d;
}

int jump_iterative(pair<int,int>* p,int pstart,int pend, pair<int,int>* q,int qstart, int qend, double l, int **memory_jump){
    //fill the last element
    if(distanceTo(p[pend],q[qend]) > l){
        memory_jump[pend][qend] = 0;
    }
    else{
        memory_jump[pend][qend] = 1;
    }
    //fill the rightmost column
    for (int i = pend-1; i>=pstart; i--){
        if( distanceTo(p[i],q[qend]) <= l && memory_jump[i+1][qend] == 1){
            memory_jump[i][qend] = 1;
        }
        else{
            memory_jump[i][qend] = 0;
        }
    }
    //fill the bottom row
    for (int i = qend-1; i>=qstart; i--){
        if( distanceTo(p[pend],q[i]) <= l && memory_jump[pend][i+1] == 1){
            memory_jump[pend][i] = 1;
        }
        else{
            memory_jump[pend][i] = 0;
        }
    }
    //fill the rest
    for (int i = pend-1;i>=pstart;i--){
        for(int j = qend-1;j>=qstart;j--){
            //current point distance no greater than the leash and any other three route is working
            if (distanceTo(p[i],q[j]) <= l && (memory_jump[i+1][j]||memory_jump[i][j+1]||memory_jump[i+1][j+1]) ){
                memory_jump[i][j] = 1;
            }
            else{
                memory_jump[i][j] = 0;
            }
        }
    }
    return memory_jump[pstart][qstart];
}

int binary_search_jump(int *arr, int left, int right,pair<int,int>* p,int pstart,int pend, pair<int,int>* q,int qstart, int qend, double l, int **memory_jump){
    while(right-left>1){
        int middle = (left+right)/2;
        if(jump_iterative(p,pstart,pend,q,qstart,qend,arr[middle],memory_jump)==1){
            right = middle;
        }
        else{
            left = middle;
        }
    }
    //only two elements remaining
    if (jump_iterative(p,pstart,pend,q,qstart,qend,arr[left],memory_jump)==1){
        return arr[left];
    }
    else{
        return arr[right];
    }
}







