#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

//step1
int is_intersect(int q1, int q2);
int intersections(int index1, int index2, int* q, int size, int& sum);

//step2
int intersect(int* q, int start, int end);
int group_intersect(int* q, int start, int m, int end);
void merge(int*array, int start, int end, int m);

int intersect(int* q, int start, int end){
   if ((end-start)>0){
      int m = (end-start)/2+start;
      int i1 = intersect(q, start,m);
      int i2 = intersect(q,m+1,end);
       int i3 = group_intersect(q,start,m,end);
       cout<<"i1 "<<i1<<endl;
       cout<<"i2 "<<i2<<endl;
       cout<<"i3 "<<i3<<endl;
       return i1+i2+i3;
   }
   return 0;
}

int group_intersect(int* q, int start, int m, int end){
    //sort two sub group
    merge(q,start,m,(m-start)/2+start);
    merge(q,m+1,end,(end-m-1)/2+m+1);
    
    for (int i =start; i <=m; i++){
        cout<<q[i]<<" ";
    }
    cout<<endl;
    for (int i =m+1; i <=end; i++){
        cout<<q[i]<<" ";
    }
    cout<<endl;

    
    int num_intersection_pairs = 0;
    int i = end;
    int j = m;
    while( i>=m+1 && j>=start){
        if(q[i]>q[j]){
            i--;
            //this line intersects with every line between (q[j], q[m]]
            num_intersection_pairs+=(m-j);
        }
        else if (q[i]<=q[j]){
            j--;
        }
        if(j<start){
            //lines between [q[m+1],q[i]] intersects with every line
            num_intersection_pairs+=(i-m)*(m-start+1);
        }
    }
    return num_intersection_pairs;
}

void merge(int*array, int start, int end, int m){
    int i = start, j = m+1;
    //copy array
    int *copy = new int [end+1];
    for (int g = start; g <= end;g++){
        copy[g] = array[g];
    }
    for(int k = start; k <= end; k++){
        if (j>end){
            array[k]=copy[i];
            i++;
        }
        else if(i>m){
            array[k]=copy[j];
            j++;
        }
        else if(copy[i]<copy[j]){
            array[k]=copy[i];
            i++;
        }
        else{
            array[k]=copy[j];
            j++;
        }
    }
    delete[] copy;
}

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
    num_intersection_pairs = intersect(q,0,size-1);
    
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
