/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Nom, Prénom - Matriule - 2020/12 - <Cont.hpp>
 * Exemple de conteneur (projet n°1)
 */
#ifndef _CONT_H_
#define _CONT_H_

#include  "Vect.hpp"
#include  "BST.hpp"
#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <utility>             // swap, move, forward...
#include  <exception>
#include  <stdexcept>           // standard exceptions
#include  <iostream>             // output streams

// Common output operator ====================================================

namespace _Cont_base {
  namespace {
    template <typename U>
    struct _Base {
      constexpr void _dsp (std::ostream& out) const
        {static_cast<const U*>(this)->_dsp(out);}
    };
  }
}

template <typename U>
std::ostream& operator<< (std::ostream& out, const _Cont_base::_Base<U>& b)
  {b._dsp(out); return out;}

// Abstract base class =======================================================

template <typename T>
class Cont_base { // abstract

  using value_type      = T;
  using reference       = T&;
  using const_ref = const  T&;
public:
  class Info;//BST
  class Ptr2Info;//Vect
protected:
  static const Info _EMPTY;
  // Access methods
  static constexpr std::ptrdiff_t _index (const Info& i) {return i._index;}
  static constexpr std::ptrdiff_t& _index (Info& i) {return i._index;}
  static constexpr const Info* _ptr (const Ptr2Info& p) {return p._ptr;}
  static constexpr const Info*& _ptr (Ptr2Info& p) {return p._ptr;}

  // Implementation
  std::size_t _used = 0;
  virtual void _dsp (std::ostream&) const = 0;
  // Non virtual assignations => protected
  Cont_base& operator= (const Cont_base&) = default;
  Cont_base& operator= (Cont_base&& c){   
    if (this != &c)
    {
       _used = c._used; c._used = 0;
    } 
    return *this;}
public:
  // Constructors & destructor
  constexpr Cont_base () noexcept = default;
  constexpr Cont_base (const Cont_base&) noexcept = default;
  constexpr Cont_base (Cont_base&& c) noexcept: _used(c._used) {c._used = 0;}
  virtual ~Cont_base () noexcept = default;

  //insert
  virtual const T& insert ( std::ptrdiff_t i , const T& v)  = 0 ;
  //find
  virtual const T&   find ( std::ptrdiff_t i , const T& v)const  = 0 ;
  virtual const T&  find (const T&  v) const   = 0;
  //erase
  virtual bool  erase ( std::ptrdiff_t i , const T& v) = 0 ;
  virtual bool erase (const T&  v)   = 0 ;
  // Getter
  constexpr std::size_t used () const noexcept {return _used;};

}; // Cont_base<T>

template <typename T>
const typename Cont_base<T>::Info Cont_base<T>::_EMPTY{};

// Embedded class Info =======================================================

template <typename T>
class Cont_base<T>::Info: public _Cont_base::_Base<typename Cont_base<T>::Info> {

  friend class Cont_base<T>;   // for _index static methods
  friend struct _Cont_base::_Base<Info>; //for _dsp methods

  std::ptrdiff_t _index = -1;
  const T _data{};
  
  constexpr void _dsp (std::ostream& out) const {out << _data;}
public:
  // Traits
  using value_type      = T;
  using reference       = T&;
  using const_ref = const T&;
  // Constructors & casts
  constexpr Info () noexcept = default;
  constexpr Info (std::ptrdiff_t i, const T& v) noexcept: _index(i), _data(v) {}
  constexpr Info (const_ref v) noexcept: _data(v) {}             // implicit cast
  constexpr operator const_ref () const noexcept {return _data;} // implicit cast
  template <typename>
  friend constexpr bool operator< (const Info&, const Info&) noexcept;
  template <typename>
  friend constexpr bool operator== (const Info&, const Info&) noexcept;
  constexpr bool operator< (const Info& i) const noexcept
    {return _data < i._data;}
  constexpr bool operator== (const Info& i) const noexcept
    {return _data == i._data;}
}; // Info
template <typename T>
bool operator<(const typename Cont_base<T>::Info& i ,const typename  Cont_base<T>::Info& j )noexcept{
  return true ? i.operator<(j) : false ;
}
template <typename T>
bool operator== (const typename Cont_base<T>::Info& i,const typename Cont_base<T>::Info& j) noexcept{
  return true ? i.operator==(j) : false ;
}
// Embedded class Ptr2Info ===================================================

