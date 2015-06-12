/*
*Class: F1403022
*Name: Tian Xiaoliang
*NO: 5140309520

*/
#include<iostream>
//Using the following library only to create random number.
#include<cstdlib>
#include<ctime>
using namespace std;

class Exception{
public:
    Exception(const char* ErrorMsg){cerr<<ErrorMsg<<endl;abort();}
}; //A class for handling my exception of run-time errors.

template<class Tem>
class MyList{
    template<class Tem1> friend ostream &operator<<(ostream &os, const MyList<Tem1> &obj);
    template<class Tem1> friend MyList<Tem1> operator + (const MyList<Tem1> &l1, const MyList<Tem1> &l2);
    template<class Tem1> friend MyList<Tem1> operator + (const MyList<Tem1> &l1, const Tem1 &item);
private:
	Tem *a;
	int size;
	int maxsize; //The real size of the list.
	void double_space(int &maxsize); // Enlarge the size.

public:
	MyList();
	MyList(int num, const Tem &item); //Copy the item in the list for num times.
	MyList(const MyList<Tem> &l);//Deep copy construction.
    MyList(Tem* arr, int len);//Copy the first few items of the array.

	void push(const Tem &item);//Push the item in the button of the list.
	Tem pop();//Delete the last item and return it.
	void insert(int index, const Tem &item);//Insert the item in the subscript place.
	void clean();//Clean the list.

	int get_size()const;//Return the size of the list.
	Tem get_item(int index)const;//Return the item related to the index.
    MyList get_item(int start, int end);//Return the items from start to end.

	void erase(int start, int end);//Delete the list from start to end.
	int count(const Tem &item);//Return the number of the item which is equal to the given one.
	void remove(const Tem &item);//Delete the first item which is equal to the given one.

	MyList &operator = (const MyList<Tem> &l);//Assignment
	MyList &operator += (const Tem &item);//Add the given item in the button.
	MyList &operator += (const MyList<Tem> &l);//Add the given list in the button.
	Tem &operator [](int index);//return the item related to the index.

	void sort(bool less=true);// if less==true, sort the list from small to large; else sort in reverse.
	void reverse();//Invert the list.

	~MyList(){delete [] a;}
};

template<class Tem>
MyList<Tem>::MyList()
{
    size = 0;maxsize=100;
    a = new Tem [maxsize];
    if(a==NULL) throw Exception("Allocation failure.");
}

template<class Tem>
MyList<Tem>::MyList(int num, const Tem &item)
{
    int i;
    size=num;
    maxsize = size+20;
    a = new Tem [maxsize];
    if(a==NULL) throw Exception("Allocation failure.");
    for(i=0;i<size;++i) a[i]=item;
}

template<class Tem>
MyList<Tem>::MyList(const MyList<Tem> &l)
{
    size=l.size;
    maxsize = size+20;
    a = new Tem [maxsize];
    if(a==NULL) throw Exception("Allocation failure.");
    for(int i=0;i<size;++i) a[i]=l.a[i];
}

template<class Tem>
MyList<Tem>::MyList(Tem* arr, int len)
{
    size=len;maxsize=size+20;
    a = new Tem [maxsize];
    if(a==NULL) throw Exception("Allocation failure.");
    for(int i=0;i<size;++i) a[i]= arr[i];
}

template<class Tem>
void MyList<Tem>::double_space(int &maxsize)
{
    maxsize *= 2;
    Tem *b;
    b=new Tem [size];
    if(b==NULL) throw Exception("Allocation failure.");
    for(int i=0;i<size;++i) b[i]=a[i];
    delete [] a;
    a = new Tem [maxsize];
    if(a==NULL) throw Exception("Allocation failure.");
    for(int i=0;i<size;++i) a[i]=b[i];
    delete [] b;
}

template<class Tem>
void MyList<Tem>::push(const Tem &item)
{
    if(size==maxsize) double_space(maxsize);
    a[size++]=item;
}

