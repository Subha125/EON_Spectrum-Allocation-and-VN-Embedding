#include "head.h";
#include "Event.h";
//#include "properSA.h";
/**************************************Load the Input Network file************************************/

bool C_graph::Load_edge_graph()
{
	O_edge_map.clear();
	ifstream inputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\network_Modified.txt");

	if (!inputfile)						//如果文件为空，报错
	{
		cerr << "the file is empty" << endl;
		exit(1);
	}

	O_edge.edge_id = 0;
	O_edge.edge_vertax_a = 0;
	O_edge.edge_vertax_b = 0;
	O_edge.edge_cost = INFINITE;	//Initialize the value as Infinite
	O_edge._availablility = 0; //Subha
	inputfile >> num_of_vertax >> num_of_edge;

	while (!inputfile.eof())
	{
		inputfile >> O_edge.edge_id >> O_edge.edge_vertax_a >> O_edge.edge_vertax_b >> O_edge.edge_cost >> O_edge._availablility ;
		//for (int i = 0; i < 400; i++)
		//{
			//O_edge.FS_Array[i] = 1;   //Initialize All the FS of All the edges are Free/available. Available =1, Not available =0;  
		//}
		O_edge_map[O_edge.edge_id] = O_edge;
	}
	return true;

}

//******************************For Computing Capacity of Every Substrate Nodes**************************************//

bool C_graph::Load_compute_node_graph()
{
	O_Compute_Node_map.clear();
	ifstream inputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\Network_Node.txt");
	if (!inputfile)						
	{
		cerr << "the file is empty" << endl;
		exit(1);
	}
	int node_id, Compute_FN , node_degree;
	O_Compute_Node._node_i = 0;
	O_Compute_Node._Compute_FN = 0;
	O_Compute_Node._node_degree = 0;
	O_Compute_Node._number_node = 0;

	inputfile >> num_of_vertax;

	O_Compute_Node._number_node = num_of_vertax;
	while (!inputfile.eof())
	{
		inputfile >> node_id >> Compute_FN >> node_degree;
		O_Compute_Node._node_i = node_id;
		O_Compute_Node._Compute_FN = Compute_FN; //Subha
		O_Compute_Node._node_degree = node_degree;
		O_Compute_Node_map[O_Compute_Node._node_i] = O_Compute_Node;
	}

	return true;
}



/**********************************************************************************************
                       For Loading the Adjacent Graph
*********************************************************************************************/
bool C_graph::Load_adj_graph()
{
	O_adj_list.clear();
	O_adj_map.clear();//Clear all the values
	for (int i = 1; i <= num_of_vertax; i++)
	{    
		/*****************Putting the Computing Capacity of every Nodes***************/

		for (O_Compute_Node_map_iterator = O_Compute_Node_map.begin(); O_Compute_Node_map_iterator != O_Compute_Node_map.end(); O_Compute_Node_map_iterator++)
		{
			O_Compute_Node = O_Compute_Node_map_iterator->second;
			if (O_Compute_Node._node_i == i)
			{
				O_adj._Compute_FN = O_Compute_Node._Compute_FN;  
				O_adj._node_degree = O_Compute_Node._node_degree;
				//O_adj.n[O_adj.y] = O_Compute_Node._node_i;


			}



			continue;

		}

		/*****************************************************************************/
		for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++)
		{
			O_edge = O_edge_map_iterator->second;
			if (i == O_edge.edge_vertax_a)
			{
				O_adj.adj_node_id = O_edge.edge_vertax_b;
				O_adj.adj_edge_id = O_edge.edge_id;
				O_adj.adj_edge_cost = O_edge.edge_cost;
				O_adj._availablility = O_edge._availablility;
				/******************SubhaZone*******************/
				//for (int i = 0; i < 400; i++)
				//{
				//	O_adj.FS_Array[i] = O_edge.FS_Array[i];   //Putting the value of Each FS into adjacent Map
				//}
				
				/**********************************************/
				O_adj_list.push_front(O_adj);
			}
			else if (i == O_edge.edge_vertax_b)
			{
				O_adj.adj_node_id = O_edge.edge_vertax_a;
				O_adj.adj_edge_id = O_edge.edge_id;
				O_adj.adj_edge_cost = O_edge.edge_cost;
				O_adj._availablility = O_edge._availablility;
				/******************SubhaZone*******************/
				//for (int i = 0; i < 400; i++)
				//{
				//	O_adj.FS_Array[i] = O_edge.FS_Array[i];
				//}

				/**********************************************/
				O_adj_list.push_front(O_adj);
			}
			continue;
		}
		O_adj_map.insert(map<int, list<C_adj> >::value_type(i, O_adj_list));	//O_adj_map[i]=O_adj_list;
		O_adj_list.clear();
	}	
	//cout << "******************" << endl;
	return true;
}

/********************************************************************************************
					   For Loading the Modified_Adjacent Graph
*********************************************************************************************/
/*
bool C_graph::Load_Modified_adj_graph()
{
	for (int i = 1; i <= num_of_vertax; i++)
	{
		/*****************Putting the Computing Capacity of every Nodes**************

		for (O_adj_map_iterator = O_adj_map.begin(); O_adj_map_iterator != O_adj_map.end(); O_adj_map_iterator++)
		{
			O_adj._Compute_FN_compare = 0;

			if (O_adj_map_iterator->first == i)
			{

				O_heap_node_resource.node_id = i;
				O_heap_node_resource._Compute_FN = O_adj._Compute_FN;
				O_heap_resource_priority_queue.push(O_heap_node_resource);

			}
			continue;
		}
			
	}
	O_heap_node_resource = O_heap_resource_priority_queue.top();
	O_node = O_node_map[O_heap_node_resource.node_id];
	O_node.nodeResource = O_heap_node_resource._Compute_FN;
	while (O_heap_resource_priority_queue.size() != 0)
	{
		O_heap_resource_priority_queue.pop();
		//cout << "node ID:" << 
	}
	for (O_node_map_iterator = O_node_map.begin(); O_node_map_iterator != O_node_map.end(); O_node_map_iterator++)
	{
		O_node = O_node_map_iterator->second;
		cout << '\n';
		cout << "Node Id: " << O_node_map_iterator->first << '\t' << "Resource: " << O_node.nodeResource << endl;
	}
	cout << "******************" << endl;

	
	return true;
}
*/

/*********************************************************************************************/

/**********************************Checking Node Resources after mapping***************************/
bool C_graph::sNodeResourceUpdated()
{
	ofstream outputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\Updated_SNode_resource.txt");
	//for (int i = 1; i <= 43; i++)
	//{
	for (O_Compute_Node_map_iterator = O_Compute_Node_map.begin(); O_Compute_Node_map_iterator != O_Compute_Node_map.end(); O_Compute_Node_map_iterator++)
	{
		O_Compute_Node = O_Compute_Node_map_iterator->second;
		
		outputfile << '\n';

		outputfile << "sNode ID " << O_Compute_Node._node_i << "      " << "  sNode remaining resource is:  " << O_Compute_Node._Compute_FN << endl;
			
	}
	
	return true;
}
/******************************************************************************************************************************/

/********************************************************************************************
					   For Providing Resources on Edges
*********************************************************************************************/
bool C_graph::sEdgeResourceProvision()
{ 
	O_SEdgeMap.clear();
	ifstream inputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\input_edge_remaining_resource.txt");
	if (!inputfile)						//如果文件为空，报错
	{
		cerr << "the input_edge_remaining_resource file is empty" << endl;
		exit(1);
	}
	while (!inputfile.eof())
	{
		inputfile >> O_SEdge.edge_id; // >> O_SEdge.Free_FS;

		for (int i = 0; i < 320; i++)
		{
			O_SEdge.FS_Array[i] = 1;   //Initialize All the FS of All the edges are Free/available. Available =1, Not available =0;  
		}
		/*for (int i = 300; i < 400; i++)
	    {
			O_SEdge.FS_Array[i] = 0;   //Initialize All the FS of All the edges are Free/available. Available =1, Not available =0;  
		}*/
		int Free_FSlot = 0;
		for (int i = 0; i < 320; i++)
		{
			if ((O_SEdge.FS_Array[i]) == 1)
			{
				Free_FSlot = Free_FSlot + 1;
			}

		}
		O_SEdge.sEdgeResource = Free_FSlot;
		O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
		
		
	}

	//*****************输出骨干链路资源信息*************
	ofstream outputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\output_original_edge_resource.txt");
	//for (int i = 1; i <= 43; i++)
	//{
		for (O_SEdgeMapIterator = O_SEdgeMap.begin();  O_SEdgeMapIterator != O_SEdgeMap.end();  O_SEdgeMapIterator++)
		{
			O_SEdge = O_SEdgeMapIterator->second;
			outputfile << '\n';
			
				outputfile << "sEdge ID " << O_SEdge.edge_id << "      " << "  sEdge remaining resource is:  " << O_SEdge.sEdgeResource << endl;	
			
		}
			
	return true;
}
/*********************************************************************************************/
/******************************Checking Edge Resource after Mapping*********************************/

bool C_graph::sEdgeResourceUpdated()
{
	double final_resource=0;
	ofstream outputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\Updated_edge_resource.txt");
	//for (int i = 1; i <= 43; i++)
	//{
	for (O_SEdgeMapIterator = O_SEdgeMap.begin(); O_SEdgeMapIterator != O_SEdgeMap.end(); O_SEdgeMapIterator++)
	{
		
		O_SEdge = O_SEdgeMapIterator->second;
		int Free_FSlot = 0;
		for (int i = 0; i < 320; i++)
		{
			if ((O_SEdge.FS_Array[i]) == 1)
			{
				Free_FSlot = Free_FSlot + 1;
			}

		}
		O_SEdge.sEdgeResource = Free_FSlot;
		outputfile << '\n';

		outputfile << "sEdge ID " << O_SEdge.edge_id << "      " << "  sEdge remaining resource is:  " << ( 320 - O_SEdge.sEdgeResource) << endl;
		final_resource = final_resource + O_SEdge.sEdgeResource;
	}
	cout << '\n' << "final Resource = " << (13760 - final_resource) << endl;
	return true;
}

/**************************************************************************************************/

bool C_graph::Output_adj_map()//定义输出邻接表信息的函数
{
	ofstream outputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\output_adj.txt");
	outputfile << "num_of_node is " << num_of_vertax << "  num_of_edge is " << num_of_edge << endl;
	for (O_adj_map_iterator = O_adj_map.begin(); O_adj_map_iterator != O_adj_map.end(); O_adj_map_iterator++)
	{
		outputfile << "node " << O_adj_map_iterator->first << endl;
		O_adj_list = O_adj_map_iterator->second;
		for (O_adj_list_iterator = O_adj_list.begin(); O_adj_list_iterator != O_adj_list.end(); O_adj_list_iterator++)
		{
			O_adj = *O_adj_list_iterator;	
			/******************Counting the total number of Availabe FS for each Edges*******************/
			//int Free_FS = 0;
			//for (int i = 0; i < 400; i++)
			//{
			//	if ((O_adj.FS_Array[i]) == 1)
			//	{
			//		Free_FS = Free_FS + 1;
			//	}
			//}

			/*********************************************************************************************/
			
			
			outputfile << "next vertax: " << O_adj.adj_node_id << "	adj edge id: " << O_adj.adj_edge_id << "   adj cost: " << O_adj.adj_edge_cost << "  " << "  Availability of this Link :" << O_adj._availablility << endl;
		}
		outputfile << '\n';
		outputfile << "Computing Capacity of this node : " << O_adj._Compute_FN << '\n' << endl;
		outputfile << "Nodal Degree of this node : " << O_adj._node_degree << '\n' << endl;
	}
	return true;
}

