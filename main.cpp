//подключение нужных библиотек

#include <iostream>
#include <cstring>
#include <fstream>
#include <random>

using namespace std;

struct vertex
{
    string name; // название вершины
};

struct edge
{ // грань
    vertex from;
    vertex to;
    double weight;
};

template <class T>
class Queue
{ //реализация очереди на шаблоне
private:
    struct queue_element
    {
        T value;
        queue_element *next;
    };
    queue_element *head;

public:
    Queue()
    {
        head = nullptr;
    }

    //добавление вверх стека
    void push(const T &value)
    {
        if (head == nullptr)
        {
            head = new queue_element[1];
            head->value = value;
            head->next = nullptr;
        }
        else
        {
            queue_element *cur = head;
            while (cur->next != nullptr)
            {
                cur = cur->next;
            }
            cur->next = new queue_element[1];
            cur = cur->next;
            cur->value = value;
            cur->next = nullptr;
        }
    }

    //удаление снизу
    void pop()
    {
        if (head == nullptr)
            return;
        queue_element *new_head = head->next;
        delete[] head;
        head = new_head;
    }

    //получение элемента по индексу
    T get(size_t index)
    {
        size_t cur_index = 0;
        queue_element *cur = head;
        if (cur == nullptr)
        {
            cerr << "Wrong index!\n";
            exit(-1);
        }
        while (cur_index != index)
        {
            if (cur == nullptr)
            {
                cerr << "Wrong index!\n";
                exit(-1);
            }
            else
            {
                cur = cur->next;
                cur_index++;
            }
        }
        if (cur != nullptr)
            return cur->value;
        else
        {
            cerr << "Wrong index!\n";
            exit(-1);
        }
    }

    //получение размера очереди
    size_t get_size()
    {
        size_t result = 0;
        queue_element *cur = head;
        while (cur != nullptr)
        {
            cur = cur->next;
            result++;
        }
        return result;
    }
};

template <class T>
class Stack{
private:
    
    struct stack_element{
        T value;
        stack_element* next;
    };

    stack_element* head;

public:
    Stack(){
        head = nullptr;
    }

    void push(const T& value){
        if (head == nullptr){
            head = new stack_element[1];
            head->value = value;
            head->next = nullptr;
        }
        else{
            stack_element* cur = head;
            while (cur->next != nullptr){
                cur = cur->next;
            }
            cur->next = new stack_element[1];
            cur = cur->next;
            cur->value = value;
            cur->next = nullptr;
        }
    }

    T get_top(){
        if (head == nullptr){
            cerr << "Wrong index!\n";
            exit(-1);
        }
        stack_element* cur = head;
        while (cur->next != nullptr){
            cur = cur->next;
        }
        return cur->value;   
    }

    void pop(){
        if (head == nullptr) return;
        stack_element* cur = head;
        stack_element* pre_cur = cur;
        while (cur->next != nullptr){
            pre_cur = cur;
            cur = cur->next;
        }

        delete[] cur;
        if (cur == head) head = nullptr;
        if (pre_cur != nullptr) pre_cur->next = nullptr;
    }

    size_t get_size(){
        size_t result = 0;
        stack_element* cur = head;
        while (cur != nullptr){
            cur = cur->next;
            result++;
        }
        return result;
    }

};


template <class T>
class Vector
{ //реализация вектора

private:
    T *v;
    size_t real_size;
    size_t size;

public:
    Vector()
    {
        v = nullptr;
        size = 0;
        real_size = 0;
    }

    Vector(size_t Size)
    {
        v = new T[Size];
        size = Size;
        real_size = size;
    }

    //добавить элемент справа
    void push_back(T value)
    {
        int new_size = size + 1;
        if (new_size > real_size)
        {
            new_size = size * 2;
            if (size == 0)
                new_size = 1;
            real_size = new_size;
            T *newV = new T[new_size];
            for (int i = 0; i < size; i++)
            {
                newV[i] = v[i];
            }
            newV[size] = value;
            delete[] v;
            v = newV;
            size++;
        }
        else
        {
            v[size] = value;
            size++;
        }
    }

    //получить элемент по индексу
    T &operator[](size_t index)
    {
        if (index < size)
        {
            return v[index];
        }
        else
        {
            cerr << "Wrong index!\n";
            exit(-1);
        }
    }

