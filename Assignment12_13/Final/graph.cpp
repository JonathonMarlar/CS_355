#include"graph.h"
#include<string>
using namespace std;

void print(ostream&,int *,int);
int menu();


int main()
{

	ifstream infile;
	ofstream outfile;
	graph G;
	bool flag = false, flag2 = true;
	int choice, a = -1,  b= -1;
	string fileName;
	while(choice = menu())
	{
		switch(choice)
		{
		case 1:
			if(flag2)
			{
				while(!flag)
				{
					cout << "Please enter the file name: ";
					cin >> fileName;
					infile.open(fileName.c_str());
					if(infile)
						flag = true;
					else
					{
						cout << "ERROR FILE NOT FOUND!" << endl;
						system("pause");
						system("cls");
					}
				}
				G.setSize(infile);
				G.build(infile);
				flag2 = false;
			}
			else
			{
				cout << "Please clear the current graph before loading a new one." <<endl;
				
			}
			break;
		case 2:
			G.print(cout);
			break;
		case 3:
			if ( flag ) 
			{
				a=b=-1;
				while(a < 0 || b < 0 || a > G.getSize() || b > G.getSize())
				{
					cout <<"Please enter your starting point: ";
					cin >> a;			
					cout << "Please enter your ending point: ";
					cin >> b;
				}
				if(G.shortestPathU(a-1,b-1))
				{
					G.print(cout);
					cout << "The shortest path from " << a <<" to " << b << " is: ";
					print(cout,G.getPath(),G.getSize());
				}
				else
					cout << "No path exists from " << a << " to " << b << endl;
			}
			else
			{
				cout << "No graph loaded." << endl;
			}
			break;
		case 4:
			if ( flag )
			{
				G.~graph();
				flag = false;
				flag2 = true;
				infile.close();
			}
			else
				cout << "No graph loaded." << endl;
			break;		
		}
		system("pause");
		system("cls");
	}
	infile.close();
	system("pause");
	return 0;
}
void print(ostream& out,int * ar,int e)
{	
	out << "{ ";
	for(int c = 0; c < e; c++)
	{
		if(ar[c] != -1)
			out << ar[c]+1 << ' ';
	}
	out << '}';
	out << endl;
}

int menu()
{
	int choice;
	
	cout << "1. Choose file" << endl;
	cout << "2. Print graph" << endl;
	cout << "3. Show shortest path" << endl;
	cout << "4. Clear current graph." << endl;
	cout << "0. EXIT"<<endl;
	cout << "Please enter your choice: ";
	cin >> choice;
	system("cls");
	return choice;
}

