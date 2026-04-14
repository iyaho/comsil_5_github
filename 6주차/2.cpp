#include <iostream>

using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node *link;
    Node(T element)
    {
        data = element;
        link = NULL;
    }
};
// Linked List Class
template <typename T>
class LinkedList
{
protected:
    Node<T> *first;
    int current_size;
public:
    
    LinkedList()
    {
        first = 0;
        current_size = 0;
    };

    Node<T>* getFirst() { return first; };
    void setFirst(Node<T> *node) { first = node; };
    int GetSize() { return current_size; }; // 리스트의 노드 개수를 리턴
    void subSize() { current_size--; }; 
    void Insert(T element); // 맨 앞에 원소를 삽입
    virtual bool Delete(T &element); // 맨 뒤의 원소를 삭제
    void Print();
};

template <typename T>
void LinkedList<T>::Insert(T element)
{
    Node<T> *newnode = new Node(element);
    newnode->link = first;
    first = newnode;
    current_size++;
}

template <typename T>
bool LinkedList<T>::Delete(T &element)
{
    if(first == 0)
        return false;
    Node<T> *current = first;
    Node<T> *previous = NULL;
    while(1)
    {
        if(current->link == 0) // find end node
        {
            if(previous) previous->link = current->link;
            else first = first->link;
            break;
        }
        previous = current;
        current = current->link;
    }
    element = current->data;
    delete current;
    current_size--;
    return true;
}

template <typename T>
void LinkedList<T>::Print(){
    if (first == 0) return;
    Node<T> *current = first;
    int i = 1;
    while(1)
    {
        if (current == 0) break;
        cout << "[" << i << "|" << current->data << "]";
        i++;
        current = current->link;
        
        if (i <= current_size) cout << "->";
    }
    cout << "\n";
}

template <typename T>
class Stack : public LinkedList<T>{
protected:
public:
    Stack() : LinkedList<T>() {};
    ~Stack();

    bool Delete(T &element);
};

template <typename T>
bool Stack<T>::Delete(T &element){
    
    Node<T> *current = LinkedList<T>::getFirst();
    if (current == 0)
        return false;
    Node<T> *next = current->link;
    element = current->data;
    delete current;
    LinkedList<T>::setFirst(next);
    LinkedList<T>::subSize();
    return true;
}

void prnMenu()
{
    cout<<"*******************************************"<<endl;
    cout<<"* 1. 삽입 2. 삭제 3. 출력 4. 종료 *"<<endl;
    cout<<"*******************************************"<<endl;
    cout<<endl;
    cout<<"원하시는 메뉴를 골라주세요: ";
}

int main()
{
    // 스택 및 연결 리스트 테스트용 코드
    int mode, selectNumber, tmpItem;
    LinkedList<int> *p;
    bool flag = false;
    
    cout<<"자료구조 선택(1: Stack, Other: Linked List): ";
    cin>>mode;
    // 기반 클래스의 포인터를 사용하여 기반 클래스 뿐만 아니라
    // 파생 클래스의 인스턴스 또한 접근할 수 있다. if(mode == 1)
    if(mode == 1)
        p = new Stack<int>(); // 정수를 저장하는 스택
    else
        p = new LinkedList<int>(); // 정수를 저장하는 연결 리스트
    // 처리 부분
    do{
        prnMenu();
        cin>>selectNumber;
        switch(selectNumber)
        {
            case 1:
                cout<<"원하시는 값을 입력해주세요: ";
                cin>>tmpItem;
                p->Insert(tmpItem);
                cout<<tmpItem<<"가 삽입되었습니다."<<endl;
                break; 
            case 2:
                if(p->Delete(tmpItem)==true)
                    cout<<tmpItem<<"가 삭제되었습니다."<<endl;
                else
                    cout<<"비어있습니다. 삭제 실패"<<endl;
                break; 
            case 3:
                cout<<"크기: "<<p->GetSize()<<endl;
                p->Print();
                break; 
            case 4:
                flag = true;
                break;
            default:
                cout<<"잘못 입력하셨습니다."<<endl;
            break;
        }
        if(flag)
        break;
    }
    while(1);
    return 0;
}