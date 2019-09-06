#pragma once
#pragma once
// Graph.h: interface for the C_arc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__06145978_4468_4D00_9396_E4C9FF455BF0__INCLUDED_)
#define AFX_GRAPH_H__06145978_4468_4D00_9396_E4C9FF455BF0__INCLUDED_

#if _MSC_VER > 1000 
#pragma once 
#endif 
#pragma  warning(disable:4786)

#include <map>
#include <vector>
#include <list>
#include <queue>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
//#include "properSA.h";
using namespace std;

#ifndef  INFINITE
#define  INFINITE         999999 
#endif 
#define  FALSE_NODE       999999
/*************Dynamic***************/
#define  FALSE_EDGE       999999
#define  ARRIVAL    1
#define  DEPARTURE  0

#define  Er_begin      40  //(Erlang)
#define  Er_end        600  //(Erlang)
#define  Er_pace       2000  //(Erlang)
#define  total_request_number 1000//00000
/********************************/

typedef  unsigned long    ULONG;
typedef  long double      LDOUBLE;
/*******************************************************************************************

*******************************************************************************************/
class C_edge
{
public:
	int			edge_id;
	int			edge_vertax_a;
	int			edge_vertax_b;
	double		edge_cost; //骨干链路代价设为1，方便按跳数找路
	double		edgeResource; //定义骨干链路带宽容量
	int      _Compute_FN; //Subha
	double    _availablility; //Subha
	double    FS_Array[400];   //Subha_Link_Resources
};
/****************SUBHA**********************/

class C_SEdge
{
public:
	int			edge_id;
	double		sEdgeResource; 
	double    _availablility; //Subha
	double    FS_Array[400];   //Subha_Link_Resources
	list<int>					embeddedVedgesList;//定义list存放该物理边中嵌入的虚拟边
	list<int>::iterator		embeddedVedgesListIterator;
};


class C_Compute_Node
{
public:
	ULONG   _node_i;
	int     _Compute_FN; //Subha
	int     _number_node;
	int     _node_degree;
	list<int>					embeddedVnodesList;
	list<int>::iterator		embeddedVnodesListIterator;
	//bool     _visited_mark;
	void operator = (const C_Compute_Node& O_Compute_Node)
	{
		_node_i = O_Compute_Node._node_i; //Subha
		_Compute_FN = O_Compute_Node._Compute_FN; //Subha
		_number_node = O_Compute_Node._number_node;
		_node_degree = O_Compute_Node._node_degree;
	}

};
/*****************************************************************/
class C_Compute_Node_resource_contrast :binary_function<const C_Compute_Node&, const C_Compute_Node&, bool>
{
public:
	bool operator()(const C_Compute_Node &a, const C_Compute_Node &b) const
	{
		return a._Compute_FN < b._Compute_FN;
	}
};

/********************** For Dynamic Traffic (C_event)*****************************/
//typedef  pair<ULONG, ULONG>   C_random_node_pair;
class C_event
{
  public:
	double   _time;//事件发生时间
	bool     _type;//ARRIVAL=1到达,DEPARTURE=0离去
	ULONG    _request_id;//请求标识
	double   _arrival_time;
	double   _holding_time;
	int      _random_vNetwork_id;
	//C_random_node_pair    _random_node_pair;

