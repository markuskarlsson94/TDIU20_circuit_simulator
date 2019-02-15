#include "krets.h" 
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

Node::Node(): current{0} {}

Component::Component(string const & n, Node* node1, Node* node2):name{n}, n{node1}, p{node2} {}

Battery::Battery(string const & n, double const c, Node* input, Node* output): Component(n, input, output), current{c} {}
Battery::~Battery() {}
void Battery::simulate(double const)
{
    p->current=current;
    n->current=0;
}
string Battery::get_name() const
{
    return name;
}
void Battery::print_info()
{
    cout << setprecision(2) << fixed << setw(6) << right << volt << "  " << right << curr << " ";
}
void Battery::update_info()
{
    volt=current;
    curr=0;
}

Resistor::Resistor(string const & n, double const r, Node* node1, Node* node2): Component(n,node1,node2), resistance{r} {}
Resistor::~Resistor() {}
void Resistor::simulate(double const step) 
{
    double potDif=abs(n->current-p->current);
    if (n->current>p->current)
    {
	double val=potDif/resistance;
	n->current-=step*val;
	p->current+=step*val;
    }
    else
    {
	double val=potDif/resistance;
	p->current-=step*val;
	n->current+=step*val;
    }
}
string Resistor::get_name() const
{
    return name;
}
void Resistor::print_info()
{
    cout << setprecision(2) << fixed << setw(6) << right << volt << "" << right << setw(6)<< curr << " ";
}
void Resistor::update_info()
{
    volt=abs(n->current-p->current);
    curr=volt/resistance;
}

Capacitor::Capacitor(string const & n, double const c, Node* node1, Node* node2): Component(n,node1,node2), capacitance{c}, charge{0} {}
Capacitor::~Capacitor() {}
    
void Capacitor::simulate(double const step) 
{
    double difference;
    if (n->current > p->current)
    {
	difference=n->current-p->current;
	double d=(capacitance*(difference-charge))*step;
	charge+=d;
	n->current-=d;
	p->current+=d;
    }
    else
    {
	difference=p->current - n->current;
	double d=(capacitance*(difference-charge))*step;
	charge+=d;
	p->current-=d;
	n->current+=d;
    }
}
string Capacitor::get_name() const
{
    return name;
}
void Capacitor::print_info()
{
    cout << setprecision(2) << fixed << setw(6) << right << volt << "  " << right << curr << " ";
}
void Capacitor::update_info()
{
    volt=abs(n->current-p->current);
    curr=capacitance*(volt-charge);
}

void write_top_row(vector <Component*>& v)
{
    for(unsigned int i=0; i<v.size(); i++)
    {
	cout << setw(12) << right<< v.at(i)->get_name() << " ";
    }
    cout << endl;
    for(unsigned int i=0; i<v.size(); i++)
    {
	cout << setw(12) << right<< "Volt  Curr" << " ";
    }
    cout << endl;
}

void write_net(vector <Component*>& v)
{ 
    for(unsigned int i=0; i<v.size(); i++)
    {
	 v.at(i)->print_info();
    }
    cout << endl;
}

void simulate_net(vector <Component*>& v, int iterations, int prints, double step)
{
    double threshold=iterations/prints;
    int n{0};

    write_top_row(v);

    for (int j=0; j<iterations; j++)
    {
	for(unsigned int i=0; i<v.size(); i++)
	{
	    v.at(i)->simulate(step);
	}

	++n;
	if (n>=threshold)
	{
	    for(unsigned int i=0; i<v.size(); i++)
	    {
		v.at(i)->update_info();
	    }
	    write_net(v);
	    n=0;
	}
    }
}

void clear_net(vector <Component*> & v)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
	delete v.at(i);
    }
    v.clear();
}
