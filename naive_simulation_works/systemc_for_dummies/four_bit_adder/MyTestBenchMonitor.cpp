#include "MyTestBenchMonitor.h"

void MyTestBenchMonitor::Display_Patterns()
{
	cout << "At time : " << sc_time_stamp();

#if 0
	for(int i=0;i<4;i++)
	{	
		cout << "\ta = "; cout <<  TBM_a[i] ;
		cout << "\tB = "; cout << TBM_b[i] ;
		if(i == 3)
	        {
			i++;
			cout << "\tz = "; cout << TBM_z[i] << TBM_z[i-1] ;
		}
		else
			cout << "\tz = "; cout << TBM_z[i];
		cout << endl;
	}
#endif
	cout << "\ta = ";
       	for (int i = 3; i >= 0; i--)
		cout << TBM_a[i];

	cout << "\tb = ";
	for (int i = 3; i >= 0; i--)
		cout << TBM_b[i];

	cout << "\tz = ";
	for (int i = 4; i >= 0; i--)
		cout << TBM_z[i];

	cout << endl;
}