/*****************************************************************************************************
                                      Find_shortestpath (One)
******************************************************************************************************/
bool C_graph::Find_shortest_path(int src_node_id, int des_node_id, int path_num)
{   
	// Subha for (int z = 1; z <= 24; z++)  
	// Subha {
		src_node = src_node_id;
		des_node = des_node_id;
		path_number = path_num;
		/*if (src_node_id == des_node_id)
		{
			cerr << "Source and destination can't be same" << endl;
			cout << "No path" << endl;
			system("pause");
			exit(1);
		} */
		O_node_map.clear();
		O_shortest_edge_path_list.clear();
		O_shortest_node_path_list.clear();
		for (int i = 1; i <= num_of_vertax; i++)	
		{
			O_node.pre_node = FALSE_NODE;
			O_node.node_cost = INFINITE;
			O_node.node_visited = false;
			O_node_map[i] = O_node;
		}																				///1_node_map

		C_node	O_next_node; 
		int		next_node_id;
		int		cur_node_id;
		/********************SUBHA ZONE****************************/
	//	C_node_modified	O_node_modified;
		//int		node_id_modified;

		/**********************************************************/
		O_node.pre_node = src_node;
		cur_node_id = src_node;
		O_node.node_cost = 0;
		O_node.node_visited = true;
		O_node_map[cur_node_id] = O_node;												///2node_map

	/********************************************Subha Zone_1*********************************************************/
		/*
		ifstream inputfile("E:\\MS MATERIALS\\C++ Codes\\VMmigration\\textfile\\New folder\\Output_Shortest_paths.txt");

		if (!inputfile)
		{
			cerr << "the file is empty" << endl;
		}
		int Exs_Src_Id , Exs_Dst_Id;
	inputfile >> Exs_Src_Id >> Exs_Dst_Id;

		while (!inputfile.eof())
		{
			//O_node_map_modified[node_id_modified] = inputfile >> O_node_modified.node_id;
			//inputfile >> O_edge.edge_id;

			//O_edge_map_modified[O_edge.edge_id] = O_edge;
		}
		/*
		if (src_node_id == Exs_Src_Id && des_node_id == Exs_Dst_Id)
		{
			cerr << "Shortest path already exists" << endl;
			cout << "No path" << endl;
			//cout << O_edge.edge_id <<'\n';
			system("pause");
			//O_adj_list = O_adj_map[O_edge.edge_id];

			//O_adj.adj_edge_cost = INFINITE;
			//exit(1);
		}
		*/
		/******************************************************************************/
		while (cur_node_id != des_node)
		{
			O_adj_list = O_adj_map[cur_node_id];
			for (O_adj_list_iterator = O_adj_list.begin(); O_adj_list_iterator != O_adj_list.end(); O_adj_list_iterator++)
			{
				next_node_id = (*O_adj_list_iterator).adj_node_id;
				O_next_node = O_node_map[next_node_id];
				O_node = O_node_map[cur_node_id];

				if (O_next_node.node_visited != true)
				{
					if ((O_node.node_cost + (*O_adj_list_iterator).adj_edge_cost) < O_next_node.node_cost)
					{
						O_next_node.node_cost = (O_node.node_cost + (*O_adj_list_iterator).adj_edge_cost);
						O_next_node.pre_node = cur_node_id;
						O_node_map[next_node_id] = O_next_node;
					}															     ///   node_visited
					
				}
                  //SUBHA O_node.path_cost = O_next_node.node_cost;
			}
			O_adj_list.clear();


			for (O_node_map_iterator = O_node_map.begin(); O_node_map_iterator != O_node_map.end(); O_node_map_iterator++)
			{
				O_node = O_node_map_iterator->second; //等价于 O_node = (*O_node_map_iterator).second; 
				if (O_node.node_visited != true)
				{
					O_heap_node.node_id = O_node_map_iterator->first;
					O_heap_node.cost_of_path = O_node.node_cost;  

					O_heap_priority_queue.push(O_heap_node);	

				}
			}
			O_heap_node = O_heap_priority_queue.top();		//
			O_node = O_node_map[O_heap_node.node_id];	//
			O_node.node_visited = true;								//这一段目的根据选出的cost最小的点，更改这个点的node_visited，
			//Subha O_node.path_cost = O_heap_node.cost_of_path;     //SUBHAAAAAAAAAAAAAAAAA
			cur_node_id = O_heap_node.node_id;				//同时改当前节点

			O_node_map[cur_node_id] = O_node;							      ///4、在3中更改完的相邻结点找出cost最小者，更改其标记node_visited
																			  ///   并将更改后的点放入O_node_map
			if (O_node.node_cost == INFINITE)//当再node_map中选出的最小代价点的cost为INFINIE时，说明源节点到不了这个结点，证明原图断开，所以返回false
			{
				// SUBHA cout << "there is no shortest path between source_node " << src_node << " destination_node " << des_node << endl;
				return false;
			}


			while (O_heap_priority_queue.size() != 0) //将堆空间清空
			{
				O_heap_priority_queue.pop();
			}
		}


		//*************************************************************以结点形式输出最短路
		cur_node_id = des_node;						//此时源节点等于目的结点
		while (cur_node_id != src_node)
		{
			O_shortest_node_path_list.push_front(cur_node_id);
			O_node = O_node_map[cur_node_id];
			cur_node_id = O_node.pre_node;
			if (cur_node_id == src_node)
			{
				O_shortest_node_path_list.push_front(cur_node_id);
			}
		}
		//开始输出结点形式最短路
		// SUBHA cout << "the src_node_id is  " << src_node << endl;
		//SUBHA cout << "the des_node_id is  " << des_node << endl;
		//SUBHA cout << "the shortest path in node is:  " << endl;
		//Subha//
/*SUBHAAA
		for (O_shortest_node_path_list_iterator = O_shortest_node_path_list.begin(); O_shortest_node_path_list_iterator != O_shortest_node_path_list.end(); O_shortest_node_path_list_iterator++)
		{
			cout << (*O_shortest_node_path_list_iterator);

			if ((*O_shortest_node_path_list_iterator) != des_node)
			{
				cout << "---";
			}
		}
		cout << endl;              */

		//***********************************************************以边的形式输出最短路
		cur_node_id = des_node; //因为经过结点形式输出最短路时，cur_node_id经过while循环已经等于src_node_id了，所以要重新将des_node_id赋给cur_node_id
		while (cur_node_id != src_node)
		{
			O_adj_list = O_adj_map[cur_node_id];
			O_node = O_node_map[cur_node_id];
			for (O_adj_list_iterator = O_adj_list.begin(); O_adj_list_iterator != O_adj_list.end(); O_adj_list_iterator++)
			{
				O_adj = *O_adj_list_iterator;

				if (O_adj.adj_node_id == O_node.pre_node)
				{
					O_shortest_edge_path_list.push_front(O_adj.adj_edge_id);
				}
				continue;
			}
			cur_node_id = O_node.pre_node;
		}
		//开始输出边形式最短路
	//SUBHA 	cout << "the shortest path in edge is:  " << endl;

	//	 Load_adj_graph(); //******COSTSubha
		o_paths.path_id = path_num;
		
		o_paths.source_id = src_node;
		o_paths.destination_id = des_node;
		//Subha o_paths.Path_cost = O_node.path_cost;
		for (O_shortest_edge_path_list_iterator = O_shortest_edge_path_list.begin(); O_shortest_edge_path_list_iterator != O_shortest_edge_path_list.end(); O_shortest_edge_path_list_iterator++)
		{
		 //SUBHA	cout << "---" << (*O_shortest_edge_path_list_iterator) ;

	       /********SUBHA ZONE***************/
			
			o_paths.adj_edge = *O_shortest_edge_path_list_iterator;
			o_paths_list.push_back(o_paths);
			//o_paths.adj_edge = INFINITE;
			/*********************************/
			continue;
		}
		//SUBHA cout <<'\n';
		//continue;
		
	// Subha}
	o_paths_map.insert(map<int, list<C_Paths> >::value_type(path_num, o_paths_list));
	   //Subha	
	o_paths_list.clear();


	//SUBHA    cout << endl << endl;;

	

	O_node_map.clear();
	return true;
}

/**********************************************************************************************
          Finding Link Disjoint Shortest paths (Number depends on the Input parameter)
***********************************************************************************************/

bool C_graph::Find_link_disjoint_path(int src_node_id, int des_node_id)
{
	for (O_shortest_edge_path_list_iterator = O_shortest_edge_path_list.begin(); O_shortest_edge_path_list_iterator != O_shortest_edge_path_list.end(); O_shortest_edge_path_list_iterator++)
	{
		O_edge = O_edge_map[*O_shortest_edge_path_list_iterator];
		O_edge.edge_cost = O_edge.edge_cost*INFINITE; //Putting the costs of the edges of Previous path as Infinite
		O_edge_map[*O_shortest_edge_path_list_iterator] = O_edge;
	}
	for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++) //loading the edge map again to update the changed Costs
	{
		O_edge = O_edge_map_iterator->second;
	//	cout << "edge_id: " << O_edge.edge_id << "   edge_vertax_a is: " << O_edge.edge_vertax_a << "  edge_vertax_b is: " << O_edge.edge_vertax_b << "	edge_cost is " << O_edge.edge_cost << endl;
	}
	//cout << endl;
	Load_adj_graph();
	for (O_adj_map_iterator = O_adj_map.begin(); O_adj_map_iterator != O_adj_map.end(); O_adj_map_iterator++) //loading the adj map again to update the changes
	{
		int i = 0;
		i = O_adj_map_iterator->first;
		O_adj_list = O_adj_map_iterator->second;
		//cout << i << endl;
		for (O_adj_list_iterator = O_adj_list.begin(); O_adj_list_iterator != O_adj_list.end(); O_adj_list_iterator++)
		{
			O_adj = *O_adj_list_iterator;
			//cout << O_adj.adj_node_id << "  " << O_adj.adj_edge_cost << endl;
		}
		//SUBHA cout << endl;
	}
	Find_shortest_path(src_node_id, des_node_id,1); //Call Find_shortest_path() function to calculate the next Shortest path (Link-Disjoint)
	return true;
}


/**********************************************For a particular Source and Destination ( No need)**************************************************************/

/*
bool C_graph::Output_paths_map()
{
	ofstream outputfile("E:\\MS MATERIALS\\C++ Codes\\VMmigration\\textfile\\New folder\\Output_Shortest_paths.txt");
	outputfile << src_node << "    " << des_node << '\n' << endl;
	cout << src_node << "    " << des_node << '\n' << endl;
	int i=1, j;
	//outputfile << path_num << "    ";
	for (o_paths_map_iterator = o_paths_map.begin(); o_paths_map_iterator != o_paths_map.end(); o_paths_map_iterator++)
	{
		outputfile << "path " << o_paths_map_iterator->first << endl;
		cout << "path " << o_paths_map_iterator->first << endl;
		o_paths_list = o_paths_map_iterator->second;

		//o_paths = *o_paths_list_iterator;	
		//outputfile << "Source" << '\t' << o_paths.source_id << '\t' << "Destination" << '\t' << o_paths.destination_id << '\t' << '\n';

		outputfile << "Source" << '\t' << o_paths.source_id << "        " << "Destination" << '\t' << o_paths.destination_id << '\t' << '\n';
		cout << "Source" << '\t' << o_paths.source_id << "        " << "Destination" << '\t' << o_paths.destination_id << '\t' << '\n';
		for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
		{
			o_paths = *o_paths_list_iterator;	
			
			//outputfile << "Source" << '\t' << o_paths.source_id << '\t' << "Destination" << '\t' << o_paths.destination_id << '\t' << '\n';
			
					outputfile << " " << o_paths.adj_edge;
					cout << " " << o_paths.adj_edge;
					//outputfile << '\n';
				
			//
		}
		outputfile << '\n';
		cout << '\n';
	}
	return true;
}

/**********************************************************************************************************************************************************/  


/*****************************************************************************************************************************
**********************************************All_disjoint_Shortest_paths_All nodes*******************************************
******************************************************************************************************************************/
bool C_graph::Output_Allpaths_map()
{
	int num_paths;
	cout << "Please enter the maximum number of paths you want: ";
	cin >> num_paths;
	int required_BW;
	cout << "Please enter the required Bandwidth: ";
	cin >> required_BW;
	ofstream outputfile5("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\Output_Allpaths_map.txt");
	//o_paths.Path_cost = 0;
	int i = 1, j, k;
	for (i = 1; i <= 24; i++)
	{                                                      // From every Source nodes to every Destination Nodes
		for (j = 1; j <= 24; j++)
		{
			Load_edge_graph();

			Load_adj_graph();
			if (i != j)
			{
				for (k = 1; k <= num_paths; k++)
				{

					Find_shortest_path(i, j, k);

					Find_link_disjoint_path(i, j);
				}

				
				for (o_paths_map_iterator = o_paths_map.begin(); o_paths_map_iterator != o_paths_map.end(); o_paths_map_iterator++)
				{
					double Path_Dist = 0;
					int totEdges = 0;
					o_paths.path_distance = 0;
					o_paths.total_num_edges = 0;
					//o_paths.Path_cost = 0;
					o_paths_list = o_paths_map_iterator->second;
					
					outputfile5 << "Source" << '\t' << o_paths.source_id << "        " << "Destination" << '\t' << o_paths.destination_id << '\t' << '\n';
					cout << "Source" << '\t' << o_paths.source_id << "        " << "Destination" << '\t' << o_paths.destination_id << '\t' << '\n';
					outputfile5 << "path " << o_paths_map_iterator->first << endl;
					cout << "path " << o_paths_map_iterator->first << endl;
					for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
					{
						//o_paths.path_distance = 0;
						//o_paths.total_num_edges = 0;
						o_paths = *o_paths_list_iterator;
						outputfile5 << "  " << o_paths.adj_edge;
						cout << "  " << o_paths.adj_edge;
						Load_edge_graph();
						for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++) 
						{
							//o_paths.path_distance = 0;
							
							O_edge = O_edge_map_iterator->second;
							if (O_edge.edge_id == o_paths.adj_edge)
							{
								Path_Dist = Path_Dist + O_edge.edge_cost;
							}
							else
								continue;
						}
						
						for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++)
						{
							//o_paths.total_num_edges = 0;
							O_edge = O_edge_map_iterator->second;
							if (O_edge.edge_id == o_paths.adj_edge)
							{
								totEdges = totEdges + 1;
							}
							else
								continue;
						}

					}
					
						outputfile5 << '\n';
						cout << '\n';
						outputfile5 << "Total Distance of this path: " << Path_Dist << " KM " << endl;
						cout << "Total Distance of this path: " << Path_Dist << " KM " << endl;
						o_paths.path_distance = Path_Dist;
						outputfile5 << '\n';
						cout << '\n';
						//outputfile5 << o_paths.path_distance;
						//outputfile5 << '\n';
						outputfile5 << "Total number of edges of this path : " << totEdges << endl;
						cout << "Total number of edges of this path : " << totEdges << endl;
						o_paths.total_num_edges = totEdges;
						outputfile5 << '\n';
						cout << '\n';
						//outputfile5 << o_paths.total_num_edges;
						//outputfile5 << '\n';
				    	int z= FS_modulationSelection(o_paths.path_distance, required_BW);
						outputfile5 << "Required FS for this requested Bandwidth (" << required_BW << " GB) is: " << z << endl;
						cout << "Required FS for this requested Bandwidth (" << required_BW << " GB) is: " << z << endl;
						if ((o_paths.source_id == 24) && (o_paths.destination_id == 21) && (o_paths_map_iterator->first == 2))
						{
							int F_index =  Allocated_FS(z, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
							outputfile5 << "Final first Index of Frequency slot for this requirement is: " << F_index << endl;
					    }
						
						LDOUBLE availability = Availabilty_calculation(o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
						outputfile5 << "Availability of this path is: " << availability << endl;
					// Allocated_FS(z, o_paths_map_iterator->first, 1, 5);
					outputfile5 << '\n' << '\n';
					cout << '\n' << '\n';
				}

				

				o_paths_map.clear();
				o_paths_list.clear();
			}
			else
				continue;
		}
	}

	return true;
}

/******************************************************************Creation of Virtual Networks*******************************************************************************/


/******************************************************************************************************
                             Virtual Nodes Connectivity
*******************************************************************************************************/
bool C_graph::connectivityOfVnodes(int a, int b)
{
	list<int>					markList; //临时定义的list用来记录寻找可达节点被标记为true（访问过）的虚拟节点
	list<int>::iterator		markListIterator;
	O_VNode = O_VNodeMap[a];
	O_VNode.visitedMark = true;
	O_VNodeMap[a] = O_VNode;
	markList.push_back(a);
	for (markListIterator = markList.begin(); markListIterator != markList.end(); markListIterator++)
	{
		O_VNode = O_VNodeMap[*markListIterator];
		for (O_VNode.adjVnodeListIterator = O_VNode.adjVnodeList.begin(); O_VNode.adjVnodeListIterator != O_VNode.adjVnodeList.end(); O_VNode.adjVnodeListIterator++)
		{
			C_VNode T_VNode;
			T_VNode = O_VNodeMap[*O_VNode.adjVnodeListIterator];
			if (T_VNode.visitedMark == false)//标记为false的节点表示没有访问过
			{
				markList.push_back(T_VNode.vNode_id);//将没有访问过的（false）节点放入markList
				T_VNode.visitedMark = true;//将访问过的节点标记改为true
				O_VNodeMap[T_VNode.vNode_id] = T_VNode;
			}
		}
	}
	//判断完a(形参)到b(形参)的连通性，再将所有O_VNode的vistedMark全部重置为false；否则所有虚拟网内节点的vistedMark第一次就会被该函数全置为true，后面就无法在通过visitedMark判断哪些节点被访问过
	for (O_VNodeMapIterator = O_VNodeMap.begin(); O_VNodeMapIterator != O_VNodeMap.end(); O_VNodeMapIterator++)
	{
		O_VNode = O_VNodeMapIterator->second;
		O_VNode.visitedMark = false;
		O_VNodeMap[O_VNode.vNode_id] = O_VNode;
	}
	for (markListIterator = markList.begin(); markListIterator != markList.end(); markListIterator++)
	{
		if (*markListIterator == b)
		{
			return true;
		}
	}
	markList.clear();


	return false;
}

