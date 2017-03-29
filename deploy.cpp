#include "deploy.h"
#include "lib/lib_io.h"
#include<string.h>
#include<iostream>
#include <time.h>
using namespace std;

struct Edge
{
    int width;
    int cost;
    bool is_connect= false;
};
struct Cost_Edge
{
    int need;
    int net_id;
};

int vex_num;//网络节点数量
int edge_num;//网络链路数量
int consume_num;//消费节点数量
int one_sever_cost;//一台视频内容服务器部署成本
Edge *net_matrix[MAX_EDGE_NUM];  //邻接矩阵
Cost_Edge need[MAX_EDGE_NUM];        //需要的带宽

int gen_list[MAX_EDGE_NUM]; //基因评估对照表
int body_list[MAX_EDGE_NUM];//染色体评估对照表

int god_num=0; //神基因数量（单基因，一直遗传）
int god_code[MAX_EDGE_NUM];//神基因

int *body[MAX_EDGE_NUM];
int body_num;
void spfa()
{

}
//评估函数（最小费用流）
int evaluate(int *a_body)
{

}
//进化
void evolusion()
{

}
//自然选择
void select()
{

}
//交叉算子
void on_cross()
{

}
//
int cost()
{

}
bool is_content(int id,int index,int*sever)
{
    for(int i=0;i<god_num;i++)
    {
        if(id==god_code[i])
        {
            return true;
        }
    }
    for(int i=0;i<index;i++)
    {
        if(id==sever[i])
        {
            return true;
        }
    }
    return false;
}
void initGroup()
{
    int body_num=vex_num;
    for(int i=0;i<body_num;i++)
    {
        for(int j=0;j<vex_num;j++)
        {
            body[i][j]=0;
        }
    }
    //将神基因赋值为１
    for(int i=0;i<god_num;i++)
    {
        for(int j=0;j<body_num;j++)
        {
            body[j][god_code[i]]=1;
        }
    }
    for(int i=0;i<body_num;i++)
    {
        int auto_sever_num=rand()%(consume_num-god_num);
        int *sever=new int[auto_sever_num];
        int point=rand()%vex_num;//服务器点
        int index=0;
        while(index<auto_sever_num)
        {
            if(is_content(point,index,sever))
            {
                point=rand()%vex_num;
            }
            else
            {
                body[i][point]=1;
                sever[index]=point;
                index++;
            }
        }
    }
}

//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename) {
    init(topo, line_num);
    string output = to_string(consume_num);
    output += "\n\n";
    for (int i = 0; i < consume_num; i++) {
        output += to_string(need[i].net_id) + " " + to_string(i) + " " + to_string(need[i].need) + "\n";
    }
    cout << output;
    cout << "this is god:" << endl;
    for (int i = 0; i < god_num; i++) {
        cout << god_code[i] << " ";
    }

    const char *topo_file = output.c_str();
    write_result(topo_file, filename);
}

int main() {
    srand( (unsigned)time( NULL ) );
    char *topo[MAX_EDGE_NUM];
    char *topo_file="/home/cust/Desktop/case3.txt";
  //  cout << "enter input file" << endl;
  //  cin >> topo_file;
   // cout << "eter result file" << endl;
  //  cin >> result_file;
  //  int line_num = read_file(topo, MAX_EDGE_NUM, topo_file);
   // deploy_server(topo, line_num, "/home/cust/Desktop/resut.txt");
    return 0;
}

void init(char * topo[MAX_EDGE_NUM], int line_num)
{
    char *p;
    vex_num = atoi(strtok_r(topo[0], " ", &p));
    edge_num = atoi(strtok_r(p, " ", &p));
    consume_num = atoi(p);
    one_sever_cost = atoi(topo[2]);
    for(int i=0;i<vex_num;i++)
    {
        net_matrix[i]=new Edge[vex_num];
    }
    for(int i=4;i<edge_num+4;i++)
    {
        int begin=atoi(strtok_r(topo[i]," ",&p));
        int end=atoi(strtok_r(p," ",&p));
        int width=atoi(strtok_r(p," ",&p));
        int cost=atoi(p);
        net_matrix[begin][end].width=width;
        net_matrix[begin][end].cost=cost;
        net_matrix[begin][end].is_connect= true;

        net_matrix[end][begin].width=width;
        net_matrix[end][begin].cost=cost;
        net_matrix[end][begin].is_connect= true;
    }
    //初始化基因评估对照表
    for(int i=0;i<vex_num;i++)
    {
        int grade=0;
        int k=0;
        for(int j=0;j<vex_num;j++)
        {
            if(net_matrix[i][j].is_connect)
            {
                k++;
                grade+=net_matrix[i][j].width/net_matrix[i][j].cost;
            }

        }
        gen_list[i]=grade*(k/edge_num);
    }
    for(int i=edge_num+5;i<consume_num+edge_num+5;i++)
    {
        int consume_id=atoi(strtok_r(topo[i]," ",&p));
        int net_id=atoi(strtok_r(p," ",&p));
        int width=atoi(p);
        need[consume_id].net_id=net_id;
        need[consume_id].need=width;

        //初始化神个体
        int reply_width=0;
        for(int i=0;i<vex_num;i++)
        {
            if(net_matrix[net_id][i].is_connect)
            {
                reply_width+=net_matrix[net_id][i].width;
            }
        }
        if(reply_width<width)
        {
            god_code[god_num]=net_id;
            god_num++;
        }
    }
}