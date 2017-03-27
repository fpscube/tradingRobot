/*
 * Genetical.h
 *
 *  Created on: 17 mars 2017
 *      Author: PC-STEPHANE
 */

#ifndef GENETICAL_H_
#define GENETICAL_H_

class Genetical {
public:
	Genetical(int pNbGenomByGeneration,int pNbGenByGenom,int pNbBestGenom,double pGenomMixRatio,double pGenomMutationRatio);

	/* Create a new generation if it is the first call or create a new generation
	 * from best genom of previous generation
	 */
	void newGeneration();


	/* Select next genom in current generation
	 * return false if there are no more genom in current generation
	 */
	bool selectNextGenom();

	/* Return current genom in current generation */
	double * getGenom();

	/* Save score for current genom
	 * in current generation
	 */
	void saveGenomScore(double score);


	/* Internal*/
	int GenerationCounter;
	double **GenomTab[2];
	int GenomTabPos;
	int *BestGenomIndexTab;
	double *BestGenomScoreTab;
	int BestGenomTabPos;

	/* Config Parameters */
	int NbGenomeByGeneration;
	int NbGenByGenom;
	int NbBestGenom;
	double GenomMixRatio;
	double GenomMutationRatio;

};

#endif /* GENETICAL_H_ */