/******************************************************************************************************
                          Single Virtual Network Creation
*******************************************************************************************************/
bool C_graph::singleVNetworkCreate(int randNumOfVnode , double availability)	//输入为已知该虚拟网节点个数，为randNumOfNnode
{
	

	VM_id_count = VM_id;
	VLink_id_count = VLink_id;

	//每生成一个虚拟网首先要对其每个虚拟节点赋予唯一的vNode_id，然后务必将所有O_VNode有关成员变量全部初始化，要不然会残留上一个虚拟网的数据
	for (int i = 1; i <= randNumOfVnode; i++)
	{
		O_VNode.vNode_id = VM_id;		//对虚拟节点赋予唯一的虚拟机id
		O_VNode.adjVnodeList.clear();
		O_VNode.visitedMark = false;
		O_VNode.vNodeDegree = 0;
		O_VNode.ontoSNode = 0;
		VM_id++;
		int resource = rand() % 4 + 2;  //It will generate the random requested gresources from 7 to 10 units
		O_VNode.vNodeResourceRequested = resource;
		O_VNodeMap[O_VNode.vNode_id] = O_VNode;
	}
	//开始根据概率确定两个虚拟节点之间是否存在虚拟链路，生成O_VNodeMap和O_VEdgeMap
	/******************Providing Availability randomly**********/
	
	
	/****************************************/
	for (int i = VM_id_count; i < VM_id - 1; i++)
	{
		for (int j = i + 1; j < VM_id; j++)
		{
			if ((rand() / double(RAND_MAX))> 0.5)//虚拟节点i，j之间以0.5的概率生成虚拟链路
			{
				//一旦确定有边，及时修改O_VNode的有关数据***********
				O_VNode = O_VNodeMap[i];
				O_VNode.adjVnodeList.push_back(j);	//确定i的邻接虚拟节点有j
				O_VNode.vNodeDegree++;				//结点i的度数加1
				O_VNodeMap[i] = O_VNode;
				O_VNode.adjVnodeList.clear();//因为在清空之前，该list中的数据已经存到了相应map中

				O_VNode = O_VNodeMap[j];
				O_VNode.adjVnodeList.push_back(i);	//确定j的邻接虚拟节点有i
				O_VNode.vNodeDegree++;				//结点j的度数加1
				O_VNodeMap[j] = O_VNode;
				O_VNode.adjVnodeList.clear();//因为在清空之前，该list中的数据已经存到了相应map中
				
											 
				/********************************************/
				
				/*******************************************/
				//一旦确定有边，及时修改O_VEdge的有关数据***********
				O_VEdge.vEdge_id = VLink_id;	//对生成的虚拟链路赋予唯一的链路id
				VLink_id++;
				O_VEdge.aVnode = i;
				O_VEdge.bVnode = j;
				O_VEdge.vEdgeResourceRequested = rand() % 387 + 14;
				
				O_VEdge.availabilityRequired = availability;
				O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;
			}
		}
	}



	//开始判断生成的网络是否连通，并采取措施使之连通
#pragma region MyRegion

	//将虚拟节点放入堆中，按照制定好的规则：从上至下，节点度数依次增大
	for (int i = VM_id_count; i < VM_id; i++)
	{
		O_heap_Vnode.vNode_id = i;
		O_VNode = O_VNodeMap[i];
		O_heap_Vnode.vNodeDegree = O_VNode.vNodeDegree;
		O_heap_Vnode_priority_queue.push(O_heap_Vnode);
	}

	//从小度数节点开始检查生成的网络是否联通，如果不连通，就选取度数最小的两个点添加虚拟链路
	O_heap_Vnode = O_heap_Vnode_priority_queue.top();
	O_VNode = O_VNodeMap[O_heap_Vnode.vNode_id];
	int tempA = O_VNode.vNode_id;
	O_heap_Vnode_priority_queue.pop();
	int tempB;
	while (O_heap_Vnode_priority_queue.size() != 0)
	{
		O_heap_Vnode = O_heap_Vnode_priority_queue.top();
		O_VNode = O_VNodeMap[O_heap_Vnode.vNode_id];
		tempB = O_VNode.vNode_id;
		if (connectivityOfVnodes(tempA, tempB) == false)//如果tempA和tempB之间不连通
		{
			//cout << tempA << "   and   " << tempB << "       NOT  interconneted" << endl;

			//连接新的边，修改O_VNode邻接节点list的有关数据
			O_VNode = O_VNodeMap[tempA];
			O_VNode.adjVnodeList.push_back(tempB); //在tempA的邻接节点list中加入tempB
			O_VNode.vNodeDegree++;
			O_VNodeMap[tempA] = O_VNode;
			O_VNode.adjVnodeList.clear();

			O_VNode = O_VNodeMap[tempB];
			O_VNode.adjVnodeList.push_back(tempA); //在tempB的邻接节点list中加入tempA
			O_VNode.vNodeDegree++;
			O_VNodeMap[tempB] = O_VNode;
			O_VNode.adjVnodeList.clear();

			//连接新的边，修改O_VEdge的有关数据
			O_VEdge.vEdge_id = VLink_id;	//对新添加的虚拟链路赋予唯一的链路id
			VLink_id++;
			O_VEdge.aVnode = tempA;
			O_VEdge.bVnode = tempB;
			O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

		}
		O_heap_Vnode_priority_queue.pop();
	}

#pragma endregion

	return true;
}

/******************************************************************************************************
                                      VNetworkMap
*******************************************************************************************************/
bool C_graph::allVNetworksGeneration(int totalNumOfVnet)
{
	ofstream outputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\output_Final_allVNets_map_connection.txt");
	ofstream outputfile1("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\output_Final_allVNets_map_containednode.txt");
	//ofstream outputfile2("E:\\1-vs-code\\VMmigration\\textfile\\output_step_O_VNodeMap.txt");
	ofstream outputfile3("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\output_Final_O_VNodeMap.txt");
	//ofstream outputfile4("E:\\1-vs-code\\VMmigration\\textfile\\output_step_all_connectivity.txt");
	ofstream outputfile5("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\output_Final_O_VEdgeMap.txt");
	srand(time(NULL));
	for (int i = 0; i < totalNumOfVnet; i++) //产生totalNumOfVnet个虚拟网
	{
		cout << "Virtual Network  " << i + 1 << "   Generated Successfully" << endl;
		O_VNetwork.vNetwork_id = VNetwork_id;
		VNetwork_id++;
		
		int a = rand() % 4 + 2; 
		//int j = rand() % 100 + 1;
		double avail;
		if (VNetwork_id >= 1 && VNetwork_id <=68)
		{
			avail = 0.99;
		}
		else if (VNetwork_id >= 69 && VNetwork_id <= 102)
		{
			avail = 0.995;
		}
		else if (VNetwork_id >= 103 && VNetwork_id <= 124)
		{
			avail = 0.999;
		}
		else if (VNetwork_id >= 125 && VNetwork_id <= 129)
		{
			avail = 0.9995;
		}
		else if (VNetwork_id >= 130 && VNetwork_id <= 10000)
		{
			avail = 0.9999;
		}
		/*else if (j == 99)
		{
			avail = 0.9995;
		}
		else if (j == 100)
		{
			avail = 0.9999;
		}*/
		singleVNetworkCreate(a , avail);

		//*********每生成一个虚拟网就将此时的O_VNodeMap输出，对应于outputfile2("E:\\1-vs-code\\VMmigration\\textfile\\output_step_O_VNodeMap.txt");
#pragma region MyRegion
		/*
		for (O_VNodeMapIterator = O_VNodeMap.begin(); O_VNodeMapIterator != O_VNodeMap.end(); O_VNodeMapIterator++)
		{
			O_VNode = O_VNodeMapIterator->second;
			outputfile2 << "O_VNode_id: " << O_VNode.vNode_id << "      visitedMark: " << O_VNode.visitedMark << "   adjO_VNodelist:  ";
			for (O_VNode.adjVnodeListIterator = O_VNode.adjVnodeList.begin(); O_VNode.adjVnodeListIterator != O_VNode.adjVnodeList.end(); O_VNode.adjVnodeListIterator++)
			{
				outputfile2 << (*O_VNode.adjVnodeListIterator) << "      ";
			}
			outputfile2 << endl;
		}
		outputfile2 << "***************************************************************************" << endl;
		*/
#pragma endregion
		//*********每生成一个虚拟网就测试connectivity函数，对应于outputfile4("E:\\1-vs-code\\VMmigration\\textfile\\output_step_all_connectivity.txt");
#pragma region MyRegion
		/*
		for (int i = VM_id_count; i<VM_id - 1; i++)
		{
			for (int j = i + 1; j<VM_id; j++)
			{
				if (connectivityOfVnodes(i, j) == false)
				{
					outputfile4 << i << "  " << j << "      is NOT interconnected" << endl;
				}
			}
		}
		outputfile4 << "*******************************************************" << endl;
		*/
#pragma endregion

		O_VNetwork.numOfVnode = a;
		for (int j = VM_id_count; j < VM_id; j++)
		{
			O_VNetwork.containedVnodeList.push_back(j);
		}
		for (int k = VLink_id_count; k < VLink_id; k++)
		{
			O_VNetwork.containedVlinkList.push_back(k);
		}
		O_VNetworkMap[O_VNetwork.vNetwork_id] = O_VNetwork;
		O_VNetwork.containedVlinkList.clear();
		O_VNetwork.containedVnodeList.clear();
	}

	
	
		

	/******************************************************************************************************/

	//*********最终的的O_VNodeMap_Final输出
#pragma region MyRegion
  
	



	    for (O_VNodeMapIterator = O_VNodeMap.begin(); O_VNodeMapIterator != O_VNodeMap.end(); O_VNodeMapIterator++)
	    {
		
		
		  O_VNode = O_VNodeMapIterator->second;
		 // outputfile3 << "Virtual Network ID:" << O_VNode.vNetwork_id <<'\n';
		  outputfile3 << "O_VNode_id: " << O_VNode.vNode_id << "    vNodeDgree:  " << O_VNode.vNodeDegree << "      visitedMark: " << O_VNode.visitedMark << "     vNodeResourceRquested:  " << O_VNode.vNodeResourceRequested << "   adjO_VNodelist:  ";
		    for (O_VNode.adjVnodeListIterator = O_VNode.adjVnodeList.begin(); O_VNode.adjVnodeListIterator != O_VNode.adjVnodeList.end(); O_VNode.adjVnodeListIterator++)
		    {
			outputfile3 << (*O_VNode.adjVnodeListIterator) << "      ";
			//outputfile3 << "Virtual Network ID:" << O_VNetworkMapIterator->first << '\n';
		    }
		  
		   outputfile3 << endl;
	    }
  
  
	outputfile3 << "***************************************************************************" << endl;
#pragma endregion

	for (O_VEdgeMapIterator = O_VEdgeMap.begin(); O_VEdgeMapIterator != O_VEdgeMap.end(); O_VEdgeMapIterator++)
	{
		O_VEdge = O_VEdgeMapIterator->second;
		outputfile5 << "O_VEdge_id is:  " << O_VEdge.vEdge_id << "    edgeResourceRequested is:  " << O_VEdge.vEdgeResourceRequested << "   Availability Requirement :   " << O_VEdge.availabilityRequired << endl;
	}

	//**********最终O_VNetworkMap以及边的连接情况
	for (O_VNetworkMapIterator = O_VNetworkMap.begin(); O_VNetworkMapIterator != O_VNetworkMap.end(); O_VNetworkMapIterator++)
	{
		O_VNetwork = O_VNetworkMapIterator->second;
		outputfile << "vnetwork id is:   " << O_VNetwork.vNetwork_id << "     number of node included is   " << O_VNetwork.numOfVnode << endl;
		for (O_VNetwork.containedVlinkListIterator = O_VNetwork.containedVlinkList.begin(); O_VNetwork.containedVlinkListIterator != O_VNetwork.containedVlinkList.end(); O_VNetwork.containedVlinkListIterator++)
		{
			O_VEdge = O_VEdgeMap[(*O_VNetwork.containedVlinkListIterator)];
			outputfile << O_VEdge.aVnode << " " << O_VEdge.bVnode << endl;
		}
	}

	//***********输出每一个VNetwork包含的虚拟机
	for (O_VNetworkMapIterator = O_VNetworkMap.begin(); O_VNetworkMapIterator != O_VNetworkMap.end(); O_VNetworkMapIterator++)
	{
		O_VNetwork = O_VNetworkMapIterator->second;
		outputfile1 << "ID of this V_Network :" << O_VNetwork.vNetwork_id << endl;
		outputfile1 << "Number of Virtual Nodes of this V_Network :" << O_VNetwork.numOfVnode <<"  Virtual Nodes" << endl;
		outputfile1 << "The Virtual Nodes of this V_Network  are the Following:"<< endl;
		for (O_VNetwork.containedVnodeListIterator = O_VNetwork.containedVnodeList.begin(); O_VNetwork.containedVnodeListIterator != O_VNetwork.containedVnodeList.end(); O_VNetwork.containedVnodeListIterator++)
		{
			outputfile1 << (*O_VNetwork.containedVnodeListIterator) << " ";
		}
		outputfile1 << endl;
		outputfile1 << '\n' << '\n';
	}


	return true;
}

/******************************************************************End of Creation of Virtual Networks*******************************************************************************/

/******************************************************************************************************
*****************Implementation of Algorithm_1 (Modulation and number of FS Selection)*****************
*******************************************************************************************************/
int C_graph::FS_modulationSelection(int distance, int bandwidth)
{
	int total_distance = distance;
	int required_bw = bandwidth;
	int totalFS = INFINITE;
	    if ((8000 > total_distance) && (total_distance >= 4000))
	    {
		   totalFS = ((required_bw / 25) + ((required_bw % 25) != 0));
	    }
	    else if ((4000 > total_distance) && (total_distance >= 2000))
	    {
		totalFS = ((required_bw / 50) + ((required_bw % 50) != 0));
	    }
	    else if ((2000 > total_distance) && (total_distance >= 1000))
	    {
		totalFS = ((required_bw / 75) + ((required_bw % 75) != 0));
	    }
	    else if (1000 > total_distance)
	    {
		totalFS = ((required_bw / 100) + ((required_bw % 100) != 0));
	    }
	    else
	    {
		totalFS = INFINITE;
	    }
	//cout << "Total Frequency slots required :" << totalFS <<'\n';
	return totalFS;
}

