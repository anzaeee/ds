//Class-based approach to making a graph by reading input from a file.


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class edges
{
    public:
        edges()
        {}

    private:
        string label;
        int weight;
};

class vertices
{
    private:
        string label;
        edges* edges_list;
        int time;
    public:
        vertices()
        {}
        vertices* current_vertice() {return this;}
        void set_label(string x)
        {
            this->label = x;
        }
        void set_time(int x) { this->time = x;}
        void set_edges_list( edges* x) {this->edges_list = x;}
};



class graph
{
    private:
        int delivery_time;
        int total_vertices;
        vertices* V; //making this to access member functions of vertices class
        edges* E; //makign this to access member functions of edges class
    
    public:
    //member variables
    //    int delivery_time;
     //   int numberofvertices;

        graph() {}
        void set_vertices(vertices* x)
        {
            this->V = x; //start of the vertices array
        }
        vertices* get_vertices(){ return V;}
        void set_total_vertices(int n)
        {
            this->total_vertices = n;
        }
        int get_total_vertices()
        {
            return this->total_vertices;
        }

        void add_edge(string label, int weight)
        {

        }
        void set_delivery_time( int x) {this->delivery_time = x;}
        int get_delivery_time() {return this->delivery_time; }
        void create_graph(string filename)
        {
            
            fstream file;
	        file.open(filename, ios::in);
            string line;

            while (!file.eof()) {
                getline(file, line);
                char key = line[0];
                if (line == "")			//to break if the line is empty
                    break;

                stringstream d(line);

                if (key == 'V')
                {
                    string v; //to store the vertices
                    for (int i = 1; i <= line.size(); i++)
                    {
                            if (line[i] == ',' or line[i] == '=' or line[i] == '{' or line[i] == '}' )
                                continue;
                            else
                                v += line[i];
                    }
                    this->set_total_vertices(v.length() - 2);

                    //Now to create the vertices array
                    vertices* arr = new vertices[this->get_total_vertices()];
                    this->set_vertices(arr);
                    for (int i = 0; i < this->get_total_vertices(); i++)
                        (arr + i)->set_label(to_string(line[i]));
                }
                else if ( key == 'E')
                {
                    vertices* V = get_vertices();
                }
                else if ( key == 'W')
                {
                    //weights are periodically not required therefore skipping as of right now
                }
                else if (key == 'T')
                {
                    string time;
                    for (int i = 1; i <= line.size(); i++)
                    {
                        if(line[i] == key or line[i] =='=')
                            continue;
                        else
                            time += line[i];
                    }

                    this->set_delivery_time(stoi(time));
                    }

                }
        }
        void hamilton_circuit()
        {

        }
};

int main()
{
    graph G;
    G.create_graph("input.txt");

}