template<class Tem>
Tem MyList<Tem>::pop()
{
    if(size==0) {throw Exception("The list is empty!");}
    else {
        size--;maxsize--;
        return a[size];
    }
}

template<class Tem>
void MyList<Tem>::insert(int index, const Tem &item)
{
    Tem lodging,pre=item;;
    if(size==maxsize) double_space(maxsize);
    try{
        if(index>size || index<0) throw Exception("Index out of range.");
        if(index==size) {push(item);return;}
        else{
            for(int i=index;i<size;++i){
                lodging=a[i];a[i]=pre;pre=lodging;
            }
        }
        a[size++]=pre;
    }
    catch(Exception ex){}
}

template<class Tem>
void MyList<Tem>::clean()
{
    if(size!=0){
        delete [] a;
        maxsize=100;size=0;
        a = new Tem [maxsize];
        if(a==NULL) throw Exception("Allocation failure.");
    }
}
template<class Tem>
int MyList<Tem>::get_size()const
{
    return size;
}

template<class Tem>
Tem MyList<Tem>::get_item(int index)const
{
    try{
        if(index>size || index<0)
            throw Exception("Index out of range.");
        else return a[index];
    }
    catch(Exception ex){}
}

template<class Tem>
void MyList<Tem>::erase(int start, int end)
{
    if(end<0) end=(end+size)%size;
    try{
        if(end >= size || start>end || start<0)
            throw Exception("Index out of range.");
        else{
            for(int i=start;i<size+start-end-1;++i)
                a[i]=a[i+end-start+1];
            size -=(end-start+1);
        }
    }
    catch(Exception ex){}
}
template<class Tem>
MyList<Tem> MyList<Tem>::get_item(int start, int end)
{
    MyList<Tem> result;
    if(end<0 && end>= -size) end=(end+size)%size;
    try{
        if(start<0 || end>=size || end<0 || start>=size)
            throw Exception("Index out of range.");
        else if(start>end){         //return an empty list.
            delete [] result.a; result.a=NULL;
            return result;
        }
        else{
            for(int i=start;i<=end;++i)
                result.push(a[i]);
            return result;
        }
    }
    catch(Exception ex){}
}//If the end is negative, the subscript is in reverse.
template<class Tem>
int MyList<Tem>::count(const Tem &item)
{
    int times=0;
    for(int i=0;i<size;++i)
        if(a[i]==item) ++times;
    return times;
}
template<class Tem>
void MyList<Tem>::remove(const Tem &item)
{
    int loc;
    for(int i=0;i<size;++i)
        if(a[i]==item) {loc=i;break;}
    erase(loc,loc);
}

template<class Tem>
MyList<Tem> &MyList<Tem>::operator = (const MyList<Tem> &l)
{
    if(this==&l) return *this;
    delete [] a;
    size=l.size;
    maxsize = size+20;
    a = new Tem [maxsize];
    if(a==NULL) throw Exception("Allocation failure.");
    for(int i=0;i<size;++i) a[i]=l.a[i];
    return *this;
}
template<class Tem>
MyList<Tem> &MyList<Tem>::operator += (const Tem &item)
{
    push(item);
    return *this;
}

template<class Tem>
MyList<Tem> &MyList<Tem>::operator += (const MyList<Tem> &l)
{
    Tem item;
    for(int i=0;i<l.get_size();++i){
        item=l.get_item(i);
        push(item);
    }
    return *this;
}

template <class Tem>
Tem &MyList<Tem>::operator [](int index)
{
    try{
        if(index<0 && index>=size)
            throw Exception("Index out of range.");
        else return a[index];
    }
    catch(Exception ex){}
}

