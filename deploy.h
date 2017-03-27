#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "lib_io.h"

void deploy_server(char * graph[MAX_EDGE_NUM], int edge_num, char * filename);
void init(char * topo[MAX_EDGE_NUM], int line_num);
void initGroup();
void evolusion();
void select();
void on_cross();

	

#endif
