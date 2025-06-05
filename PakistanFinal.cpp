#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include <iomanip> 
#include <unordered_map>
using namespace std;
struct Node
{
    string countryName;
    int population;
    int income;
    int rain;
    Node *next ;
    Node *pre;
    Node(string n , int r , int m , int c)
    {
        countryName = n;
        population = r;
        income = m;
        rain = c;
        next = NULL;
        pre = NULL;
    }
};

//--------------------------------------------------------------------------------------------------------------------------------

class MaxHeap {
private:
    std::vector<Node*> list;
    int ptr;

public:
    MaxHeap() : list(35), ptr(-1) {}

    bool isFull() const {
        return ptr == list.size() - 1;
    }

    bool isEmpty() const {
        return ptr == -1;
    }

    int parent(int i) const {
        return (i - 1) / 2;
    }

    int right(int i) const {
        return 2 * i + 2;
    }

    int left(int i) const {
        return 2 * i + 1;
    }

    void swap(int n, int m) {
        Node* temp = list[n];
        list[n] = list[m];
        list[m] = temp;
    }

    void insert(Node* key) {
        if (isFull()) {
            std::cout << "Full" << std::endl;
            return;
        }
        list[++ptr] = key;
        upheap(ptr);
    }

    void upheap(int index) {
        if (index == 0) return;
        int parentIdx = parent(index);
        if (list[parentIdx]->rain < list[index]->rain) {
            swap(parentIdx, index);
            upheap(parentIdx);
        }
    }

    Node* deleteMax() {
        if (isEmpty()) {
            std::cout << "Empty" << std::endl;
            return nullptr;
        }
        Node* maxElement = list[0];
        list[0] = list[ptr--];
        downHeap(0);
        return maxElement;
    }

    void downHeap(int index) {
        int leftIdx = left(index);
        int rightIdx = right(index);
        int largest = index;

        if (leftIdx <= ptr && list[leftIdx]->rain > list[largest]->rain) {
            largest = leftIdx;
        }
        if (rightIdx <= ptr && list[rightIdx]->rain > list[largest]->rain) {
            largest = rightIdx;
        }

        if (largest != index) {
            swap(index, largest);
            downHeap(largest);
        }
    }

    void print(Node* temp) {
        cout<<temp->countryName<<", \t "<<temp->population<<",\t  "<<temp->income<<",\t   "<<temp->rain<<endl;

    }

    void heapSort() {
        cout<<"City Name\tPopulation\tIncome\tRainfall(Anually)"<<endl;
        while(!isEmpty()) {
            print(deleteMax());
        }
    }
};

//--------------------------------------------------------------------------------------------------------------------------------

struct Node *head = NULL;
struct Node *tail = NULL;

void addNode(string n , int r , int m , int c)
{
    Node* newNode = new Node(n , r , m , c);

    if(head == NULL)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->pre = tail;
        tail = newNode;
    }
}

void printAll()
{ // It will print the whole linked list
    Node* temp = head->next;
    int count = 1;
    cout<<"City Name\tPopulation\tIncome\tRainfall(Anually)"<<endl<<endl;

    while(temp != NULL)
    {
        cout<<count<<") "<<temp->countryName<<", \t "<<temp->population<<",\t  "<<temp->income<<",\t   "<<temp->rain<<endl;
        count++;
        temp = temp->next;
    }
}



//--------------------------------------------------------------------------------------------------------------------------------

struct TreeNode {
    string countryName;
    int population;
    int income;
    int rain;
    TreeNode *left ;
    TreeNode *right;
    TreeNode(string n , int r , int m , int c) //Constructor 
    {
        countryName = n;
        population = r;
        income = m;
        rain = c;
        left = NULL;
        right = NULL;
    }

};

TreeNode * root = NULL; //entry point to BST 
//Initially set to null (tree is empty)


/*TreeNode* addToTree2(TreeNode * root , string n,  int r , int m , int c)
Adds a new node to the BST based on the population 
*/

