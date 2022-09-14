#include <iostream>
#include <sstream>
#include "graphiso.h"

using namespace std;

// ================= Complete - Begin Graph class implementation ===================
Graph::Graph(std::istream& istr)
{
    string aline;
    while(getline(istr,aline))
    {
        istringstream iss(aline);
        string u, v;
        if(iss >> u){
            VERTEX_SET_T neighbors;
            while(iss >> v)
            {
                neighbors.insert(v);
            }
            adj_.insert(std::make_pair(u,neighbors));
        }
    }
}


bool Graph::edgeExists(const VERTEX_T& u, const VERTEX_T& v) const
{
    if((adj_.find(u) != adj_.end()) && (adj_.at(u).find(v) != adj_.at(u).end()))
    {
        return true;
    }
    return false;
}
const VERTEX_SET_T& Graph::neighbors(const VERTEX_T& v) const
{
    if(adj_.find(v) == adj_.end()){
        throw std::invalid_argument("Neighbors: invalid vertex - not in  map");
    }
    return adj_.at(v);
}
VERTEX_LIST_T Graph::vertices() const
{
    VERTEX_LIST_T verts;
    for(const auto& p : adj_)
    {
        verts.push_back(p.first);
    }
    return verts;
}
// ================= Complete - End Graph class implementation ===================

// Prototype and helper functions here
bool isConsistent(VERTEX_LIST_T g1verts, unsigned int g1vCount, const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping);
bool isoHelper(VERTEX_LIST_T g1verts, VERTEX_SET_T g2verts, unsigned int g1vCount, unsigned int g2vCount, 
    const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping);

// To be completed
bool isConsistent(VERTEX_LIST_T g1verts, unsigned int g1vCount, const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    //iterate through the map to make sure each vertex pair has the same number of neighbors (same degree)
    for(unsigned int i=0; i<=g1vCount; i++)
    {
        // Check mappings for necessary vertices to see if there is any violation
        // and return false
        if(g1.neighbors(g1verts[i]).size() != g2.neighbors(mapping[g1verts[i]]).size()){
            return false;
        }

        for(auto n : g1.neighbors(g1verts[i])){
            if(mapping.find(n) != nullptr){
                if(!(g2.edgeExists(mapping[g1verts[i]], mapping[n]))){
                    return false;
                }
            }
        }
    }
    return true;
}

// Add any helper functions you deem useful
bool isoHelper(VERTEX_LIST_T g1verts, VERTEX_SET_T g2verts, unsigned int g1vCount, unsigned int g2vCount, 
    const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    //if all g1 vertices have successfully been explored, return true
    if(g1vCount == g1verts.size()){
        return true;
    }

    //if all g2 vertices have been explored for this g1 vertex, move on to the next
    if(g2vCount == g2.vertices().size()){
        return isoHelper(g1verts, g2verts, g1vCount+1, 0, g1, g2, mapping);
    }
    else{
        //iterate through the vertices of g2
        for(auto g2v : g2.vertices()){
            //make sure this g2 vertex isn't already mapped
            if(g2verts.find(g2v) == g2verts.end()){
                g2verts.insert(g2v);
                //insert the g1 vertex, g2 vertex pair into the hash table
                mapping.insert({g1verts[g1vCount], g2v});
                //if the isomorph is valid
                if(isConsistent(g1verts, g1vCount, g1, g2, mapping)){
                    //move through the vertices, if they all return true, return true
                    if(isoHelper(g1verts, g2verts, g1vCount+1, 0, g1, g2, mapping)){
                        return true;
                    }
                }
                //if it didn't work out, remove it from the set so it can be checked for other g1 vertices
                g2verts.erase(g2v);
            }
        }
        //something didn't work, remove that vertex pair, return false to backtrack

        mapping.remove(g1verts[g1vCount]);
        return false;
    }
}

// To be completed
bool graphIso(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    VERTEX_LIST_T g1verts = g1.vertices();
    VERTEX_SET_T g2verts;
    if(g1verts.size() != g2.vertices().size())
    {
        return false;
    }
    // Add code here
    
    // Delete this and return the correct value...
    // This is just placeholder to allow compilation
    return isoHelper(g1verts, g2verts, 0, 0, g1, g2, mapping);
}

