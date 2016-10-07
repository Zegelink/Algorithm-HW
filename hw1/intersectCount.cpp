#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

int is_intersect(int q1, int q2);
int intersections(int index1, int index2, int* q, int size, int& sum);

int main(){

   ifstream file;
   file.open("input.txt");
   int size;
   file>>size;
   if(size<2){
      cout<<("the size of lines are smaller than 2")<<endl;
      return 0;
   }


   //p is not really useful since we know it is in ascending order
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

    //size starts from 0, so minus 1.
    int num_intersection_pairs = 0;
    intersections(0,1,q,size-1,num_intersection_pairs);
    
    //write result into file
    ofstream outputfile;
    outputfile.open("output.txt");
    outputfile<<num_intersection_pairs;
    outputfile.close();
    
   delete[] p;
   delete[] q;
   file.close();
   return 0;
}

int intersections(int index1, int index2, int* q, int size, int& sum){
    //cout<<index1<<"  "<<index2<<" "<<sum<<endl;
    sum += is_intersect(q[index1],q[index2]);
    //base case: last two lines to compare
    if(index1 == size-1){
        if(index2 >= size){
           //last line 
            return 0;
        }
        else{
            return intersections(index1,index2+1,q,size,sum);
        }
    }
    else{
        if(index2 == size){
            return intersections(index1+1,index1+2,q,size,sum);
        }
        else{
            return intersections(index1,index2+1,q,size,sum);
        }
    }
}

//a function that determines if two lines intersect
//precondition:p1<p2
int is_intersect(int q1, int q2){
    if (q1>=q2){
        return 1;
    }
    else{
       return 0;
    }
}
