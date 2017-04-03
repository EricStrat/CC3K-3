#include "subject.h"
#include "observer.h"
#include "subscriptions.h"

Subject::~Subject() {}

void Subject::attach(Observer *o) { observers.emplace_back( o );  }

void Subject::notifyObservers()
{
  for ( auto it = observers.begin(); it != observers.end(); ++it ) (*it)->notify( *this );
}