/**************************************************************************************************************************
************************Implementation of Algorithm 5 (Cost Function & Proper RSA Selection)*******************************
***************************************************************************************************************************/
int C_graph::Allocated_FS(int totalFS, int pathId, int srcId, int dstId)
{

	int total_num_FS = totalFS;
	int path_num = pathId;
	int src = srcId;
    int dst = dstId;
   //int totalEdgeNum = totalEdge;
   //int totalEdgeNum1 = INFINITE;
   int smallC = INFINITE, totalC = INFINITE, i, j, k;
   int one[400], two[400];
   int x[400], c[400];
   int FinalIndex = INFINITE;
    //int cost = 0;

   for (int i = 0; i < 400; i++)
   {
	one[i] = 1;
    }


  /********************************Putting the original values into respective Arrays**********************************/


  for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
  {
	o_paths = *o_paths_list_iterator;
	for (O_SEdgeMapIterator = O_SEdgeMap.begin(); O_SEdgeMapIterator != O_SEdgeMap.end(); O_SEdgeMapIterator++)
	{
		O_SEdge = O_SEdgeMapIterator->second;
		if (O_SEdge.edge_id == o_paths.adj_edge)
		{
			/**************************************************************************************/
		   // O_SEdge = O_SEdgeMap[o_paths.adj_edge];
			for (int i = 0; i < 400; i++)
			{
				two[i] = O_SEdge.FS_Array[i];
			}

			/*****************************/
			for (int i = 0; i < 400; i++)
			{
				smallC = 0;
				for (int l = i; l < (i + total_num_FS); l++)
				{

					smallC = smallC + two[l];
				}
				if (smallC == total_num_FS)
				{
					x[i] = 1;

				}
				else
				{
					x[i] = 0;
				}
			}
			for (int i = 0; i < 400; i++)
			{
				totalC = 0;
				if (i == 0 && (x[i] == 1) && (one[i] == 1))
				{
					totalC = two[i + total_num_FS] + one[i + total_num_FS];
					c[i] = totalC;

				}
				else if (i == 399 && (x[i] == 1) && (one[i] == 1))
				{
					totalC = two[i - 1] + one[i - 1];
					c[i] = totalC;
				}
				else  if ((x[i] == 1) && (one[i] == 1))
				{
					totalC = two[i - 1] + two[i + total_num_FS] + one[i - 1] + one[i + total_num_FS];
					c[i] = totalC;
				}
				else
				{
					c[i] = INFINITE;
				}


			}

			for (int i = 0; i < 400; i++)
			{
				one[i] = x[i];
			}

			/**********************************/
		}
		//else
		//	continue;
	
	}

		
	
  }
    FinalIndex = 0;
   for (int i = 1; i < 400; i++)
   {

	  if ((c[i]) < (c[FinalIndex]))
	  {
		FinalIndex = i;
	  }
	
   }
	
   //if (FinalIndex == 0)
   //{
	   if (c[FinalIndex] >= 500)// || (c[FinalIndex] <= 0))
	   {
		   FinalIndex = INFINITE;
	   }
   //}

	//cout << "COST :  ";
	//   cout << "Final Index of the path : " << FinalIndex << endl;
	//cout << c[FinalIndex] << '\n';
	//cout << '\n';
	
  return FinalIndex;

}

/*****************************************End of Algorithm 5***********************************************************/


/******************************************************************************************************
**************************************Availability Calculation*****************************************
*******************************************************************************************************/

LDOUBLE C_graph::Availabilty_calculation(int pathId, int srcId, int dstId)
{
	double availability = 1;
	double Final_availability = 0;
	for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
	{
		o_paths = *o_paths_list_iterator;
		for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++)
		{
			O_edge = O_edge_map_iterator->second;
			if (O_edge.edge_id == o_paths.adj_edge)
			{
				availability = availability * (O_edge._availablility);
			}
		}
	}
	Final_availability = availability;

	return Final_availability;
}
/**************************************End of Availability Calculation****************************************/