	C_event()
	{
		_time = 0.0;
		_type = DEPARTURE;
		_request_id = 0;
		_arrival_time = 0;
		_holding_time = 0;
		//_random_node_pair.first = FALSE_NODE;
		//_random_node_pair.second = FALSE_NODE;
	}
	void operator = (const C_event& O_event)
	{
		_time = O_event._time;
		_type = O_event._type;
		_request_id = O_event._request_id;
		_arrival_time = O_event._arrival_time;
		_holding_time = O_event._holding_time;
		//_random_node_pair = O_event._random_node_pair;
	}
};
class C_accepted_request
{
public:
	ULONG                _request_id;
	//	ULONG                _capacity;//请求带宽
	//	double               _arrival_time;
	//	double               _holding_time;
	// 	C_wave_list_pair          WP_wave_edge_list_pair;//pair<waveID, list<edgeID>>
	// 	C_wave_list_pair          BP_wave_edge_list_pair;//pair<waveID, list<edgeID>>
	// 	C_wave_list_pair          WP_wave_vertex_list_pair;//pair<waveID, list<vertexID>>
	// 	C_wave_list_pair          BP_wave_vertex_list_pair;//pair<waveID, list<vertexID>>
	// 	C_wave_list_pair_map      waveID_WP_edge_segment_map;//<segmentID,pair<waveID,WPlist>>
	// 	C_wave_list_pair_map      waveID_WP_vertex_segment_map;
	// 	C_wave_list_pair_map      waveID_BP_edge_segment_map;
	// 	C_wave_list_pair_map      waveID_BP_vertex_segment_map;
	// 	list<ULONG>          working_edge_list;//为edge_list
	// 	list<ULONG>          working_vertex_list;//为vertex_list
	// 	//用于path protection
	// 	list< ULONG >        backup_1_edge_list;//为edge_list
	// 	list< ULONG >        backup_1_vertex_list;//为vertex_list
	// 	list< ULONG >        backup_2_edge_list;//为edge_list
	// 	list< ULONG >        backup_2_vertex_list;//为vertex_list
	// 	//用于segment protection
	// 	C_working_list_map working_edge_list_map;//为edge_list组
	// 	C_working_list_map working_vertex_list_map;//为vertex_list组
	// 	C_backup_list_map  backup_1_edge_list_map;//为edge_list组
	// 	C_backup_list_map  backup_1_vertex_list_map;//为vertex_list组
	// 	C_backup_list_map  backup_2_edge_list_map;//为edge_list组
	// 	C_backup_list_map  backup_2_vertex_list_map;//为vertex_list组


};
typedef map< ULONG, C_accepted_request, less<ULONG> > C_accepted_request_map;//keyword:ULONG  _request_id;
typedef C_accepted_request_map::iterator            C_accepted_request_map_it;

/*******************************End of Dynamic Classes*************************************************/

/*******************************************************************************************
定义节点信息，用来后面不断改变节点信息
*******************************************************************************************/
class C_node
{
public:
	int			node_id; //骨干网络服务器节点编号
	int		nodeResource; //定义骨干节点资源容量
	int			pre_node;
	double		node_cost;
	double      path_cost;
	bool		node_visited;
};
/*******************************************************************************************
定义邻接表信息，放入adj_map中后，方便查找一个点的邻接表信息
*******************************************************************************************/
class C_adj
{
public:
	int		adj_node_id;
	int		adj_edge_id;
	double	adj_edge_cost;
	int      _Compute_FN; //Subha
	int     _Compute_FN_compare;
	int      _node_degree;;
	double    _availablility; //Subha
	double    FS_Array[400];
};
/******************************************************************************************
C_heap_vertex类说明：用于定义某节点的邻接节点堆中的一个邻接节点
******************************************************************************************/
class C_heap_node
{
public:
	int			node_id;
	double		cost_of_path;

};

/*
class C_heap_node_resource
{
public:
	int			node_id;
	int         _Compute_FN;

};  */

/*****************SUBHA ZONE****************************/


class C_Paths
{
public:
	int			path_id; 
	int			adj_edge;
	int         source_id;
	int         destination_id;
	double      path_distance;
	int         total_num_edges;
	//double		node_cost;
	//bool			node_visited;
};

/*class C_SEdge
{
public:
	int							sEdge_id;//实际上和edge_id完全相同，这里只是为了便于表达
	double                     Resource_FS_Array[400]; //定义骨干链路带宽容量
	int                        Free_FS;
	//list<int>					embeddedVedgesList;//定义list存放该物理边中嵌入的虚拟边
	//list<int>::iterator		embeddedVedgesListIterator;
};*/


