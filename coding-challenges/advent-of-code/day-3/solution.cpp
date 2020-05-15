#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Point {
    int x, y;
};
struct Segment {
    Point p1, p2;
    bool isVertical;
};
 
void addSegment(vector<Segment> &segmentVector, const string &segmentString, const Point &startPoint){
    char direction = segmentString[0];
    int distance = stoi(segmentString.substr(1, segmentString.length()));
    Point endPoint = startPoint;
    bool isVertical = (direction == 'U' || direction == 'D');
    switch(direction){
        case 'R': endPoint.x += distance; break;
        case 'L': endPoint.x -= distance; break;
        case 'U': endPoint.y += distance; break;
        case 'D': endPoint.y -= distance; break;
    }
    segmentVector.push_back({startPoint, endPoint, isVertical});
}

bool isBetween(int c, int a, int b){
    if(a > b) return isBetween(c, b, a);
    return a <= c && c <= b;
}

void addIntersection(vector<Point> &intersectionPoints, const Segment &vert, const Segment &horz){
    if(isBetween(vert.p1.x, horz.p1.x, horz.p2.x)
            && isBetween(horz.p1.y, vert.p1.y, vert.p2.y)){
        intersectionPoints.push_back({vert.p1.x, horz.p1.y});
    }
}

vector<Point> getIntersectionPoints(const vector<Segment> &segmentsA, const vector<Segment> &segmentsB){
    vector<Point> intersectionPoints;
    for(const Segment &segA : segmentsA){
        for(const Segment &segB : segmentsB){
            if(segA.isVertical && !segB.isVertical){
                addIntersection(intersectionPoints, segA, segB);
            }else if(!segA.isVertical && segB.isVertical){
                addIntersection(intersectionPoints, segB, segA);
            }
        }
    }
    return intersectionPoints;
}

bool checkIfPointOnSegment(const Point &p, const Segment &seg, int &time){
    int distance = 0;
    bool pointFound = false;
    if(seg.isVertical){
        if(isBetween(p.y, seg.p1.y, seg.p2.y) && p.x == seg.p1.x){
            distance = abs(seg.p2.y - seg.p1.y) - abs(seg.p2.y - p.y);
            pointFound = true;
        }else{
            distance = abs(seg.p2.y - seg.p1.y);
        }
    }else{
        if(isBetween(p.x, seg.p1.x, seg.p2.x) && p.y == seg.p1.y){
            distance = abs(seg.p2.x - seg.p1.x) - abs(seg.p2.x - p.x);
            pointFound = true;
        }else{
            distance = abs(seg.p2.x - seg.p1.x);
        }
    }
    time += abs(distance);
    return pointFound;
}

int timeToPoint(const Point &p, const vector<Segment> &segmentsA, const vector<Segment> &segmentsB){
    int timeA = 0, timeB = 0;
    for(Segment s : segmentsA){
        if(checkIfPointOnSegment(p, s, timeA)) break;
    }
    for(Segment s : segmentsB){
        if(checkIfPointOnSegment(p, s, timeB)) break;
    }
    return timeA + timeB;
}

int main(){
    // read input file
    ifstream inputFile;
    string lineA, lineB;
    inputFile.open("input.txt");
    if(inputFile.is_open()){
        getline(inputFile, lineA);
        getline(inputFile, lineB);
    }
    inputFile.close();

    // create wire A segments
    stringstream ss(lineA);
    vector<Segment> segmentsA;
    string segmentString;
    Point startPoint = {0, 0};
    while(getline(ss, segmentString, ',')){
        addSegment(segmentsA, segmentString, startPoint);
        startPoint = segmentsA.back().p2;
    }

    // create wire B segments
    ss = stringstream(lineB);
    vector<Segment> segmentsB;
    startPoint = {0, 0};
    while(getline(ss, segmentString, ',')){
        addSegment(segmentsB, segmentString, startPoint);
        startPoint = segmentsB.back().p2;
    }

    // find smallest distance in intersection set
    vector<Point> intersectionPoints = getIntersectionPoints(segmentsA, segmentsB);
    int minDistance = INT_MAX;
    int minTime = INT_MAX;
    int distance, time = 0;
    for(const Point &p : intersectionPoints){
        if((distance = abs(p.x) + abs(p.y)) < minDistance){
            minDistance = distance;
        }
        if((time = timeToPoint(p, segmentsA, segmentsB)) < minTime){
            minTime = time;
        }
    }
    cout << "Shortest distance: " << minDistance << endl;
    cout << "Shortest time    : " << minTime << endl;
}