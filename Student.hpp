#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;

class Student
{
	public:
		Student() = default;
		Student(string mat,int note): _matricule(mat),_note(note){};
		Student(const Student& s): _matricule(s._matricule),_note(s._note){};
		string getName() const;
		void setMat( string mat ){_matricule = mat; };
		void setNote( int n ){_note = n; };
		string getMat() const{return _matricule;};
		int getNote() const{return _note;};

        constexpr bool operator< (const Student& s) const noexcept
        {return _note < s._note;}
		constexpr bool operator== (const Student& s) const noexcept
		{return _note == s._note && _matricule == s._matricule;}
		/*
		constexpr bool operator!= (const Student& s) const noexcept
		{return _matricule != s._matricule;}
		*/
        friend inline ostream& operator<< (std::ostream& out, const Student& s);
       
	private:
		string _matricule;
		int _note;
		
};

inline ostream& operator<< (ostream& out, const Student& s){out<< s.getMat(); return out;}
inline constexpr bool operator< (const Student& s, const Student& t) noexcept{return true ? s.operator<(t) : false ;}
inline constexpr bool operator== (const Student& s, const Student& t) noexcept{return true ? s.operator==(t) : false ;}


#endif // STUDENT_H_INCLUDED  