/**************************************************************************************************************************
*************************************Implementation of Virtual Network Mapping*********************************************
***************************************************************************************************************************/
int C_graph::singleVNetworkMapping(int vnetwork_id)
{
	
	int success = 0;
	int Net_id = vnetwork_id;
	int pathOneFS = 0;
	int pathTwoFS = 0;
	//int total
	/********************************Node Mapping********************************/
	 O_VNetwork = O_VNetworkMap[vnetwork_id];
	 //****After determining the virtual network, put all virtual nodes in the virtual network into O_VNode_requested_resource_queue
	 O_originalComputeNodeMap = O_Compute_Node_map;
	 O_originalSEdgeMap = O_SEdgeMap;
	 O_originalVNodeMap = O_VNodeMap;
	 O_originalVEdgeMap = O_VEdgeMap;

	 Load_edge_graph(); 
	 O_original_edge_map = O_edge_map; //Backup O_edge_map

	 bool mappingSuccessMark = false;//Define a tag to record whether a single virtual network map is successful, true means success, and false means failure
	 bool protectionMark = false;
	 //****For each virtual network, it will try to map them from node 1 to node 24
	 if (vnetwork_id % 2 == 0)
	 {
		 for (int i = 1; i <= 24; i++)
		 {
			 mappingSuccessMark = true;
			 Load_adj_graph();
			 //**** Now Start mapping the virtual network for the i th time
			 O_adj_list = O_adj_map[i];
			 if (O_adj_list.size() + 1 >= O_VNetwork.containedVnodeList.size())//If ith node has more or less adjacent nodes than or equal to the number of virtual nodes contained in the virtual network to be mapped
			 {
				 O_Compute_Node = O_Compute_Node_map[i];
				 //****Put ith node and all its adjacency nodes into the queue O_Compute_Node_resource_queue
				 O_Compute_Node_resource_queue.push(O_Compute_Node);  //Here we first put the ith substrate node in the queue

				 for (O_adj_list_iterator = O_adj_list.begin(); O_adj_list_iterator != O_adj_list.end(); O_adj_list_iterator++)//Puts all of ith adjacency nodes in the queue
				 {
					 O_adj = (*O_adj_list_iterator);
					 O_Compute_Node = O_Compute_Node_map[O_adj.adj_node_id];
					 O_Compute_Node_resource_queue.push(O_Compute_Node);
				 }
				 //****Put all virtual nodes of the virtual network, where the parameter is passed into the O_VNode_requested_resource_queue
				 for (O_VNetwork.containedVnodeListIterator = O_VNetwork.containedVnodeList.begin(); O_VNetwork.containedVnodeListIterator != O_VNetwork.containedVnodeList.end(); O_VNetwork.containedVnodeListIterator++)
				 {
					 O_VNode = O_VNodeMap[(*O_VNetwork.containedVnodeListIterator)];
					 O_VNode_requested_resource_queue.push(O_VNode);
				 }
				 //****The following while loop attempts to map all virtual nodes to the corresponding server. If this fails, the mappingSuccessMark = false
				 while (!O_VNode_requested_resource_queue.empty())
				 {
					 O_VNode = O_VNode_requested_resource_queue.top();
					 O_Compute_Node = O_Compute_Node_resource_queue.top();//Virtual machines that require the most resources map to servers that have the most resources
					 if ((O_Compute_Node._Compute_FN >= O_VNode.vNodeResourceRequested) && (O_Compute_Node._node_degree >= O_VNode.vNodeDegree))
					 {
						 O_Compute_Node._Compute_FN = O_Compute_Node._Compute_FN - O_VNode.vNodeResourceRequested;//Change the resource of the mapped server
						 O_Compute_Node.embeddedVnodesList.push_back(O_VNode.vNode_id);//Change the virtual machine that the server holds
						 O_Compute_Node_map[O_Compute_Node._node_i] = O_Compute_Node;//Update O_SNodeMap

						 O_VNode.ontoSNode = O_Compute_Node._node_i;//Change the server that the virtual machine maps to
						 O_VNodeMap[O_VNode.vNode_id] = O_VNode;//Update O_VNodeMap

						 O_VNode_requested_resource_queue.pop();
						 O_Compute_Node_resource_queue.pop();
					 }
					 else
					 {
						 mappingSuccessMark = false;
						 break;//Terminate the while (!O_VNode_requested_resource_queue.Empty()) loop
					 }
				 }
				 //****Empty O_SNode_remaining_resource_queue O_VNode_requested_resource_queue
				 while (!O_Compute_Node_resource_queue.empty())
				 {
					 O_Compute_Node_resource_queue.pop();
				 }
				 while (!O_VNode_requested_resource_queue.empty())
				 {
					 O_VNode_requested_resource_queue.pop();
				 }
				 /**********************************End of Node Mapping for Odd Virtual Network***************************************/
				 /*************************************Start Link Mapping Using MULTIPLE PATHS******************************************/
				 if (mappingSuccessMark == true)
				 {

					 mappingSuccessMark = false; //Initialize a false
					 protectionMark = true;
					 for (O_VNetwork.containedVlinkListIterator = O_VNetwork.containedVlinkList.begin(); O_VNetwork.containedVlinkListIterator != O_VNetwork.containedVlinkList.end(); O_VNetwork.containedVlinkListIterator++)
					 {
						 O_VEdge = O_VEdgeMap[*O_VNetwork.containedVlinkListIterator];

						 for (O_SEdgeMapIterator = O_SEdgeMap.begin(); O_SEdgeMapIterator != O_SEdgeMap.end(); O_SEdgeMapIterator++)
						 {
							 O_SEdge = O_SEdgeMapIterator->second;

						 }

						 int Original_requested_resource = O_VEdge.vEdgeResourceRequested;
						 Load_adj_graph();
						 Load_edge_graph();
						 int aSubstrate, bSubstrate;
						 O_VNode = O_VNodeMap[O_VEdge.aVnode];
						 aSubstrate = O_VNode.ontoSNode;

						 O_VNode = O_VNodeMap[O_VEdge.bVnode];
						 bSubstrate = O_VNode.ontoSNode;

						 for (int k = 1; k <= 3; k++)
						 {

							 Find_shortest_path(aSubstrate, bSubstrate, k);

							 Find_link_disjoint_path(aSubstrate, bSubstrate);
						 }

						 for (o_paths_map_iterator = o_paths_map.begin(); o_paths_map_iterator != o_paths_map.end(); o_paths_map_iterator++)
						 {
							 double Path_Dist = 0;
							 int totEdges = 0;
							 o_paths.path_distance = 0;
							 o_paths.total_num_edges = 0;
							 o_paths_list = o_paths_map_iterator->second;

							 int S_source = o_paths.source_id;
							 int S_destination = o_paths.destination_id;
							 int path_id = o_paths_map_iterator->first;

							 /// cout << "Source" << '\t' << o_paths.source_id << "        " << "Destination" << '\t' << o_paths.destination_id << '\t' << '\n';//
							 // cout << "path " << o_paths_map_iterator->first << endl; //


							 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
							 {
								 Load_edge_graph();
								 o_paths = *o_paths_list_iterator;
								 O_edge = O_edge_map[o_paths.adj_edge];
								 /// cout << "  " << o_paths.adj_edge;   //

								 for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++)
								 {

									 O_edge = O_edge_map_iterator->second;
									 if (O_edge.edge_id == o_paths.adj_edge)
									 {
										 Path_Dist = Path_Dist + O_edge.edge_cost;
									 }
									 else
										 continue;
								 }

								 for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++)
								 {
									 O_edge = O_edge_map_iterator->second;
									 if (O_edge.edge_id == o_paths.adj_edge)
									 {
										 totEdges = totEdges + 1;
									 }
									 else
										 continue;
								 }

							 }

							 o_paths.path_distance = Path_Dist;
							 ///cout << '\n';
							/// cout << "Total Distance of this path: " << o_paths.path_distance << " KM " << endl;  //
							 /********************for Path 1 (working)********************/
							 if ((S_source == aSubstrate) && (S_destination == bSubstrate) && path_id == 1)
							 {

								 int remain_bandwidth = 0;
								 double availability_one = Availabilty_calculation(path_id, S_source, S_destination);
								 // cout << availability_one << endl;
								 int z = FS_modulationSelection(o_paths.path_distance, O_VEdge.vEdgeResourceRequested);
								 if (z != INFINITE)
								 {
									 for (int j = z; j >= 1; j--)
									 {
										 int F_index = Allocated_FS(j, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
										 if (F_index != INFINITE)
										 {
											 mappingSuccessMark = false;

											 /**************************************************************************************/
											 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
											 {
												 o_paths = *o_paths_list_iterator;
												 O_SEdge = O_SEdgeMap[o_paths.adj_edge];
												 for (int i = F_index; i < (F_index + j); i++)
												 {
													 O_SEdge.FS_Array[i] = 0;

													 O_SEdge.sEdgeResource = O_SEdge.sEdgeResource - 1;

												 }

												 O_SEdge.embeddedVedgesList.push_back(O_VEdge.vEdge_id);
												 O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
												 // O_VEdge.PathList = path_id;     // O_shortest_edge_path_list;     //O_shortest_edge_path_list;
												 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

											 }
											 /**************************************************************************************************************************************************************************/
											/// cout << "Final Index of the path from : " << F_index << " to " << (F_index + j - 1) << '\n';
											 if ((8000 > o_paths.path_distance) && (o_paths.path_distance >= 4000))
											 {
												 Original_requested_resource = Original_requested_resource - (j * 25);
											 }
											 else if ((4000 > o_paths.path_distance) && (o_paths.path_distance >= 2000))
											 {
												 Original_requested_resource = Original_requested_resource - (j * 50);
											 }
											 else if ((2000 > o_paths.path_distance) && (o_paths.path_distance >= 1000))
											 {
												 Original_requested_resource = Original_requested_resource - (j * 75);
											 }
											 else if (1000 > o_paths.path_distance)
											 {
												 Original_requested_resource = Original_requested_resource - (j * 100);
											 }

											 O_VEdge.ontoPathList.push_back(path_id);
											 O_VEdge.FS_fIndex_list.push_back(F_index);
											 O_VEdge.FS_lIndex_list.push_back(F_index + j - 1);
											 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;
											 /********************************************/
											 /*O_Path_Collection.path_id = path_id;
											 O_Path_Collection.path_src = S_source;
											 O_Path_Collection.path_dst = bSubstrate;
											 O_Path_Collection.first_fs = F_index;
											 O_Path_Collection.last_fs = F_index + j - 1;
											 O_Path_Collection_list.push_back(O_Path_Collection);
											 // O_Path_Collection_Map[O_Path_Collection.path_id_one] = O_Path_Collection;
											 O_Path_Collection_Map.insert(map<int, list<Path_Collection>>::value_type(O_Path_Collection.path_id, O_Path_Collection_list));
											 O_Path_Collection_list.clear();*/
											 /****************************************************************************************************************************************************************************************/
										 }

										 if ((Original_requested_resource < O_VEdge.vEdgeResourceRequested) && (Original_requested_resource <= 0))
										 {
											 // Original_requested_resource = Original_requested_resource - O_VEdge.vEdgeResourceRequested;
											 mappingSuccessMark = true;
											 // Original_requested_resource = O_VEdge.vEdgeResourceRequested;
											// if (availability_one < O_VEdge.availabilityRequired)
											 //{
												 pathOneFS = j;
												 //cout << pathOneFS << " Value asche**************" <<endl;
												 protectionMark = true;
											// }


											 break; // Now changed
										 }
										 /* else if ((O_VEdge.vEdgeResourceRequested < Original_requested_resource) && (O_VEdge.vEdgeResourceRequested > 0))
										  {
											  mappingSuccessMark = false;
											  Original_requested_resource = O_VEdge.vEdgeResourceRequested;
											 // break;
										  }*/
										 else if ((Original_requested_resource <= O_VEdge.vEdgeResourceRequested) && (Original_requested_resource > 0))
										 {
											 mappingSuccessMark = false;
											 // Original_requested_resource = O_VEdge.vEdgeResourceRequested;
											  // break;
											// if (availability_one < O_VEdge.availabilityRequired)
											 //{
												 pathOneFS = j;
												 // cout << pathOneFS << " Value asche**************" << endl;
												 protectionMark = true;
											// }

											 break;
										 }
										 else
										 {
											 mappingSuccessMark = false;
											 O_SEdgeMap = O_originalSEdgeMap;
											 protectionMark = false;
											 continue;
										 }

										 // if (mappingSuccessMark == true)    // Now changed
											 // break;                         // Now changed

									 }
								 }
								 else
								 {
								   mappingSuccessMark = false;
                                 }



							 }


							 /********************for Path 2 (Protection) ********************/
							 if (protectionMark == true && mappingSuccessMark == true)
							 {

								 if ((S_source == aSubstrate) && (S_destination == bSubstrate) && path_id == 2)
								 {
									 // cout << "ASCHE *********************" << endl;
									//int remain_bandwidth = 0;

									 int z = pathOneFS;


									 int F_index = Allocated_FS(z, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
									 if (F_index != INFINITE)
									 {
										 total_backup = total_backup + z;
										 mappingSuccessMark = true;
										 /**************************************************************************************/
										 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
										 {
											 o_paths = *o_paths_list_iterator;
											 O_SEdge = O_SEdgeMap[o_paths.adj_edge];
											 for (int i = F_index; i < (F_index + z); i++)
											 {
												 O_SEdge.FS_Array[i] = 0;

												 O_SEdge.sEdgeResource = O_SEdge.sEdgeResource - 1;

											 }

											 O_SEdge.embeddedVedgesList.push_back(O_VEdge.vEdge_id);
											 O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
											 // O_VEdge.ontoPhyEdgeList = O_shortest_edge_path_list;     //O_shortest_edge_path_list;
											 // O_VEdge.ontoPathList.push_front(path_id);
											// O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;
											 
										 }
										 /******************************************************************************************************************/
										 if (z != 0)
										 {
											 /// cout << '\n' << "Total Slots required for Protection with Path 2: " << z << endl;
											 /// cout << "       Final Index of this Protection path (Path 2) from :       " << F_index << " to " << (F_index + z - 1) << '\n';

										 }



										 O_VEdge.ontoPathList.push_back(path_id);
										 O_VEdge.FS_fIndex_list.push_back(F_index);
										 O_VEdge.FS_lIndex_list.push_back(F_index + z - 1);
										 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

										 protectionMark = false;


										 /********************************************/
										/* O_Path_Collection.path_id = path_id;
										 O_Path_Collection.path_src = S_source;
										 O_Path_Collection.path_dst = bSubstrate;
										 O_Path_Collection.first_fs = F_index;
										 O_Path_Collection.last_fs = F_index + z - 1;
										 // O_Path_Collection_Map[O_Path_Collection.path_id_two] = O_Path_Collection;
										 O_Path_Collection_list.push_back(O_Path_Collection);
										 O_Path_Collection_Map.insert(map<int, list<Path_Collection>>::value_type(O_Path_Collection.path_id, O_Path_Collection_list));
										 O_Path_Collection_list.clear();*/
										 /*******************************************************************************************************************************************/
									 }

									 else
									 {
										 mappingSuccessMark = true;

										 O_SEdgeMap = O_originalSEdgeMap;
										 protectionMark = true;
										 break;
									 }
									 // if (mappingSuccessMark == true)
									// break;
									 // }

								 }
							 }
							 /*****************************************************************/





							 /********************for Path 2 (working) ********************/
							 if (mappingSuccessMark == false)
							 {
								 if ((S_source == aSubstrate) && (S_destination == bSubstrate) && path_id == 2)
								 {

									 int remain_bandwidth = 0;

									 int z = FS_modulationSelection(o_paths.path_distance, Original_requested_resource);
									 // for (int j = z; j >= 1; j--)
									 // {
									 if (z != INFINITE)
									 {
										 double availability_two = Availabilty_calculation(path_id, S_source, S_destination);
										 int F_index = Allocated_FS(z, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
										 if (F_index != INFINITE)
										 {
											 mappingSuccessMark = false;
											 /**************************************************************************************/
											 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
											 {
												 o_paths = *o_paths_list_iterator;
												 O_SEdge = O_SEdgeMap[o_paths.adj_edge];
												 for (int i = F_index; i < (F_index + z); i++)
												 {
													 O_SEdge.FS_Array[i] = 0;

													 O_SEdge.sEdgeResource = O_SEdge.sEdgeResource - 1;

												 }

												 O_SEdge.embeddedVedgesList.push_back(O_VEdge.vEdge_id);
												 O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
												 // O_VEdge.ontoPhyEdgeList = O_shortest_edge_path_list;     //O_shortest_edge_path_list;
												 // O_VEdge.ontoPathList.push_front(path_id);
												 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

											 }
											 /******************************************************************************************************************/
											/// cout << "Final Index of the path from : " << F_index << " to " << (F_index + z - 1) << '\n';
											 if ((8000 > o_paths.path_distance) && (o_paths.path_distance >= 4000))
											 {
												 Original_requested_resource = Original_requested_resource - (z * 25);
											 }
											 else if ((4000 > o_paths.path_distance) && (o_paths.path_distance >= 2000))
											 {
												 Original_requested_resource = Original_requested_resource - (z * 50);
											 }
											 else if ((2000 > o_paths.path_distance) && (o_paths.path_distance >= 1000))
											 {
												 Original_requested_resource = Original_requested_resource - (z * 75);
											 }
											 else if (1000 > o_paths.path_distance)
											 {
												 Original_requested_resource = Original_requested_resource - (z * 100);
											 }

											 O_VEdge.ontoPathList.push_back(path_id);
											 O_VEdge.FS_fIndex_list.push_back(F_index);
											 O_VEdge.FS_lIndex_list.push_back(F_index + z - 1);
											 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

											 /********************************************/
											 /*O_Path_Collection.path_id = path_id;
											 O_Path_Collection.path_src = S_source;
											 O_Path_Collection.path_dst = bSubstrate;
											 O_Path_Collection.first_fs = F_index;
											 O_Path_Collection.last_fs = F_index + z - 1;
											 // O_Path_Collection_Map[O_Path_Collection.path_id_two] = O_Path_Collection;
											 O_Path_Collection_list.push_back(O_Path_Collection);
											 O_Path_Collection_Map.insert(map<int, list<Path_Collection>>::value_type(O_Path_Collection.path_id, O_Path_Collection_list));
											 O_Path_Collection_list.clear();*/
											 /*********************************************/
											 if (Original_requested_resource <= 0)
											 {
												 mappingSuccessMark = true;
												// if (availability_two < O_VEdge.availabilityRequired)
												// {
													 pathTwoFS = z;

													 protectionMark = true;
												// }

											 }
											 else
											 {
												 mappingSuccessMark = false;
												 O_SEdgeMap = O_originalSEdgeMap;
												 protectionMark = false;
												 break;
											 }
											 /*******************************************************************************************************************************************/
										 }

										 else
										 {
											 mappingSuccessMark = false;
											 O_SEdgeMap = O_originalSEdgeMap;
											 protectionMark = false;
											 break;
										 }
									 }
									
									 // if (mappingSuccessMark == true)
									// break;
									 // }
									 else
									 {
										 mappingSuccessMark = false;
									 }

								 }

							 }


							 /********************for Path 3 (Protection) ********************/
							 if (protectionMark == true && mappingSuccessMark == true)
							 {

								 if ((S_source == aSubstrate) && (S_destination == bSubstrate) && path_id == 3)
								 {

									 //int remain_bandwidth = 0;
									 int z = 0;
									 if (pathOneFS > 0 && pathTwoFS == 0)
									 {
										 z = pathOneFS;
									 }
									 else if (pathOneFS == 0 && pathTwoFS > 0)
									 {
										 z = pathTwoFS;
									 }
									 else if (pathOneFS > 0 && pathTwoFS > 0)
									 {
										 if (pathOneFS > pathTwoFS)
											 z = pathOneFS;
										 else
											 z = pathTwoFS;
									 }

									 int F_index = Allocated_FS(z, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
									 if (F_index != INFINITE)
									 {
										 mappingSuccessMark = true;
										 total_backup = total_backup + z;
										 /**************************************************************************************/
										 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
										 {
											 o_paths = *o_paths_list_iterator;
											 O_SEdge = O_SEdgeMap[o_paths.adj_edge];
											 for (int i = F_index; i < (F_index + z); i++)
											 {
												 O_SEdge.FS_Array[i] = 0;

												 O_SEdge.sEdgeResource = O_SEdge.sEdgeResource - 1;

											 }

											 O_SEdge.embeddedVedgesList.push_back(O_VEdge.vEdge_id);
											 O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
											 // O_VEdge.ontoPhyEdgeList = O_shortest_edge_path_list;     //O_shortest_edge_path_list;
											 // O_VEdge.ontoPathList.push_front(path_id);
											// O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;
											 
										 }
										 /******************************************************************************************************************/
										 if (z != 0)
										 {
											 /// cout << '\n' << "Total Slots required for Protection with path 3 : " << z << endl;
											 /// cout << "       Final Index of this Protection path (path 3) from :       " << F_index << " to " << (F_index + z - 1) << '\n';

										 }



										 O_VEdge.ontoPathList.push_back(path_id);
										 O_VEdge.FS_fIndex_list.push_back(F_index);
										 O_VEdge.FS_lIndex_list.push_back(F_index + z - 1);
										 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

										 protectionMark = false;

										 /********************************************/
										/* O_Path_Collection.path_id = path_id;
										 O_Path_Collection.path_src = S_source;
										 O_Path_Collection.path_dst = bSubstrate;
										 O_Path_Collection.first_fs = F_index;
										 O_Path_Collection.last_fs = F_index + z - 1;
										 //O_Path_Collection_Map[O_Path_Collection.path_id_three] = O_Path_Collection;
										 O_Path_Collection_list.push_back(O_Path_Collection);
										 O_Path_Collection_Map.insert(map<int, list<Path_Collection>>::value_type(O_Path_Collection.path_id, O_Path_Collection_list));
										 O_Path_Collection_list.clear();*/
										 /*******************************************************************************************************************************************/										 /*******************************************************************************************************************************************/
									 }

									 else
									 {
										 mappingSuccessMark = false;
										 /// cout << '\n' << "Total Slots required for Protection: " << z << endl;
										 /// cout << "    Prottection is not possible for this link.    " << endl;
										 O_SEdgeMap = O_originalSEdgeMap;
										 protectionMark = false;
										 break;
									 }
									 // if (mappingSuccessMark == true)
									// break;
									 // }

								 }
							 }

							 /****************************************************************/
							 if (mappingSuccessMark == true && protectionMark == false)
							 {
								 break;
							 }

							 /*else
							 {
								 continue;
							 }*/

							 /* if (mappingSuccessMark == false)//If this mapping is not successful
							  {
								  O_SEdgeMap = O_originalSEdgeMap;
							  }
							 // break;
							 */
						 }

						 if (Original_requested_resource <= 0)
						 {
							 mappingSuccessMark = true;
							 protectionMark = false;
						 }
						 else
						 {
							 mappingSuccessMark = false;
							 protectionMark = false;
						 }
						 //O_Path_Collection_Map.clear();

						 o_paths_map.clear();
						 o_paths_list.clear();

					 }


					 if (mappingSuccessMark == false)//If this mapping is not successful
					 {
						 //****Restore the tampered O_Compute_Node_Map, O_SEdgeMap, O_VNodeMap, O_VEdgeMap
						 O_VNodeMap = O_originalVNodeMap;
						 O_Compute_Node_map = O_originalComputeNodeMap;//O_VNodeMap and O_SNodeMap are tampered when mapping nodes to change node resources
						 O_edge_map = O_original_edge_map;
						 O_SEdgeMap = O_originalSEdgeMap;
						 O_VEdgeMap = O_originalVEdgeMap;//O_SEdgeMap and O_VEdgeMap have been tampered by changing link resources while mapping links
					 }

				 }

			 }
			 else
			 {
				 mappingSuccessMark = false;
			 }
			 if (mappingSuccessMark == false)//If this mapping is not successful
			 {
				 //****Restore the tampered O_SNodeMap, O_SEdgeMap, O_VNodeMap, O_VEdgeMap
				 O_VNodeMap = O_originalVNodeMap;
				 O_Compute_Node_map = O_originalComputeNodeMap;//O_VNodeMap and O_SNodeMap are tampered when mapping nodes to change node resources
				 O_edge_map = O_original_edge_map;
				 O_SEdgeMap = O_originalSEdgeMap;
				 O_VEdgeMap = O_originalVEdgeMap;//O_SEdgeMap and O_VEdgeMap have been tampered by changing link resources while mapping links
			 }
			 else
			 {
				 break; //Terminate for (int I = 1;I < = 24;I++) loop
			 }

		 }
	     
	 }
	 else
	 {
	    for (int i = 24; i >= 1; i--)
	    {
		 mappingSuccessMark = true;
		 Load_adj_graph();
		 //**** Now Start mapping the virtual network for the i th time
		 O_adj_list = O_adj_map[i];
		 if (O_adj_list.size() + 1 >= O_VNetwork.containedVnodeList.size())//If ith node has more or less adjacent nodes than or equal to the number of virtual nodes contained in the virtual network to be mapped
		 {
			 O_Compute_Node = O_Compute_Node_map[i];
			 //****Put ith node and all its adjacency nodes into the queue O_Compute_Node_resource_queue
			 O_Compute_Node_resource_queue.push(O_Compute_Node);  //Here we first put the ith substrate node in the queue

			 for (O_adj_list_iterator = O_adj_list.begin(); O_adj_list_iterator != O_adj_list.end(); O_adj_list_iterator++)//Puts all of ith adjacency nodes in the queue
			 {
				 O_adj = (*O_adj_list_iterator);
				 O_Compute_Node = O_Compute_Node_map[O_adj.adj_node_id];
				 O_Compute_Node_resource_queue.push(O_Compute_Node);
			 }
			 //****Put all virtual nodes of the virtual network, where the parameter is passed into the O_VNode_requested_resource_queue
			 for (O_VNetwork.containedVnodeListIterator = O_VNetwork.containedVnodeList.begin(); O_VNetwork.containedVnodeListIterator != O_VNetwork.containedVnodeList.end(); O_VNetwork.containedVnodeListIterator++)
			 {
				 O_VNode = O_VNodeMap[(*O_VNetwork.containedVnodeListIterator)];
				 O_VNode_requested_resource_queue.push(O_VNode);
			 }
			 //****The following while loop attempts to map all virtual nodes to the corresponding server. If this fails, the mappingSuccessMark = false
			 while (!O_VNode_requested_resource_queue.empty())
			 {
				 O_VNode = O_VNode_requested_resource_queue.top();
				 O_Compute_Node = O_Compute_Node_resource_queue.top();//Virtual machines that require the most resources map to servers that have the most resources
				 if ((O_Compute_Node._Compute_FN >= O_VNode.vNodeResourceRequested) && (O_Compute_Node._node_degree >= O_VNode.vNodeDegree))
				 {
					 O_Compute_Node._Compute_FN = O_Compute_Node._Compute_FN - O_VNode.vNodeResourceRequested;//Change the resource of the mapped server
					 O_Compute_Node.embeddedVnodesList.push_back(O_VNode.vNode_id);//Change the virtual machine that the server holds
					 O_Compute_Node_map[O_Compute_Node._node_i] = O_Compute_Node;//Update O_SNodeMap

					 O_VNode.ontoSNode = O_Compute_Node._node_i;//Change the server that the virtual machine maps to
					 O_VNodeMap[O_VNode.vNode_id] = O_VNode;//Update O_VNodeMap

					 O_VNode_requested_resource_queue.pop();
					 O_Compute_Node_resource_queue.pop();
				 }
				 else
				 {
					 mappingSuccessMark = false;
					 break;//Terminate the while (!O_VNode_requested_resource_queue.Empty()) loop
				 }
			 }
			 //****Empty O_SNode_remaining_resource_queue O_VNode_requested_resource_queue
			 while (!O_Compute_Node_resource_queue.empty())
			 {
				 O_Compute_Node_resource_queue.pop();
			 }
			 while (!O_VNode_requested_resource_queue.empty())
			 {
				 O_VNode_requested_resource_queue.pop();
			 }
			 /**********************************End of Node Mapping for Odd Virtual Network***************************************/
			 /*************************************Start Link Mapping Using MULTIPLE PATHS******************************************/
			 if (mappingSuccessMark == true)
			 {

				 mappingSuccessMark = false; //Initialize a false
				 protectionMark = true;
				 for (O_VNetwork.containedVlinkListIterator = O_VNetwork.containedVlinkList.begin(); O_VNetwork.containedVlinkListIterator != O_VNetwork.containedVlinkList.end(); O_VNetwork.containedVlinkListIterator++)
				 {
					 O_VEdge = O_VEdgeMap[*O_VNetwork.containedVlinkListIterator];

					 for (O_SEdgeMapIterator = O_SEdgeMap.begin(); O_SEdgeMapIterator != O_SEdgeMap.end(); O_SEdgeMapIterator++)
					 {
						 O_SEdge = O_SEdgeMapIterator->second;

					 }

					 int Original_requested_resource = O_VEdge.vEdgeResourceRequested;
					 Load_adj_graph();
					 Load_edge_graph();
					 int aSubstrate, bSubstrate;
					 O_VNode = O_VNodeMap[O_VEdge.aVnode];
					 aSubstrate = O_VNode.ontoSNode;

					 O_VNode = O_VNodeMap[O_VEdge.bVnode];
					 bSubstrate = O_VNode.ontoSNode;

					 for (int k = 1; k <= 3; k++)
					 {

						 Find_shortest_path(aSubstrate, bSubstrate, k);

						 Find_link_disjoint_path(aSubstrate, bSubstrate);
					 }

					 for (o_paths_map_iterator = o_paths_map.begin(); o_paths_map_iterator != o_paths_map.end(); o_paths_map_iterator++)
					 {
						 double Path_Dist = 0;
						 int totEdges = 0;
						 o_paths.path_distance = 0;
						 o_paths.total_num_edges = 0;
						 o_paths_list = o_paths_map_iterator->second;

						 int S_source = o_paths.source_id;
						 int S_destination = o_paths.destination_id;
						 int path_id = o_paths_map_iterator->first;

						 /// cout << "Source" << '\t' << o_paths.source_id << "        " << "Destination" << '\t' << o_paths.destination_id << '\t' << '\n';//
						 // cout << "path " << o_paths_map_iterator->first << endl; //


						 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
						 {
							 Load_edge_graph();
							 o_paths = *o_paths_list_iterator;
							 O_edge = O_edge_map[o_paths.adj_edge];
							 /// cout << "  " << o_paths.adj_edge;   //

							 for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++)
							 {

								 O_edge = O_edge_map_iterator->second;
								 if (O_edge.edge_id == o_paths.adj_edge)
								 {
									 Path_Dist = Path_Dist + O_edge.edge_cost;
								 }
								 else
									 continue;
							 }

							 for (O_edge_map_iterator = O_edge_map.begin(); O_edge_map_iterator != O_edge_map.end(); O_edge_map_iterator++)
							 {
								 O_edge = O_edge_map_iterator->second;
								 if (O_edge.edge_id == o_paths.adj_edge)
								 {
									 totEdges = totEdges + 1;
								 }
								 else
									 continue;
							 }

						 }

						 o_paths.path_distance = Path_Dist;
						 ///cout << '\n';
						/// cout << "Total Distance of this path: " << o_paths.path_distance << " KM " << endl;  //
						 /********************for Path 1 (working)********************/
						 if ((S_source == aSubstrate) && (S_destination == bSubstrate) && path_id == 1)
						 {

							 int remain_bandwidth = 0;
							 double availability_one = Availabilty_calculation(path_id, S_source, S_destination);
							 // cout << availability_one << endl;
							 int z = FS_modulationSelection(o_paths.path_distance, O_VEdge.vEdgeResourceRequested);
							 if (z != INFINITE)
							 {
								 for (int j = z; j >= 1; j--)
								 {
									 int F_index = Allocated_FS(j, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
									 if (F_index != INFINITE)
									 {
										 mappingSuccessMark = false;

										 /**************************************************************************************/
										 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
										 {
											 o_paths = *o_paths_list_iterator;
											 O_SEdge = O_SEdgeMap[o_paths.adj_edge];
											 for (int i = F_index; i < (F_index + j); i++)
											 {
												 O_SEdge.FS_Array[i] = 0;

												 O_SEdge.sEdgeResource = O_SEdge.sEdgeResource - 1;

											 }

											 O_SEdge.embeddedVedgesList.push_back(O_VEdge.vEdge_id);
											 O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
											 // O_VEdge.PathList = path_id;     // O_shortest_edge_path_list;     //O_shortest_edge_path_list;
											 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

										 }
										 /**************************************************************************************************************************************************************************/
										/// cout << "Final Index of the path from : " << F_index << " to " << (F_index + j - 1) << '\n';
										 if ((8000 > o_paths.path_distance) && (o_paths.path_distance >= 4000))
										 {
											 Original_requested_resource = Original_requested_resource - (j * 25);
										 }
										 else if ((4000 > o_paths.path_distance) && (o_paths.path_distance >= 2000))
										 {
											 Original_requested_resource = Original_requested_resource - (j * 50);
										 }
										 else if ((2000 > o_paths.path_distance) && (o_paths.path_distance >= 1000))
										 {
											 Original_requested_resource = Original_requested_resource - (j * 75);
										 }
										 else if (1000 > o_paths.path_distance)
										 {
											 Original_requested_resource = Original_requested_resource - (j * 100);
										 }

										 O_VEdge.ontoPathList.push_back(path_id);
										 O_VEdge.FS_fIndex_list.push_back(F_index);
										 O_VEdge.FS_lIndex_list.push_back(F_index + j - 1);
										 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;
										 /********************************************/
										 /*O_Path_Collection.path_id = path_id;
										 O_Path_Collection.path_src = S_source;
										 O_Path_Collection.path_dst = bSubstrate;
										 O_Path_Collection.first_fs = F_index;
										 O_Path_Collection.last_fs = F_index + j - 1;
										 O_Path_Collection_list.push_back(O_Path_Collection);
										 // O_Path_Collection_Map[O_Path_Collection.path_id_one] = O_Path_Collection;
										 O_Path_Collection_Map.insert(map<int, list<Path_Collection>>::value_type(O_Path_Collection.path_id, O_Path_Collection_list));
										 O_Path_Collection_list.clear();*/
										 /****************************************************************************************************************************************************************************************/
									 }

									 if ((Original_requested_resource < O_VEdge.vEdgeResourceRequested) && (Original_requested_resource <= 0))
									 {
										 // Original_requested_resource = Original_requested_resource - O_VEdge.vEdgeResourceRequested;
										 mappingSuccessMark = true;
										 // Original_requested_resource = O_VEdge.vEdgeResourceRequested;
										// if (availability_one < O_VEdge.availabilityRequired)
										 //{
										 pathOneFS = j;
										 //cout << pathOneFS << " Value asche**************" <<endl;
										 protectionMark = true;
										 // }


										 break; // Now changed
									 }
									 /* else if ((O_VEdge.vEdgeResourceRequested < Original_requested_resource) && (O_VEdge.vEdgeResourceRequested > 0))
									  {
										  mappingSuccessMark = false;
										  Original_requested_resource = O_VEdge.vEdgeResourceRequested;
										 // break;
									  }*/
									 else if ((Original_requested_resource <= O_VEdge.vEdgeResourceRequested) && (Original_requested_resource > 0))
									 {
										 mappingSuccessMark = false;
										 // Original_requested_resource = O_VEdge.vEdgeResourceRequested;
										  // break;
										// if (availability_one < O_VEdge.availabilityRequired)
										 //{
										 pathOneFS = j;
										 // cout << pathOneFS << " Value asche**************" << endl;
										 protectionMark = true;
										 // }

										  break;
									 }
									 else
									 {
										 mappingSuccessMark = false;
										 O_SEdgeMap = O_originalSEdgeMap;
										 protectionMark = false;
										 continue;
									 }

									 // if (mappingSuccessMark == true)    // Now changed
										 // break;                         // Now changed

								 }
							 }
							 else
							 {
								 mappingSuccessMark = false;
							 }



						 }


						 /********************for Path 2 (Protection) ********************/
						 if (protectionMark == true && mappingSuccessMark == true)
						 {

							 if ((S_source == aSubstrate) && (S_destination == bSubstrate) && path_id == 2)
							 {
								 // cout << "ASCHE *********************" << endl;
								//int remain_bandwidth = 0;

								 int z = pathOneFS;


								 int F_index = Allocated_FS(z, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
								 if (F_index != INFINITE)
								 {
									 total_backup = total_backup + z;
									 mappingSuccessMark = true;
									 /**************************************************************************************/
									 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
									 {
										 o_paths = *o_paths_list_iterator;
										 O_SEdge = O_SEdgeMap[o_paths.adj_edge];
										 for (int i = F_index; i < (F_index + z); i++)
										 {
											 O_SEdge.FS_Array[i] = 0;

											 O_SEdge.sEdgeResource = O_SEdge.sEdgeResource - 1;

										 }

										 O_SEdge.embeddedVedgesList.push_back(O_VEdge.vEdge_id);
										 O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
										 // O_VEdge.ontoPhyEdgeList = O_shortest_edge_path_list;     //O_shortest_edge_path_list;
										 // O_VEdge.ontoPathList.push_front(path_id);
										// O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;
										 
									 }
									 /******************************************************************************************************************/
									 if (z != 0)
									 {
										 /// cout << '\n' << "Total Slots required for Protection with Path 2: " << z << endl;
										 /// cout << "       Final Index of this Protection path (Path 2) from :       " << F_index << " to " << (F_index + z - 1) << '\n';

									 }



									 O_VEdge.ontoPathList.push_back(path_id);
									 O_VEdge.FS_fIndex_list.push_back(F_index);
									 O_VEdge.FS_lIndex_list.push_back(F_index + z - 1);
									 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

									 protectionMark = false;


									 /********************************************/
									/* O_Path_Collection.path_id = path_id;
									 O_Path_Collection.path_src = S_source;
									 O_Path_Collection.path_dst = bSubstrate;
									 O_Path_Collection.first_fs = F_index;
									 O_Path_Collection.last_fs = F_index + z - 1;
									 // O_Path_Collection_Map[O_Path_Collection.path_id_two] = O_Path_Collection;
									 O_Path_Collection_list.push_back(O_Path_Collection);
									 O_Path_Collection_Map.insert(map<int, list<Path_Collection>>::value_type(O_Path_Collection.path_id, O_Path_Collection_list));
									 O_Path_Collection_list.clear();*/
									 /*******************************************************************************************************************************************/
								 }

								 else
								 {
									 mappingSuccessMark = true;

									 O_SEdgeMap = O_originalSEdgeMap;
									 protectionMark = true;
									 break;
								 }
								 // if (mappingSuccessMark == true)
								// break;
								 // }

							 }
						 }
						 /*****************************************************************/





						 /********************for Path 2 (working) ********************/
						 if (mappingSuccessMark == false)
						 {
							 if ((S_source == aSubstrate) && (S_destination == bSubstrate) && path_id == 2)
							 {

								 int remain_bandwidth = 0;

								 int z = FS_modulationSelection(o_paths.path_distance, Original_requested_resource);
								 // for (int j = z; j >= 1; j--)
								 // {
								 if (z != INFINITE)
								 {
									 double availability_two = Availabilty_calculation(path_id, S_source, S_destination);
									 int F_index = Allocated_FS(z, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
									 if (F_index != INFINITE)
									 {
										 mappingSuccessMark = false;
										 /**************************************************************************************/
										 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
										 {
											 o_paths = *o_paths_list_iterator;
											 O_SEdge = O_SEdgeMap[o_paths.adj_edge];
											 for (int i = F_index; i < (F_index + z); i++)
											 {
												 O_SEdge.FS_Array[i] = 0;

												 O_SEdge.sEdgeResource = O_SEdge.sEdgeResource - 1;

											 }

											 O_SEdge.embeddedVedgesList.push_back(O_VEdge.vEdge_id);
											 O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
											 // O_VEdge.ontoPhyEdgeList = O_shortest_edge_path_list;     //O_shortest_edge_path_list;
											 // O_VEdge.ontoPathList.push_front(path_id);
											 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

										 }
										 /******************************************************************************************************************/
										/// cout << "Final Index of the path from : " << F_index << " to " << (F_index + z - 1) << '\n';
										 if ((8000 > o_paths.path_distance) && (o_paths.path_distance >= 4000))
										 {
											 Original_requested_resource = Original_requested_resource - (z * 25);
										 }
										 else if ((4000 > o_paths.path_distance) && (o_paths.path_distance >= 2000))
										 {
											 Original_requested_resource = Original_requested_resource - (z * 50);
										 }
										 else if ((2000 > o_paths.path_distance) && (o_paths.path_distance >= 1000))
										 {
											 Original_requested_resource = Original_requested_resource - (z * 75);
										 }
										 else if (1000 > o_paths.path_distance)
										 {
											 Original_requested_resource = Original_requested_resource - (z * 100);
										 }

										 O_VEdge.ontoPathList.push_back(path_id);
										 O_VEdge.FS_fIndex_list.push_back(F_index);
										 O_VEdge.FS_lIndex_list.push_back(F_index + z - 1);
										 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

										 /********************************************/
										 /*O_Path_Collection.path_id = path_id;
										 O_Path_Collection.path_src = S_source;
										 O_Path_Collection.path_dst = bSubstrate;
										 O_Path_Collection.first_fs = F_index;
										 O_Path_Collection.last_fs = F_index + z - 1;
										 // O_Path_Collection_Map[O_Path_Collection.path_id_two] = O_Path_Collection;
										 O_Path_Collection_list.push_back(O_Path_Collection);
										 O_Path_Collection_Map.insert(map<int, list<Path_Collection>>::value_type(O_Path_Collection.path_id, O_Path_Collection_list));
										 O_Path_Collection_list.clear();*/
										 /*********************************************/
										 if (Original_requested_resource <= 0)
										 {
											 mappingSuccessMark = true;
											 // if (availability_two < O_VEdge.availabilityRequired)
											 // {
											 pathTwoFS = z;

											 protectionMark = true;
											 // }

										 }
										 else
										 {
											 mappingSuccessMark = false;
											 O_SEdgeMap = O_originalSEdgeMap;
											 protectionMark = false;
											 break;
										 }
										 /*******************************************************************************************************************************************/
									 }

									 else
									 {
										 mappingSuccessMark = false;
										 O_SEdgeMap = O_originalSEdgeMap;
										 protectionMark = false;
										 break;
									 }
								 }

								 // if (mappingSuccessMark == true)
								// break;
								 // }
								 else
								 {
									 mappingSuccessMark = false;
								 }

							 }

						 }


						 /********************for Path 3 (Protection) ********************/
						 if (protectionMark == true && mappingSuccessMark == true)
						 {

							 if ((S_source == aSubstrate) && (S_destination == bSubstrate) && path_id == 3)
							 {

								 //int remain_bandwidth = 0;
								 int z = 0;
								 if (pathOneFS > 0 && pathTwoFS == 0)
								 {
									 z = pathOneFS;
								 }
								 else if (pathOneFS == 0 && pathTwoFS > 0)
								 {
									 z = pathTwoFS;
								 }
								 else if (pathOneFS > 0 && pathTwoFS > 0)
								 {
									 if (pathOneFS > pathTwoFS)
										 z = pathOneFS;
									 else
										 z = pathTwoFS;
								 }

								 int F_index = Allocated_FS(z, o_paths_map_iterator->first, o_paths.source_id, o_paths.destination_id);
								 if (F_index != INFINITE)
								 {
									 total_backup = total_backup + z;
									 mappingSuccessMark = true;
									 /**************************************************************************************/
									 for (o_paths_list_iterator = o_paths_list.begin(); o_paths_list_iterator != o_paths_list.end(); o_paths_list_iterator++)
									 {
										 o_paths = *o_paths_list_iterator;
										 O_SEdge = O_SEdgeMap[o_paths.adj_edge];
										 for (int i = F_index; i < (F_index + z); i++)
										 {
											 O_SEdge.FS_Array[i] = 0;

											 O_SEdge.sEdgeResource = O_SEdge.sEdgeResource - 1;

										 }

										 O_SEdge.embeddedVedgesList.push_back(O_VEdge.vEdge_id);
										 O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
										 // O_VEdge.ontoPhyEdgeList = O_shortest_edge_path_list;     //O_shortest_edge_path_list;
										 // O_VEdge.ontoPathList.push_front(path_id);
										// O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;
										 
									 }
									 /******************************************************************************************************************/
									 if (z != 0)
									 {
										 /// cout << '\n' << "Total Slots required for Protection with path 3 : " << z << endl;
										 /// cout << "       Final Index of this Protection path (path 3) from :       " << F_index << " to " << (F_index + z - 1) << '\n';

									 }



									 O_VEdge.ontoPathList.push_back(path_id);
									 O_VEdge.FS_fIndex_list.push_back(F_index);
									 O_VEdge.FS_lIndex_list.push_back(F_index + z - 1);
									 O_VEdgeMap[O_VEdge.vEdge_id] = O_VEdge;

									 protectionMark = false;

									 /********************************************/
									/* O_Path_Collection.path_id = path_id;
									 O_Path_Collection.path_src = S_source;
									 O_Path_Collection.path_dst = bSubstrate;
									 O_Path_Collection.first_fs = F_index;
									 O_Path_Collection.last_fs = F_index + z - 1;
									 //O_Path_Collection_Map[O_Path_Collection.path_id_three] = O_Path_Collection;
									 O_Path_Collection_list.push_back(O_Path_Collection);
									 O_Path_Collection_Map.insert(map<int, list<Path_Collection>>::value_type(O_Path_Collection.path_id, O_Path_Collection_list));
									 O_Path_Collection_list.clear();*/
									 /*******************************************************************************************************************************************/										 /*******************************************************************************************************************************************/
								 }

								 else
								 {
									 mappingSuccessMark = false;
									 /// cout << '\n' << "Total Slots required for Protection: " << z << endl;
									 /// cout << "    Prottection is not possible for this link.    " << endl;
									 O_SEdgeMap = O_originalSEdgeMap;
									 protectionMark = false;
									 break;
								 }
								 // if (mappingSuccessMark == true)
								// break;
								 // }

							 }
						 }

						 /****************************************************************/
						 if (mappingSuccessMark == true && protectionMark == false)
						 {
							 break;
						 }

						 /*else
						 {
							 continue;
						 }*/

						 /* if (mappingSuccessMark == false)//If this mapping is not successful
						  {
							  O_SEdgeMap = O_originalSEdgeMap;
						  }
						 // break;
						 */
					 }

					 if (Original_requested_resource <= 0)
					 {
						 mappingSuccessMark = true;
						 protectionMark = false;
					 }
					 else
					 {
						 mappingSuccessMark = false;
						 protectionMark = false;
					 }
					 //O_Path_Collection_Map.clear();

					 o_paths_map.clear();
					 o_paths_list.clear();

				 }


				 if (mappingSuccessMark == false)//If this mapping is not successful
				 {
					 //****Restore the tampered O_Compute_Node_Map, O_SEdgeMap, O_VNodeMap, O_VEdgeMap
					 O_VNodeMap = O_originalVNodeMap;
					 O_Compute_Node_map = O_originalComputeNodeMap;//O_VNodeMap and O_SNodeMap are tampered when mapping nodes to change node resources
					 O_edge_map = O_original_edge_map;
					 O_SEdgeMap = O_originalSEdgeMap;
					 O_VEdgeMap = O_originalVEdgeMap;//O_SEdgeMap and O_VEdgeMap have been tampered by changing link resources while mapping links
				 }

			 }

		 }
		 else
		 {
			 mappingSuccessMark = false;
		 }
		 if (mappingSuccessMark == false)//If this mapping is not successful
		 {
			 //****Restore the tampered O_SNodeMap, O_SEdgeMap, O_VNodeMap, O_VEdgeMap
			 O_VNodeMap = O_originalVNodeMap;
			 O_Compute_Node_map = O_originalComputeNodeMap;//O_VNodeMap and O_SNodeMap are tampered when mapping nodes to change node resources
			 O_edge_map = O_original_edge_map;
			 O_SEdgeMap = O_originalSEdgeMap;
			 O_VEdgeMap = O_originalVEdgeMap;//O_SEdgeMap and O_VEdgeMap have been tampered by changing link resources while mapping links
		 }
		 else
		 {
			 break; //Terminate for (int I = 1;I < = 24;I++) loop
		 }

	    }
		 
     }


	 if (mappingSuccessMark == true)
	 {
		// cout << "Virtual Network    " << vnetwork_id << "    Mapping Successful" << endl;
		 success = 1;
		// O_VNetwork.failedVnetList.push_back(vnetwork_id);
		// O_VNetworkMap[O_VNetwork.vNetwork_id] = O_VNetwork;
	 }
	 else
	 {
		// cout << "Virtual Network    " << vnetwork_id << "    Mapping  Not Successful" << endl;
		 success = 0;
		 failedVnetList.push_front(Net_id);
		 
	 }

	 cout << '\n' << '\n' << '\n';
	/****************************************************************************/
	return success;

}

bool C_graph::allVNetworkMapping(int totalNumOfVnet)
{
	int total_success = 0;
	ofstream outputfile("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\output_single_vNetwork_mapping_checking.txt");
	ofstream	outputfile1("E:\\MS MATERIALS\\C++ Codes\\Simulation_Comparisn\\My_algoDynamic\\VMmigration\\textfile\\New folder\\output_aftermapping_OVnodeMap_checking.txt");
	for (int i = 1; i <= totalNumOfVnet; i++)
	{
		
		int success = singleVNetworkMapping(i);
		total_success = total_success + success;
		outputfile << "vNetwork id is:   " << O_VNetwork.vNetwork_id << "      which contains  " << O_VNetwork.containedVnodeList.size() << "    vNodes  and     " << O_VNetwork.containedVlinkList.size() << "   vLinks" << endl;
		outputfile << "vNodes situation follows:" << endl;
		for (O_VNetwork.containedVnodeListIterator = O_VNetwork.containedVnodeList.begin(); O_VNetwork.containedVnodeListIterator != O_VNetwork.containedVnodeList.end(); O_VNetwork.containedVnodeListIterator++)
		{
			int vnodeId = (*O_VNetwork.containedVnodeListIterator);
			O_VNode = O_VNodeMap[vnodeId];
			outputfile << "vNode id:  " << vnodeId << "      required vNodeResource:   " << O_VNode.vNodeResourceRequested << "     mapped onto sNode:   " << O_VNode.ontoSNode << "     this sNode remaining reource is:   " << O_Compute_Node_map[O_VNode.ontoSNode]._Compute_FN << endl;
		}

		outputfile << "vLinks situation follows:" << endl;
		for (O_VNetwork.containedVlinkListIterator = O_VNetwork.containedVlinkList.begin(); O_VNetwork.containedVlinkListIterator != O_VNetwork.containedVlinkList.end(); O_VNetwork.containedVlinkListIterator++)
		{
			
			int aSubstrate, bSubstrate;
			O_VNode = O_VNodeMap[O_VEdge.aVnode];
			aSubstrate = O_VNode.ontoSNode;
			O_VNode = O_VNodeMap[O_VEdge.bVnode];
			bSubstrate = O_VNode.ontoSNode; 
			int vlinkId = (*O_VNetwork.containedVlinkListIterator);
			O_VEdge = O_VEdgeMap[vlinkId];
			outputfile << "vLink id:   " << vlinkId << "     required vLinkResource:   " << O_VEdge.vEdgeResourceRequested << "     mapped between substrate node :" << aSubstrate << " and " << bSubstrate << " With Paths :"<< endl;
			for (O_VEdge.ontoPathListIterator = O_VEdge.ontoPathList.begin(); O_VEdge.ontoPathListIterator != O_VEdge.ontoPathList.end(); O_VEdge.ontoPathListIterator++)
			{
				
				outputfile << (*O_VEdge.ontoPathListIterator) << "   ----  ";
			}
			
			outputfile << endl;


			/*outputfile << "vLink id:   " << vlinkId << "     required vLinkResource:   " << O_VEdge.vEdgeResourceRequested << "     mapped onto sNodes between " << endl;;
			for (O_VEdge.ontoPhyEdgeListIterator = O_VEdge.ontoPhyEdgeList.begin(); O_VEdge.ontoPhyEdgeListIterator != O_VEdge.ontoPhyEdgeList.end(); O_VEdge.ontoPhyEdgeListIterator++)
			{
				outputfile << (*O_VEdge.ontoPhyEdgeListIterator) << "  (" << O_SEdgeMap[*O_VEdge.ontoPhyEdgeListIterator].sEdgeResource << ")-----";
			}
			outputfile << endl;*/
			


		}

		
		
		outputfile << "*********************************************************" << endl;

		outputfile << "*********************************************************" << endl;
	}
	//for (O_VNetwork.failedVnetListIterator = O_VNetwork.failedVnetList.begin(); O_VNetwork.failedVnetListIterator != O_VNetwork.failedVnetList.end(); O_VNetwork.failedVnetListIterator++)
	//{
	cout << "The failed V_networks are : " << endl;
	for (auto v : failedVnetList)
	{
		cout << v << "    " ;
	}
	cout << '\n' << " Total backup :  " << total_backup;
	cout << '\n';
	cout << '\n';
	//}
	cout << "Total number of successful mapping is : " << total_success <<endl;
	cout << "Total number of unsuccessful mapping is : " << totalNumOfVnet-total_success << endl;
	for (O_VNodeMapIterator = O_VNodeMap.begin(); O_VNodeMapIterator != O_VNodeMap.end(); O_VNodeMapIterator++)
	{
		O_VNode = O_VNodeMapIterator->second;
		outputfile1 << "Vnode_id:  " << O_VNode.vNode_id << "   ontoSnode:  " << O_VNode.ontoSNode << "      vNodeRequestedResource: " << O_VNode.vNodeResourceRequested << endl;

	}


	return true;
}


/**************************************************************************************************************************
*************************************Implementation of Virtual Network Releasing*******************************************
***************************************************************************************************************************/

bool C_graph::singleVNetworkRelease(int vnetwork_id)
{
	O_VNetwork = O_VNetworkMap[vnetwork_id];
	//O_VNetwork.vNetwork_id << "      which contains  " << O_VNetwork.containedVnodeList.size() << "    vNodes  and     " << O_VNetwork.containedVlinkList.size() << "   vLinks" << endl;
	//outputfile << "vNodes situation follows:" << endl;
	for (O_VNetwork.containedVnodeListIterator = O_VNetwork.containedVnodeList.begin(); O_VNetwork.containedVnodeListIterator != O_VNetwork.containedVnodeList.end(); O_VNetwork.containedVnodeListIterator++)
	{
		int vnodeId = (*O_VNetwork.containedVnodeListIterator);
		O_VNode = O_VNodeMap[vnodeId];
		//outputfile << "vNode id:  " << vnodeId << "      required vNodeResource:   " << O_VNode.vNodeResourceRequested << "     mapped onto sNode:   " << O_VNode.ontoSNode << "     this sNode remaining reource is:   " << O_Compute_Node_map[O_VNode.ontoSNode]._Compute_FN << endl;
		O_Compute_Node_map[O_VNode.ontoSNode]._Compute_FN = O_Compute_Node_map[O_VNode.ontoSNode]._Compute_FN + O_VNode.vNodeResourceRequested;
	
	}
	for (O_VNetwork.containedVlinkListIterator = O_VNetwork.containedVlinkList.begin(); O_VNetwork.containedVlinkListIterator != O_VNetwork.containedVlinkList.end(); O_VNetwork.containedVlinkListIterator++)
	{
		Load_adj_graph();
		Load_edge_graph();
		int vlinkId = (*O_VNetwork.containedVlinkListIterator);
		O_VEdge = O_VEdgeMap[vlinkId];

		int aSubstrate, bSubstrate;
		O_VNode = O_VNodeMap[O_VEdge.aVnode];
		aSubstrate = O_VNode.ontoSNode;
		O_VNode = O_VNodeMap[O_VEdge.bVnode];
		bSubstrate = O_VNode.ontoSNode;
		

		
		for (O_VEdge.ontoPathListIterator = O_VEdge.ontoPathList.begin(); O_VEdge.ontoPathListIterator != O_VEdge.ontoPathList.end(); O_VEdge.ontoPathListIterator++)
		{
			
		   int path_ID =	 (*O_VEdge.ontoPathListIterator);
		  // cout << '\n' << "***********PID "<< path_ID << endl;
		   for (O_VEdge.FS_fIndex_listIterator = O_VEdge.FS_fIndex_list.begin(); O_VEdge.FS_fIndex_listIterator != O_VEdge.FS_fIndex_list.end(); O_VEdge.FS_fIndex_listIterator++)
		   {
			   
			   int fir_ind = (*O_VEdge.FS_fIndex_listIterator);
			  // cout << '\n' << "***********FID " << fir_ind << endl;
			   for (O_VEdge.FS_lIndex_listIterator = O_VEdge.FS_lIndex_list.begin(); O_VEdge.FS_lIndex_listIterator != O_VEdge.FS_lIndex_list.end(); O_VEdge.FS_lIndex_listIterator++)
			   {
				  
				   int lst_ind = (*O_VEdge.FS_lIndex_listIterator);
				  // cout << '\n' << "***********LID " << lst_ind << endl;

				   Load_adj_graph();
				   Load_edge_graph();
				   for (O_SEdgeMapIterator = O_SEdgeMap.begin(); O_SEdgeMapIterator != O_SEdgeMap.end(); O_SEdgeMapIterator++)
				   {
					   //cout << "*********** aye "  << endl;
					   O_SEdge = O_SEdgeMapIterator->second;
					   for (O_SEdge.embeddedVedgesListIterator = O_SEdge.embeddedVedgesList.begin(); O_SEdge.embeddedVedgesListIterator != O_SEdge.embeddedVedgesList.end(); O_SEdge.embeddedVedgesListIterator++)
					   {
						   int V_edge_id = (*O_SEdge.embeddedVedgesListIterator);
						   if (V_edge_id == vlinkId)
						   {
							   for (int i = fir_ind; i <= lst_ind; i++)
							   {
								   O_SEdge.FS_Array[i] = 1;

								   O_SEdge.sEdgeResource = O_SEdge.sEdgeResource + 1;

							   }

							   
							   O_SEdgeMap[O_SEdge.edge_id] = O_SEdge;
						   }
					   }

				   }
				   

				  /* for (int k = 1; k <= 3; k++)
				   {

					   Find_shortest_path(aSubstrate, bSubstrate, k);

					   Find_link_disjoint_path(aSubstrate, bSubstrate);
				   }*/
				   
				   
				  // o_paths_map.clear();
				  // o_paths_list.clear();
				   O_VEdge.FS_lIndex_list.pop_front();
				   break;

			   }

			   O_VEdge.FS_fIndex_list.pop_front();
			   break;
		   }


		}

	}
		
		
		
	return true;

}




/*
bool C_graph::checking()
{
	//for (int i = 1; i <= 24; i++)
	//{                                                      // From every Source nodes to every Destination Nodes
		//for (int j = 1; j <= 24; j++)
		//{
			//if (i != j)
			//{


				for (O_Path_Collection_Map_Iterator = O_Path_Collection_Map.begin(); O_Path_Collection_Map_Iterator != O_Path_Collection_Map.end(); O_Path_Collection_Map_Iterator++)
				{
					cout << '\n' << "Path ID:  " << O_Path_Collection_Map_Iterator->first;
					O_Path_Collection_list = O_Path_Collection_Map_Iterator->second;
					for (O_Path_Collection_list_iterator = O_Path_Collection_list.begin(); O_Path_Collection_list_iterator != O_Path_Collection_list.end(); O_Path_Collection_list_iterator++)
					{
						O_Path_Collection = *O_Path_Collection_list_iterator;
						cout << "  " << O_Path_Collection.path_src << "  " << O_Path_Collection.path_dst << "  " << O_Path_Collection.first_fs << "  " << O_Path_Collection.last_fs << endl;


					}
				}
				O_Path_Collection_Map.clear();
				O_Path_Collection_list.clear();
			//}
		//}
	//}
	return true;
}*/



/***************************************************************************************************
                                  Dynamic Request Building
****************************************************************************************************/


//***************************************************************************//
//The Exponential function You have a negative exponential distribution
//***************************************************************************//
double C_graph::Exponential(double lamda)
{
	double u;
	u = (double)rand() / (double)RAND_MAX;//u ~ U(0,1)
	while (u == 1 || u == 0)
	{
		u = (double)rand() / (double)RAND_MAX;//u ~ U(0,1)
	}
	return(-lamda * log(u));
}

//***************************************************************************//
//Description of the Random_node_pair function：Generate random node pairs
//***************************************************************************//
int C_graph::Random_V_Network_ID()
{
	//srand(time(NULL));
	
		int random_Vnet_number;

		random_Vnet_number = rand() % 100 + 1;
		
	
	return random_Vnet_number;
}

bool C_graph::Arrival_event(C_event & O_event)
{
	return true;
}

bool C_graph::Departure_event(C_event & O_event)
{

	return true;
}


//***************************************************************************************************************//
//Simulation function description: Calls to arrival_event and departure_event handle arrival and departure events
//***************************************************************************************************************//

bool C_graph::Simulation()
{
	//Define simulation variables
	double        simulation_clock;
	ULONG         request_id;
	bool          blocking; //Block marks
//	ULONG         total_request_number = 1;
	double        arrival_interval;
	double        departure_interval;
	ULONG         arrival_rate_Beta; //connection request arrival rate
	ULONG         departure_rate_Miu = 1.0;
	ULONG         arrival_counter;
	ULONG         departure_counter;
	C_event       T_event;
	C_event       O_event;
	C_event_heap  O_event_heap;
	//C_random_node_pair  O_random_node_pair;
	int total_success = 1;
	//Random seed
	srand(time(0));
	//	srand( 1 );

	//ofstream outputfile("outputfile.txt", ios::app);

	/////////////////////////////////////////////////////////////////////////////////////
	//A poisson flow with different connection strengths
	/////////////////////////////////////////////////////////////////////////////////////
	//	for( arrival_rate_Beta = 45; arrival_rate_Beta <= 60; arrival_rate_Beta += 5 )
	for (arrival_rate_Beta = Er_begin; arrival_rate_Beta <= Er_end; arrival_rate_Beta += Er_pace)
	{

		//Initialize the simulation variables
		arrival_interval = Exponential(1.0 / arrival_rate_Beta);
		
		departure_interval = Exponential(1.0 / departure_rate_Miu);
		
		//		departure_interval       = 0.0;
		simulation_clock = 0.0;
		request_id = 0;
		arrival_counter = 0;
		departure_counter = 0;
		reserved_total_capacity = 0; //Total reserved resources
//		backup_total_capacity    = 0; //The total number of actual backup resources that were not Shared
		working_tatal_capacity = 0; //Total working resources
		total_recovery_nbr = 0;
		blocking_number = 0; //Block number
		O_accepted_request_map.clear();
		//		wave                     = 1;

		//Generate the first event (arrival request)
		O_event._request_id = ++request_id;
		O_event._time = simulation_clock + arrival_interval;
		O_event._type = ARRIVAL;
		O_event._arrival_time = simulation_clock + arrival_interval;
		O_event._holding_time = departure_interval;
		srand(time(NULL));
		O_event._random_vNetwork_id = Random_V_Network_ID();
		int success = singleVNetworkMapping(O_event._request_id);
		O_event_heap.push(O_event);  //The first event goes into the heap
		
/////////////////////////////////////////////////////////////////////////////////////
//The event heap is not finished and the event is processed in a loop
/////////////////////////////////////////////////////////////////////////////////////
		while (!O_event_heap.empty())
		{
			O_event = O_event_heap.top();
			O_event_heap.pop();
			T_event = O_event;
			simulation_clock = O_event._time;  //The simulation clock is pushed to the current event

/////////////////////////////////////////////////////////////////////////////////////
// Process dynamic indication
/////////////////////////////////////////////////////////////////////////////////////

		///////////////
		//Handle arrival events
		///////////////
			if (O_event._type == ARRIVAL)
			{
				//cout<<"   request_id= "<<O_event._request_id<<"   arriving!!!"<<endl;
				cout << "-->" << O_event._request_id << endl;
				//////////////////
				//Handle the arrival event
				//////////////////
				//int success = singleVNetworkMapping(O_event._request_id);
				
				blocking = !Arrival_event(O_event);

				//////////////////
				//Generate the next arrival event
				//////////////////
				if (request_id < total_request_number)
				{
					//total_success = total_success + success;
					arrival_interval = Exponential(1.0 / arrival_rate_Beta);
					departure_interval = Exponential(1.0 / departure_rate_Miu);
					// 					cout<<endl<<"arrival_interval="<<arrival_interval<<endl;
					O_event._time = simulation_clock + arrival_interval;
					O_event._request_id = ++request_id;
					O_event._type = ARRIVAL;
					O_event._arrival_time = simulation_clock + arrival_interval;
					O_event._holding_time = departure_interval;
					//srand(time(NULL));
					O_event._random_vNetwork_id = Random_V_Network_ID();
					int success = singleVNetworkMapping(O_event._request_id);  //mapping one by one
					O_event_heap.push(O_event);
					total_success = total_success + success;
					//////////////////////////////////////////////////////////////////
					/*
							int a = rand() % 100+ 1 ;
							if( a < 5 )
							{
								blocking=true;
							}
							else
							{
								blocking=false;
							}
					*/
					//////////////////////////////////////////////////////////////////
				}//if( request_id < total_request_number )

			///////////////////
			//This departure event occurs
			///////////////////
				if (blocking == false)//Indicates that the event has been received
				{
					//					departure_interval = Exponential( 1.0/departure_rate_Miu );
					// 					cout<<endl<<"departure_interval="<<departure_interval<<endl;
					//					T_event._time      = simulation_clock + departure_interval;
					T_event._time = T_event._arrival_time + T_event._holding_time;
					T_event._type = DEPARTURE;
					O_event_heap.push(T_event);
				}
			 	else//if( blocking == true )//Indicates that the event was not received
				{
					blocking_number++;
					// outputfile<<endl;
					// outputfile<<endl;
					// outputfile<<"!!!!!!!!!!!!blocking!!!!!!!!!!!"<<"blocking_number = "<<blocking_number<<endl;
					// outputfile<<endl;
					// outputfile<<endl;

				}

			}//if( O_event._type == ARRIVAL )

		///////////////
		//Handle leaving events
		///////////////
			else//if( O_event._type == DEPARTURE )
			{
				//cout<<"request_id= "<<O_event._request_id<<"  leaving"<<endl;
				singleVNetworkRelease(O_event._request_id);
				cout << "   " << O_event._request_id << "-->" << endl;
				Departure_event(O_event);

			}

		} //while (!O_event_heap.empty());


		double blocking_rate = 0;
		blocking_rate = ((double)request_id - total_success) / (double)request_id;
		cout << '\n' << request_id << endl;

		//output of paper_5
		// 		outputfile<<endl<<"******************************************************"<<endl;
		// 		outputfile<<"Waves="<<W
		// 			<<", OEOs="<<Max_OEO_pool_size<<", min_Q="<<min_Q_factor
		// 			<<", Load="<<arrival_rate_Beta
		// 			<<", Total_requests="<<request_id<<endl<<"alpha="<<alpha<<", Share_limit="<<Share_limit<<endl;
		// 		outputfile<<"------------------------------------------------------"<<endl;
		// 		outputfile<<"total_BP= "<<blocking_rate<<"  ";
		// 		outputfile<<"wave_BP= "<<wave_block_rate<<"  ";
		// 		outputfile<<"OEO_BP= "<<OEO_block_rate<<"  ";
		// 		outputfile<<"Average Vulnerability= "<<(vulnerability + vulnerability_d) / (double)(2*(request_id - blocking_number))<<endl;
		// 		outputfile<<"------------------------------------------------------"<<endl;
		// 		outputfile<<"******************************************************"<<endl;
		
		
		cout << "The failed V_networks are : " << endl;
		for (auto v : failedVnetList)
		{
			cout << v << "    ";
		}
		cout <<'\n'<< " Total backup :  " << total_backup;
		cout << '\n';
		//}
		cout << "Total number of successful mapping is : " << total_success << endl;
		cout << "Total number of unsuccessful mapping is : " << request_id - total_success << endl;
		cout << '\n' << "Blocking rate is : " << blocking_rate << endl;
	}//for( arrival_rate_Beta = 40; arrival_rate_Beta <=200; arrival_rate_Beta +=40 )
	
	return true;
}