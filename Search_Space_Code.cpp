/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
/* store locations? maybe? */
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <math.h>
#include <time.h>
using namespace std;

class node
{
    public:
    int* liz_x;
    int* liz_y;
    int* tree_x;
    int* tree_y;
    int depth;
    int num_of_trees;
    int liz_count;
    node()
    {

    }
    node(int p)
    {
        liz_count=p;
        liz_x=new int[p];
        liz_y=new int[p];
        for(int i=0;i<p;i++)
        {
            liz_x[i]=-1;
            liz_y[i]=-1;
        }
    }
    int insert_node(node* new_node)
    {
        new_node->tree_x=tree_x;
        new_node->tree_y=tree_y;
        new_node->depth=depth + 1;
        new_node->num_of_trees=num_of_trees;
        new_node->liz_count=liz_count;
    }
    int insert_xy(node* parent,int x, int y)
    {
        int i=0;
        while(parent->liz_x[i]!=-1)
        {
            liz_x[i]=parent->liz_x[i];
            liz_y[i]=parent->liz_y[i];
            i++;
        }
        liz_x[i]=x;
        liz_y[i]=y;
    }
    void copy_node(node* to_copy, int p)
    {
        tree_x=to_copy->tree_x;
        tree_y=to_copy->tree_y;
        depth=to_copy->depth;
        num_of_trees=to_copy->num_of_trees;
        liz_count=to_copy->liz_count;
        liz_x=new int[p];
        liz_y=new int[p];
        for(int i=0;i<p;i++)
        {
            liz_x[i]=to_copy->liz_x[i];
            liz_y[i]=to_copy->liz_y[i];
        }
    }
    ~node()
    {
        delete[] liz_x;
        delete[] liz_y;
    }
};

bool clashes_with_tree(node* parent_node, int x, int y)
{
    int j=0;
    int clash=0;
    while(j<parent_node->num_of_trees)
    {
        if(parent_node->tree_x[j]==x && parent_node->tree_y[j]==y)
        {
            clash=1;
            break;
        }
        j++;
    }
    if (clash==1) return true;
    return false;
}

bool clashes_with_tree(node* grid)
{
    for (int i=0;i<grid->liz_count;i++)
    {
        for(int k=0;k<grid->num_of_trees;k++)
        {
            if(grid->liz_x[i]==grid->tree_x[k] && grid->liz_y[i]==grid->tree_y[k]) return true;
        }
    }
    return false;
}

bool clashes_with_liz(node* grid)
{
    for (int i=0;i<grid->liz_count-1;i++)
    {
        for(int k=i+1;k<grid->liz_count;k++)
        {
            if(grid->liz_x[i]==grid->liz_x[k] && grid->liz_y[i]==grid->liz_y[k] && grid->liz_x[i]!=-1 && grid->liz_y[i]!=-1) return true;
        }
    }
    return false;
}

bool is_valid(node* parent_node, int x, int y)
{
    if (!clashes_with_tree(parent_node,x,y))
    {
        for(int i=0;i<parent_node->liz_count;i++)
        {
            if (parent_node->liz_x[i]==-1) break;
            if (parent_node->liz_x[i]==x && parent_node->liz_y[i]==y) return false;
            if (parent_node->liz_x[i]==x || parent_node->liz_y[i]==y)
            {
                int j=0;
                int tree_found=0;
                while(j<parent_node->num_of_trees)
                {
                    if(((parent_node->tree_x[j]==x) && ((parent_node->tree_y[j]>y && parent_node->tree_y[j]<parent_node->liz_y[i])||(parent_node->tree_y[j]<y && parent_node->tree_y[j]>parent_node->liz_y[i])))||((parent_node->tree_y[j]==y) && ((parent_node->tree_x[j]>x && parent_node->tree_x[j]<parent_node->liz_x[i])||(parent_node->tree_x[j]<x && parent_node->tree_x[j]>parent_node->liz_x[i]))))
                    {    
                        tree_found=1;
                        break;
                    }
                    j++;
                }
                if (tree_found==0) return false;
            }
            if ((abs(parent_node->liz_x[i]-x)==abs(parent_node->liz_y[i]-y))&&(parent_node->liz_x[i]!=-1 && parent_node->liz_y[i]!=-1))
            {
                int tree_found=0;
                int j=0;
                while(j<parent_node->num_of_trees)
                {
                    if ((abs(parent_node->liz_x[i]-parent_node->tree_x[j])==abs(parent_node->liz_y[i]-parent_node->tree_y[j])) && (abs(x-parent_node->tree_x[j])==abs(y-parent_node->tree_y[j])) && ((parent_node->tree_x[j]>parent_node->liz_x[i] && parent_node->tree_x[j]<x)||(parent_node->tree_x[j]<parent_node->liz_x[i] && parent_node->tree_x[j]>x)))
                    {
                        tree_found=1;
                        break;
                    }
                    j++; 
                }
                if (tree_found==0) return false;
            }
        }
        return true;
    }
    return false;
}

