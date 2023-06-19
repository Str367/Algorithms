#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <time.h>
#include <cstdlib>


using namespace std;

struct edge
{
    int weight;
    int start;
    int end;
    bool deleted;
    bool deleted_sort;
    bool deleted_sort1;
    bool deleted_random1;
    int leader;
    /* data */
};

struct vertex
{
    int deltain;
    int deltaout;
    int numin;
    int numout;
    bool used;
};

int find(int* leader,int vertex){
    if (leader[vertex] == vertex) return vertex;
    return leader[vertex]=find(leader,leader[vertex]);
}

void sortedalg(edge sorted_edges[],int v,int e){
    bool** reachable = new bool*[v]; //added edge
    bool* reached = new bool[v];//if a vertex is traversed in dfs
    stack<int> s;

    for(int i = 0;i<v;i++){
        reachable[i] = new bool[v];
        memset(reachable[i],0,sizeof(bool)*v);
    }
    // if(sorted_edges[e-1].weight>0){
    // reachable[sorted_edges[e-1].start][sorted_edges[e-1].end] = true;
    // sorted_edges[e-1].deleted_sort = false;
    // }
    for(int i = 0 ;i<e;i++){
        if(!sorted_edges[i].deleted) reachable[sorted_edges[i].start][sorted_edges[i].end] = true;
    }
    bool flag;
    int d;
    for(int i = e-1;i>=0;i--){ //if the edge add will cause a cycle
        if(sorted_edges[i].weight<=0) break;
        else if(sorted_edges[i].deleted){
            flag = true;
            int target = sorted_edges[i].start;
            int start = sorted_edges[i].end;
            memset(reached,0,sizeof(bool)*v);
            reached[start] = true;
            for (int j = 0; j < v; j++)
            {
                if(reachable[start][j]){
                    if(j == target)
                    {
                        flag = false;
                        break;
                    }
                    else
                    {
                        s.push(j);
                        reached[j] = true;
                    }
                    
                }
                /* code */
            }
            while (flag && !s.empty())
            {   
                
                d = s.top();
                s.pop();
                for (int j = 0; j < v; j++)
                {
                    if(reachable[d][j] && !reached[j])
                    {
                        if(j == target)
                        {
                            flag = false;
                        }
                        else
                        {
                            reached[j] = true;
                            s.push(j);
                        }
                    }

                    /* code */
                }
                
                /* code */
            }
            while (!s.empty()) {
                s.pop();
            }
            if (flag)
            {
                //cout<<i<<"added\n";
                sorted_edges[i].deleted_sort = false;
                reachable[sorted_edges[i].start][sorted_edges[i].end] = true;
                /* code */
            }
        }
    }
    return;
}

void randomalg(edge sorted_edges[],int v,int e,int order[]){
    for(int i = 0;i<e;i++){

        if(order[sorted_edges[i].start]<order[sorted_edges[i].end]){
            sorted_edges[i].deleted_random1 = false;
        }
    }
}

void sortedalg1(edge sorted_edges[],int v,int e){
    short** graph = new short*[v];
    for(int i = 0;i<v;i++){
        graph[i] = new short[v];
        for(int j = 0;j<v;j++) graph[i][j] = 101;
    }
    vertex vertices[v];
    int order[v];
    int sp = 0;
    int ep = v-1;
    for(int i = 0;i<v;i++){
        vertices[i].deltain = 0;
        vertices[i].deltaout = 0;
        vertices[i].numin = 0;
        vertices[i].numout = 0;
        vertices[i].used = false;
    }
    for(int i = 0;i<e;i++){
        if(true){
            vertices[sorted_edges[i].start].deltaout += sorted_edges[i].weight;
            vertices[sorted_edges[i].end].deltain += sorted_edges[i].weight;
            vertices[sorted_edges[i].end].numin ++;
            vertices[sorted_edges[i].start].numout ++;
            graph[sorted_edges[i].start][sorted_edges[i].end] = (short)(sorted_edges[i].weight);
        }
    }
    int index;
    int d;
    bool ssflag,bkflag,dchangedflag;
    while(true){
        bkflag = true;
        ssflag = true;
        dchangedflag = true;
        d=0;
        for(int i = 0;i<v;i++){
            if (!vertices[i].used){
                if(vertices[i].numout == 0){ // it's a sink
                    order[ep--] = i;
                    ssflag = false;
                    bkflag = false;
                    vertices[i].used = true;
                    for(int j = 0;j<v;j++){
                        if(graph[j][i] != 101){
                            vertices[j].deltaout -= graph[j][i];
                            vertices[j].numout --;
                        }
                    }
                }
                else if(vertices[i].numin == 0){
                    order[sp++] = i;
                    ssflag = false;
                    bkflag = false;
                    vertices[i].used = true;
                    for(int j = 0;j<v;j++){
                        if(graph[i][j] != 101){
                            vertices[j].deltain -= graph[i][j];
                            vertices[j].numin --;
                        }
                    }
                }
                else if(ssflag){
                    bkflag = false;
                    if(dchangedflag)
                    {
                        dchangedflag = false;
                        d = vertices[i].deltaout - vertices[i].deltain;
                        index = i;  
                    }
                    else if (vertices[i].deltaout - vertices[i].deltain > d){
                        d = vertices[i].deltaout - vertices[i].deltain;
                        index = i; 
                    }
                }
                
            } 
        }
        if(ssflag && !dchangedflag){
                bkflag = false;
                vertices[index].used = true;
                order[sp++] = index;
                for(int j = 0;j<v;j++){
                    if(graph[j][index] != 101){
                        vertices[j].deltaout -= graph[j][index];
                        vertices[j].numout --;
                    }
                    if(graph[index][j] != 101){
                        vertices[j].deltain -= graph[index][j];
                        vertices[j].numin --;
                    }
                }
            }
        if(bkflag) break;
    }
    // for(int i = 0;i<v;i++) cout<<order[i]<<"\n";
    int forder[v];
    for(int i = 0;i<v;i++) forder[order[i]] = i;
    for(int i = 0;i<e;i++){

        if(forder[sorted_edges[i].start]<forder[sorted_edges[i].end]){
            sorted_edges[i].deleted_sort1 = false;
        }
    }
}

