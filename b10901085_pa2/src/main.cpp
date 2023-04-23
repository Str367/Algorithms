#include <iostream>
#include <fstream>

using namespace std;
// long long int counter = 0;

int recursion(int* s,int** m,int** c,int start,int end){ //s: data for chords m:ans for sub problem n:for M(0,n)
    //cout<<"start= "<<start<<", end= "<<end<<endl;
    // counter++;
    // if(start>=end) return 0;
    // for(int i = 0 ;i<12;i++){
    //     for(int j = 0;j<12;j++)
    //         cout<<m[i][j]<<" ";
    //     cout<<endl;
    // };
    // cout<<endl;
    if (m[start][end] != -1) return m[start][end];
    else if(start==end){
        m[start][end] = 0;
        return 0;
    }
    else if(s[start] == end)
    {
        c[start][end] = -4;
        if(end-start<=2)
        {
            m[start][end] = 1;
            return 1;
        }
        else m[start][end] = recursion(s,m,c,start+1,end-1)+1;
        return m[start][end];
        //c[start] = end; //改
    }
    else if(s[start]<start||end<s[start])
    {
        m[start][end] = recursion(s,m,c,start+1,end);
        c[start][end] = -1;
        return m[start][end];
    }
    else if(s[start]==start+1){
        m[start][end] = 1+recursion(s,m,c,start+2,end);
        c[start][end] = -2;
        return m[start][end];
    }
    else if(s[start]==end-1){
        m[start][end] = 1+recursion(s,m,c,start+1,end-2); 
        c[start][end] = -3;   
        return m[start][end];
    }
    else if(recursion(s,m,c,start+1,end)>1+recursion(s,m,c,start+1,s[start]-1)+recursion(s,m,c,s[start]+1,end)){
        m[start][end] = m[start+1][end];
        c[start][end] = -1;
        return m[start][end];
    }
    else{
        m[start][end] = 1+m[start+1][s[start]-1]+m[s[start]+1][end];
        c[start][end] = start;
        return m[start][end];
    }

    //else m[n] = (s[n] == -1) ? recursion(s,m,n-1) : (1+recursion(s,m,s[n]-1)>recursion(s,m,n-1) ? 1+recursion(s,m,s[n]-1) : recursion(s,m,n-1));
    //cout<<"m["<<start<<"]["<<end<<"]= "<<m[start][end]<<endl;
    // return m[start][end]; 
}

void printChord(int* s,int** c,fstream &fout,int start,int end){
    if(start == end) return;
    else if(c[start][end]>=0){
        fout<<start<<" "<<s[start]<<endl;
        printChord(s,c,fout,start+1,s[start]-1);
        printChord(s,c,fout,s[start]+1,end);
        return;
    }
    else if(c[start][end]==-1){  //case where chord at start is not considered
        printChord(s,c,fout,start+1,end);
        return;
    }
    else if(c[start][end]==-2){ //case where chord at start is connected to start+1
        fout<<start<<" "<<s[start]<<endl;
        printChord(s,c,fout,start+2,end);
        return;
    }
    else if(c[start][end]==-3){ //case where chord at start is connected to end-1
        fout<<start<<" "<<s[start]<<endl;
        printChord(s,c,fout,start+1,end-2);
        return;
    }
    else if(c[start][end]==-4){ //case where chord at start is connected to end
        fout<<start<<" "<<end<<endl;
        if(end-start>2) printChord(s,c,fout,start+1,end-1);
        return;
    }
}

int main(int argc,char **argv){
    // const string fileName = "./12.in";
    if(argc!=3){
        cout<<"usage:bin/mps <input_file> <output_file>"<<endl;
        return 0;
    }
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int n;
    fin>>n;
    int S[n] = {0};
    int** M;
    int** C;
    M = new int* [n];
    C = new int* [n];
    for(int i = 0;i < n;i++){
        M[i] = new int[n];
        C[i] = new int[n];
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        {
            M[i][j] = -1;
            C[i][j] = -100;
        }
    }
    int i,j;
    
    // cout<<"array initialized complete"<<endl;
    while(fin>>i){
        if(fin.eof()) break;
        else {
            fin>>j;
            // cout<<i<<" "<<j<<endl;
            S[j] = i;
            S[i] = j;
        }
    }
    
    // cout<<"input file complete"<<endl;
    fout<<recursion(S,M,C,0,n-1)<<endl;
    // cout<<"recursion complete"<<endl;
    printChord(S,C,fout,0,n-1);
    // for(int i=0;i<n;i++) cout<<C[i]; 
    
    // int k = 0;
    // while(k<n){
    //     if(C[k]!=0) {
    //         fout<<k<<" "<<C[k]<<endl;
    //         k=C[k]+1;
    //     }
    //     else k++;
    // }
    fin.close();
    fout.close();
    // cout<<"counter: "<<counter<<endl;
    return 0;
}