int check_liz_num(node* parent_node,int p)
{
    int ret=1;
    for (int i=0;i<p;i++)
    {
        if(parent_node->liz_x[i]==-1)
        {
            ret=0;
            break;
        }
    }
    return ret;
}

bool accept_prob(float temp, int delta)
{
    if(delta<0) return true;
    if(((float)rand()/RAND_MAX)<exp(-delta/temp)) return true;
    return false;
}

int num_of_attacks(node* grid)
{
    int num=0;
    for (int i=0;i<grid->liz_count-1;i++)
    {
        for(int k=i+1;k<grid->liz_count;k++)
        {
            if (grid->liz_x[i]==grid->liz_x[k] || grid->liz_y[i]==grid->liz_y[k])
            {
                int j=0;
                int tree_found=0;
                while(j<grid->num_of_trees)
                {
                    if(((grid->tree_x[j]==grid->liz_x[i]) && ((grid->tree_y[j]>grid->liz_y[i] && grid->tree_y[j]<grid->liz_y[k])||(grid->tree_y[j]<grid->liz_y[i] && grid->tree_y[j]>grid->liz_y[k])))||((grid->tree_y[j]==grid->liz_y[i]) && ((grid->tree_x[j]>grid->liz_x[i] && grid->tree_x[j]<grid->liz_x[k])||(grid->tree_x[j]<grid->liz_x[i] && grid->tree_x[j]>grid->liz_x[k]))))
                    {    
                        tree_found=1;
                        break;
                    }
                    j++;
                }
                if (tree_found==0) num++;
            }
            if ((abs(grid->liz_x[k]-grid->liz_x[i])==abs(grid->liz_y[k]-grid->liz_y[i])))
            {
                int tree_found=0;
                int j=0;
                while(j<grid->num_of_trees)
                {
                    if ((abs(grid->liz_x[k]-grid->tree_x[j])==abs(grid->liz_y[k]-grid->tree_y[j])) && (abs(grid->liz_x[i]-grid->tree_x[j])==abs(grid->liz_y[i]-grid->tree_y[j])) && ((grid->tree_x[j]>grid->liz_x[k] && grid->tree_x[j]<grid->liz_x[i])||(grid->tree_x[j]<grid->liz_x[k] && grid->tree_x[j]>grid->liz_x[i])))
                    {
                        tree_found=1;
                        break;
                    }
                    j++; 
                }
                if (tree_found==0) num++;
            }
        }
    }
    return num;
}

void generate_new_valid_grid(node* new_grid, int n)
{
    int rand_liz=rand() % new_grid->liz_count;

    while(true)
    {
        int cur_x=new_grid->liz_x[rand_liz];
        int cur_y=new_grid->liz_y[rand_liz];
        new_grid->liz_x[rand_liz]=rand() % n;
        new_grid->liz_y[rand_liz]=rand() % n;
        if (!clashes_with_tree(new_grid) && !clashes_with_liz(new_grid))
        {
            break;
        }
        new_grid->liz_x[rand_liz]=cur_x;
        new_grid->liz_y[rand_liz]=cur_y;
    }
}

