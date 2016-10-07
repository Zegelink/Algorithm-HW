#include <iostream>
#include <fstream>
using namespace std;

int is_intersect(int p1, int p2, int q1, int q2);
int intersections(int index1, int index2, int* p, int* q, int size);


int main(){

   ifstream file;
   file.open("input.txt");

   int size;
   file>>size;

   int* p = new int [size];
   int* q = new int [size];

   for (int i = 0; i < size; i++){
      file>>p[i];
      //eliminate the , symbol
      file.get();
   }
   for (int i = 0; i < size; i++){
      file>>q[i];
      file.get();
   }
    //size starts from 0, so minus 1. divide by 2 for repeating pairs.
    int num_intersection_pairs = intersections(0,0,p,q,size-1)/2;
    
    ofstream outputfile;
    outputfile.open("output.txt");
    outputfile<<num_intersection_pairs;
    outputfile.close();
    
   delete[] p;
   delete[] q;
   file.close();
   return 0;
}

int intersections(int index1, int index2, int* p, int* q, int size){
    //cout<<index1<<"  "<<index2<<endl;
    if(index1 == size){
        if(index2 == size){
            //same line, last compare
            return 0;
        }
        else{
            return is_intersect(p[index1],p[index2],q[index1],q[index2])+
            intersections(index1,index2+1,p,q,size);
        }
    }
    else{
        if(index2 == size){
            return is_intersect(p[index1],p[index2],q[index1],q[index2])+
            intersections(index1+1,0,p,q,size);
        }
        else{
            return is_intersect(p[index1],p[index2],q[index1],q[index2])+
            intersections(index1,index2+1,p,q,size);
        }
    }
}

//a function that determines if two lines intersect
int is_intersect(int p1, int p2, int q1, int q2){
    if (p1 == p2){
        //this indicate the same line for our problem
        return 0;
    }
    if (q1 == q2){
        //intersect at y = 1
        return 1;
    }
    if(q1>q2){
        if(p1>p2){
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        if(p1>p2){
            return 1;
        }
        else{
            return 0;
        }
    }
}