TreeNode* addToTree2(TreeNode * root , string n,  int r , int m , int c){
    if(root == NULL) {
        TreeNode* newRoot = new TreeNode(n, r, m, c); //new node gets added
        return newRoot;
    }
    if(root->population > r) { //comparing population 
        root-> left = addToTree2(root->left, n, r, m, c);
    }else {
        root-> right = addToTree2(root->right, n, r, m, c);
    }
    return root;
} //continued recursively until a NULL position is found for the new node


void addToTree() //adds data from the linked list to the bst
{
    Node* temp = head->next; 
    int count = 1;
    while(temp != NULL)
    {
        root = addToTree2(root, temp->countryName, temp->population, temp->income, temp->rain); //adds data to bst
        temp = temp->next;
    }
}

void displayCountry(TreeNode *root) {
    cout<<root->countryName<<",\t "<< root->population<<", \t"<< root->income<<", \t"<< root->rain<<endl;
}

void displayTree(TreeNode *root) { //displays entire bst in sorted order based on the population
    if(root == NULL) return; //performs an in-order traversal (outputs the node in increasing order of population)
    displayTree(root-> left);
    displayCountry(root);
    displayTree(root-> right);

}


//--------------------------------------------------------------------------------------------------------------------------------
void sortUsingHeap(Node* head) { // it will sort nodes on the basis of rain 
    Node* temp = head->next;
    MaxHeap h;
    while(temp) {
        h.insert(temp);
        temp = temp->next;
    }
    h.heapSort();
}

//--------------------------------------------------------------------------------------------------------------------------------
void readCSV(const string& filename, vector<vector<string>>& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> row;
        while (getline(ss, item, ',')) {
            row.push_back(item);
        }
        data.push_back(row);
    }
    file.close();
}


// Function to create a 2D array dynamically based on the CSV data
void createGraph(int**& a, const vector<vector<string>>& data, int& rows, int& cols) {
    // Exclude the first row and first column, which are headers
    rows = data.size() - 1; // Subtract one for header row
    cols = data[0].size() - 4; // Subtract one for header column and three for last columns

    // Allocate memory for the 2D array
    a = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        a[i] = new int[cols];
    }

    // Populate the array, skipping headers and last three columns
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j < cols + 1; ++j) {
            try {
                a[i - 1][j - 1] = stoi(data[i][j]);
            } catch (invalid_argument& e) {
                cerr << "Error: Non-numeric data encountered at (" << i << "," << j << ")." << endl;
                a[i - 1][j - 1] = 0; // Or handle this case appropriately
            }
        }
    }
}
// Function to print the 2D array
void printGraph(int** a, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------
std::vector<int> dijkstra(int** a, const std::string str, vector<string> s) {
    // Check if the starting city is in the city list
    unordered_map<string, int> cityMap;
    for (int i = 0; i < s.size(); i++) {
        cityMap[s[i]] = i;
    }

    // Check if the city exists in the list
    if (cityMap.find(str) == cityMap.end()) {
        cout << "Error: City " << str << " is not in the list!" << endl;
        return {}; // Return an empty vector if the city is not found and exit the function
    }

    int startVertex = cityMap[str]; // Get the starting vertex index

    std::vector<int> distances(34, INT_MAX);
    std::vector<bool> visited(34, false);

    distances[startVertex] = 0;

    for (int count = 0; count < 34; count++) {
        int minDistance = INT_MAX;
        int u = -1;

        for (int i = 0; i < 34; i++) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < 34; v++) {
            if (a[u][v] != 0 && !visited[v]) {
                int alt = distances[u] + a[u][v];
                if (alt < distances[v]) {
                    distances[v] = alt;
                }
            }
        }
    }

    // Print distances for each vertex
    int ptr = 0;
    for (int dist : distances) {
        if (dist != INT_MAX) {
            cout << "Distance of " << s[ptr++] << " from " << str << " is " << dist << " ";
            cout << endl;
        } else {
            ptr++;
        }
    }

    return distances;
}

//--------------------------------------------------------------------------------------------------------------------------------

