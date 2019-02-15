#ifndef KRETS_H 
#define KRETS_H

#include <vector>
#include <string>
#include <cmath>

class Node
{
public:
    Node();
    double current;
};

class Component
{
public:
    Component(std::string const & n, Node* node1, Node* node2);
    virtual ~Component() = default;
    virtual void simulate(double const step)=0;
    virtual std::string get_name() const=0 ;
    virtual void print_info()=0;
    virtual void update_info()=0;
protected:
    std::string name;
    double volt, curr;
    Node* n;
    Node* p;
};

class Battery: public Component
{
public:
    Battery(std::string const & n, double const c, Node* input, Node* output);
    ~Battery();
    void simulate(double const);
    std::string get_name() const;
    void print_info();
    void update_info();
private:
    double current;
};

class Resistor: public Component
{
public: 
    Resistor(std::string const & n, double const r, Node* node1, Node* node2);
    ~Resistor();
    void simulate(double const step);
    std::string get_name() const;
    void print_info();
    void update_info();
private:
    double resistance;
};

class Capacitor: public Component
{
public:
    Capacitor(std::string const & n, double const c, Node* node1, Node* node2);
    ~Capacitor();
    
    void simulate(double const step);
    std::string get_name() const;
    void print_info();
    void update_info();
private:
    double capacitance, charge;
};

void write_top_row(std::vector <Component*>& v);
void write_net(std::vector <Component*>& v);
void simulate_net(std::vector <Component*>& v, int iterations, int prints, double step);
void clear_net(std::vector <Component*> & v);

#endif