int bfs(node* res_node,int p, int n, std::vector<int> t_x, std::vector<int> t_y, int last_try)
{
    if (p>n && t_x.size()==0) 
    {   
        return 0;
    }
    if(t_x.size()==(n*n))
    {
        return 0;
    }
    int* tree_x=new int[t_x.size()];
    int* tree_y=new int[t_y.size()];
    std::copy(t_x.begin(),t_x.end(),tree_x);
    std::copy(t_y.begin(),t_y.end(),tree_y);
    std::queue<node> node_queue;
    node* root=new node(p);
    root->depth=0;
    root->tree_x=tree_x;
    root->tree_y=tree_y;
    root->num_of_trees=t_x.size();
    node_queue.push(*root);
    int goal_found=0;
    int loop_count=0;
    time_t old_secs=time(NULL);
    while(node_queue.size()>0)
    {
        time_t new_secs=time(NULL);
        if(loop_count==1200000)
        {
            if((new_secs-old_secs)>=290)
            {
                delete[] tree_x;
                delete[] tree_y;
                return 0;
            }
            loop_count=1194000;
        }
        loop_count++;
        node* temp=&(node_queue.front());
        if (check_liz_num(temp,p))
        {
            goal_found=1;
            break;
        }
        int any_new=0;
        if(temp->depth<n)
        {
            for(int i=0;i<n;i++)
            {
                if(is_valid(temp,i,temp->depth))
                {
                    node* temp_push=new node(p);
                    temp->insert_node(temp_push);
                    temp_push->insert_xy(temp,i,temp->depth);
                    node_queue.push(*temp_push);
                    any_new=1;
                }
            }
            if (any_new==0 || last_try==1)
            {
                node* dummy_node=new node();
                dummy_node->copy_node(temp,p);
                dummy_node->depth+=1;
                node_queue.push(*dummy_node);
            }
        }
        else
        {
            if (t_x.size()>0)
            {
                for(int i=tree_x[temp->depth-n]+1;i<n;i++)
                {
                    if(is_valid(temp,i,tree_y[temp->depth-n]))
                    {
                        node* temp_push=new node(p);
                        temp->insert_node(temp_push);
                        temp_push->insert_xy(temp,i,tree_y[temp->depth-n]);
                        node_queue.push(*temp_push);
                        any_new=1;
                    }
                }
                if (any_new==0)
                {
                    if((temp->depth-n)<t_x.size())
                    {
                        node* dummy_node=new node();
                        dummy_node->copy_node(temp,p);
                        dummy_node->depth+=1;
                        node_queue.push(*dummy_node);
                    }
                }
            }
        }
        node_queue.pop();
    }
    if (goal_found==1)
    {
        res_node->copy_node(&(node_queue.front()),p);
        delete[] tree_x;
        delete[] tree_y;
        return 1;
    }
    delete[] tree_x;
    delete[] tree_y;
    return 0;
}

void bfs(int p, int n, std::vector<int> t_x, std::vector<int> t_y)
{
    node* res_node=new node();
    int w_o=0;
    if(bfs(res_node,p,n,t_x,t_y,0)) w_o=1;
    else if(t_x.size()>0 && bfs(res_node,p,n,t_y,t_x,0)) w_o=2;
         else if ((t_x.size()>0 && bfs(res_node,p,n,t_x,t_y,1))) w_o=1;
              else return;  
    ofstream output("output.txt");
    output<<"OK\n";
    int out_arr[n][n];
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            out_arr[i][j]=0;
        }
    }
    for (int i=0;i<p;i++)
    {
        if(w_o==1)out_arr[res_node->liz_x[i]][res_node->liz_y[i]]=1;
        else out_arr[res_node->liz_y[i]][res_node->liz_x[i]]=1;
    }
    for (int i=0;i<t_x.size();i++)
    {
        out_arr[t_x.at(i)][t_y.at(i)]=2;
    }
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            output<<out_arr[i][j];
        }
        output<<"\n";
    }
    output.close();
}

