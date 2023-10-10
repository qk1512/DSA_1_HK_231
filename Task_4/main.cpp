#include "main.h"
#include "Restaurant.cpp"
#include <vector>


void simulate(string filename, imp_res* r)
{
	ifstream ss(filename);
	if(ss.fail())
	{
		cout << "ERROR: " << filename << endl;
		return;
	}
	string str, maxsize, name, energy, num;
	int i = 1;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "RED") // RED <NAME> <ENERGY>
        {
            ss >> name;
            ss >> energy;
            r->RED(name, stoi(energy));
    	}
    	else if(str == "BLUE") // BLUE <NUM>
    	{
                ss >> num;
    			r->BLUE(stoi(num));
		}
    	else if(str == "PURPLE") // PURPLE
    	{
    			r->PURPLE();
		}
		else if(str == "REVERSAL") // REVERSAL
		{
    			r->REVERSAL();	
		}
    	else if(str == "UNLIMITED_VOID") // UNLIMITED_VOID
     	{   	
    			r->UNLIMITED_VOID();
    	}
    	else if(str == "DOMAIN_EXPANSION") // DOMAIN_EXPANSION
    	{
				solution << str << " " << "line " << i << endl;
    			r->DOMAIN_EXPANSION();
    	}
    	else // LIGHT <NUM>
    	{
			ss >> num;
			solution << str << " " << num << " " << "line " << i << endl;
			r->LIGHT(stoi(num));
    	}
		i++;
    }
}

void printTestFail(int i)
{

	string file_solution_you = "test/solution_you/output" + to_string(i) + ".txt";
	string file_solution = "test/solution/output" + to_string(i) + ".txt";
	ifstream read_solution_you(file_solution_you);
	ifstream read_solution(file_solution);
	string s1, s2;
	int  k = 1;
	while(read_solution_you >> s1 && read_solution >> s2)
	{
		if(s1 != s2){
			cout << "fail test " << i << " line " << k << endl;
			break;
		}
		if(s1 == "LIGHT")
		{
			read_solution_you >> s1 ; read_solution >> s2;
			read_solution_you >> s1 ; read_solution >> s2;
			read_solution_you >> s1 ; read_solution >> s2;
		}
		k ++;
	}
	if(read_solution_you >> s1 || read_solution >> s2){
		cout << "fail test " << i << " line " << k << endl;
	}
}

void comparefile(int start, int end)
{
	string folder_solution_you = "test/solution_you/output";
	string folder_solution = "test/solution/output";
	vector<int> result;
	for(int i = start; i <= end; i++)
	{
		string file_solution_you = folder_solution_you + to_string(i) + ".txt";
		string file_solution = folder_solution + to_string(i) + ".txt";

		ifstream read_solution_you(file_solution_you);
		ifstream read_solution(file_solution);
		if(read_solution_you.fail() || read_solution.fail())
		{
			cout << "Error reading file\n" << end;
			return;
		}
		string s1, s2;
		while(read_solution_you >> s1 && read_solution >> s2)
		{
			if(s1 != s2){
				result.push_back(i);
				break;
			}
		}
		if(read_solution_you >> s1 || read_solution >> s2){
			if(result.size() > 0 && result[result.size() - 1] != i)
			result.push_back(i);
		}
	}

	if(result.size() == 0){
		cout << "Success: test " << start << " to " << end << endl; 
	}
	else
	{
		cout << "percent success : " << (1 - result.size() * 1.0 / (end - start + 1)) * 100 << "%" << endl;
		cout << "Fail : test [";
		for(int i = 0; i < result.size()- 1; i++){
			cout << result[i] << ", ";
		}
		cout << result[result.size() - 1] << "]\n";
		printTestFail(result[0]);
	}
	
}


int main(int argc, char* argv[]) {
	cout << "Start program" << endl;
	string folder_input = "test/input/input";
	string folder_solution_you = "test/solution_you/output";
{
	int start = 1;
	int end = 100;

	if(argc < 2 || argc == 2 && argv[1][0] == 'a')
	{
		cout << "checking : "; 
		for(int i = start; i <= end; i++)
		{
			cout << i << " ";
			solution.open(folder_solution_you + to_string(i) + ".txt");
			imp_res* r = new imp_res();
			string fileName = folder_input + to_string(i) + ".txt";
			simulate(fileName, r);
			delete r;			
			solution.close();
		}
		cout << "\nOK: runs without errors\n" << endl;
		comparefile(start, end);
	}
	else if(argc == 2)
	{
		string s = argv[1];
		solution.open(folder_solution_you + s + ".txt");
		imp_res* r = new imp_res();
		string fileName = folder_input + s + ".txt";
		simulate(fileName, r);
		delete r;			
		solution.close();
		cout << "\nOK: runs without errors\n" << endl;
		comparefile(stoi(s), stoi(s));
	}
	else if(argc == 3)
	{
		cout << "checking : "; 
		string s1 = argv[1], s2 = argv[2];
		start = stoi(s1);
		end = stoi(s2);
		for(int i = start; i <= end; i++)
		{
			cout << i << " ";
			solution.open(folder_solution_you + to_string(i) + ".txt");
			imp_res* r = new imp_res();
			string fileName = folder_input + to_string(i) + ".txt";
			simulate(fileName, r);
			delete r;			
			solution.close();
		}
		cout << "\nOK: runs without errors\n" << endl;
		comparefile(start, end);		
	}
}
	
}

