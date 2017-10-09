#include "Neuron.h"
#include <iostream>
#include <fstream>
#include <climits>

int main()
{
	//double current_t_ (0) ;
	double t_start_ (0) ;
	double t_stop_ (0) ;
	//double t_final_ (0);
	double current_step_(0) ;
	double I (0.0) ;
	double Iext (0.0);
	double h (0.2); // the interval of time in each step
	double nb_steps_ (1000) ;
	
	std::cout << "Enter a value for the current " ;
	//control
	while(Iext <= 0.0)
	{
		std::cin >> Iext ;
		if (std::cin.fail())
		{
			std::cout << "ERROR : enter a positive value" << std::endl ;
			std::cin.clear() ;
			std::cin.ignore(INT_MAX, '\n') ;
		}
	} ;
	
	std::cout << "Enter a time interval "<<std::endl ;
	//control
	std::cout << "When does the current start ? (number between 0 and 500) "<<std::endl;
	int CONTROLVALUE ;
	do
	{
		std::cin >> CONTROLVALUE ;
		std::cout << endl ;
		if((std::cin.fail()) or (CONTROLVALUE < 0))
		{
			std::cout << "Error : enter a positive integral number" << std::endl ;
			std::cin.clear() ;
			std::cin.ignore(INT_MAX, '\n') ;
		}else{
			t_start_ = CONTROLVALUE ;
			CONTROLVALUE = 1 ; 
		}
	}while(CONTROLVALUE <= 0) ;
	
	std::cout << "When does the current stops ? (number of steps between starting time and 500) "<<std::endl;
	do
	{
		std::cin >> CONTROLVALUE ;
		std::cout << endl ;
		if(std::cin.fail())
		{
			std::cout << "Error : enter a positive integral number" << std::endl ;
			std::cin.clear() ;
			std::cin.ignore(INT_MAX, '\n') ;
		}else if(CONTROLVALUE > t_start_)
		{
			t_stop_ = CONTROLVALUE ;
			CONTROLVALUE = 1 ; 
			}else{
				std::cout<<"Your number is invalid"<<std::endl ;
				std::cin.clear() ;
				std::cin.ignore(INT_MAX, '\n') ;
			}
	}while(CONTROLVALUE <= 0) ;
	
	vector <Neuron> Neurons_ ;
	Neuron mono ;
	Neurons_.push_back(mono) ;
	Neuron sono (10.0, 0 ) ;
	Neurons_.push_back(sono) ;
	
	std::ofstream Project_Neuron ;
	Project_Neuron.open("Potentials.txt") ;
	Project_Neuron << "Neuron 1" << '\t' << "Neuron 2" << std::endl ;
	
	while ( current_step_<= nb_steps_)
	{	
		if((current_step_ < t_start_) or (current_step_ > t_stop_))
		{
			I = 0.0 ;
		}else{
			I = Iext ;
		}
		
		for (size_t i = 0; i < Neurons_.size() ; i++)
		{
			Neurons_[i].UpdateState(current_step_*h, h, I) ;
			Project_Neuron << Neurons_[i].GetPotential()<<'\t' << '\t' ;
		} ;
		Project_Neuron << std::endl ;
		current_step_ += 1 ;
	} ; 
	
	Project_Neuron.close() ;
	
	return 0 ;
}
