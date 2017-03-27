#include "deploy.h"
#include "lib/lib_io.h"
#include<string.h>
#include<iostream>
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

int edge_of_net[MAX_EDGE_NUM];  //每个网络节点的边数
int list[MAX_EDGE_NUM]; //基因评估对照表

int *old_normal＿body[MAX_EDGE_NUM];
int *new_normal＿body[MAX_EDGE_NUM];           //服务节点染色体编码，每一行代表一条染色体
int gene_num[MAX_EDGE_NUM];               //每条染色体的基因数量

int normal_body_num; //正常个体数
int god_num=0; //神一样的个体数量（单基因，永生不死）
int god_code[MAX_EDGE_NUM];//神基因


//评估函数(评估每条染色体的优劣)
int evaluate(int *normal_body,int len)
{
    int grade = 0;
    for(int i=0;i<len;i++) {
        int net_id = normal_body[i];
        grade += list[net_id];
    }
    return  grade;
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

//杀死不合法的个体（１.路径不存在）
void kill_illigal(int *normal_body,int len)
{
    for(int i=0;i<len;i++)
    {

    }
}

void initGroup()
{
    int normal_num=consume_num-god_num-1;

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
    char *topo[MAX_EDGE_NUM];
    char *topo_file="/home/cust/Desktop/case3.txt";
  //  cout << "enter input file" << endl;
  //  cin >> topo_file;
   // cout << "eter result file" << endl;
  //  cin >> result_file;
    int line_num = read_file(topo, MAX_EDGE_NUM, topo_file);
    deploy_server(topo, line_num, "/home/cust/Desktop/resut.txt");
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
        list[i]=grade*(k/edge_num);
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