template <typename T>
class Cont_base<T>::Ptr2Info: public _Cont_base::_Base<typename Cont_base<T>::Ptr2Info> {

  friend class Cont_base<T>;   // for _ptr static methods
  friend struct _Cont_base::_Base<Ptr2Info>;

  const Info *_ptr = nullptr;
  
  constexpr void _dsp (std::ostream& out) const
    {out << (_ptr ? *_ptr : _EMPTY);}
public:
  // Traits
  using value_type      = T;
  using reference       = T&;
  using const_ref = const T&;
  // Constructors & casts
  constexpr Ptr2Info () noexcept = default;
  constexpr operator const Info& () const noexcept     // implicit cast
    {return _ptr ? *_ptr : _EMPTY;}
  constexpr operator const T& () const noexcept        // implicit cast
    {return _ptr ? *_ptr : _EMPTY;}
  // Getter
  constexpr bool isEmpty () const noexcept {return !_ptr;}
  template <typename>
  friend constexpr bool operator< (const Ptr2Info&, const Ptr2Info&) noexcept;
  constexpr bool operator< (const Ptr2Info& i) const noexcept
    {return _ptr->_data < i._ptr->_data;}
  constexpr bool operator== (const Ptr2Info& i) const noexcept
    {return _ptr->_data == i._ptr->_data;}
}; // Ptr2Info
template <typename T>
bool operator<(const typename Cont_base<T>::Ptr2Info& i ,const typename  Cont_base<T>::Ptr2Info& j ){
  return true ? i.operator<(j) : false ;
}
template <typename T>
bool operator== (const typename Cont_base<T>::Ptr2Info& i,const typename Cont_base<T>::Ptr2Info& j) noexcept{
  return true ? i.operator==(j) : false ;
}
namespace _Cont_base {
  template <typename> using _Base = void;   // "destroy" access to real _Base
}

// Main class ================================================================

template <typename T>
class Cont final: private Cont_base<T>,public  BST<typename Cont_base<T>::Info>,public Vect<typename Cont_base<T>::Ptr2Info>  {
  using _Base = Cont_base<T>;
  using _Vect = Vect<typename Cont_base<T>::Ptr2Info> ;
  using _BST =  BST<typename Cont_base<T>::Info> ;
  using _Base::_index;
  using _Base::_ptr;
  using _Base::_used;
  using _Base::_EMPTY;
protected :
  void _dsp (std::ostream& out ) const override ; //_BST
public:
  // Traits
  using Info = typename _Base::Info;
  using Ptr2Info = typename _Base::Ptr2Info;
  using _BST::insert;
  using _BST::find;
  using _BST::erase ;
  using _Vect::operator[];
  using _Base::used;
  
  //constructeur 
  constexpr Cont () noexcept = default;
  constexpr Cont (std::size_t size)noexcept : _Base() , _BST() , _Vect(size){}

  // constructor Copie/transfert
  constexpr Cont (const Cont &cont)noexcept :_Base(cont) , _BST(cont) , _Vect(cont){
   _BST::traverse([this](const Info& v){
        _ptr(_Vect::operator[](_index(v))) = &v;});
  }
  constexpr Cont (Cont&& cont) noexcept: _Base(std::move(cont)) , _BST(std::move(cont)) , _Vect(std::move(cont)){
    _BST::traverse([this](const Info& v){
        _ptr(_Vect::operator[](_index(v))) = &v;});
  }
  