/*
class C_heap_node_modified
{
public:
	int			node_id;
	double		cost_of_path;

};
*/
/******************************************************/
/******************************************************************************************
定义队列排序方法，用于在算法中根据cost进行比较
*******************************************************************************************/
/*
class C_heap_node_resource_contrast :binary_function < const C_heap_node_resource&, const C_heap_node_resource&, bool>// 前两个表示第一，第二个参数，bool 表示 operator的返回值
{
public:
	bool operator()(const C_heap_node_resource &a, const C_heap_node_resource &b) const

	{
		if (a._Compute_FN < b._Compute_FN)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
};
*/
/*************************************************************************/
class C_heap_node_contrast :binary_function < const C_heap_node&, const C_heap_node&, bool>// 前两个表示第一，第二个参数，bool 表示 operator的返回值
{
public:
	bool operator()(const C_heap_node &a, const C_heap_node &b) const

	{
		if (a.cost_of_path > b.cost_of_path)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
};

/***********************定义虚拟节点***********************/
class C_VNode
{
public:
	int							vNode_id;
	int							ontoSNode;
	int							vNodeDegree;
	int						vNodeResourceRequested;
	//int                         vNetwork_id;
	bool							visitedMark;
	list<int>					adjVnodeList;
	list<int>::iterator		adjVnodeListIterator;
};
/**************For sorting the V_node Requested Resources*************/

class C_VNode_requested_resource_contrast
{
public:
	bool operator()(const C_VNode &a, const C_VNode &b) const
	{
		return a.vNodeResourceRequested < b.vNodeResourceRequested;
	}
};



/********************定义堆虚拟节点***********************/
class C_heap_Vnode
{
public:
	int							vNode_id;
	int							vNodeDegree;
};

class C_heap_Vnode_contrast :binary_function < const C_heap_Vnode&, const C_heap_Vnode&, bool>
{
public:
	bool operator()(const C_heap_Vnode &a, const C_heap_Vnode &b) const

	{
		if (a.vNodeDegree > b.vNodeDegree)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
};

/***********************定义虚拟链路***********************/
class C_VEdge
{
public:
	int							vEdge_id;
	int							aVnode;						//	链路端点a
	int							bVnode;						//链路端点b
	int						vEdgeResourceRequested;		//虚拟链路资源消耗
	double                  availabilityRequired;
	
	list<int>					ontoPhyEdgeList;	//映射的物理链路list
	list<int>::iterator		ontoPhyEdgeListIterator;
	list<int>					ontoPathList;	
	list<int>::iterator		ontoPathListIterator;
	list<int>					FS_fIndex_list;
	list<int>::iterator		FS_fIndex_listIterator;
	list<int>					FS_lIndex_list;
	list<int>::iterator		FS_lIndex_listIterator;

	int                     PathList;
};
/***********************定义虚拟网************************/
class C_VNetwork
{
public:
	int							vNetwork_id;
	int							numOfVnode;					//包含虚拟节点的个数
	list<int>					containedVnodeList;		//包含的虚拟节点的list
	list<int>::iterator		containedVnodeListIterator;
	list<int>					containedVlinkList;			//包含的虚拟链路的list
	list<int>::iterator		containedVlinkListIterator;

};


class Path_Collection
{
public:
	int							path_id;
	//int							path_id_two;
	//int							path_id_three;
	int							first_fs;	//包含虚拟节点的个数
	int							last_fs;
	int                         path_src;
	int                         path_dst;
	//list<int>					containedVnodeList;		//包含的虚拟节点的list
	//list<int>::iterator		containedVnodeListIterator;
	//list<int>					containedVlinkList;			//包含的虚拟链路的list
	//list<int>::iterator		containedVlinkListIterator;

};

/******************************************************************************************
定义整张图的信息
******************************************************************************************/
class C_graph
{
public:
	int num_of_vertax;
	int num_of_edge;
	int src_node;
	int des_node;
	int path_number;

	ULONG   blocking_number;  //Dynamic
	C_accepted_request_map O_accepted_request_map;   //Dynamic
	ULONG                  reserved_total_capacity;  //Dynamic
	ULONG                  working_tatal_capacity;   //Dynamic
	ULONG                  total_recovery_nbr;       //Dynamic

	C_event       T_event;
	C_event       O_event;

#pragma region MyRegion

