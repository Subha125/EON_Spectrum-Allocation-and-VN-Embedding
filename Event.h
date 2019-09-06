#include "head.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


//***************************************************************************//
//C_event_contrast类说明：用于事件堆堆元素(时间)优先级比较
//***************************************************************************//
class C_event_contrast:binary_function < const C_event&, const C_event&, bool >
{
	public:
		bool operator()(const C_event& a, const C_event& b) const
		{
			if(a._time > b._time)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
};

//***************************************************************************//
//C_event_heap类说明：用于定义事件堆，最小时间排在最前
//***************************************************************************//
typedef	priority_queue<C_event, vector<C_event>, C_event_contrast > C_event_heap;//堆

