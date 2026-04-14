#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include <iostream>
using namespace std;

//LinkedList Node
template <typename T>
class Node{
	public:
		//데이터를 저장할 변수
		T data;
		//노드구조체 이용; 다음노드의 주소를 저장할 포인터
		Node *link;

		Node(T element){
		  data = element;
		  link = 0;
		}
	};

//LinkedList Class
template <typename T>
class LinkedList{
	protected:
		//첫번째 노드의 주소를 저장할 포인터
		Node<T> *first;
		int current_size;
	public:
		//생성자, 초기화 
		LinkedList(){
			first = 0;
			current_size = 0;
		};

		//노드 개수를 리턴
		int GetSize(){
			return current_size;
		};

		//맨 앞에 원소를 삽입, LinkedList와 Stack 둘다 같다
		void Insert(T element);
		
		//맨 뒤의 원소를 삭제, 제일 나중에 들어온 원소 삭제  - LinkedList
		virtual bool Delete(T &element);

		//리스트 출력
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


#endif