  /*
    constexpr Cont (const _Vect&)noexcept;
    constexpr Cont (_Vect&&)noexcept;
    constexpr Cont (const _BST&)noexcept;
    constexpr Cont (_BST&&)noexcept;
  */
  //operator copie/transfert  
  Cont& operator= (const Cont& cont) {
    _Base::operator=(cont);
    _BST::operator=(cont);
    _Vect::operator=(cont);
    _BST::traverse([this](const Info& v){
        _ptr(_Vect::operator[](_index(v))) = &v;});
        return *this;
  }
  Cont& operator= (Cont&& cont){
    _Base::operator=(std::move(cont));
    _BST::operator=(std::move(cont));
    _Vect::operator=(std::move(cont));
    _BST::traverse([this](const Info& v){
        _ptr(_Vect::operator[](_index(v))) = &v;});
    return *this;
  }

  /*
  Cont& operator= (const _Vect&);
  Cont& operator= (_Vect&&);
  Cont& operator= (const _BST&);
  Cont& operator= (_BST&&);
  */

  // initializer
  Cont (const std::initializer_list<T>& init) noexcept: _Base(),_BST(),_Vect(init.size()) {
  auto p = init.begin();
  for (std::size_t i = 0; i < init.size() ; ++i)  insert(i,*p++); //conversion size_t to ptrdiff_t
  } 
  // initializer with dimension
  Cont (std::size_t dim , const std::initializer_list<T>& init) noexcept: _Base(),_BST(),_Vect(dim) {//conversion size_t to ptrdiss_t
  std::size_t size = init.size() > dim ? dim : init.size();
  auto p = init.begin();
  for (std::size_t i = 0; i < init.size() ; ++i)  insert(i,*p++);
  }
  
  //method overrided from Cont_base ==============
  const T& insert ( std::ptrdiff_t i , const T& v)  override;
  const T& find ( std::ptrdiff_t i , const T& v)const  override {return find({i,v});}
  const T& find (const T& v) const  override {return _BST::find(v);}
  bool erase ( std::ptrdiff_t i , const T& v) override;
  bool erase (const T& v)  override {return erase(_BST::find(v));}
  
  //method overrided from BST====================
  const Info& insert (const Info& info) override{
    insert(_index(info),info); 
    return find(info);
  }
  const Info& find (const Info& info) const noexcept override;  
  bool erase (const Info& info)  override {return erase(_index(info),info);}

  
  // fonction externe
friend inline std::ostream& operator<< (std::ostream& out, const Cont<T>& c)
  {c._dsp(out); return out;}
  
}; // Cont<T>

template <typename T>
void Cont<T>::_dsp (std::ostream& out) const {
  _BST::_dsp(out);
}

//insert value in spicifier index
template <typename T>
const T& Cont<T>::insert (std::ptrdiff_t i , const  T& v){
   Info *info = new Info(i,v);
   if(!find(v)){// if theyre not this value on tree
     Ptr2Info ptr = operator[](i);
     if(_ptr(ptr) != nullptr){erase(*_ptr(ptr));} //delete if position is ocupped
     _used++;
     _ptr(operator[](i)) = info; //add new
     return _BST::insert(*info); 
   }
   std::ptrdiff_t idx = _index(_BST::find(v));
   if( i != idx ){
      erase(_BST::find(v));
     _ptr(_Vect::operator[](i)) = info;
     return _BST::insert(*info);
   }
  return find(*info); 
}

//find info with object info 
template <typename T>
const typename Cont_base<T>::Info& Cont<T>::find( const Info& info) const noexcept {
  Ptr2Info ptr = _Vect::operator[](_index(info));
  if(*_ptr(ptr) != info){return _EMPTY;}
  return *_ptr(ptr);
  };

// erase value with indix
template <typename T>
bool Cont<T>::erase(std::ptrdiff_t i , const T& v)  {
  bool res = false ;
  if(find(i,v)){
    res = _BST::erase(v);
    if(res ){
      _used--;
      delete _ptr(_Vect::operator[](i)); 
      _ptr(_Vect::operator[](i)) = nullptr;
    }
  } 
  return res;
}

// Deduction guides ==========================================================

template <typename T>
Cont (const Vect<T>&) -> Cont<typename T::value_type>;

template <typename T>
Cont (const BST<T>&) -> Cont<typename T::value_type>;


#endif // _CONT_H_

