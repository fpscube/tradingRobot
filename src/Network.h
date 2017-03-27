/*
 * Network.h
 *
 *  Created on: 16 mars 2017
 *      Author: PC-STEPHANE
 */

#ifndef NETWORK_H_
#define NETWORK_H_

class Network {
public:
	Network(int pNbInput,int pNbOutput,int pNbNeuronByLayer);

	/* return config size */
	int getConfigSize();
	/* run network */
	void run(double *pInput,double *pOutput,double *pConfigTab);


	int NbInput;
	int NbOutput;
	int NbNeuronByLayer;
	double * firstLayerOutput;
	double * secondLayerOutput;

};

#endif /* NETWORK_H_ */
