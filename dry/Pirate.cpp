#include "Pirate.h"


Pirate::Pirate(const string& name, int bounty): name(name), bounty(bounty) {}


void Pirate::setName(const string& name){
    this->name = name;
}
void Pirate::setBounty(int bounty){
    this->bounty = bounty;
}


std::string Pirate::getName() const{
    return name;
}

int Pirate::getBounty() const{
    return bounty;
}


std::ostream &operator<<(std::ostream &os, const Pirate &pirate){
    os << pirate.name<< " ";
    os << pirate.bounty;
    return os;
}