#include <cmath> 
#include <stdexcept>
#include <iostream>
#include <vector>
#include "krets.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Felhantering av kommandoargument----------------------------------------
    if (argc != 5)
    {
	cout << "Error: Wrong number of arguments. Expected 4, recieved " << argc-1 << endl;
	return 0;
    }

    int sims, rows;
    double step, voltage;

    //Parameter 1-------------------------------------------------------------
    try 
    {
	sims=stoi(argv[1]);
    }
    catch (std::invalid_argument)
    {
	cout << "Error: Enter an integer in parameter 1" << endl;
	return 0;
    }
    if (sims<0)
    {
	cout << "Error: Expected integer larger than 0 in parameter 1" << endl;
	return 0;
    }

    //Parameter 2-------------------------------------------------------------
    try 
    {
	rows=stoi(argv[2]);
    }
    catch (std::invalid_argument)
    {
	cout << "Error: Enter an integer in parameter 2" << endl;
	return 0;
    }
    if (rows<0)
    {
	cout << "Error: Expected integer larger than 0 in parameter 2" << endl;
	return 0;
    }

    //Parameter 3-------------------------------------------------------------
    try
    {
	step=stod(argv[3]);
    }
    catch (std::invalid_argument)
    {
	cout << "Error: Enter a double in parameter 3" << endl;
	return 0;
    }
    if (step<0.0)
    {
	cout << "Error: Expected double larger than 0 in parameter 3" << endl;
	return 0;
    }

    //Parameter 4-------------------------------------------------------------
    try
    {
	voltage=stod(argv[4]);
    }
    catch (std::invalid_argument)
    {
	cout << "Error: Enter a double in parameter 4" << endl;
	return 0;
    }
    if (voltage<0.0)
    {
	cout << "Error: Expected double larger than 0 in parameter 4" << endl;
	return 0;
    }

    //Krets definitioner-------------------------------------------------------
    vector <Component*> net;
    Node n1, n2, n3, n4;

    //Krets 1----------------------------------------------
        
    net.push_back(new Battery{"Bat",voltage, & n4, & n1});
    net.push_back(new Resistor{"R1",6, & n1, & n2});
    net.push_back(new Resistor{"R2",4, & n2, & n3});
    net.push_back(new Resistor{"R3",8, & n3, & n4});
    net.push_back(new Resistor{"R4",12, &n2, & n4});
    cout << endl <<"Krets 1:" << endl;

    simulate_net(net,sims,rows,step);
    clear_net(net);

    //Krets 2-----------------------------------------------
    
    n1.current=0;
    n2.current=0;
    n3.current=0;
    n4.current=0;

    net.push_back(new Battery{"Bat",voltage, & n4, & n1});
    net.push_back(new Resistor{"R1",150, & n1, & n2});
    net.push_back(new Resistor{"R2",50, & n1, & n3});
    net.push_back(new Resistor{"R3",100, & n2, & n3});
    net.push_back(new Resistor{"R4",300, & n2, & n4});
    net.push_back(new Resistor{"R5",250, & n3, & n4});
    cout << endl << "Krets 2:" << endl;
    
    simulate_net(net,sims,rows,step);
    clear_net(net);

    //Krets 3-----------------------------------------------

    n1.current=0;
    n2.current=0;
    n3.current=0;
    n4.current=0;

    net.push_back(new Battery{"Bat",voltage, & n4, & n1});
    net.push_back(new Resistor{"R1",150, & n1, & n2});
    net.push_back(new Resistor{"R2",50, & n1, & n3});
    net.push_back(new Capacitor{"C3",1.0, & n2, & n3});
    net.push_back(new Resistor{"R4",300, & n2, & n4});
    net.push_back(new Capacitor{"C5",0.75, & n3, & n4});
    cout << endl << "Krets 3:" << endl;

    simulate_net(net,sims,rows,step);
    clear_net(net);

    return 0;
}
