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
    Point start, end;
    bool isVertical;
};
 
void addSegment(vector<Segment> &segmentVector, const string &parameter, const Point &startPoint){
    char direction = parameter[0];
    int distance = stoi(parameter.substr(1, parameter.length()));
    Point endPoint = startPoint;
    bool isVertical = false;
    switch(direction){
        case 'R': endPoint.x += distance; break;
        case 'L': endPoint.x -= distance; break;
        case 'U':
            endPoint.y += distance;
            isVertical = true;
            break;
        case 'D':
            endPoint.y -= distance;
            isVertical = true;
    }
    segmentVector.push_back({startPoint, endPoint, isVertical});
}

// checks if c is within [a, b] or [b, a]
bool withinRange(int c, int a, int b){
    int start = a >= b ? b : a;
    int end = a >= b ? a : b;
    return start <= c && c <= end;
}

// takes vertical segment first 
void addIntersection(vector<Point> &intersectionPoints, const Segment &vert, const Segment &horz){
    if(withinRange(vert.start.x, horz.start.x, horz.end.x)
            && withinRange(horz.start.y, vert.start.y, vert.end.y)){
        intersectionPoints.push_back({vert.start.x, horz.start.y});
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
        if(withinRange(p.y, seg.start.y, seg.end.y) && p.x == seg.start.x){
            distance = abs(seg.end.y - seg.start.y) - abs(seg.end.y - p.y);
            pointFound = true;
        }else{
            distance = abs(seg.end.y - seg.start.y);
        }
    }else{
        if(withinRange(p.x, seg.start.x, seg.end.x) && p.y == seg.start.y){
            distance = abs(seg.end.x - seg.start.x) - abs(seg.end.x - p.x);
            pointFound = true;
        }else{
            distance = abs(seg.end.x - seg.start.x);
        }
    }
    time += abs(distance);
    return pointFound;
}

int timeToPoint(const Point &p, const vector<Segment> &segmentsA, const vector<Segment> &segmentsB){
    int timeA = 0;
    for(Segment s : segmentsA){
        if(checkIfPointOnSegment(p, s, timeA)) break;
    }
    int timeB = 0;
    for(Segment s : segmentsB){
        if(checkIfPointOnSegment(p, s, timeB)) break;
    }
    return timeA + timeB;
}

int main(){
    // read input file
    ifstream inputFile;
    string lineA;
    string lineB;
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
    Point currentCoords = {0, 0};
    while(getline(ss, segmentString, ',')){
        addSegment(segmentsA, segmentString, currentCoords);
        currentCoords = segmentsA.back().end;
    }

    // create wire B segments
    ss = stringstream(lineB);
    vector<Segment> segmentsB;
    currentCoords = {0, 0};
    while(getline(ss, segmentString, ',')){
        addSegment(segmentsB, segmentString, currentCoords);
        currentCoords = segmentsB.back().end;
    }

    // find smallest distance in intersection set
    vector<Point> intersectionPoints = getIntersectionPoints(segmentsA, segmentsB);
    int minDistance = INT_MAX;
    int minTime = INT_MAX;
    int distance = 0;
    int time = 0;
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