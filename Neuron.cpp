#include "Neuron.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std ;

Neuron::Neuron()
:potential_(0.0), nb_spikes_(0), spikes_time_() 
{}

Neuron::Neuron (double pot_, unsigned int nb_/*, vector<double> sp_times_*/)
:potential_(pot_), nb_spikes_(nb_)/*, spikes_time_(sp_times_) */
{}

/*
Neuron::Neuron(Neuron n)
:potential_(n.GerPotential()), nb_spikes_(n.GetNbspikes()), spikes_time_(n.GetSpikestime()) 
{}
*/

Neuron::~Neuron()
{}

double Neuron::GetPotential() 
{
	return potential_ ;
}

unsigned int  Neuron::GetNbspikes() 
{
	return nb_spikes_ ;
}

vector<double> Neuron::GetSpikestime() 
{
	return spikes_time_ ;
}

bool Neuron::IsRefractory(double t)
{
	if (spikes_time_.empty())
	{
		return false ;
	}
	if(t - spikes_time_.back() < refractorytime_)
	{
		return true ;
	}
	return false ;
}

bool Neuron::HasSpiked(double t)
{
	
}

void Neuron::UpdateState(double t_, double dt_, double I) 
{
	if (IsRefractory(t_)) //neuron refractory-> pot = 0 sinon on applique la formule
	{
		potential_ = 0 ;
	}else{ 
		potential_ = exp(-dt_/tau_) * potential_ + I * (tau_ / c_) * (1 - exp(-dt_/tau_)); 
		if (potential_ >= threshold_)
		{
			spikes_time_.push_back(t_ + dt_) ;
			nb_spikes_ += 1 ;
		}
	}
	neuron_step_ += 1 ;
}
