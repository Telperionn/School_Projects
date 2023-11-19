#ifndef PAIR_H  //file pair.h
#define PAIR_H  //pair, class definition



// more or less from STL library
// found in <utility> and <pair>

//*******************************************************************************
//	Programmer: Patrick Sadowy/Streller
//	Instructor: Professor Streller
//	Course: cs232
//	Date: 5/6/21
//	ADT name: pair
//	ADT file: pair.h
//
//	Class Name: pair
//
//	Data Elements: A pair class consists of a templated x value, and templated y
//                  value. Together they create a pair of values.
//
//	Structure: The elements of the pair are any data type value the user wishes.
//
//	A pair object has the following public data members:
//       T1 first - first component
//       T2 second - second component
// 
// 	A pair object has the following friend functions:
// 
//      friend bool operator< ( const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs ) - 
//              overloaded < relational operator
//      friend bool operator== ( const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs ) - 
//              overloaded == relational operator
// 
//	A pair object has the following public functions:
// 
//		Pair() - 
//      Pair(  const T1 v1,  const T2 v2 ) - 
//      Pair ( const Pair<U1,U2>& X) - 
//      Pair<T1,T2> makePair(  const T1& v1,  const T2& v2   ) - 
//      
//
//*******************************************************************************
//		Class Pair DEFINITION SECTION
//*******************************************************************************

template< class T1, class T2>
class Pair
  {
  public:

    T1 first;
    T2 second;

    // default constructor
    Pair(): first( T1() ), second( T2() )
    { }

    // constructor that initializes first and second
    Pair(  const T1 v1,  const T2 v2 ):
        first(v1), second(v2)
    { }


    //copy constructor
    template< typename U1, typename U2 >
    Pair ( const Pair<U1,U2>& X)
        : first( X.first ),  second( X.second )
    {}

    // overload <=
    template< typename U1, typename U2 >
    Pair& operator= ( const  Pair<U1,U2>& init )
    {
      return *this = Pair(init);
    }


    // overload <
    friend bool operator< ( const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs )
    {
      return lhs.first < rhs.first || !( rhs.first < lhs.first  && lhs.second < rhs.second   );
    }

    // overload ==
    friend bool operator== ( const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs )
    {
      return lhs.first == rhs.first && lhs.second == rhs.second ;
    }



  };



template< class T1, class T2 >
Pair<T1,T2> makePair(  const T1& v1,  const T2& v2   )
{
  return  Pair< T1, T2>(v1,v2);
}


#endif
