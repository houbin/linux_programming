#include <iostream>                                                                 
using namespace std;                                                                
/*                                                                                  
	#������#%                                                                       
          #����ʵ��#%                                                               
*/                                                                                  
//#ɸѡ�㷨#%                                                                       
void sift(int d[], int ind, int len)                                                
{                                                                                   
	//#��iΪҪɸѡ�Ľڵ�#%                                                          
	int i = ind;                                                                    
                                                                                    
	//#c�б���i�ڵ������#%                                                       
	int c = i * 2 + 1; //#+1��Ŀ�ľ���Ϊ�˽���ڵ��0��ʼ����������һֱΪ0������#%
                                                                                    
	while(c < len)//#δɸѡ��Ҷ�ӽڵ�#%                                             
	{                                                                               
		//#���Ҫɸѡ�Ľڵ�������������Һ��Ӳ�������ֵС���Һ���#%             
		//#�Ӷ�����ѡ���ϴ�Ĳ���¼#%                                               
		if(c + 1 < len && d[c] < d[c + 1])                                          
			c++;                                                                    
		//#���Ҫɸѡ�Ľڵ��е�ֵ�������Һ��ӵĽϴ������˳�#%                       
		if(d[i] > d[c]) break;                                                      
		else                                                                        
		{                                                                           
			//#����#%                                                               
			int t = d[c];                                                           
			d[c] = d[i];                                                            
			d[i] = t;                                                               
			//                                                                      
			//#����Ҫɸѡ�Ľڵ��Ҫɸѡ������#%                                   
			i = c;                                                                  
			c = 2 * i + 1;                                                          
		}                                                                           
	}                                                                               
                                                                                    
	return;                                                                         
}                                                                                   
                                                                                    
void heap_sort(int d[], int n)                                                      
{                                                                                   
	//#��ʼ������, i�����һ����Ҷ�ӽڵ㿪ʼ#%                                      
	for(int i = (n - 2) / 2; i >= 0; i--)                                           
		sift(d, i, n);                                                              
                                                                                    
	for(int j = 0; j < n; j++)                                                      
	{                                                                               
                //#����#%                                                           
		int t = d[0];                                                               
		d[0] = d[n - j - 1];                                                        
		d[n - j - 1] = t;                                                           
                                                                                    
		//#ɸѡ���Ϊ0 #%                                                           
		sift(d, 0, n - j - 1);                                                      
                                                                                    
	}                                                                               
}                                                                                   
                                                                                    
int main()                                                                          
{                                                                                   
	int a[] = {3, 5, 3, 6, 4, 7, 5, 7, 4}; //#QQ#%                                  
                                                                                    
	heap_sort(a, sizeof(a) / sizeof(*a));                                           
                                                                                    
	for(int i = 0; i < sizeof(a) / sizeof(*a); i++)                                 
	{                                                                               
		cout << a[i] << ' ';                                                        
	}                                                                               
	cout << endl;                                                                   
    return 0;                                                                       
}                                                                                   