    void Bubble_Sort(int comp(T, T))
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)
            {
                if (comp(v[j], v[j + 1]) == -1)
                {
                    swap(v[j], v[j + 1]);
                }
            }
        }
    }

    //быстрая сортировка
    void Quick_Sort(int comp(T, T))
    {
        Stack<pair<int, int>> stack;
        stack.push(make_pair(0, size - 1));
        while (stack.get_size() != 0)
        {
            int left = stack.get_top().first;
            int right = stack.get_top().second;
            int middle = left + (right - left) / 2;
            if (left == right)
            {
                stack.pop();
                continue;
            }

            for (int i = left; i <= middle; i++)
            {
                for (int j = middle + 1; j <= right; j++)
                {
                    if (comp(v[i], v[j]) == -1)
                    {
                        swap(v[i], v[j]);
                    }
                }
            }
            stack.pop();
            stack.push(make_pair(left, middle));
            stack.push(make_pair(middle + 1, right));

        }
    }

    size_t get_size()
    {
        return size;
    }
};

template <class T>
class Set
{ //реализация сета - множества с неповторяющимися элементами
private:
    struct element
    {
        T value;
        int id;
        element *next;
    };
    element *head;
    size_t size;

public:
    Set()
    {
        head = nullptr;
        size = 0;
    }
    //добавить в сет
    void add(const T &Value)
    {
        if (head == nullptr)
        {
            head = new element[1];
            head->value = Value;
            head->id = size;
            head->next = nullptr;
            size++;
        }
        else
        {
            element *cur = head;
            if (cur->value == Value)
                return;
            while (cur->next != nullptr)
            {
                if (cur->value == Value)
                    return;
                cur = cur->next;
            }
            if (cur->value == Value)
                return;
            cur->next = new element[1];
            cur = cur->next;
            cur->value = Value;
            cur->next = nullptr;
            cur->id = size;
            size++;
        }
    }

    //получить индекс элемента по значению
    int get_id(const T &Value)
    {
        element *cur = head;
        while (cur != nullptr)
        {
            if (cur->value == Value)
            {
                return cur->id;
            }
            cur = cur->next;
        }
        return -1;
    }

    //получить значение по индексу элемента
    T &get_value(int id)
    {
        element *cur = head;
        while (cur != nullptr)
        {
            if (cur->id == id)
            {
                return cur->value;
            }
            cur = cur->next;
        }
        cerr << "Error in get_value()\n";
        exit(-1);
        
    }

    //размер сета
    size_t get_size()
    {
        return size;
    }
};

class DisjointSet
{ //система непересекающися множеств
private:
    size_t *parent;
    size_t *elements_num;
    size_t size;

public:
    DisjointSet(size_t Size)
    {
        size = Size;
        parent = new size_t[size];
        elements_num = new size_t[size];
        for (size_t i = 0; i < size; i++)
        {
            parent[i] = i;
            elements_num[i] = 1;
        }
    }

    //найти, кто главный в текущем множестве (множестве, в котором состоит данный элемент)
    size_t Find(size_t index)
    {
        if (index < size)
            return parent[index];
        else
        {
            cerr << "Wrong index!";
            exit(-1);
        }
    }

    // объединить два непересекающихся множества
    void Union(size_t first, size_t second)
    {

        //добавляем первое ко второму
        if ((first >= size) or (second >= size))
        {
            cerr << "Wrong index!";
            exit(-1);
        }
        if (elements_num[first] > elements_num[second])
        { //если первое множество более многоэлемнтое
            //то добавляем второе к нему
            elements_num[first] += elements_num[second];
            size_t parent_second = parent[second];
            for (int i = 0; i < size; i++)
            {

                if (parent[i] == parent_second)
                {
                    parent[i] = parent[first];
                    elements_num[i] = 0;
                }
            }
        }
        else
        {
            elements_num[second] += elements_num[first];
            size_t parent_first = parent[first];
            for (int i = 0; i < size; i++)
            {

                if (parent[i] == parent_first)
                {
                    parent[i] = parent[second];
                    elements_num[i] = 0;
                }
            }
        }
    }
};

/*
1. Вершина имеет вид {"from", "to", weight}
2. Есть вектор ребер. Его нужно будет отсортировать по возрастанию weight.
    В вектор можно добавлять в конец.

3. Проходим по отсортированному вектору ребер.
    Смотрим, лежат ли вершины в одной Компоненте Связности.
    Если не лежат, объединяем в одну КС.

*/

