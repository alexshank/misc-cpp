#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

// represents a tree of masses (parents) orbitted by satellites (children)
class Node {
    private:
        string mass;
        set<Node> satellites;

        // determine if node contains a child
        int contains(const string &mass) const {
            bool found = false;
            if((this->mass).compare(mass) == 0){
                found = true;
            }else if((this->satellites).size() > 0){
                for(const Node &satellite : this->satellites){
                    found = satellite.contains(mass);
                    if(found) break;
                }
            }
            return found;
        }

        // determine if node contains both given children (used to find
        // diverging point of tree to you and santa)
        int containsBoth(const string &massA, const string &massB) const {
            bool containsA = false;
            bool containsB = false;
            for(const Node &satellite : this->satellites){
                if(satellite.contains(massA)) containsA = true;
                if(satellite.contains(massB)) containsB = true;
            }
            return containsA && containsB;
        }

        // distance from root node to given node
        int distance(const string &mass, const int &level) const {
            int distance = -1;
            if((this->mass).compare(mass) == 0){
                distance = level;
            }else if((this->satellites).size() > 0){
                for(const Node &satellite : this->satellites){
                    if(satellite.contains(mass)){
                        distance = satellite.distance(mass, level + 1);
                    }
                }
            }
            return distance;
        }

        // lowest node that contains both children
        int divergingLevel(const string &massA, const string &massB, const int &level) const {
            if((this->satellites).size() > 0){
                for(const Node &satellite : this->satellites){
                    if(satellite.containsBoth(massA, massB)){
                        return satellite.divergingLevel(massA, massB, level + 1);
                    }
                }
            }
            return level;
        }

    public:
        Node(const string &mass, const vector<string> &orbits){
            this->mass = mass.substr(0,3);
            for(const string orbitPair : orbits){
                // add children satellites circling this mass 
                if(orbitPair.substr(0, 3).compare(this->mass) == 0){
                    satellites.insert(Node(orbitPair.substr(4, 7), orbits));
                }
            }
        }

        // needed for ordered set
        bool operator<(const Node &a) const {
            return this->mass < a.mass;
        }

        // number of direct children in entire tree
        int directChildCount() const {
            int result = satellites.size();
            if(satellites.size() > 0){
                for(Node child : satellites){
                    result += child.directChildCount();
                }
            }
            return result;
        }
        
        // number of indirect children in entire tree
        int indirectChildCount(const int &level) const {
            int result = 0;
            if (satellites.size() > 0){
                for(Node child : satellites){
                    // indirect children of current node
                    result += child.satellites.size() * level;
                    // indirect children of current node's children
                    if(child.satellites.size() > 0){
                        result += child.indirectChildCount(level + 1);
                    }
                }
            }
            return result;
        }

        // moves needed by santa and you to reach diverging point of tree
        // orbital dist of (Y->D + S->D) = orbital dist of (You->Santa)
        // subtract 2 because alogorithm counts the two starting positions
        int orbitalTransfers(const string &massA, const string &massB) const {
            int yourDist = this->distance(massA, 0);
            int santaDist = this->distance(massB, 0);
            int divergeLevel = this->divergingLevel(massA, massB, 0);
            return (yourDist - divergeLevel) + (santaDist - divergeLevel) - 2;
        }
};

int main(){
    // read input file
    ifstream inputFile;
    string line;
    vector<string> orbits;
    inputFile.open("input.txt");
    if(inputFile.is_open()){
        while(getline(inputFile, line)){
            orbits.push_back(line);
        }
    }
    inputFile.close();

    Node test = Node("COM", orbits);
    cout << "Part I : " << test.directChildCount() + test.indirectChildCount(1) << endl;
    cout << "Part II: " << test.orbitalTransfers("YOU", "SAN") << endl;
}