int dfs(node* res_node,int p, int n, std::vector<int> t_x, std::vector<int> t_y, int last_try)
{
    if (p>n && t_x.size()==0) 
    {    
        return 0;
    }
    if(t_x.size()==(n*n))
    {
        return 0;
    }
    int* tree_x=new int[t_x.size()];
    int* tree_y=new int[t_y.size()];
    std::copy(t_x.begin(),t_x.end(),tree_x);
    std::copy(t_y.begin(),t_y.end(),tree_y);
    std::stack<node> node_queue;
    node* root=new node(p);
    root->depth=0;
    root->tree_x=tree_x;
    root->tree_y=tree_y;
    root->num_of_trees=t_x.size();
    node_queue.push(*root);
    int goal_found=0;
    int loop_count=0;
    time_t old_secs=time(NULL);
    while(!node_queue.empty())
    {
        time_t new_secs=time(NULL);
        if(loop_count==1200000)
        {
            if((new_secs-old_secs)>=290) 
            {
                delete[] tree_x;
                delete[] tree_y;
                return 0;
            }
            loop_count=1194000;
        }
        loop_count++;
        node* temp=new node();
        temp->copy_node(&(node_queue.top()),p);
        if (check_liz_num(temp,p))
        {
            goal_found=1;
            break;
        }
        node_queue.pop();
        int any_new=0;
        if(temp->depth<n)
        {
            for(int i=0;i<n;i++)
            {
                if(is_valid(temp,i,temp->depth))
                {
                    node* temp_push=new node(p);
                    temp->insert_node(temp_push);
                    temp_push->insert_xy(temp,i,temp->depth);
                    node_queue.push(*temp_push);
                    any_new=1;
                }
            }
            if (any_new==0 || last_try==1)
            {
                node* dummy_node=new node();
                dummy_node->copy_node(temp,p);
                dummy_node->depth+=1;
                node_queue.push(*dummy_node);
            }
        }
        else
        {
            if (t_x.size()>0)
            {
                for(int i=tree_x[temp->depth-n]+1;i<n;i++)
                {
                    if(is_valid(temp,i,tree_y[temp->depth-n]))
                    {
                        node* temp_push=new node(p);
                        temp->insert_node(temp_push);
                        temp_push->insert_xy(temp,i,tree_y[temp->depth-n]);
                        node_queue.push(*temp_push);
                        any_new=1;
                    }
                }
                if (any_new==0)
                {
                    if((temp->depth-n)<t_x.size())
                    {
                        node* dummy_node=new node();
                        dummy_node->copy_node(temp,p);
                        dummy_node->depth+=1;
                        node_queue.push(*dummy_node);
                    }
                }
            }
        }
        delete temp;
    }
    if (goal_found==1)
    {
        res_node->copy_node(&(node_queue.top()),p);
        delete[] tree_x;
        delete[] tree_y;
        return 1;
    }
    delete[] tree_x;
    delete[] tree_y;
    return 0;
}

void dfs(int p, int n, std::vector<int> t_x, std::vector<int> t_y)
{
    node* res_node=new node();
    int w_o=0;
    if(dfs(res_node,p,n,t_x,t_y,0)) w_o=1;
    else if(t_x.size()>0 && dfs(res_node,p,n,t_y,t_x,0)) w_o=2;
         else if ((t_x.size()>0 && dfs(res_node,p,n,t_x,t_y,1))) w_o=1;
              else return;
    ofstream output("output.txt");
    output<<"OK\n";
    int out_arr[n][n];
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            out_arr[i][j]=0;
        }
    }
    for (int i=0;i<p;i++)
    {
        if(w_o==1)out_arr[res_node->liz_x[i]][res_node->liz_y[i]]=1;
        else out_arr[res_node->liz_y[i]][res_node->liz_x[i]]=1;
    }
    for (int i=0;i<t_x.size();i++)
    {
        out_arr[t_x.at(i)][t_y.at(i)]=2;
    }
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            output<<out_arr[i][j];
        }
        output<<"\n";
    }
    output.close();
}