//функция компаратор для граней
int comp(edge e1, edge e2)
{
    bool asc = true;
    int sign = 1;
    if (!asc)
        sign = -1;
    if (e1.weight > e2.weight)
        return -sign;
    else if (e1.weight < e2.weight)
        return sign;
    else
        return 0;
}

// реализация алгоритма Краскала

void Kruskal_Algo(Vector<edge> &edges, Set<string> &s, size_t &result)
{
    size_t vertex_num = s.get_size();
    DisjointSet dset(vertex_num);
    // cout << "Number of edges: " << edges.get_size() << endl;

    edges.Quick_Sort(comp); //сортируем грани по возрастанию веса

    //выводим список граней ASC

    for (int i = 0; i < edges.get_size(); i++)
    {
        //для каждой грани,
        //для каждой вершины этой грани
        //проверяем, находится ли эта вершина в одной КС со второй вершиной
        size_t first_id = s.get_id(edges[i].from.name);
        size_t second_id = s.get_id(edges[i].to.name);
        if (dset.Find(first_id) != dset.Find(second_id))
        {
            cout << "First_id: " << first_id << "\tSecond_id: " << second_id << endl;
            dset.Union(first_id, second_id);
            result += edges[i].weight;

            cout << "Edge " << s.get_value(first_id)  << " " << s.get_value(second_id) << " " << edges[i].weight << " added!\n";
        }
    }
}

void BFS(Vector<Vector<size_t>> &graph)
{
    size_t size = graph.get_size();
    int *colors = new int[size];

    for (int i = 0; i < size; i++)
        colors[i] = 0;

    Queue<int> queue;
    queue.push(0);

    while (queue.get_size() != 0)
    {
        colors[queue.get(0)] = 1;
        cout << "Current vertex: " << queue.get(0) << "\t";
        cout << "Added: ";
        for (int i = 0; i < graph[queue.get(0)].get_size(); i++)
        {
            if (colors[graph[queue.get(0)][i]] == 0)
            {
                cout << graph[queue.get(0)][i] << " ";
                queue.push(graph[queue.get(0)][i]);
                colors[graph[queue.get(0)][i]] = 1;
            }
        }
        cout << endl;
        colors[queue.get(0)] = 2; // black
        queue.pop();
    }

}

void DFS(Vector<Vector<size_t>> &graph){
    size_t size = graph.get_size();
    int *colors = new int[size];

    for (int i = 0; i < size; i++)
        colors[i] = 0;


    Stack<int> stack;
    stack.push(0);

    while (stack.get_size() != 0){
        size_t top = stack.get_top();
        cout << "Current vertex: " << top << "\t";
        cout << "Added: ";
        colors[top] = 1;
        stack.pop();

        for (int i = 0; i < graph[top].get_size(); i++)
        {
            if (colors[graph[top][i]] == 0)
            {
                cout << graph[top][i] << " ";
                stack.push(graph[top][i]);
                colors[graph[top][i]] = 1;
            }
        }
        cout << endl;
        colors[top] = 2; // black
    }
}

int comp_int(int a, int b){
    if (a > b) return -1;
    if (a < b) return 1;
    if (a == b) return 0;
}

int main()
{

    ifstream fin;
    fin.open("input.txt");

    Vector<edge> edges;
    Set<string> s;

    while (!fin.eof())
    {
        vertex v1, v2;
        double weight;
        fin >> v1.name >> v2.name >> weight;
        s.add(v1.name);
        s.add(v2.name);
        edges.push_back({v1, v2, weight});
    }

    Vector<Vector<size_t>> graph(s.get_size());

    for (int i = 0; i < edges.get_size(); i++)
    {
        graph[s.get_id(edges[i].from.name)].push_back(s.get_id(edges[i].to.name));
        graph[s.get_id(edges[i].to.name)].push_back(s.get_id(edges[i].from.name));
    }

    fin.close();

    size_t result = 0;

    Kruskal_Algo(edges, s, result);

    cout << "\nKruskal algo result: " << result << endl;

    cout << "BFS:\n";

    BFS(graph);


    cout << "DFS: \n\n";
    DFS(graph);


    return 0;
}