template <class Tem>
void MyList<Tem>::sort(bool less)
{   //The Merge sort.
    int low=1,up,m=1;
    int n = size;
    Tem *extra;
    extra = new Tem [n+1];
    if(extra==NULL) throw Exception("Allocation failure.");
    while(m<n){
        if((low+2*m-1)<n) up=low+2*m-1;
        else up=n;
        int p=low,q=low+m,r;
        for(r=1;r<=n;++r) extra[r]=a[r-1];
        r=low-1;

        while(p<low+m && q<up+1){
            if(less)
                while(p<low+m && extra[p]<=extra[q]) a[r++]=extra[p++];
            else {while(p<low+m && extra[p] >= extra[q]) a[r++]=extra[p++];}
            if(p<low+m){
                if(less)
                    while(q<up+1 && extra[q] < extra[p]) a[r++]=extra[q++];
                else {while(q<up+1 && extra[q] > extra[p]) a[r++]=extra[q++];}
            }
        }

        if(p==low+m) for(;q<=up;q++) a[r++]=extra[q];
        if(q==up+1) for(;p<=low+m-1;p++) a[r++]=extra[p];

        if(up+m < n) low=up+1;
        else{m *= 2; low=1;}
    }
    delete []extra;
}

template <class Tem>
void MyList<Tem>::reverse()
{
    Tem lodging;
    int left=0,right=size-1;
    while(left<right){
        lodging=a[left];
        a[left]=a[right];
        a[right]=lodging;
        ++left;--right;
    }
}

template <class Tem>
ostream & operator<<(ostream &os, const MyList<Tem> &obj)
{
   int len;
   len = obj.get_size();
   os<<'[';
   for(int i=0;i<len;++i){
     if(i==len-1)
        os<<obj.get_item(i);
    else os<<obj.get_item(i)<<", ";
   }
   os<<']';
   return os;
}

template <class Tem>
MyList<Tem> operator + (const MyList<Tem> &l1, const MyList<Tem> &l2) //Merge the two list.
{
    MyList<Tem> L = l1;
    L += l2;
    return L;
}

template <class Tem>
MyList<Tem> operator + (const MyList<Tem> &l1, const Tem &item) //Merge the list and an item.
{
    MyList<Tem> L = l1;
    L += item;
    return L;
}

int main()
{
	MyList<int> a, b;
	int i,num;
	//Test for sorting.
	srand(time(NULL));
	for (i=0; i<200; ++i){
        num=rand();
        a.push(num);
	}
	a.sort(false);
	cout<<a<<"\n"<<endl;

	//Test for a nested list.
	a.clean();
	for(i=0;i<5;++i)
        a.push(i);
    a[3]=15;
	MyList<MyList<int> > NestList;
    NestList.push(a);// a = [0, 1, 2, 15, 4]
	a.reverse();
	a += 12; // a = [4, 15, 2, 1, 0, 12]
	NestList.insert(0,a);
	cout<<"The NestList is "<<NestList<<endl;
	//NestList=[[4, 15, 2, 1, 0, 12],[0, 1, 2, 15, 4]]
	for (i=0; i<NestList[0].get_size(); ++i)
		cout<<NestList[0][i]<<endl;
    cout<<endl;

    //Test for other object.
    b = a.get_item(4, -3); // b = []
	b = a.get_item(3, -1); // b = [1, 0, 12]
	a += b; // a = [4, 15, 2, 1, 0, 12, 1, 0, 12]
	cout<<"\nThe times the item occurs is "<<a.count(12)<<endl;
	b.clean(); // b = []
	cout<<"Size of b: "<<b.get_size()<<endl;
	a.erase(2, 5); // a = [4, 15, 1, 0, 12]
	b = a + a; // b = [4, 15, 1, 0, 12, 4, 15, 1, 0, 12]
	b.insert(3, 116); // b = [4, 15, 1, 116, 0, 12, 4, 15, 1, 0, 12]
	b.remove(4); // b = [15, 1, 116, ...]
	cout<<b<<endl;

	//Test for other templates.
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;

    //Test for run-time error.
    //a.insert(100,10);//Index out of range.
    //a.erase(1,20);//Index out of range.
    //a.get_item(1,-13);//Index out of range.
    //a.get_item(100);//Index out of range.
    a.clean();
    //a.pop();//Pop an empty list.

	return 0;
}
