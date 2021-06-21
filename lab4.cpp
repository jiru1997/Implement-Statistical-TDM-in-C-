#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>
#include <map>
#include <algorithm>
#include <math.h>
using namespace std;

vector<queue<string> > data(26);


map<string, int> graph;
vector<int> order;
vector<string> result;

int main(int argc, char* argv[])
{

    ifstream file(argv[1]);
    string line;
    assert( file.is_open() );
    int index = 0;
    int lastTime = 0;
    int allSum = 0;
    while(true)
    {
        assert(getline(file,line));
        stringstream ss(line);
        if(line[1] == 'o')
        {
            string tempData;
            ss >> tempData;
            stringstream stream;
            stream << tempData[tempData.size() - 2];
            string temp = stream.str();
            graph[temp] = index;
            int cycleRead = 1;
            string everyData;
            int firstNumber = 0;
            while(ss >> tempData)
            {
                if(cycleRead % 3 == 1)
                {
                    stringstream st;
                    st << tempData;
                    int number;
                    st >> number;
                    firstNumber = number;
                    tempData = tempData + "&";
                    everyData = everyData + tempData;
                }else if(cycleRead % 3 == 2)
                {
                    stringstream st;
                    st << tempData;
                    int number;
                    st >> number;
                    allSum += (number - firstNumber);
                    lastTime = max(lastTime, number);
                    tempData = tempData + "#";
                    everyData = everyData + tempData;
                }else if(cycleRead % 3 == 0)
                {
                    if(tempData.size() == 3)
                        everyData = everyData + tempData.substr(0, tempData.size() - 1);
                    else
                        everyData = everyData + tempData;
                    data[index].push(everyData);
                    everyData = "";
                }
                cycleRead++;
            }
            index ++;

        }else{
            string tempData;
            while(ss >> tempData)
            {
                order.push_back(graph[tempData]);
            }
            break;
        }
    }


    while(true)
    {
        int tempmin = 1000000;
        bool flag = false;

        
        for(int i  = 0; i < index; i++)
        {
            int cur = order[i];
            if(!data[cur].size()) continue;
            flag = true;
            string tempcom = data[cur].front();
            int beginInt = 0;
            stringstream st;
            st << tempcom[0];
            st >> beginInt;
            tempmin = min(tempmin, beginInt);
        }

        if(flag == false)
            break;

        for(int i = 0 ; i < index; i++)
        {
            int cur = order[i];
            if(!data[cur].size()) continue;
            string tempcom = data[cur].front();
            int beginInt = 0;
            stringstream st;
            st << tempcom[0];
            st >> beginInt;
            if(beginInt == tempmin)
            {
                result.push_back(tempcom);
                data[cur].pop();
            }
        }
    }


    double dataRate = (double)lastTime / (double) allSum;
    dataRate = floor( dataRate * 100.000f + 0.5) / 100.000f;


    cout << "SF" << endl;
    double nextNumber = 0;
    for(int i = 0 ; i < result.size(); i++)
    {
        string curResult = result[i];
        double firstNumber = (double)curResult[0] - '0';
        int point = curResult.find('&');
        int secondNumber = curResult[point + 1] - '0';
        double newStep = dataRate * (secondNumber - firstNumber);
        firstNumber = nextNumber;
        newStep = firstNumber + newStep;
        nextNumber = newStep;
        point = curResult.find('#');
        stringstream st;
        st << curResult[point + 1];
        string token;
        st >> token;
        ostringstream oss;
        oss << firstNumber;
        string position1 = oss.str();
        ostringstream oss1;
        oss1 << newStep;
        string position2 = oss1.str();
        stringstream st2;
        st2 << graph[token];
        string position3;
        st2 >> position3;
        string result = position3 + "," + " " + position1 + " " + position2 + " " + curResult.substr(point + 1);
        cout << result << endl;
    }

    cout << "EF" << endl;
    return 0;
}
