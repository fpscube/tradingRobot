//============================================================================
// Name        : tradingRobot.cpp
// Author      : S.KOEHLER
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Genetical.h"
#include "Network.h"
using namespace std;

extern int gPriceTabSize ;
extern double gPriceTab[];

void sinus() {

	double bestScore=10000;
	Network network(
			/*nbInput*/1,
			/*nbOutput*/1,
			/*nbNeuronByLayer*/40);
	Genetical genetical(
			/*pNbGenomByGeneration*/500,
			/*pNbGenByGenom*/network.getConfigSize(),
			/*pNbBestGenom*/10,
			/*pGenomMixRatio*/0.5,
			/*pGenomMutationRatio*/0.001);

	for (int i=0;i<500;i++)
	{
		genetical.newGeneration();
		do{
			double score=0;
			double *genom = genetical.getGenom();

			double step = 2*M_PI/100;
			double x;
			for (x=-M_PI;x<M_PI;x+=step)
			{
				double resultT=sin(x);
				double normalizedX = x/M_PI;
				double resultN = 0;
				network.run(&normalizedX,&resultN,genom);
				score += fabs(resultT-resultN);
			}
			if(bestScore>score)
			{

				bestScore =score;
				printf ("Generation %d Score %f \n",i,score);
			}

			genetical.saveGenomScore(score);


		}while(genetical.selectNextGenom());
	}




}

void trading()
{
	double bestScore=10000;
	double input[7];
	double pip=0.00001;
	Network network(
			/*nbInput*/7,
			/*nbOutput*/1,
			/*nbNeuronByLayer*/40);
	Genetical genetical(
			/*pNbGenomByGeneration*/500,
			/*pNbGenByGenom*/network.getConfigSize(),
			/*pNbBestGenom*/10,
			/*pGenomMixRatio*/0.5,
			/*pGenomMutationRatio*/0.001);

	for (int i=0;i<2;i++)
	{
		genetical.newGeneration();
		do{
			double score=0;
			double *genom = genetical.getGenom();
			bool buy = false;
			bool sell = false;
			double output=0;
			double openPrice=0;
			double gain=0;
			//for all price in record
			for (int x=0;x<gPriceTabSize;x++)
			{
				double price = gPriceTab[x];
				input[0] = price;
				input[1] = price;// M 5
				input[2] = price;// M 10
				input[3] = price;// M 20
				input[4] = price;// M 50
				input[5] = output;
				input[6] = gain;// (5% = 1, -5% = -1)

				network.run(input,&output,genom);

				if ((output < 0.4)  &&  buy)
				{
					buy=false;
					gain+=price-(openPrice+pip);
				}
				if ((output > -0.4) &&  sell)
				{
					sell=false;
					gain+=(openPrice-pip) - price;
				}
				if ((output > 0.5)  && !buy)
				{
					buy=true;
					openPrice=price;
				}
				if ((output < -0.5) && !sell)
				{
					sell=true;
					openPrice=price;
				}
			}
			score = -gain;


			if(bestScore>score)
			{
				bestScore =score;
				printf ("Generation %d Score %f \n",i,gain);
			}

			genetical.saveGenomScore(score);


		}while(genetical.selectNextGenom());
	}


}

int main()
{

	trading();
	return 0;
}

