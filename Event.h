#include "head.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


//***************************************************************************//
//C_event_contrast��˵���������¼��Ѷ�Ԫ��(ʱ��)���ȼ��Ƚ�
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
//C_event_heap��˵�������ڶ����¼��ѣ���Сʱ��������ǰ
//***************************************************************************//
typedef	priority_queue<C_event, vector<C_event>, C_event_contrast > C_event_heap;//��

