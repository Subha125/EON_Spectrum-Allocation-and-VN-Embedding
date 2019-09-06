#include "head.h"
//#include<conio.h>
int main()
{
	//int srcid, dstid;
  //public: 
	//  int k;
	C_graph	O_graph;
	O_graph.Load_edge_graph();
	O_graph.Load_compute_node_graph();
	O_graph.Load_adj_graph();
	O_graph.Output_adj_map();
	O_graph.sEdgeResourceProvision();
	
	//	O_graph.Output_paths_map();
   // O_graph.Output_Allpaths_map();
	O_graph.allVNetworksGeneration(300);
	
	//O_graph.Allocated_FS(4,2,1,5);
	// O_graph.FS_modulationSelection(999, 380);
	//O_graph.singleVNetworkMapping(3);
	//O_graph.Load_compute_node_graph();
	//O_graph.Load_adj_graph();
	//O_graph.Output_adj_map();
	O_graph.allVNetworkMapping(300);
    //O_graph.Simulation();
	O_graph.sEdgeResourceUpdated();
	O_graph.sNodeResourceUpdated();
	//O_graph.checking();
	system("pause");
	return 0;
}