	//以下是edge_map中所会用到的信息
	bool Load_edge_graph();//声明一个函数，将edge的信息导入对应的map中
	C_edge							O_edge;
	map<int, C_edge>		O_edge_map;

	//以下是adj_map中所要用到的信息
	bool Load_adj_graph();
	//bool Load_Modified_adj_graph();
	bool Output_adj_map();
	C_adj												O_adj;

	list<C_adj>										O_adj_list;
	list<C_adj>::iterator							O_adj_list_iterator;

	map<int, list<C_adj>>					O_adj_map;
	map<int, list<C_adj>>::iterator		O_adj_map_iterator;

	map<int, C_edge>::iterator				O_edge_map_iterator;

	
	C_SEdge							O_SEdge;
	map<int, C_SEdge>		        O_SEdgeMap;
	map<int, C_SEdge>::iterator	     O_SEdgeMapIterator;


	//*************************************************************************//
	//typedef   map<ULONG, C_Compute_Node, less<ULONG> >     C_Compute_Node_map;
	//typedef   C_Compute_Node_map::iterator             C_Compute_Node_map_iterator;
	/****************************************************************************/
	C_Compute_Node                               O_Compute_Node;
	map<int, C_Compute_Node>					 O_Compute_Node_map;
	map<int, C_Compute_Node>::iterator			 O_Compute_Node_map_iterator;

	//C_Compute_Node_map            O_Compute_Node_map;
	//C_Compute_Node_map_iterator   O_Compute_Node_map_iterator;
	
	bool Load_compute_node_graph();
	
	
	//以下是找最短路函数所用到的信息
	bool Find_shortest_path(int src_node_id,  int des_node_id, int path_num);
	C_node									O_node;
	map<int, C_node>					O_node_map;
	
	
	map<int, C_node>::iterator		O_node_map_iterator;
	C_heap_node							O_heap_node;

	priority_queue<C_heap_node, vector<C_heap_node>, C_heap_node_contrast >		 O_heap_priority_queue;

	/*********************************************************************/
	/*
	C_heap_node_resource							O_heap_node_resource;

	priority_queue<C_heap_node_resource, vector<C_heap_node_resource>, C_heap_node_resource_contrast >		 O_heap_resource_priority_queue;
	*/
	/************************************************/
	bool Find_link_disjoint_path(int src_node_id, int des_node_id);
	
	/********************SUBHA ZONE************************/
	bool Output_paths_map();
	C_Paths                                               o_paths;
	list<C_Paths>									 o_paths_list;
	list<C_Paths>::iterator							 o_paths_list_iterator;

	map<int, list<C_Paths>>					o_paths_map;
	map<int, list<C_Paths>>::iterator		o_paths_map_iterator;
/*
	C_node_modified									O_node_modified;
	map<int, C_node_modified>					O_node_map_modified;

	
	map<int, C_node_modified>::iterator		O_node_map_iterator_modified;
	C_heap_node_modified							O_heap_node_modified;

	priority_queue<C_heap_node_modified, vector<C_heap_node_modified>, C_heap_node_contrast >		 O_heap_priority_queue_modified;

	*/
	/******************************************************/
	list<int>					failedVnetList;
	int                         total_backup=0;

	bool sEdgeResourceProvision();//将骨干链路资源信息由文件导入

	/*C_SEdge											O_SEdge;
	//map<int, C_SEdge>						O_SEdgeMap;
	//map<int, C_SEdge>::iterator			O_SEdgeMapIterator;
	list<C_SEdge>										O_SEdge_list;
	list<C_SEdge>::iterator							O_SEdge_list_iterator;

	map<int, list<C_SEdge>>						      O_SEdgeMap;
	map<int, list<C_SEdge>>::iterator			O_SEdgeMapIterator; */

	
	
	//输出最短路要用到的信息

	bool Out_put_shortest_path();

	list<int>					O_shortest_node_path_list;
	list<int>					O_shortest_edge_path_list;
	list<int>::iterator		O_shortest_node_path_list_iterator;
	list<int>::iterator		O_shortest_edge_path_list_iterator;

