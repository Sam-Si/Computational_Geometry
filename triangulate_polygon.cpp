#include "bits/stdc++.h"

using namespace std;
const double EPS = 0.000001;

class Vertex;
class Edge;
class DCEL;
class Point;
class Triangulation;
class YMonotone;

/**! \class Generic Red Black Tree
* \A Red Black Tree that supports any data type
*
* An RBTree with logarithmic Operations.
* Can be used with any custom data type, provided the method this.compareTo(that) is defined. 
*/
template <typename T>
class RBTree{
public:
    static const int RED = 0, BLACK = 1, DBLACK = 2;
    //\struct Node of a Red-Black Tree
    struct data{
        int color;
        T val;
        data *left, *right, *parent;
        bool isNull;
        data(T v, int col, data* p) : val(v), color(col), parent(p), left(NULL), right(NULL), isNull(0) {};
        data() : left(NULL), right(NULL), isNull(1), color(BLACK) {};
    };
    data* root;
    data* aux;
    data* nullNode(){
        return (new data());
    }
    //\fn Constructor
    RBTree(){
        root = nullNode();
        aux = nullNode();
    }
    //!Right Rotation at node.
    void rotateRight(data* node, bool interchange = true){
        data* tmp = node->parent;
        if(tmp == root){
            root = node;
        }
        else if(tmp->parent->left == tmp){
            tmp->parent->left = node;

        }
        else{
            tmp->parent->right = node;
        }
        node->parent = tmp->parent;
        tmp->parent = node;
        tmp->left = node->right;
        node->right = tmp;
        if(interchange) swap(node->color, tmp->color);
    }
    //!Left Rotation at node.
    void rotateLeft(data* node, bool interchange = true){
        data* tmp = node->parent;
        if(tmp == root){
            root = node;
        }
        else if(tmp->parent->left == tmp){
            tmp->parent->left = node;
        }
        else{
            tmp->parent->right = node;
        }
        node->parent = tmp->parent;
        tmp->parent = node;
        tmp->right = node->left;
        node->left = tmp;
        if(interchange) swap(node->color, tmp->color);
    }
    //!Balances the tree after a successful insertion.
    void fixInsert(data* node){
        if(root == node) {
            root->color = BLACK;
            root->parent = NULL;
            return;
        }
        if(node->parent->color == BLACK) return;
        if(node->parent == root){
            node->parent->color = BLACK;
            return;
        }
        data* par = node->parent;
        data* gpar = par->parent;
        data* uncle = (gpar->left == par) ? gpar->right : gpar->left;

        if(!uncle->isNull && uncle->color == RED){
            par->color = BLACK;
            uncle->color = BLACK;
            gpar->color = RED;
            fixInsert(par);
            return;
        }

        if(par->left == node){
            if(gpar->left == par){
                rotateRight(par);
            }
            else{
                rotateRight(node);
                rotateLeft(node);
            }
        }
        else{
            if(gpar->right == par){
                rotateLeft(par);
            }
            else{
                rotateLeft(node);
                rotateRight(node);
            }
        }
    } 
    //!Inserts a new value into the tree.
    void insert(T val){
        data* t = new data(val, RED, NULL);
        t->left = nullNode(); 
        t->left->parent = t;
        t->right = nullNode(); 
        t->right->parent = t;
        if(root->isNull){
            root = t;
            root->isNull = 0;
        }
        else{
            data *node = root, *prev = NULL;
            while(!node->isNull){
                prev = node;
                if(val.compareTo(node->val) <= 0)
                    node = node->left;
                else
                    node = node->right;
            }
            if(val.compareTo(prev->val) <= 0) prev->left = t;
            else prev->right = t;
            t->parent = prev;
        }
        fixInsert(t);
    }
    //!Finds the value less than or equal to x.
    T find(T x){
        data* node = root;
        T returnVal = *(new T());
        while(!node->isNull){
            int compare = x.compareTo(node->val);
            if(compare == 0){
                return node->val;
            }
            else if(compare < 0){
                node = node->left;
            }
            else{
                returnVal = node->val;
                node = node->right;
            }
        }
        return returnVal;
    }
    //!Finds Successor of a node
    data* successor(data* node){
        data* t = node->right;
        while(!t->left->isNull) t = t->left;
        return t;
    }
    //!Replaces node with child
    void replaceNode(data* node, data* child){
        child->parent = node->parent;
        if(node->parent == NULL){
            root = child;
        }
        else{
            if(node->parent->left == node)  node->parent->left = child;
            else node->parent->right = child;
        }
    }
    //!Delete Utility 6
    void deleteCase6(data* node){
        data* par = node->parent;
        data* sibling = (node == par->left) ? par->right : par->left;
        sibling->color = sibling->parent->color;
        sibling->parent->color = BLACK;
        if(node == par->left){
            sibling->right->color = BLACK;
            rotateLeft(sibling, false);
        }
        else{
            sibling->left->color = BLACK;
            rotateRight(sibling, false);
        }
        if(sibling->parent == NULL) root = sibling;
    }
    //!Delete Utility 5
    void deleteCase5(data* node){
        data* par = node->parent;
        data* sibling = (node == par->left) ? par->right : par->left;
        if(sibling->color == BLACK){
            if(node == par->left && sibling->right->color == BLACK && sibling->left->color == RED) rotateRight(sibling->left);
            else if(node == par->right && sibling->left->color == BLACK && sibling->right->color == RED) rotateLeft(sibling->right);
        }
        deleteCase6(node);
    }
    //!Delete Utility 4
    void deleteCase4(data* node){
        data* par = node->parent;
        data* sibling = (node == par->left) ? par->right : par->left;
        if(par->color == RED && sibling->color == BLACK && sibling->left->color == BLACK && sibling->right->color == BLACK){
            sibling->color = RED;
            par->color = BLACK;
            return;
        }
        else{
            deleteCase5(node);
        }
    }
    //!Delete Utility 3
    void deleteCase3(data* node){
        data* par = node->parent;
        data* sibling = (node == par->left) ? par->right : par->left;
        if(par->color == BLACK && sibling->color == BLACK && sibling->left->color == BLACK && sibling->right->color == BLACK){
            sibling->color = RED;
            deleteCase1(par);
        }
        else{
            deleteCase4(node);
        }
    }
    //!Delete Utility 2
    void deleteCase2(data* node){
        data* par = node->parent;
        data* sibling = (node == par->left) ? par->right : par->left;
        if(sibling->color == RED){
            if(sibling == par->left)    rotateRight(sibling);
            else rotateLeft(sibling);
            if(sibling->parent == NULL) root = sibling;
        }
        deleteCase3(node);
    }
    //!Delete Utility 1
    void deleteCase1(data* node){
        if(node->parent == NULL){
            root = node;
            return;
        }
        deleteCase2(node);
    }
    //!Basic Deletion when node has only one child
    void deleteEasy(data* node){
        data* child = (node->right->isNull) ? node->left : node->right;
        replaceNode(node, child);
        if(node->color == BLACK){
            if(child->color == RED) child->color = BLACK;
            else    deleteCase1(child);
        }
    }
    //!Deletes x from the tree
    void erase(T x, data* node){
        if(node->isNull || node == NULL) return;
        int compare = x.compareTo(node->val);
        if(compare == 0){
            if(node->left->isNull || node->right->isNull){
                deleteEasy(node);
            }
            else{
                data* succ = successor(node);
                node->val = succ->val;
                erase(succ->val, node->right);
            }
        }
        if(compare < 0) erase(x, node->left);
        else erase(x, node->right);
    }
    //!Deletes x from the tree. User-called Function
    void erase(T x){
        erase(x, root);
    }
    //!Prints the Inorder Traversal of the tree.
    void print(data* node){
        if(node->isNull) return;
        print(node->left);
        cout << "(" << node->val.low.index << "," << node->val.hi.index << ") ";
        print(node->right);
    }
    //!Called by user when he/she wants to print the tree.
    void print(){
        print(root);
        if(!root->isNull) cout << endl;
    }
};
/**! \class Point
* \2-Dimensional Point
*/
class Point{
public:
	double x;
	double y;

