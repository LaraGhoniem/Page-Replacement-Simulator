#include<bits/stdc++.h>
using namespace std;

void FIFO_LRU(int *input,int NumberOfFrames,int n,int alg)
{
    deque<int> frames;
    unordered_map<int, int> indices;
    int faults = 0;
    for (int i=0; i<n; i++)
    {
        if(find(frames.begin(), frames.end(), (input[i])) != frames.end())
        {
            cout<<endl<<input[i]<<" already present (no page fault) \n";
            if(alg==2)
            indices[input[i]] = i;
        }
        else
        {
            cout<<"\n";
            if (frames.size() < NumberOfFrames)
            {
                frames.push_back(input[i]);
                faults++;
            }
            else
            {
                int j = INT_MAX, y;
                for (auto x : frames)
                {
                    if (indices[x] < j)
                    {
                        j = indices[x];
                        y = x;
                    }
                }
                for(auto x : frames){
                    if(x!=y){
                        frames.pop_front();
                        frames.push_back(x);
                    }
                    else{
                        frames.pop_front();
                        frames.push_back(input[i]);
                    }
                }
                faults++;
            }
            for(auto j=frames.begin();j!=frames.end();++j){
                cout<<*j;
            }
            cout<<" (page fault)\n";
            indices[input[i]] = i;
        }
        
    }
    cout<<endl<<"Final: ";
    for(auto j=frames.begin();j!=frames.end();++j){
        cout<<*j;
    }
    cout<<endl<<"Page Faults: "<<faults;
}


bool search(int value, vector<int>& FrameTable)
{
    for (int i = 0; i < FrameTable.size(); i++)
        if (FrameTable[i] == value)
            return true;
    return false;
}

int check(int input[], vector<int>& FrameTable, int n, int index) {
    bool c = false;
    for (int i = 0; i < FrameTable.size(); i++) {
        int j;
        c = false;
        for (j = index; j < n; j++) {
            if (FrameTable[i] == input[j]) {
                c = true;
                break;
            }
        }
        if (c == true) { break; }
    }
    if (c == true) { return false; }
    return true;
}

int checkFuture(int input[], unordered_map<int, int> indices, vector<int>& FrameTable, int n, int index)
{
    bool ch = check(input, FrameTable, n, index);
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
            for (j = index; j < n; j++) {
                if (FrameTable[i] == input[j]) {
                    if (j > furthest) {
                        furthest = j;
                        tempo = i;
                    }
                    c = true;
                    break;
                }
            }
            if (j == n) {
                return i;
            }
        }
        return (tempo == -1) ? 0 : tempo;
    }
}

void OPT(int *input,int NumberOfFrames,int n)
{
    vector<int> FrameTable;
    unordered_map<int, int> indices;
    int numberOfHits = 0;
    for (int i = 0; i < n; i++) {
        if (search(input[i], FrameTable)) {
            cout<<endl<<input[i]<<" already present (no page fault) \n";
            numberOfHits++;
            continue;
        }
        if (FrameTable.size() < NumberOfFrames)
        {
            FrameTable.push_back(input[i]);
            indices[input[i]] = i;
        }
        else {
            int j = checkFuture(input, indices, FrameTable, n, i + 1);
            FrameTable[j] = input[i];
            indices[input[i]] = i;
        }
        cout<<"\n";
        for(auto j=FrameTable.begin();j!=FrameTable.end();++j){
                cout<<*j;
            }
        cout<<" (page fault)\n";
    }
    cout<<endl<<"Final: ";
    for(auto j=FrameTable.begin();j!=FrameTable.end();++j){
        cout<<*j;
    }
}


int main()
{
    int n;
    int NumberOfFrames;

    int alg;
    cout << "Pick a page replacement algorithm:\n 1. First In, First Out (FIFO)\n 2. Least Recently Used (LRU)\n 3. Optimal (OPT)\n\n ";
    cin >> alg;
    while(!(alg==1||alg==2||alg==3)){
        cout<<endl<<"Please pick a valid choice.. (1-3):\t";
        cin >> alg;
    }

    cout<<"\nEnter the number of frames: ";
    cin>>NumberOfFrames;

    cout<<"Enter the size of input: ";
    cin>>n;
    
    int *input=new int[n];

    cout<<"Enter values: ";
    for(int i=0; i<n; i++)
        cin>>input[i];

    if(alg==1||alg==2)
        FIFO_LRU(input,NumberOfFrames,n,alg);
    else if(alg==3)
        OPT(input,NumberOfFrames,n);

    return 0;
}