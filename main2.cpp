#include "graph2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


bool similar(string w1, string w2){
	//function that checks if two words are different by exactly 1 letter
	int differences = 0;
	for(int i = 0; i < w1.length(); i++){
		if(w1[i]!=w2[i]){ //compare each letter
			differences++;
		}
	}
	return differences==1;
}


graph words_to_graph(const string wordfile, vector<string>& v1){
	cout<<"reading dictionary into graph..."<<endl<<endl;
	graph g;
	ifstream file1(wordfile); //open file

	string w;
	while(file1 >> w){//add all words to the graph and vector
		v1.push_back(w);
		g.add_vertex();
	}
	file1.close();

	for(size_t i = 0; i<v1.size(); i++){//iterate across the entire vector
		for(size_t j = 1+i; j<v1.size(); j++){//iterate across remaining elements
			if(similar(v1[i],v1[j])){//add edge to graph if similar
				g.add_edge(i,j);
			}
		}
	}
	return g;
}

void solve_doublet(string w1, string w2, graph& g, vector<string>& words){
	cout<<"Solving "<<w1<<" to "<<w2<<"..."<<endl;
	unordered_map<size_t, size_t> parent; //map to store breadth first search path
    queue<size_t> q; //queue for breadth first seach

    //size_t's to find the index of the start and ending word in the graph
    size_t start_vertex =0;
    size_t end_vertex =0;
    for (size_t i = 0; i <words.size();i++){ //loop over graph to get index
        if(words[i] == w1) {
            start_vertex = i;
        }
        if(words[i] == w2) {
            end_vertex = i;
        }
    }

    //add the starting vertex to the map and queue
    parent[start_vertex] = start_vertex; //parent of start vertex is itself
    q.push(start_vertex);

    while(!q.empty()){//breadth first search algorithm
        size_t current_vertex = q.front();//take first element from queue
        q.pop();
        if(current_vertex == end_vertex){// if the end word is found
            break;//exit the loop
        }
        list<size_t> neighbors = g.neighbors(current_vertex);//create list of the current neighbors
        for(auto neighbor : neighbors){//loop over neighborgs
            if(parent.find(neighbor) == parent.end()){//if the neighbor hasn't been visisted yet
                parent[neighbor] = current_vertex;//add to map
                q.push(neighbor);// add to queue
            }
        }
    }


    vector<string> solution_vector;
    if(parent.find(end_vertex) != parent.end()){//checks if there is a solution
        size_t vertex = end_vertex;
        while(vertex != start_vertex){ //iterate across parent map in reverse
            solution_vector.push_back(words[vertex]); // add to solution vector
            vertex = parent[vertex];
        }
        solution_vector.push_back(w1);//add begining word
        reverse(solution_vector.begin(), solution_vector.end());
    }
    else{
    	cout<<"There is no solution!"<<endl<<endl;
    	return;
    }

    //print the solution
    for(size_t i = 0; i< solution_vector.size()-1; i++){
    	cout<<solution_vector[i]<<" -> ";
    }
    cout<<solution_vector[solution_vector.size()-1]<<endl<<endl;
}

int main(){
	cout<<endl;
	vector<string> words;
	graph g1 = words_to_graph("knuth.txt",words);

	solve_doublet("black","white",g1,words);
	solve_doublet("tears","smile",g1,words);
	solve_doublet("small","giant",g1,words);
	solve_doublet("stone","money",g1,words);
	solve_doublet("angel","devil",g1,words);
	solve_doublet("amino","right",g1,words);
	solve_doublet("amigo","signs",g1,words);
	
	return 0;
}