	Point(){
		x = 0, y = 0;
	}
	Point(int _x, int _y){
		x = _x, y = _y;
	}
    //!Vector Area of triangle formed by the three points.
	static double vectorArea(Point p, Point q, Point r)
    {
        return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    }
    //!Returns true if three points take a left turn
	static bool turnsLeft(Point p, Point q, Point r)
    {
        double area = vectorArea(p, q, r);
        if(area < 0) return true;
        return false;
    }
    //!Returns true if three points take a right turn
    static bool turnsRight(Point p, Point q, Point r)
    {
        double area = vectorArea(p, q, r);
        if(area > 0) return true;
        return false;
    }
};
/**! \class Vertex
*\An Object of this class stores position and index of a vertex.
*
* It also stores various comparators for vertices
*/
class Vertex{
public:
	Point pos;
	Edge* IncidentEdge;
    int index;
    //!Empty Constructor
	Vertex(){
		pos.x = 0, pos.y = 0;
		IncidentEdge = NULL;
	}
    //!Constructor with co-ordinates
	Vertex(double x, double y, int i = -1){
		pos.x = x, pos.y = y;
		IncidentEdge = NULL;
        index = i;
	}
    //!Point Constructor
	Vertex(Point p){
		pos = p;
		IncidentEdge = NULL;
	}
    //!Returns true if that vertex lies below this vertex.
	bool liesBelow(Vertex that){
		if(this->pos.y != that.pos.y) return this->pos.y < that.pos.y;
		return this->pos.x > that.pos.x;
	}
    //!Returns true if the three vertices take a left turn.
	static bool turnsLeft(Vertex p, Vertex q, Vertex r){
		return Point::turnsLeft(p.pos, q.pos, r.pos);
	}
    //!Returns true if the three vertices take a right turn.
	static bool turnsRight(Vertex p, Vertex q, Vertex r){
		return Point::turnsRight(p.pos, q.pos, r.pos);
	}
    //Comparator function for priority queue
    struct cmp{
        bool liesBelow(Vertex a, Vertex b){
            if(a.pos.y != b.pos.y) return a.pos.y < b.pos.y;
            return a.pos.x > b.pos.x;
        }
        bool operator()(Vertex a, Vertex b){
            return liesBelow(a, b);
        }
    };
    //Comparator function for sorting purposes
    struct cmp2{
        bool operator()(Vertex a, Vertex b){
            if(abs(a.pos.y - b.pos.y) > EPS) return a.pos.y > b.pos.y;
            return a.pos.x < b.pos.x; 
        }
    };
};
/**! \class Edge
* \An Object of this class stores the start and end point of an edge.
*Also has a compareTo method that enables it to be used as a node in the Red-Black Tree.
*/
class Edge{
public:
	Vertex low;
    Vertex hi;
	int index;
	Edge(){	}
    Edge(Vertex a, Vertex b){
        low = a;
        hi = b;
    }
    Edge(const Edge& b){
        this->low = b.low;
        this->hi = b.hi;
        this->index = b.index;
    }
    //!CompareTo function returns 1 if this edge lies to the left of that edge.
	int compareTo(Edge b){
        if(this->low.index == b.low.index && this->hi.index == b.hi.index) return 0;
        Edge t1 = *(this), t2 = b;
        if(t1.hi.liesBelow(t1.low)) swap(t1.hi, t1.low);
        if(t2.hi.liesBelow(t2.low)) swap(t2.hi, t2.low);
        int swapped = 0;
        if(t2.hi.liesBelow(t1.hi)){
            swap(t1, t2);
            swapped = 1;
        }
        int ans = Vertex::turnsLeft(t2.low, t2.hi, t1.hi); 
        if(swapped) return ans;
        return !ans;
    }
};
/**! \class DCEL
* \An Object of this class stores a polygon.
*The polygon is stores as a list of vertices and its edges.
*Has functions that can split a polygon into multiple polygons along the diagonals.
*/
class DCEL{
public:
    int n;
    vector<Vertex> v;
    vector<Edge> e;
    vector<Edge> diag;
    //!Constructor that makes a DCEL from a vector of vertices
    DCEL(vector<Vertex> _v){
        n = _v.size();
        v = _v;
        for (int i = 0; i < n; i++){
            v[i].index = i;
            int a = i;
            int b = (i + 1) % n;
            Edge p = *(new Edge());
            p.low = v[a];
            p.hi = v[b];
            e.push_back(p);
            e[i].index = i;
        }
    }
    //!Adds a diagonal between two vertices
    void addEdge(int from, int to){
        Edge e1 = *(new Edge());
        e1.low = v[from], e1.hi = v[to];
        diag.push_back(e1);
    }
    //!Gives the next remaining vertex
    list<int>::iterator getNext(list<int>::iterator i, list<int>& V){
        auto it = i;
        it++;
        if(it == V.end()) it = V.begin();
        return it;
    }
    //!Gives the previous remaining vertex
    list<int>::iterator getPrev(list<int>::iterator i, list<int>& V){
        auto it = i;
        if(it == V.begin()) it = V.end();
        it--;
        return it;
    }
    //!Splits a polygon into multiple polygons along its diagonals.
    vector<DCEL> split(){
        vector<DCEL> solution;
        if(diag.size() == 0){
            solution.push_back(*this);
            return solution;
        }
        int degree[v.size()];
        int vcnt = v.size();
        memset(degree, 0, sizeof(degree));
        for (auto u : diag){
            degree[u.low.index] ++;
            degree[u.hi.index] ++;
            vcnt += 2;
        }
        list<int> V;
        for (int i = 0; i < n; i++){
            V.push_back(i);
        }
        for (int ii = 0; ii < diag.size(); ii++){
            list<int>::iterator i = V.begin();
            while(1){
                if(degree[*i] == 0){
                    break;
                }
                i = getNext(i, V);
            }
            deque<Vertex> d;
            d.push_back(v[*i]);
            vcnt--;
            auto forward = getNext(i, V);
            while(degree[*forward] == 0){
                d.push_back(v[*forward]);vcnt--;
                forward = getNext(forward, V);
            }
            d.push_back(v[*forward]);vcnt--;
            degree[*forward]--;
            auto backward = getPrev(i, V);
            while(degree[*backward] == 0){
                d.push_front(v[*backward]);vcnt--;
                backward = getPrev(backward, V);
            }
            d.push_front(v[*backward]);vcnt--;
            degree[*backward]--;
            auto curr = backward;
            auto prev = backward;
            curr=getNext(curr, V); curr=getNext(curr, V); prev=getNext(prev, V);
            while(prev != forward){
                V.erase(prev);
                prev = curr;
                curr = getNext(curr, V);
            }
            vector<Vertex> vec;
           for (auto it : d) vec.push_back(it);    
            solution.push_back(*(new DCEL(vec)));
        }
        vector<Vertex> vec;
        for (auto it : V) vec.push_back(v[it]);
        solution.push_back(*(new DCEL(vec)));
        return solution;
    }
    //!FIxes the indexing of newly broken polygons.
    void fix(){
        n = v.size();
        e.clear();
        for (int i = 0; i < v.size(); i++){
            v[i].index = i;
        }
        for (int i = 0; i < v.size(); i++){
            e.push_back(*(new Edge(v[i], v[(i + 1) % n])));
            e[i].index = i;
        }
    }
};
/**! \class YMonotone
* \An Object of this class stores a DCEL and decomposes it into YMonotone Pieces.
*MakeMonotone has the algorithm implementation for YMonotone Decomposition.
*/
class YMonotone{
public:
    #define START 1
    #define END 2
    #define SPLIT 3
    #define MERGE 4
    #define REGULAR 5
    int n;
    vector<int> type;
    vector<int> helper;
    DCEL* d;
    //!COnstructor
    YMonotone(vector<Vertex> _v){
        n = _v.size();
        d = new DCEL(_v);
        for (int i = 0; i < n; i++){
            type.push_back(0);
            helper.push_back(0);
        }
    }
    //!Finds the type for each Vertex : Start, End, Split, Merge, Regular.
    void findTypes(){
        for (int i = 0; i < n; i++){
            int prv = (i - 1 + n) % n;
            int nxt = (i + 1) % n;
            if(d->v[prv].liesBelow(d->v[i]) && d->v[nxt].liesBelow(d->v[i])){
                if(Vertex::turnsLeft(d->v[prv], d->v[i], d->v[nxt])) type[i] = START;
                else type[i] = SPLIT;
            }
            else if(d->v[i].liesBelow(d->v[prv]) && d->v[i].liesBelow(d->v[nxt])){
                if(Vertex::turnsLeft(d->v[prv], d->v[i], d->v[nxt])) type[i] = END;
                else type[i] = MERGE;
            }
            else type[i] = REGULAR;
        }
    }
    //!Creates a dummy edge to be searched in the RBTree
    Edge dummyEdge(Vertex a){
        Edge e = *(new Edge);
        e.hi = a;
        e.low = *(new Vertex(a.pos.x, a.pos.y - 0.01));
        e.low.index = -1;
        return e;
    }
    //!Handles Vertices of type Start
    void HandleStartVertex(int i, RBTree<Edge>& tree){
        tree.insert(d->e[i]);
        helper[i] = i;
    }
    //!Handles Vertices of type End
    void HandleEndVertex(int i, RBTree<Edge>& tree){
        if(type[helper[(i - 1 + n) % n]] == MERGE){
            int from = i;
            int to = helper[(i - 1 + n) % n];
            (*d).addEdge(from, to);
        }
        tree.erase(d->e[(i - 1 + n) % n]);
    }
    //!Handles Vertices of type Split
    void HandleSplitVertex(int i, RBTree<Edge>& tree){
        Edge ej = tree.find(dummyEdge(d->v[i]));
        (*d).addEdge(i, helper[ej.index]);
        helper[ej.index] = i;
        tree.insert(d->e[i]);
        helper[i] = i;
    }
    //!Handles Vertices of type Merge
    void HandleMergeVertex(int i, RBTree<Edge>& tree){
        if(type[helper[(i - 1 + n) % n]] == MERGE){
            (*d).addEdge(i, helper[(i - 1 + n) % n]);
        }
        tree.erase(d->e[(i - 1 + n) % n]);
        Edge ej = tree.find(dummyEdge(d->v[i]));
        if(type[helper[ej.index]] == MERGE){
            (*d).addEdge(i, helper[ej.index]);
        }
        helper[ej.index] = i;
    }
    //!Handles Vertices of type Regular
    void HandleRegularVertex(int i, RBTree<Edge>& tree){
        int prv = (i - 1 + n) % n;
        int nxt = (i + 1) % n;
        if(d->v[nxt].liesBelow(d->v[prv])){
            if(type[helper[(i - 1 + n) % n]] == MERGE){
                (*d).addEdge(i, helper[(i - 1 + n) % n]);
            }
            tree.erase(d->e[(i - 1 + n) % n]);
            tree.insert(d->e[i]);
            helper[i] = i;
        }
        else{
            Edge ej = tree.find(dummyEdge(d->v[i]));
            if(type[helper[ej.index]] == MERGE){
                (*d).addEdge(i, helper[ej.index]);
            }
            helper[ej.index] = i;
        }
    }
    //!Adds diagonals to a polygon so the resultant polygons will be Y-Monotone
    void MakeMonotone(){

        priority_queue<Vertex, vector<Vertex>, Vertex::cmp> PQ;
        for(auto u : d->v){
            PQ.push(u);
        }
        RBTree<Edge> tree = *(new RBTree<Edge>());
        findTypes();
        while(!PQ.empty()){
            int vi = PQ.top().index;
            PQ.pop();
            switch(type[vi]){
                case START : HandleStartVertex(vi, tree);
                break;
                case END : HandleEndVertex(vi, tree);
                break;
                case SPLIT : HandleSplitVertex(vi, tree);
                break;
                case MERGE : HandleMergeVertex(vi, tree);
                break;
                case REGULAR : HandleRegularVertex(vi, tree);
                break;
                default:
                break;
            }
        }
    }
};
/**! \class Triangulation
* \Uses a basic algorithm for triangulating a Y-Monotone Polygon
*Method 'Triangulate' must be called with a DCEL as its argument.
*/
class Triangulation{
public:
    #define LEFT 0
    #define RIGHT 1
    
