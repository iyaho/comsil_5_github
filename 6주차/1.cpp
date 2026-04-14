#include <iostream>

using namespace std;

class Array {
    protected:
        int *data; // 배열 포인터
        int len; // 배열의 크기
    public:
    Array(int size) { // 생성자
        // size가 0 이하 값이면 에러메시지 출력하고 종료
        // size가 양수이면 new를 사용하여 배열 data를 할당, len값 초기화
        if(size <= 0) {
            cout << "Error: Size must be positive." << endl;
            exit(1);
        }
        data = new int[size];
        len = size; 
    }
    ~Array() { delete[] data; } //소멸자; 할당된 메모리 해제
    int length( ) const { return len; } // 배열의 크기 리턴

    int operator [](int i) const {  // right value : 배열의 원소의 값을 반환
        if (i < 0 || i >= len){
            cout << "Array bound error!" << "\n";
            return 0;
        }
        return data[i];
    }
    int &operator [](int i) {       // left value : 배열의 원소의 주소를 반환
        static int tmp;
        if (i < 0 || i >= len){
            cout << "Array bound error!" << "\n";
            return tmp;
        }
        return data[i];
    }
    void print() { 
        cout << "[ ";
        for(int i = 0; i < len; i++) cout << data[i] << " "; 
        cout << "]\n"; 
    }// 배열의 모든 내용을 출력해주는 함수
};

class RangeArray : public Array {
    private:
        int base;
    public:
        RangeArray(int s, int e) : Array(e - s + 1), base(s) {} // 생성자; start값 초기화, Array의 생성자 호출하여 배열 할당
        ~RangeArray() {} // 소멸자; Array의 소멸자 호출하여 메모리 해제

        int baseValue() const { return base;}
        int endValue() const { return base + length() - 1;}  

        int operator [](int i) const {
            return Array::operator[](i - base); 
        }

        int &operator [](int i) {
            return Array::operator[](i - base);
        }
};

int main() {
    int i, x, y;
    Array a(10), b(5);
    for(i=0; i<a.length(); i++) a[i]= i+1; //left value
    for(i=0; i<b.length(); i++) b[i]= i*2;

    cout<<"a(10)"; a.print();
    cout<<"b(5)"; b.print();
    cout<<"a[-1] ";
    a[-1]=7; // Array bound error!
    x=a[0]; y=b[0]; // right value
    cout<<"a[0]="<<x<<" b[0]="<<y<<endl;
    RangeArray c(-1, 3), d(3, 7);
    for(i=c.baseValue(); i<=c.endValue(); i++) c[i]=i*3; //left value
    for(i=d.baseValue(); i<=d.endValue(); i++) d[i]=i*4;
    cout<<"c(-1,3)"; c.print();
    cout<<"d(3,7)"; d.print();
    cout<<"c[-2] ";
    c[-2]=3; // Array bound error!
    x=c[-1]; y=d[3]; // right value
    cout<<"c[-1]="<<x<<" d[3]="<<y<<endl;
    return 0;
}

