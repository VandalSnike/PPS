#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Date{
private:
  int day=0;
  int month=0;
  int year=0;
public:
  Date(){}
  Date(const int& day_,const int& month_, const int& year_){ //MIGLIOARE I CONTROLLI DATE
  if(day_<=0 || day_>31){
    std::cerr << "Data inammissibile" << '\n';
  }
  if (month_<=0 ||month>12) {
    std::cerr << "Mese inammissibile" << '\n';
  }
  if (year_<0 ||year_>2021) {
    std::cerr << "Data inammissibile" << '\n';
  }
  day=day_;
  month=month_;
  year=year_;
  }
  inline int GetDay() const {return day;}
  inline int GetMonth() const {return month;}
  inline int GetYear() const {return year;}


  friend bool operator<(const Date& d1, const Date& d2);
  friend bool operator>(const Date& d1, const Date& d2);
};
  //Operator<
  bool operator<(const Date& d1, const Date& d2){
    if (d1.GetYear()!=d2.GetYear()) {
      return d1.GetYear()<d2.GetYear();
    }
    if (d1.GetMonth()!=d2.GetMonth()) {
      return d1.GetMonth()<d2.GetMonth();
    }
    if (d1.GetDay()!=d2.GetDay()) {
      return d1.GetDay()<d2.GetDay();
    }
  }
  //Operator>
  bool operator>(const Date& d1, const Date& d2){
    return d2<d1;
  }
  //operator==
  bool operator==(const Date& d1, const Date& d2){
    return (d1.GetYear()==d2.GetYear()&&
            d2.GetMonth()== d2.GetMonth() &&
            d1.GetDay()==d2.GetDay());
  }
  //operator<<
  ostream& operator<<(ostream& out, const Date& d){
    out<<d.GetDay()<<" ";
    out<<d.GetMonth()<<" ";
    out<<d.GetYear()<<" "<<endl;
    return out;
  }

class Person{
private:
  string name="";
  string surname="";
  string adress="";
  Date d;
public:
  Person(){}
  Person(const string& name_, const string& surname_, const string& adress_,
         const int& d_, const int& m_, const int& y_):name(name_), surname(surname_),adress(adress_),
                                                      d(d_,m_,y_){
  /*name=name_, surname=surname_,.....*/
  }
  Person(const string& name_, const string& surname_, const string& adress_,const Date& dinput_):
                                                      name(name_), surname(surname_),adress(adress_),
                                                      d(dinput_){ //tramite copy costructor
  }

  inline string GetName() const {return name;}
  inline string GetSurname() const {return surname;}
  inline string GetAdress() const {return adress;}
  inline const Date& GetDate() const {return d;} //Ritorno di date
  void Print(){
    std::cout << "Nome:" <<name<< '\n';
    std::cout << "Cognome:" <<surname<< '\n';
    std::cout << "Adress:" <<adress<< '\n';
    std::cout << "Date:" <<d.GetDay()<<"/"<<d.GetMonth()<<"/"<<d.GetYear()<< '\n';
  }

  friend class People;
};

// Operator<<
ostream& operator<<(ostream& out, const Person& p1){
  out<<p1.GetName()<<endl;
  out<<p1.GetSurname()<<endl;
  out<<p1.GetAdress()<<endl;
  out<<p1.GetDate(); //need to define operator<< for Date class
  return out;
}

// Operator>>
//istream& operator>>(istream& in, const )
// Operator==
bool operator==(const Person& p1, const Person& p2){
  return (p1.GetName()==p2.GetName() &&
          p1.GetSurname()==p2.GetSurname() &&
          p1.GetAdress()==p2.GetAdress() &&
          p1.GetDate()== p2.GetDate());
}


class People{
private:
  int number=0;
  Person* people=nullptr;
public:
  People(const int& n){
    number=n;
    people = new Person[number]; //call Default costructor of Person
  }

  ~People(){
    if(people!=nullptr){delete[] people; std::cout << "Deleted" << '\n';}
  }

  void SetPerson(const Person& p,const int& pos){
    if (pos<0 || pos>number) {
      return ;
    }
    people[pos]=p;  //ne crea uno lui implicito per copy costructor
  /*  people[pos].name=p.GetName();
    people[pos].surname=p.GetSurname();
    people[pos].adress=p.GetAdress();
    people[pos].d=p.GetDate();*/
  }

  inline Person GetPerson(const int& pos) const{
    if (pos<0 || pos>number) {
      std::cerr << "Error position not valid" << '\n'; ;
    }
    return people[pos];
  }

  //Cerca persona
  //Cerca più vecchio
  Person Oldest()const{
    Person oldest=people[0];
    for (size_t i = 1; i < number; i++) {
      if (people[i].GetDate()<oldest.GetDate()) {
        oldest=people[i];
      }
    }
    return oldest;
  }
  //Cerca più giovane
};

int main(){
  //tramite copy costructor
  //Date d1(29,11,62);
  // Person p1("Sandro","Petrilli","Via del Risorgimento",d1);

  Person father("Sandro","Petrilli","Via del Risorgimento",29,11,62);
  Person mother("Caterina","Priore","Via del Risorgimento",24,07,63);
  Person sister("Lidia","Petrilli","Via del Risorgimento",Date(15,02,2000));
  //father.Print();
  //mother.Print();
  cout<<father;
  cout<<mother;
  ofstream out("Try1.txt");
  if (out.good()) {
    out<<father;
    out<<mother;
  }
  out.close();

  People family(2);
  family.SetPerson(father,0);
  cout<<family.GetPerson(0);
  family.SetPerson(mother,1);
  std::cout <<family.GetPerson(1);
  std::cout << "Oldest:"<<family.Oldest() << '\n';
  return 0;
}
