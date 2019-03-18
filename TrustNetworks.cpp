# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

int main(const int argc, const char*argv[])
{
	vector<int> values;
	int tmp=0;
	while(cin>>tmp)
		values.push_back(tmp); //all values from input file stored in int vector

	int nu = values[0];
	
	vector<vector<bool>> adjMatrix(nu,vector<bool>(nu,false));
	
	//************
	//Reflexivity
	//************
	
	for(int a = 0; a < nu; a++)
	{
		for(int b=0;b<nu;b++)
		{
			if(a==b)
				adjMatrix[a][b]=true;
		}
	}
	
	//********************
	//Trust Relationships
	//********************
	
	bool numAfterZero=false;
	bool firstCase = true;
	int rowAfterZero=0;
		
	for(int i=1; i<values.size();i++)
	{
		if(firstCase)
		{
			while(values[i]!=0)
			{
				adjMatrix[values[1]-1][values[i]-1]=true;
				i++;
			}
			
			firstCase=false;
			if(i+1 == values.size())
				i++;
				
		}
		if(values[i] == 0)
		{
			i++;
			numAfterZero=true;
			rowAfterZero = i;
		}
		if(numAfterZero)
		{
			while(values[i]!=0)
			{
				adjMatrix[values[rowAfterZero]-1][values[i]-1]=true;
				i++;
			}
			numAfterZero=false;
			i--;
		}
	}
	
	//*************
	//Transitivity
	//*************
	
	int col = nu;
	int row = nu;
	int j=0;
	int k=0;
	
	for(int a=0;a<nu;a++)
	{	
		for(int i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				if(adjMatrix[i][j] == 1 && i!=j)
				{
					for(k=0;k<nu;k++)
					{
						if(adjMatrix[j][k] == 1  && adjMatrix[i][k] != 1)
							adjMatrix[i][k] = true;
					}
				}
			}
		}
	}
	
	//********************
	//Equivalence Classes
	//********************
	
	vector<int> equiClass;
	vector<int> userEvaluated;
	bool rowDone = false;
	bool clearVec = false;
	bool lastCom = false;

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col ;j++) 
		{
			if(adjMatrix[i][j] == 1 && adjMatrix[j][i] == 1)
				equiClass.push_back(j+1);	
			if(j==col-1)
				rowDone=true;
		}
	
		for(int a=0;a<equiClass.size();a++)
		{
			if(find(userEvaluated.begin(), userEvaluated.end(),equiClass[a]) != userEvaluated.end())
			{
				clearVec=true;
				equiClass.clear();
			}
		}
		
		if(rowDone==true && clearVec!= true)
		{
			cout<<"{";
			
			for(int i=0;i<equiClass.size();i++)
			{
				if(i == equiClass.size()-1)
					lastCom=true;
				
				cout<<equiClass[i];
			
				if(lastCom == false)
					cout<<",";
				
				userEvaluated.push_back(equiClass[i]);
			}
			cout<<"}"; cout<<endl;
			equiClass.clear();
		}
		clearVec=false;
		lastCom=false;
	}
}