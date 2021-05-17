#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

class Abilities;

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
  std::vector<std::shared_ptr<Observer<InfoType, StateType>>> observers;
 public:
  void attach(std::shared_ptr<Observer<InfoType, StateType>> o); 
  void notifyObservers();
  virtual InfoType getInfo() const = 0;
  virtual StateType getState() const = 0;
  virtual std::shared_ptr<Abilities> get_ability() const = 0;
};


template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(std::shared_ptr<Observer<InfoType, StateType>> o) {
  observers.emplace_back(o);
}


template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

#endif