std::vector<int> prims(int** a, const std::string str, vector<string> s) {
    // Check if the starting city is in the city list
    unordered_map<string, int> cityMap;
    for (int i = 0; i < s.size(); i++) {
        cityMap[s[i]] = i;
    }

    // Check if the city exists in the list
    if (cityMap.find(str) == cityMap.end()) {
        cout << "Error: City " << str << " is not in the list!" << endl;
        return {}; // Return an empty vector if the city is not found and exit the function
    }

    int startVertex = cityMap[str]; // Get the starting vertex index

    std::vector<int> distances(34, INT_MAX);
    std::vector<bool> visited(34, false);
    string parent[34];
    parent[startVertex] = str;

    distances[startVertex] = 0;

    for (int count = 0; count < 34; count++) {
        int minDistance = INT_MAX;
        int u = -1;

        for (int i = 0; i < 34; i++) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < 34; v++) {
            if (a[u][v] != 0 && !visited[v]) {
                if (a[u][v] < distances[v]) {
                    distances[v] = a[u][v];
                    parent[v] = s[u];
                }
            }
        }
    }

    int ptr = 0;
    for (string d : parent) {
        if (!d.empty()) {
            cout << "Parent of " << s[ptr++] << " is " << d << endl;
        } else {
            ptr++;
        }
    }

    // Calculate the total weight of the Minimum Spanning Tree
    int totalWeight = 0;
    for (int i = 0; i < 34; i++) {
        if (distances[i] != INT_MAX) {
            totalWeight += distances[i];
        }
    }

    cout << "Minimum Distance of Spanning Tree: " << totalWeight << endl;

    return distances;
}
//--------------------------------------------------------------------------------------------------------------------------------
void addNodesToHashmap(Node* head, unordered_map<int, Node*>& hashmap) { //key = income
    Node* current = head; 
    while (current != nullptr) {
        hashmap[current->income] = current;
        current = current->next;
    }
}//Insertion in a hashmap is O(1) on average, making this process efficient.



void printHashmap(const unordered_map<int, Node*>& hashmap) { //displays all the data stored in the hashmap.
    for (const auto& pair : hashmap) {
        cout << "Income: " << pair.first
             << ", City: " << pair.second->countryName
             << ", Population: " << pair.second->population
             << ", Rain: " << pair.second->rain << endl;
    }
}

void printNodeWithIncome(int income, const unordered_map<int, Node*>& hashmap) {
	//efficiently searches for a node with a specific income and prints its details or indicates if no such node exists.
    auto it = hashmap.find(income);
    if (it != hashmap.end()) {
        Node* node = it->second;
        cout << "Country: " << node->countryName
             << ", Population: " << node->population
             << ", Income: " << node->income
             << ", Rain: " << node->rain << endl;
    } else {
        cout << "No node found with income: " << income << endl;
    }
}

//=====================================================================================
struct Edge {
    int u, v, weight;
};

int findParent(int vertex, vector<int>& parent) {
    if (parent[vertex] == vertex) return vertex;
    return parent[vertex] = findParent(parent[vertex], parent);
}

void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);
    
    if (rootU != rootV) {
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

std::vector<int> kruskal(int** a, int n, vector<string> s) {
    vector<Edge> edges;

    // Create all edges from the adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] != 0) {
                edges.push_back({i, j, a[i][j]});
            }
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    vector<int> parent(n);
    vector<int> rank(n, 0);

    // Initialize parent for each vertex
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    vector<int> mstWeights;
    int totalWeight = 0;

    // Apply Kruskal's algorithm
    for (Edge edge : edges) {
        int u = edge.u;
        int v = edge.v;

        // If u and v are not connected, add this edge to the MST
        if (findParent(u, parent) != findParent(v, parent)) {
            unionSets(u, v, parent, rank);
            mstWeights.push_back(edge.weight);
            totalWeight += edge.weight;
            cout << "Edge: " << s[u] << " - " << s[v] << " with weight: " << edge.weight << endl;
        }
    }

    cout << "Total weight of the Minimum Spanning Tree (MST): " << totalWeight << endl;

    return mstWeights;
}