	//以下是寻找图中任意两点之间的最短路（以及链路分离所需要的信息）
	bool Find_any_pair_of_nodes_path();

	//用于建立list存放找出的路，以便计算各条路的连通性
	list<int>		a_route_node_list;
	list<int>		a_route_edge_list;
	list<int>		b_route_node_list;
	list<int>		b_route_edge_list;

#pragma endregion

	/**************************************************************************************************************************************/

	//单个虚拟拓扑生成
	bool singleVNetworkCreate(int numOfNode, double availability);
	int VM_id = 1;			//虚拟节点（虚拟机）的唯一编号，以此变量对所有虚拟机赋予唯一的id
	int VM_id_count;
	int VLink_id = 1;		//虚拟链路的唯一编号，以此变量对所有虚拟链路赋予唯一的id
	int VLink_id_count;
	int VNetwork_id = 1;	//虚拟网的唯一编号，以此变量对所有虚拟网络赋予唯一的id

	C_VNode											O_VNode;
	map<int, C_VNode>						O_VNodeMap;
	map<int, C_VNode>::iterator			O_VNodeMapIterator;

	C_VEdge											O_VEdge;
	map<int, C_VEdge>						O_VEdgeMap;
	map<int, C_VEdge>::iterator			O_VEdgeMapIterator;

	bool connectivityOfVnodes(int a, int b);//判断ab两点是否联通

	C_heap_Vnode									O_heap_Vnode;
	priority_queue<C_heap_Vnode, vector<C_heap_Vnode>, C_heap_Vnode_contrast >		 O_heap_Vnode_priority_queue;

	C_VNetwork										O_VNetwork;
	map<int, C_VNetwork>					O_VNetworkMap;
	map<int, C_VNetwork>::iterator		O_VNetworkMapIterator;

	Path_Collection                             O_Path_Collection;
	//map<int, Path_Collection>					O_Path_Collection_Map;
	//map<int, Path_Collection>::iterator		    O_Path_Collection_Map_Iterator;

	list<Path_Collection>									 O_Path_Collection_list;
	list<Path_Collection>::iterator							 O_Path_Collection_list_iterator;

	map<int, list<Path_Collection>>					O_Path_Collection_Map;
	map<int, list<Path_Collection>>::iterator		O_Path_Collection_Map_Iterator;


	bool allVNetworksGeneration(int totalNumOfVNet);
	bool sEdgeResourceUpdated();
	bool sNodeResourceUpdated();
	bool Output_Allpaths_map();
	int FS_modulationSelection(int distance, int bandwidth); // For selecting the proper modulation technique
	int Allocated_FS(int totalFS, int pathId, int srcId, int dstId); //For Cost Function, Proper RSA Selection and Final FS index
	LDOUBLE Availabilty_calculation(int pathId, int srcId, int dstId); //For availability calculation of Each path
	int singleVNetworkMapping(int vnetwork_id);
	bool allVNetworkMapping(int totalNumOfVnet);

	priority_queue<C_VNode, vector<C_VNode>, C_VNode_requested_resource_contrast>		O_VNode_requested_resource_queue;
	priority_queue<C_Compute_Node, vector<C_Compute_Node>, C_Compute_Node_resource_contrast>			O_Compute_Node_resource_queue;

	map<int, C_Compute_Node>			O_originalComputeNodeMap;
	map<int, C_VNode>					O_originalVNodeMap;//作为O_VNodeMap的备份
	map<int, C_VEdge>					O_originalVEdgeMap;//作为O_VEdgeMap的备份
	map<int, C_edge>					O_original_edge_map;//O_edge_map的备份，以备后面还原
	//map<int, list<C_adj>>               O_original_Sadj_map;
	map<int, C_SEdge>					O_originalSEdgeMap;


	/***********Dynamic*********/
	int Random_V_Network_ID();
    bool Arrival_event(C_event& O_event);
	bool Departure_event(C_event& O_event);
	//bool Arrival_event(O_event);
	double Exponential(double lamda);
	bool Simulation();
	bool singleVNetworkRelease(int vnetwork_id);
	bool checking();

};






#endif