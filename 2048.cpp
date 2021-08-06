#include "assignment.h"
#include "assignment.tab.hpp"

vector<vector<int>> board(5,vector<int>(5,0)); 
map<pair<int,int>,vector<string>> tile_names;

int assign_value(int value,int x,int y)
{
    if(x<1 || x>4 || y<1 || y>4)
    {
        return OUT_OF_BOUNDS;
    }
    if(value==0)
    {
        tile_names[{x,y}].clear();
    }
    board[--x][--y]=value;
    return SUCCESS;
}

void perform_move(vector<int> &arr,string* op1,string* direction1,int cord)
{
    string op= *op1;
    string direction= *direction1;
    int curr=0;
    map<int,vector<int>> m;
    for(int i=1;i<=3;i++)
    {
        if(arr[i]!=0 && arr[i]==arr[curr])
        {
            if(op=="SUBTRACT")
            {
                arr[curr]=0;
                arr[i]=0;
                if(direction=="LEFT" || direction=="RIGHT")
                {
                    for(auto k : m[curr+1])
                    {
                        tile_names[{cord,k}].clear();
                    }
                    for(auto k : m[i+1])
                    {
                        tile_names[{cord,k}].clear();
                    }
                    tile_names[{cord,curr+1}].clear();
                    tile_names[{cord,i+1}].clear();
                }
                else
                {
                    for(auto k : m[curr+1])
                    {
                        tile_names[{k,cord}].clear();
                    }
                    for(auto k : m[i+1])
                    {
                        tile_names[{k,cord}].clear();
                    }
                    tile_names[{curr+1,cord}].clear();
                    tile_names[{i+1,cord}].clear();
                }
                continue;
            }
            else if(op=="ADD")
            arr[curr]=arr[curr]*2;
            else if(op=="DIVIDE")
            arr[curr]=1;
            else if(op=="MULTIPLY")
            arr[curr]=arr[curr]*arr[curr];
            arr[i]=0;
            for(int j=0;j<m[i+1].size();j++)
            {
                m[curr+1].push_back(m[i+1][j]);
            }
            m[curr+1].push_back(i+1);
            m[i+1].clear();
            curr++;
        }
        if(arr[i]!=0)
        {
            if(arr[curr]!=0)
            {
                curr++;
            }
            if(i==curr)
            {
                continue;
            }
            for(int j=0;j<m[i+1].size();j++)
            {
                m[curr+1].push_back(m[i+1][j]);
            }
            arr[curr]=arr[i];
            arr[i]=0;
            m[curr+1].push_back(i+1);
            m[i+1].clear();
        }
    }
    for(auto i : m)
    {
        for(int j=0;j<i.second.size();j++)
        {
            //cout<<cord<<" "<<i.first<<" "<<i.second[j]<<" ";
            if(direction=="LEFT" || direction=="RIGHT")
            {
                for(int k=0;k<tile_names[{cord,i.second[j]}].size();k++)
                {
                    tile_names[{cord,i.first}].push_back(tile_names[{cord,i.second[j]}][k]);   
                }
                tile_names[{cord,i.second[j]}].clear();
            }
            else
            {
                for(int k=0;k<tile_names[{i.second[j],cord}].size();k++)
                {
                    tile_names[{i.first,cord}].push_back(tile_names[{i.second[j],cord}][k]);    
                }
                tile_names[{i.second[j],cord}].clear();
            }
            //cout<<"\n";
        }
        
    }
    if(direction=="RIGHT")
    {
        for(int i=1;i<3;i++)
        {
            vector<string> v;
            v=tile_names[{cord,5-i}];
            tile_names[{cord,5-i}]=tile_names[{cord,i}];    
            tile_names[{cord,i}]=v;
        }
    }
    else if(direction=="DOWN")
    {
        for(int i=1;i<3;i++)
        {
            vector<string> v;
            v=tile_names[{5-i,cord}];
            tile_names[{5-i,cord}]=tile_names[{i,cord}];    
            tile_names[{i,cord}]=v;
        }
    }  
}