void sa(int p, int n, std::vector<int> t_x, std::vector<int> t_y)
{
    if (p>n && t_x.size()==0) 
    {    
        return;
    }
    if(t_x.size()==(n*n))
    {
        return;
    }
    int* tree_x=new int[t_x.size()];
    int* tree_y=new int[t_y.size()];
    std::copy(t_x.begin(),t_x.end(),tree_x);
    std::copy(t_y.begin(),t_y.end(),tree_y);
    node* grid=new node(p);
    grid->depth=0;
    grid->tree_x=tree_x;
    grid->tree_y=tree_y;
    grid->num_of_trees=t_x.size();
    //generating random positions on grid
    for(int i=0;i<p;i++)
    {
        while(true)
        {
            grid->liz_x[i]=rand() % n;
            grid->liz_y[i]=rand() % n;
            if(!clashes_with_tree(grid) && !clashes_with_liz(grid))
            {
                break;
            }
        }
    }

    int cur_energy=num_of_attacks(grid);
    int z=1;
    int loop_count=0;
    time_t old_secs=time(NULL); 
    while(true)
    {
        time_t new_secs=time(NULL);
         
        if(loop_count==1200000)
        {   
            if((new_secs-old_secs)>=260)
            {
                delete[] tree_x;
                delete[] tree_y;
                delete grid;
                dfs(p,n,t_x,t_y);
                return;
            }
            loop_count=1194000;
        }
        loop_count++;
        float cur_temp=3.05/log(z+n);
        z++;
        if (cur_energy==0) break;
        node* new_grid=new node();
        new_grid->copy_node(grid,p);
        generate_new_valid_grid(new_grid,n);
        int new_energy=num_of_attacks(new_grid);
        if(accept_prob(cur_temp,(new_energy-cur_energy)))
        {
            grid->copy_node(new_grid,p);
            cur_energy=new_energy;
        }
        delete new_grid;
    }
    ofstream output("output.txt");
    if (cur_energy==0)
    {
        output<<"OK\n";
        node* res_node=grid;
        int out_arr[n][n];
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                out_arr[i][j]=0;
            }
        }
        for (int i=0;i<p;i++)
        {
            out_arr[res_node->liz_x[i]][res_node->liz_y[i]]=1;
        }
        for (int i=0;i<t_x.size();i++)
        {
            out_arr[t_x.at(i)][t_y.at(i)]=2;
        }
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                output<<out_arr[i][j];
            }
            output<<"\n";
        }
    }
    output.close();
    delete[] tree_x;
    delete[] tree_y;
    delete grid;
}

int main()
{
    string line;
    ifstream input("input.txt");
    ofstream output("output.txt");
    output<<"FAIL\n";
    output.close();
    if (input.is_open())
    {
        while(!input.eof())
        {
            int BFS=0,DFS=0,SA=0,n=-1,p=-1;
            getline(input,line);
            if (line=="BFS") BFS=1;
            if (line=="DFS") DFS=1;
            if (line=="SA") SA=1;
            getline(input,line);
            n=atoi(line.c_str());
            getline(input,line);
            p=atoi(line.c_str());
            std::vector<int> t_x;
            std::vector<int> t_y;
            for(int i=0;i<n;i++)
            {
                getline(input,line);
                for(int j=0;j<n;j++)
                {
                    if(line.at(j)=='2')
                    {
                        t_x.push_back(i);
                        t_y.push_back(j);
                    }
                }
            }
            if (BFS) bfs(p,n,t_x,t_y);//call BFS
            if (DFS) dfs(p,n,t_x,t_y);//call DFS
            if (SA) sa(p,n,t_x,t_y);//call SA
            t_x.erase(t_x.begin(),t_x.end());
            t_y.erase(t_y.begin(),t_y.end());
        }
        input.close();
    }
    else cout<<"Error opening file.\n";
    return 0;
}
