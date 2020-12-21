


#include  "Cont.hpp"
#include "Vect.hpp"
#include "BST.hpp"
#include "Student.hpp"
#include  <utility>             
#include  <exception>
#include  <iostream>           



int main () {

Cont<int> c = Cont<int>(10);
Cont<char> d = {'s','f','z','n'};

std::cout<<"==============insertion ============"<< std::endl;
std::cout<< c.insert(0,1) << std::endl;
std::cout<< c.insert(1,2) << std::endl;
std::cout<< c.insert(2,3) << std::endl;
std::cout<< c.insert(3,4) << std::endl;
Cont_base<int>::Info info1 = Cont_base<int>::Info(4,5);
std::cout<< "insert object info1(4,5): " << c.insert(info1)<< std::endl;
std::cout << "c.used = "<<c.used()<<std::endl;



Cont_base<int>::Info info2 = Cont_base<int>::Info(2,3);
std::cout<<""<< std::endl;
std::cout<<"============== find/erase/insert ============"<< std::endl;
std::cout<<" find(1): c[0] = "<<  c.find(1) << std::endl;
std::cout<<"c[3] = "<<  c[3] << std::endl;
std::cout<<"find(1,2): c[1] = "<< c.find(1,2) << std::endl;
std::cout<<"find (info1): c[4] = "<< c.find(info1) << std::endl;
std::cout<<"insert(info2): c[2] = "<< c.insert(info2) << std::endl;
std::cout<<"c[] = "<< c << std::endl;
std::cout<<"erase(1)-> "<< c.erase(1) << std::endl;
std::cout<<"erase(1,2) -> "<<c.erase(1,2)<<std::endl;
std::cout<<"erase(info2) -> "<<c.erase(info2)<<std::endl;
std::cout<<"c[] = "<< c << std::endl;
std::cout << "c.used = "<<c.used()<<std::endl;

std::cout<<""<< std::endl;
std::cout<<"============== copie & transfer ============"<< std::endl;
Cont<char> s = Cont<char>(d) ; //copie
std::cout<<"copie de  d ver s = "<< s << std::endl;
std::cout<<"apres copie d[] = "<< d << std::endl;

std::cout<<""<< std::endl;
Cont<char> g = Cont<char>(Cont<char>(s)) ; //transfer
std::cout<<"transfer d'une copie de s ver g = "<< g << std::endl;
std::cout<<"apres transfer s[] = "<< s << std::endl;

std::cout<<""<< std::endl;
Cont<int> v = Cont<int>(std::move(c)) ; //transfer
std::cout<<"transfer de c ver v = "<< v << std::endl;
std::cout<<"apres transfer c[] = "<< c << std::endl;

std::cout<<""<< std::endl;
Cont<int> z = v ; //operator copie
std::cout<<"copie de v ver z = "<< z << std::endl;
std::cout<<"apres copie v[] = "<< v << std::endl;

std::cout<<""<< std::endl;
Cont<int> w = std::move(v) ; //transfer
std::cout<<"transfer de v ver w = "<< w << std::endl;
std::cout<<"apres transfer v[] = "<< v << std::endl;



std::cout<<""<< std::endl;
std::cout<<"============== function maxValue polymorphe  ============"<< std::endl;
Vect<int> vect1 = {1,2,3,4,5};
Cont<int> cont1 = {1,2,3,4,5,6};
Vect<Cont_base<int>::Ptr2Info> *cont = new Cont<int>(cont1);
std::cout<<"max value for vect1 "<< vect1.maxValue()  << std::endl;
std::cout<<"max value for cont "<< cont->maxValue()  << std::endl;


/*
std::cout<<""<< std::endl;
std::cout<<"============== teste with class student  ============"<< std::endl;
Cont<Student> stds = Cont<Student>(5);
stds.insert(0,Student("000",10));
stds.insert(1,Student("001",11));
stds.insert(2,Student("010",12));
stds.insert(3,Student("111",13));
*/


  return 0;
}
