#include <vector>

/*
 * le comportement du neurone doit etre :
 * 		0 lorsqu'il est refractaire
 * 		spike quand le courant est a 1 (1000 pour moi... 
 * 		probablement une erreur dans les const)
 * 		TO DO
 * 		fct PotReset -> reinitialise le pot a sa valeur initiale... why tho ?
 * 		refaire le update state CHECK
 * 		inclure le temps dans les neurons CHECK
 * 		
 */

using namespace std ;

#ifndef NEURON_H
#define NEURON_H

class Neuron 
{
	private :
	
	double potential_ ;
	unsigned int nb_spikes_ ;
	vector < double > spikes_time_ ;
	double neuron_step_ = 0.0 ;
	
	//constants FIND A BETTER WAY !!
	static const double tau_ = 20 ;
	static const double threshold_ = 20;
	static const double c_ = 1 ;
	static const double refractorytime_ = 2;
	
	public :
	
	Neuron () ;
	Neuron (double pot_, unsigned int nb_/*, vector < double > sp_times_*/) ;
	~Neuron () ;
	
	double GetPotential() ;
	unsigned int  GetNbspikes() ;
	vector< double > GetSpikestime() ;
	bool IsRefractory(double t) ;
	bool HasSpiked(double t) ;
	
	void UpdateState(double t_, double dt_, double I) ;
};

#endif
