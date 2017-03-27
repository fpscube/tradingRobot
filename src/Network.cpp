/*
 * Network.cpp
 *
 *  Created on: 16 mars 2017
 *      Author: PC-STEPHANE
 */

#include "Network.h"
#include <stdlib.h>

Network::Network(int pNbInput,int pNbOutput,int pNbNeuronByLayer) {

	this->NbInput=pNbInput;
	this->NbOutput=pNbOutput;
	this->NbNeuronByLayer=pNbNeuronByLayer;
	this->firstLayerOutput = (double*)malloc(sizeof(double)*pNbNeuronByLayer);
	this->secondLayerOutput = (double*)malloc(sizeof(double)*pNbNeuronByLayer);
}

int Network::getConfigSize() {
 return (this->NbInput * this->NbNeuronByLayer + this->NbNeuronByLayer * this->NbNeuronByLayer + this->NbNeuronByLayer *  this->NbOutput);
}


void Network::run(double *pInput,double *pOutput,double *pConfigTab) {

	int configIndex=0;

	/* first Layer */
	for (int i=0;i<this->NbNeuronByLayer;i++)
	{
		this->firstLayerOutput[i]=0;
		for (int y=0;y<this->NbInput;y++)
		{
			this->firstLayerOutput[i]+=pConfigTab[configIndex++]*pInput[y];
		}
	}

	/* saturation of first layer output */
	for (int i=0;i<this->NbNeuronByLayer;i++)
	{
		if (firstLayerOutput[i] > 1)  firstLayerOutput[i] = 1;
		else if (firstLayerOutput[i] < -1)  firstLayerOutput[i] = -1;
	}

	/* second Layer */
	for (int i=0;i<this->NbNeuronByLayer;i++)
	{
		secondLayerOutput[i] = 0;
		for (int y=0;y<this->NbNeuronByLayer;y++)
		{
			secondLayerOutput[i]+=pConfigTab[configIndex++]*firstLayerOutput[y];
		}
	}

	/* saturation of second layer output */
	for (int i=0;i<this->NbNeuronByLayer;i++)
	{
		if (secondLayerOutput[i] > 1)  secondLayerOutput[i] = 1;
		else if (secondLayerOutput[i] < -1)  secondLayerOutput[i] = -1;
	}

	/* output values */
	for (int i=0;i<this->NbOutput;i++)
	{
		pOutput[i]=0;
		for (int y=0;y<this->NbNeuronByLayer;y++)
		{
			pOutput[i]+=pConfigTab[configIndex++]*secondLayerOutput[y];
		}
	}

}


