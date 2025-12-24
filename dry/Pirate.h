#pragma once
#include <iostream>

using std::string;

class Pirate {
private:
    string name;
    int bounty;
public:
    Pirate() = default;
    Pirate(const string& name, int bounty);
    ~Pirate() = default;

    void setName(const string& name);
    void setBounty(int bounty);
    int getBounty() const;

    string getName() const;

    friend std::ostream &operator<<(std::ostream &os, const Pirate &pirate);
};