    vector<int> chain;
    int n;
    //!Finds whether a vertex belongs to the left chain or the right chain
    void findChains(vector<Vertex>& v){
        chain.clear();
        for (int i = 0; i < v.size(); i++){
            int nxt = (i + 1) % (v.size());
            if(v[i].liesBelow(v[nxt])) chain.push_back(RIGHT);
            else chain.push_back(LEFT);;
        }
    }
    //!Returns true if x and y are adjacent vertices in a polygon
    bool adjacent(int x, int y){
        if(x == y + 1) return 1;
        if(y == x + 1) return 1;
        if(x == 0 && y == n - 1) return 1;
        if(y == 0 && x == n - 1) return 1;
        return 0;
    }
    //!Triangulates the Y-Monotone Polygon stored in a DCEL.
    void Triangulate(DCEL& d){
        n = d.v.size();
        if(n <= 3) return;
        findChains(d.v);
        vector<Vertex> u(d.v);
        sort(u.begin(), u.end(), Vertex::cmp2());
        stack<Vertex> s;
        s.push(u[0]);
        s.push(u[1]);
        for (int i = 2; i < u.size() - 1; i++){
            if(chain[s.top().index] != chain[u[i].index]){
                while(s.size() > 1){
                    Vertex popped = s.top();
                    s.pop();
                    d.addEdge(u[i].index, popped.index);
                }
                if(s.size() == 1) s.pop();
                s.push(u[i - 1]);
                s.push(u[i]);
            }  
            else{
                Vertex popped = s.top(); s.pop();
                Vertex middle = popped;
                Vertex destination = s.top(); s.pop();
                if(chain[u[i].index] == LEFT){
                    while(!s.empty()){
                        if(Vertex::turnsRight(u[i], middle, destination)){
                            d.addEdge(u[i].index, destination.index);
                            if(s.empty()) break;
                            middle = destination;
                            destination = s.top(); s.pop();
                        }
                        else break;
                    }
                }
                else{
                    while(!s.empty()){
                        if(Vertex::turnsLeft(u[i], middle, destination)){
                            d.addEdge(u[i].index, destination.index);
                            if(s.empty()) break;
                            middle = destination;
                            destination = s.top(); s.pop();
                        }
                        else break;
                    }
                }
                s.push(destination);
                s.push(u[i]);
            }
        }
        Vertex last = u.back();
        while(!s.empty()){
            if(!adjacent(last.index, s.top().index)){
                d.addEdge(last.index, s.top().index);
            }
            s.pop();
        }
    }
};
/**
* Driver function
*/
int main(){
    freopen("in", "r", stdin);
    freopen("out.off", "w", stdout);
    int n, f, g;
    cin >> n >> f >> g;
    vector<Vertex> v;
    for (int i = 0; i < n; i++){
        double x, y, z;
        cin >> x >> y >> z;
        v.push_back(*(new Vertex(x, y, i)));
    }
    YMonotone YM = *(new YMonotone(v));
    YM.MakeMonotone();
    vector<DCEL> sp = YM.d->split();
    Triangulation tri = *(new Triangulation());
    vector<DCEL> finalAnswer;
    int finalVertexCount = 0;
    int cnt = 0;
    for (auto &u : sp){
        u.fix();
        tri.Triangulate(u);
        vector<DCEL> tmp = u.split();
        for(auto x : tmp){
            finalVertexCount += x.v.size();
        }
        copy(tmp.begin(), tmp.end(), back_inserter(finalAnswer));
    }
    cout << "OFF" << endl;
    cout << finalVertexCount << " " << finalAnswer.size() << " 0" << endl;
    for (auto u : finalAnswer){
        for (auto ver : u.v){
            cout << ver.pos.x << " " << ver.pos.y << " 0\n";
        }
    }
    for (auto u: finalAnswer){
        cout << u.v.size() << " ";
        for (int j = 0; j < u.v.size(); j++){
            cout << cnt + j << " ";
        }cout << endl;
        cnt += u.v.size();
    }
    return 0;
}
