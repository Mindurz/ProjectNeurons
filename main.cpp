#include "Neuron.h"
#include <iostream>
#include <fstream>
#include <climits>

int main()
{
	//double current_t_ (0) ;
	int t_start_ (0) ;
	int t_stop_ (0) ;
	//double t_final_ (0);
	int current_step_(0) ;
	double I (0.0) ;
	double Iext (0.0);
	double h (0.2); // the interval of time in each step
	int nb_steps_ (1000) ;
	
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
	std::cout << "When does the current start ? (number between 0 and "<< nb_steps_<<" ) " ;
	
	do
	{
		std::cin >> t_start_ ;
		std::cout << endl ;
		if((std::cin.fail()) or (t_start_ < 0) or (t_start_ > nb_steps_))
		{
			std::cout << "Error : enter a positive integral number between 0 and "<< nb_steps_ << std::endl ;
			std::cin.clear() ;
			std::cin.ignore(INT_MAX, '\n') ;
			t_start_ = 0 ;
		}
	}while((t_start_ <= 0) or (t_start_ > nb_steps_)) ;
	
	std::cout << "When does the current stops ? (number of steps between starting time and "<<nb_steps_<<" ) "<<std::endl;
	do
	{
		std::cin >> t_stop_ ;
		std::cout << endl ;
		if((std::cin.fail()) or (t_stop_ < t_start_) or (t_stop_ > nb_steps_))
		{
			std::cout << "Error : enter a positive integral number between 0 and "<<nb_steps_<<" " << std::endl ;
			std::cin.clear() ;
			std::cin.ignore(INT_MAX, '\n') ;
			t_stop_ = 0 ;
		}
	}while((t_stop_ <= 0) or (t_stop_ > nb_steps_)) ;
	
	vector <Neuron> Neurons_ ;
	Neuron mono ;
	Neurons_.push_back(mono) ;
	Neuron sono (3.0, 0 ) ;
	Neurons_.push_back(sono) ;
	
	std::ofstream Project_Neuron ;
	Project_Neuron.open("Potentials.txt") ;
	Project_Neuron << "Neuron 1" << '\t' << "Neuron 2" << std::endl ;
	
	unsigned int spikes_connected_ (0);
	
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
			if (i > 0)
			{
				if(Neurons_[i-1].HasSpiked(current_step_*h + h))
				{
					spikes_connected_ += 1 ;
				} ;
			} ;
			Neurons_[i].UpdateState(current_step_*h, h, I, spikes_connected_) ;
			Project_Neuron << Neurons_[i].GetPotential()<<'\t' << '\t' ;
		} ;
		Project_Neuron << std::endl ;
		current_step_ += 1 ;
		spikes_connected_ = 0 ;
	} ; 
	
	Project_Neuron.close() ;
	
	return 0 ;
}