int main (int argc, char* argv[]){
    // cout<<argc;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);

    char type;
    int v,e;
    fin>>type>>v>>e;
    edge unsorted_edges[e];
    edge sorted_edges[e];
    int order[v]; // random order of vertices, order[i] = n means i is at nth place
    int leader[v]; //store root
    int rank[v]; //store rnak
    for (int i = 0; i < v; i++)
    {   
        leader[i] = i;
        order[i] = i;
        rank[i] = 0;
        /* code */
    }
            
    srand(time(NULL));
    // random_device random;
    // mt19937 generator{random_device{}()};
    // uniform_int_distribution<int> distrubution(0,v-1);
    // cout<<random()<<" "<<random();
    int x;
    int a;
    for (int i = 0; i < v; i++)
    {
        // x = distrubution(generator);
        x = rand()%v;
        // cout<<x<<"\n";
        a = order[x];
        order[x] = order[i];
        order[i] = a;
        /* code */
    }
    // for (int i = 0; i < v; i++)
    // {
    //     cout<<order[i]<<"\n";
    //     /* code */
    // }
    
    
    
    
    int counter[201] = {0}; //i=0<->-100 i=100<->0 i=200<->100
    int weight,start,end;
    int i = 0;
    while(fin>>start>>end>>weight){
        unsorted_edges[i].start = start;
        unsorted_edges[i].end = end;
        unsorted_edges[i].weight = weight;
        unsorted_edges[i].leader = -1;
        unsorted_edges[i].deleted = true;
        unsorted_edges[i].deleted_random1 = true;
        unsorted_edges[i].deleted_sort = true;
        unsorted_edges[i].deleted_sort1 = true;
        counter[weight+100]++;
        i++; 
    }
    // for (int i = 0;i<e;i++)
    // cout<<i<<" "<<edges[i].start<<" "<<edges[i].end<<" "<<edges[i].weight<<"\n";
    
    for (int i = 1;i<201;i++)
    counter[i] += counter[i-1];
    // for (int i = 0;i<200;i++)
    // cout<<i-100<<" "<<counter[i]<<"\n";
    for (int i = 0;i<e;i++)
    {
        sorted_edges[--counter[unsorted_edges[i].weight+100]] = unsorted_edges[i]; 
    }

    ///////////////////////counting sort end/////////////////////
    if (type == 'u')
    {
        // cout<<"unsorted\n";
        // for (int i = 0;i<e;i++){
        //     cout<<i<<" "<<unsorted_edges[i].start<<" "<<unsorted_edges[i].end<<" "<<unsorted_edges[i].weight<<"\n";
        // }
        // cout<<"sorted\n";
        // for (int i = 0;i<e;i++){
        //     cout<<i<<" "<<sorted_edges[i].start<<" "<<sorted_edges[i].end<<" "<<sorted_edges[i].weight<<"\n";
        // }
        // cout<<"result:\n";
        for (int i = e-1;i>=0;i--){
            // cout<<i<<" "<<sorted_edges[i].start<<" "<<sorted_edges[i].end<<" "<<sorted_edges[i].weight<<"\n";
            // cout<<"for test\n";
            // cout<<sorted_edges[i].start;
            if(find(leader,sorted_edges[i].start) != find(leader,sorted_edges[i].end)) //two vertices of th edge are not connected yet
            { 
                sorted_edges[i].deleted = false;
                int start_root = find(leader,sorted_edges[i].start);
                int end_root = find(leader,sorted_edges[i].end);
                if(rank[start_root]>=rank[end_root]){ //start cover end
                    leader[end_root] = start_root;
                    rank[start_root]++;
                }


                else{
                    leader[start_root] = end_root;
                    rank[end_root]++;
                }
            }
        }
        bool flag = true;
        int total_weight = 0;
        for (int i = 0; i < e; i++)
        {
            if(sorted_edges[i].deleted)
            {
                flag = false;
                total_weight += sorted_edges[i].weight;
                }
            /* code */
        }
        // for(int i = 0;i<v;i++){
        //     cout<<leader[i]<<" ";
        // }
        // for(int i = 0;i<v;i++){
        //     cout<<rank[i]<<" ";
        // }
        if (flag)
        {
            fout<<"0";
            /* code */
        }
        else {
            fout<<total_weight<<"\n";
            for(int i=0 ;i<e;i++)
            {           
                if(sorted_edges[i].deleted) fout<<sorted_edges[i].start<<" "<<sorted_edges[i].end<<" "<<sorted_edges[i].weight<<"\n";
            }    
        }
    }
    else if(type == 'd'){
        // cout<<"todo :v";
        for (int i = e-1;i>=0;i--){
            // cout<<i<<" "<<sorted_edges[i].start<<" "<<sorted_edges[i].end<<" "<<sorted_edges[i].weight<<"\n";
            // cout<<"for test\n";
            // cout<<sorted_edges[i].start;
            if(find(leader,sorted_edges[i].start) != find(leader,sorted_edges[i].end)) //two vertices of th edge are not connected yet
            {
                
                sorted_edges[i].deleted_sort = false;
                sorted_edges[i].deleted = false;
                // sorted_edges[i].deleted_sort1 = false;
                // sorted_edges[i].deleted_random1 = false;
                int start_root = find(leader,sorted_edges[i].start);
                int end_root = find(leader,sorted_edges[i].end);
                if(rank[start_root]>=rank[end_root]){ //start cover end
                    leader[end_root] = start_root;
                    rank[start_root]++;
                }


                else{
                    leader[start_root] = end_root;
                    rank[end_root]++;
                }
            }
        }

        sortedalg(sorted_edges,v,e);
        //randomalg(sorted_edges,v,e,order);
        //sortedalg1(sorted_edges,v,e);
        int total_sorted = 0;
        int total_sorted1 = 0;
        int total_random1 = 0;
        for (int i = 0; i < e; i++)
        {   
            if(sorted_edges[i].deleted_sort) {total_sorted += sorted_edges[i].weight;}
            // else cout<<i<<" sorted added\n";
            if(sorted_edges[i].deleted_random1) {total_random1 += sorted_edges[i].weight;}
            if(sorted_edges[i].deleted_sort1) {total_sorted1 += sorted_edges[i].weight;}
            // else cout<<i<<" random added\n";
            /* code */
        }
        // cout<<total_sorted<<endl; //1267
        // cout<<total_sorted1<<endl; //
        // cout<<total_random1<<endl; //767
        
            fout<<total_sorted<<"\n";
            for(int i = 0;i<e;i++){
                if (sorted_edges[i].deleted_sort)
            {   
                fout<<sorted_edges[i].start<<" "<<sorted_edges[i].end<<" "<<sorted_edges[i].weight<<"\n";
                /* code */
            }
            }
        
        fout.close();
        // fout.open("./output1.out",ios::out);
        // fout<<total_sorted1<<"\n";
        //     for(int i = 0;i<e;i++){
        //         if (sorted_edges[i].deleted_sort1)
        //     {   
        //         fout<<sorted_edges[i].start<<" "<<sorted_edges[i].end<<" "<<sorted_edges[i].weight<<"\n";
        //         /* code */
        //     }
        //     }
        // fout.close();
        // fout.open("./output2.out",ios::out);
        // fout<<total_random1<<"\n";
        //     for(int i = 0;i<e;i++){
        //         if (sorted_edges[i].deleted_random1)
        //     {   
        //         fout<<sorted_edges[i].start<<" "<<sorted_edges[i].end<<" "<<sorted_edges[i].weight<<"\n";
        //         /* code */
        //     }
        //     }
        // fout.close();
    }
    
    
    

    return 0;   
}