void Do_move(string* op, string* direction)
{
    //cout<<"entered Do_move"<<"\n";
    if(*direction=="LEFT")
    {
        for(int i=0;i<4;i++)
        {
            vector<int> v;
            for(int j=0;j<4;j++)
            {
                v.push_back(board[i][j]);
            }
            //cout<<"perform_move call"<<"\n";
            perform_move(v,op,direction,i+1);
            //cout<<"perform move done\n";
            for(int j=0;j<4;j++)
            {
                board[i][j]=v[j];
            }
        }
    }
    else if(*direction=="RIGHT")
    {
        for(int i=0;i<4;i++)
        {
            vector<int> v;
            for(int j=0;j<4;j++)
            {
                v.push_back(board[i][4-j-1]);
            }
            for(int j=1;j<3;j++)
            {
                vector<string> temp;
                temp=tile_names[{i+1,5-j}];
                tile_names[{i+1,5-j}]=tile_names[{i+1,j}];    
                tile_names[{i+1,j}]=temp;
            }
            perform_move(v,op,direction,i+1);
            for(int j=0;j<4;j++)
            {
                board[i][j]=v[4-j-1];
            }
        }
    }
    else if(*direction=="UP")
    {
        for(int i=0;i<4;i++)
        {
            vector<int> v;
            for(int j=0;j<4;j++)
            {
                v.push_back(board[j][i]);
            }
            perform_move(v,op,direction,i+1);
            for(int j=0;j<4;j++)
            {
                board[j][i]=v[j];
            }
        }
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            vector<int> v;
            for(int j=0;j<4;j++)
            {
                v.push_back(board[4-1-j][i]);
            }
            for(int j=1;j<3;j++)
            {
                vector<string> temp;
                temp=tile_names[{5-j,i+1}];
                //cout<<temp.size()<<"\n";
                tile_names[{5-j,i+1}]=tile_names[{j,i+1}];    
                tile_names[{j,i+1}]=temp;
            }
            perform_move(v,op,direction,i+1);
            for(int j=0;j<4;j++)
            {
                board[j][i]=v[4-j-1];
            }
        }
    }
    free(direction);
    free(op);
    insert_random_tile();
}
int set_name(string* name,int x,int y)
{
    string curr=*name;
    x--;
    y--;
    if(board[x][y]==0)
    {
        cout<<"No tile present so name cannot be assigned\n";
        return FAILURE;
    }
    for(auto i : tile_names)
    {
        for(auto j : i.second)
        {
            if(j==curr)
            {
                cout<<"Name is already assigned to some tile\n ";
                return FAILURE;
            }
        }
    }
    tile_names[{++x,++y}].push_back(curr);
    free(name);
    return SUCCESS;
}
int get_value(int x,int y)
{
    if(x<1 || x>4 || y<1 || y>4)
    {
        return OUT_OF_BOUNDS;
    }
    cout<<"Value in x,y is "<<board[--x][--y]<<"\n";
    return SUCCESS;
}
bool is_possible_to_insert()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(board[i][j]==0)
            {
                return true;
            }                
        }
    }
    return false;
}
bool insert_random_tile()
{
    srand(time(0));
    if(!is_possible_to_insert())
    {
        return false;
    }   
    int x,y;
    while(true)
    {
        x= rand()%4;
        y= rand()%4;
        if(board[x][y]==0)
        {
                break;
        }
    }
    int value = (rand()%2)*2+2;
    assign_value(value,x+1,y+1);
    return true;
}
int print_output(int error_code)
{
    if(error_code==0)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                fprintf(stderr,"%d\40",board[i][j]);
            }
        }
        for(int i=1;i<5;i++)
        {
            for(int j=1;j<5;j++)
            {
                pair<int,int> posn = {i,j};
                if(tile_names[posn].size()>0)
                {
                    fprintf(stderr,"%d,%d",i,j);
                    int temp=tile_names[posn].size();
                    for(auto x:tile_names[posn])
                    {
                        char *ans = &x[0];
                        if(temp>1)
                        fprintf(stderr,"%s,",ans);
                        else
                        fprintf(stderr,"%s\40",ans);
                        temp--;
                    }
                }
            }
        }
        fprintf(stderr,"\n");
    }
    else
    {
        fprintf(stderr,"-1\n");
    }
    return 0;
}       
void printer()
{
    for(int i=0;i<4;i++)
    {
        cout<<"------------------------------------------------------------------\n";
        cout<<"|\t";
        for(int j=0;j<4;j++)
        {
            if(board[i][j]!=0)
                cout<<board[i][j]<<"\t|\t";
            else
                cout<<" "<<"\t|\t";
        }
        cout<<"\n";
    }
    cout<<"------------------------------------------------------------------\n";
}
void initialize()
{
    cout<<"2048> HI , THIS IS A 2048 GAME ENGINE.\n2048> TYPE THE COMMANDS FOLLOWED BY '.' AND KEYWORDS IN CAPITAL LETTERS.\n";
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
                board[i][j]=0;
                tile_names[{i,j}].clear();
        }
    }
    insert_random_tile();
    printer();
}
int main()
{
    initialize();
    while(1)
    {
        printf("2048 > Please type a command.\n");
        printf("----->");
        yyparse();
        printer();
    }
return 0;
}