//==================================================================================
main() {
    ifstream csvFile;
    csvFile.open("Pakistan2.csv");
    string line , word;
    vector<string> vec;

    while(!csvFile.eof())
    {
        getline(csvFile , line);
        stringstream s(line);
        while(getline(s,word,','))
        {
            vec.push_back(word);
        }

        int pop;
        stringstream ms(vec[1]);
        ms>>pop;

        int income;
        stringstream rs(vec[2]);
        rs>>income;


        int rain;
        stringstream cs(vec[3]);
        cs>>rain;

        // add data to Node

        addNode(vec[0] , pop , income, rain);

        //clearvector

        vec.clear();
    }









    // This will creat a BST 
    addToTree();

    // This will save nodes as value and their income as key in a HashMap
    unordered_map<int, Node*> hashmap;
    addNodesToHashmap(head, hashmap);
    // printHashmap(hashmap); // This will print the whole hashmap
    // printNodeWithIncome(1850, hashmap);

    // This will read the file and creat graph from it 
    vector<vector<string>> data;
    string filename = "Pakistan.csv"; // Make sure this file is in the same directory as your source code
    readCSV(filename, data);


    int** a;
    int rows, cols;
    createGraph(a, data, rows, cols);


    // printGraph(a, rows, cols);

    vector<string> s = { 
        "Karachi", 
        "Lahore", 
        "Islamabad", 
        "Rawalpindi", 
        "Peshawar", 
        "Quetta", 
        "Multan", 
        "Faisalabad", 
        "Sialkot", 
        "Hyderabad", 
        "Abbottabad", 
        "Sukkur", 
        "Gujranwala", 
        "Gilgit", 
        "Murree", 
        "Swat", 
        "Mansehra", 
        "Bahawalpur", 
        "Mardan", 
        "Dera Ismail Khan", 
        "Sargodha", 
        "Mirpur", 
        "Muzaffarabad", 
        "Chitral", 
        "Khairpur", 
        "Gwadar", 
        "Jhang", 
        "Saidu Sharif", 
        "Nowshera", 
        "Zhob", 
        "Ziarat", 
        "Chilas", 
        "Larkana", 
        "Hunza"
    };
    



    int choice = -1;
    
    string city;
    string city2;
    
    do{
        cout << "Menu" << endl;
        cout << "Enter 1 to check all the cities in our dataset (Using Linked List)" << endl;
        cout << "Enter 2 to sort the cities on the basis of population (Using BST)" << endl;
        cout << "Enter 3 to sort the data on the basis of rainfall (Using Heap)" << endl;
        cout << "Enter 4 to get the shortest distance from the city (Using Dijkastra)"  << endl; 
        cout << "Enter 5 to get the minimum path from your desired city (Using Prims)" << endl;
        cout << "Enter 6 to get the details of the city on putting income (Using HashMaps) " << endl;
        cout << "Enter 7 to get the minimum path from your desired city(Using Kruskals..) " << endl;
        cout << "Enter -1 to exit menu" << endl;
        cin >>  choice;

        switch(choice){
            case 1:
            {
                printAll();
                break;
            }
            case 2:
            {
                cout<<"City Name\tPopulation\tIncome\tRainfall(Anually)"<<endl;
                displayTree(root);
                break;
            }
            case 3:
            {
                sortUsingHeap(head);
                break;
            }
            case 4:
            {
                cout << "Enter the city you want to see the shortest distance from" << endl;
                cin >> city ;
                dijkstra(a, city ,  s);
                break;
            }
            case 5:
            {
                cout << "Enter the city from you want to know the minimum path " << endl;
                cin >> city2;
                prims(a, city2 ,  s);
                break;
                
            }
            case 6:
            {
                cout<<"Enter the Income Amount "<<endl;
                int inc;
                cin >> inc;
                printNodeWithIncome(inc, hashmap);
                break;
            }
            case 7 :
            {
                cout << "Applying kruskal..."<<endl;
                kruskal(a , 34 , s);
                break;

            }
            case -1:
            	{
            		cout << "Byee........" <<endl;
            		break;
				}
            default:
            {
                cout << "invalid choice" << endl;
                cout << "Byee........" <<endl;
                return 0;
                break;
            }
        }
    }
    while(choice!=-1);
    return 0;
}      
    
