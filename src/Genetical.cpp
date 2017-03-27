/*
 * Genetical.cpp
 *
 *  Created on: 17 mars 2017
 *      Author: PC-STEPHANE
 */

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Genetical.h"

Genetical::Genetical(int pNbGenomByGeneration,int pNbGenByGenom,int pNbBestGenom,double pGenomMixRatio,double pGenomMutationRatio) {

	/* initialize random seed: */
	time_t t;
	srand ((unsigned) time(&t));


	/* Initialize parameters */
	this->NbGenomeByGeneration	= pNbGenomByGeneration;
	this->NbGenByGenom			= pNbGenByGenom;
	this->NbBestGenom			= pNbBestGenom;
	this->GenomMixRatio			= pGenomMixRatio;
	this->GenomMutationRatio 	= pGenomMutationRatio;

	/* Initialize counter */
	this->GenerationCounter = 0;

	/* Initialize Best Genom Tab */
	this->BestGenomIndexTab = (int *)malloc(sizeof(int)*pNbBestGenom);
	this->BestGenomScoreTab = (double *)malloc(sizeof(double)*pNbBestGenom);
	this->BestGenomTabPos = 0;

	/* Initialize Genom Tab */
	this->GenomTab[0] = (double **)malloc(sizeof(double)*pNbGenomByGeneration);
	for (int i=0;i<this->NbGenomeByGeneration;i++)
	{
		this->GenomTab[0][i] = (double *)malloc(sizeof(double)*pNbGenByGenom);
	}
	this->GenomTab[1] = (double **)malloc(sizeof(double)*pNbGenomByGeneration);
	for (int i=0;i<this->NbGenomeByGeneration;i++)
	{
		this->GenomTab[1][i] = (double *)malloc(sizeof(double)*pNbGenByGenom);
	}
	this->GenomTabPos = 0;
}


/* Create a new generation if it is the first call or create a new generation
 * from best genom of previous generation
 */
void Genetical::newGeneration()
{


	/* set current and previous buffer using  GenerationCounter modulo 2 */
	double ** currentGenomTab = this->GenomTab[this->GenerationCounter % 2];
	double ** previousGenomTab = this->GenomTab[(this->GenerationCounter + 1) % 2];

	/* First generation genom are generate with random fonction*/
	if (this->GenerationCounter == 0)
	{
		for (int i=0;i<this->NbGenomeByGeneration;i++)
		{
			for (int y=0;y<this->NbGenByGenom;y++)
			{
				currentGenomTab[i][y]=rand()/(double)RAND_MAX *2.0-1.0;
			}

		}
	}
	/* Mix best genom to create the new generation*/
	else
	{
		int indexGenom=0;
		while (indexGenom < this->NbGenomeByGeneration)
		{
			for (int iB1=0;iB1<this->NbBestGenom;iB1++){
			for (int iB2=0;iB2<this->NbBestGenom;iB2++){
				if (indexGenom >= this->NbGenomeByGeneration) continue;
				for (int i=0 ;i<this->NbGenByGenom;i++)
				{
					if(rand() < (RAND_MAX * this->GenomMutationRatio))
					{

						currentGenomTab[indexGenom][i] = rand()/(double)RAND_MAX *2.0-1.0;
					}
					else if(rand() > (RAND_MAX * this->GenomMixRatio))
					{
						int iB = this->BestGenomIndexTab[iB1];
						currentGenomTab[indexGenom][i] = previousGenomTab[iB][i];
					}
					else
					{
						int iB = this->BestGenomIndexTab[iB2];
						currentGenomTab[indexGenom][i] = previousGenomTab[iB][i];
					}

				}
				indexGenom++;
			}}
		}
	}

	this->BestGenomTabPos = 0;
	this->GenomTabPos = 0;
	this->GenerationCounter++;


}

/* Select next genom in current generation
 * return false if there are no more genom in current generation
 */
bool Genetical::selectNextGenom()
{
	this->GenomTabPos++;
	if (this->GenomTabPos < this->NbGenomeByGeneration)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

/* Return current genom in current generation */
double * Genetical::getGenom()
{
	double ** currentGenomTab = this->GenomTab[(this->GenerationCounter+1) % 2];

	return (currentGenomTab[this->GenomTabPos]);
}


/* Save score for current genom
 * in current generation
 */
void Genetical::saveGenomScore(double score)
{
	/* If best Table is not full save score and genom index */
	if ((this->BestGenomTabPos) < this->NbBestGenom)
	{
		this->BestGenomScoreTab[this->BestGenomTabPos] = score;
		this->BestGenomIndexTab[this->BestGenomTabPos] = this->GenomTabPos;
		this->BestGenomTabPos++;
	}
	else
	{
		double highScore = this->BestGenomScoreTab[0] ;
		int indexHighScore = 0;
		/* Search high score in best score tab */
		for (int i=1;i<this->NbBestGenom;i++)
		{
			if (this->BestGenomScoreTab[i] > highScore)
			{
				highScore =  this->BestGenomScoreTab[i];
				indexHighScore=i;
			}
		}

		/* replace the highest score by the current score if the current score is lowest*/
		if (highScore > score)
		{
			this->BestGenomScoreTab[indexHighScore] = score;
			this->BestGenomIndexTab[indexHighScore] = this->GenomTabPos;
		}
	}
}
