#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

bool search(int value, vector<int>& FrameTable)
{
    for (int i = 0; i < FrameTable.size(); i++)
        if (FrameTable[i] == value)
            return true;
    return false;
}

int check(int pageTable[], vector<int>& FrameTable, int SizeOfPage, int index) {
    bool c = false;
    for (int i = 0; i < FrameTable.size(); i++) {
        int j;
        c = false;
        for (j = index; j < SizeOfPage; j++) {
            if (FrameTable[i] == pageTable[j]) {
                c = true;
                break;
            }
        }
        if (c == true) { break; }
    }
    if (c == true) { return false; }
    return true;
}

int checkFuture(int pageTable[], unordered_map<int, int> indices, vector<int>& FrameTable, int SizeOfPage, int index)
{
    bool ch = check(pageTable, FrameTable, SizeOfPage, index);
    if (ch) {
        int m, y;
        int z = INT_MAX;
        for (auto x : FrameTable) {
            if (indices[x] < z)
            {
                z = indices[x];
                y = x;
            }
        }
        auto it = find(FrameTable.begin(), FrameTable.end(), y);
        if (it != FrameTable.end()) {
            m = it - FrameTable.begin();
        }
        return m;
    }
    else
    {
        int tempo = -1, furthest = index, y, m;
        for (int i = 0; i < FrameTable.size(); i++) {
            int j;
            bool c = false;
            for (j = index; j < SizeOfPage; j++) {
                if (FrameTable[i] == pageTable[j]) {
                    if (j > furthest) {
                        furthest = j;
                        tempo = i;
                    }
                    c = true;
                    break;
                }
            }
            if (j == SizeOfPage) {
                return i;
            }
        }
        return (tempo == -1) ? 0 : tempo;
    }
}

void optimalPage(int pageTable[], int SizeOfPage, int frameSize)
{
    vector<int> FrameTable;
    unordered_map<int, int> indices;
    int numberOfHits = 0;
    for (int i = 0; i < SizeOfPage; i++) {
        if (search(pageTable[i], FrameTable)) {
            numberOfHits++;
            continue;
        }
        if (FrameTable.size() < frameSize)
        {
            FrameTable.push_back(pageTable[i]);
            indices[pageTable[i]] = i;
        }
        else {
            int j = checkFuture(pageTable, indices, FrameTable, SizeOfPage, i + 1);
            FrameTable[j] = pageTable[i];
            indices[pageTable[i]] = i;
        }
        cout << "\n";
        for (auto j = FrameTable.begin(); j != FrameTable.end(); ++j) {
            cout << *j;
        }
    }
    cout << endl << "No. of Hits = " << numberOfHits << endl;
    cout << "no of misses = " << SizeOfPage - numberOfHits << endl;
}

int main()
{
    int pageTable[] = { 1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7 ,6, 3, 2, 1, 2, 3, 6 };
    int SizeOfPage = sizeof(pageTable) / sizeof(pageTable[0]);
    int frameSize = 5;
    optimalPage(pageTable, SizeOfPage, frameSize);
    return 0;
}