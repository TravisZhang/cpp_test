
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>

#define     pi     ((double)3.1415926)

struct DESIGN_SPECIFICATION
{
	double Cotoff;
	double Stopband;
	double Stopband_attenuation;
};

typedef struct
{
	double Real_part;
	double Imag_Part;
} COMPLEX;

int Ceil(double input)
{
	if (input != (int)input) return ((int)input) + 1;
	else return ((int)input);
}

int Complex_Multiple(COMPLEX a, COMPLEX b
	, double *Res_Real, double *Res_Imag)
{
	*(Res_Real) = (a.Real_part)*(b.Real_part) - (a.Imag_Part)*(b.Imag_Part);
	*(Res_Imag) = (a.Imag_Part)*(b.Real_part) + (a.Real_part)*(b.Imag_Part);

	return (int)1;
}

int Buttord(double Cotoff,
	double Stopband,
	double Stopband_attenuation)
{
	int N;

	printf("Wc =  %lf  [rad/sec] \n", Cotoff);
	printf("Ws =  %lf  [rad/sec] \n", Stopband);
	printf("As  =  %lf  [dB] \n", Stopband_attenuation);
	printf("--------------------------------------------------------\n");

	N = Ceil(0.5*(log10(pow(10, Stopband_attenuation / 10) - 1) /
		log10(Stopband / Cotoff)));

	return (int)N;

}

int Butter(int N, double Cotoff,
	double *a,
	double *b)
{
	double dk = 0;
	int k = 0;
	int count = 0, count_1 = 0;

	COMPLEX poles[N];
	COMPLEX Res[N + 1], Res_Save[N + 1];

	if ((N % 2) == 0) dk = 0.5;
	else dk = 0;

	for (k = 0; k <= ((2 * N) - 1); k++)
	{
		if (Cotoff*cos((k + dk)*(pi / N)) < 0)
		{
			poles[count].Real_part = -Cotoff*cos((k + dk)*(pi / N));
			poles[count].Imag_Part = -Cotoff*sin((k + dk)*(pi / N));
			count++;

			if (count == N) break;
		}
	}

	printf("Pk =   \n");

	for (count = 0; count < N; count++)
	{
		printf("(%lf) + (%lf i) \n", -poles[count].Real_part
			, -poles[count].Imag_Part);
	}

	printf("--------------------------------------------------------\n");


	Res[0].Real_part = poles[0].Real_part;
	Res[0].Imag_Part = poles[0].Imag_Part;

	Res[1].Real_part = 1;
	Res[1].Imag_Part = 0;

	for (count_1 = 0; count_1 < N - 1; count_1++)
	{
		for (count = 0; count <= count_1 + 2; count++)
		{
			if (0 == count)
			{
				Complex_Multiple(Res[count], poles[count_1 + 1],
					&(Res_Save[count].Real_part),
					&(Res_Save[count].Imag_Part));

				//printf( "Res_Save : (%lf) + (%lf i) \n" ,Res_Save[0].Real_part,Res_Save[0].Imag_Part);
			}

			else if ((count_1 + 2) == count)
			{
				Res_Save[count].Real_part += Res[count - 1].Real_part;
				Res_Save[count].Imag_Part += Res[count - 1].Imag_Part;
			}
			else
			{
				Complex_Multiple(Res[count], poles[count_1 + 1],
					&(Res_Save[count].Real_part),
					&(Res_Save[count].Imag_Part));

				//printf( "Res          : (%lf) + (%lf i) \n" ,Res[count - 1].Real_part,Res[count - 1].Imag_Part);

				//printf( "Res_Save : (%lf) + (%lf i) \n" ,Res_Save[count].Real_part,Res_Save[count].Imag_Part);

				Res_Save[count].Real_part += Res[count - 1].Real_part;
				Res_Save[count].Imag_Part += Res[count - 1].Imag_Part;

				//printf( "Res_Save : (%lf) + (%lf i) \n" ,Res_Save[count].Real_part,Res_Save[count].Imag_Part);

			}
			//printf("There \n" );
		}

		for (count = 0; count <= N; count++)
		{
			Res[count].Real_part = Res_Save[count].Real_part;
			Res[count].Imag_Part = Res_Save[count].Imag_Part;

			*(a + N - count) = Res[count].Real_part;
		}

		//printf("There!! \n" );
	}

	*(b + N) = *(a + N);

	//------------------------display---------------------------------//
	printf("bs =  [");

	for (count = 0; count <= N; count++)
	{
		printf("%lf ", *(b + count));
	}

	printf(" ] \n");

	printf("as =  [");

	for (count = 0; count <= N; count++)
	{
		printf("%lf ", *(a + count));
	}

	printf(" ] \n");

	printf("--------------------------------------------------------\n");

	return (int)1;

}


int Bilinear(int N,
	double *as, double *bs,
	double *az, double *bz)
{
	int Count = 0, Count_1 = 0, Count_2 = 0, Count_Z = 0;
	double Res[N + 1];
	double Res_Save[N + 1];

	for (Count_Z = 0; Count_Z <= N; Count_Z++)
	{
		*(az + Count_Z) = 0;
		*(bz + Count_Z) = 0;
	}

	for (Count = 0; Count <= N; Count++)
	{
		for (Count_Z = 0; Count_Z <= N; Count_Z++)
		{
			Res[Count_Z] = 0;
			Res_Save[Count_Z] = 0;
		}

		Res_Save[0] = 1;

		for (Count_1 = 0; Count_1 < N - Count; Count_1++)
		{
			for (Count_2 = 0; Count_2 <= Count_1 + 1; Count_2++)
			{
				if (Count_2 == 0)
				{
					Res[Count_2] += Res_Save[Count_2];

					//printf( "Res[%d] %lf  \n" , Count_2 ,Res[Count_2]);
				}
				else if ((Count_2 == (Count_1 + 1)) && (Count_1 != 0))
				{
					Res[Count_2] += -Res_Save[Count_2 - 1];

					//printf( "Res[%d] %lf  \n" , Count_2 ,Res[Count_2]);
				}
				else
				{
					Res[Count_2] += Res_Save[Count_2] - Res_Save[Count_2 - 1];

					//printf( "Res[%d] %lf  \n" , Count_2 ,Res[Count_2]);
				}
			}

			//printf( "Res : ");

			for (Count_Z = 0; Count_Z <= N; Count_Z++)
			{
				Res_Save[Count_Z] = Res[Count_Z];
				Res[Count_Z] = 0;

				//printf( "[%d]  %lf  " ,Count_Z, Res_Save[Count_Z]);     
			}

			//printf(" \n" );
		}

		for (Count_1 = (N - Count); Count_1 < N; Count_1++)
		{
			for (Count_2 = 0; Count_2 <= Count_1 + 1; Count_2++)
			{
				if (Count_2 == 0)
				{
					Res[Count_2] += Res_Save[Count_2];

					//printf( "Res[%d] %lf  \n" , Count_2 ,Res[Count_2]);
				}
				else if ((Count_2 == (Count_1 + 1)) && (Count_1 != 0))
				{
					Res[Count_2] += Res_Save[Count_2 - 1];

					//printf( "Res[%d] %lf  \n" , Count_2 ,Res[Count_2]);
				}
				else
				{
					Res[Count_2] += Res_Save[Count_2] + Res_Save[Count_2 - 1];

					//printf( "Res[%d] %lf  \n" , Count_2 ,Res[Count_2]);
				}
			}

			//	printf( "Res : ");

			for (Count_Z = 0; Count_Z <= N; Count_Z++)
			{
				Res_Save[Count_Z] = Res[Count_Z];
				Res[Count_Z] = 0;

				//printf( "[%d]  %lf  " ,Count_Z, Res_Save[Count_Z]);     
			}

			//printf(" \n" );
		}

		//printf( "Res : ");

		for (Count_Z = 0; Count_Z <= N; Count_Z++)
		{
			*(az + Count_Z) += pow(2, N - Count)  *  (*(as + Count)) * Res_Save[Count_Z];
			*(bz + Count_Z) += (*(bs + Count)) * Res_Save[Count_Z];

			//printf( "  %lf  " ,*(bz+Count_Z));         
		}

		//printf(" \n" );
	}

	for (Count_Z = N; Count_Z >= 0; Count_Z--)
	{
		*(bz + Count_Z) = (*(bz + Count_Z)) / (*(az + 0));
		*(az + Count_Z) = (*(az + Count_Z)) / (*(az + 0));
	}

	//------------------------display---------------------------------//

	printf("bz =  [");

	for (Count_Z = 0; Count_Z <= N; Count_Z++)
	{
		printf("%lf ", *(bz + Count_Z));
	}

	printf(" ] \n");

	printf("az =  [");

	for (Count_Z = 0; Count_Z <= N; Count_Z++)
	{
		printf("%lf ", *(az + Count_Z));
	}

	printf(" ] \n");

	printf("--------------------------------------------------------\n");

	return (int)1;

}


int main(void)
{
	int count;

	struct DESIGN_SPECIFICATION IIR_Filter;

	IIR_Filter.Cotoff = (double)(pi / 2);         //[red]

	IIR_Filter.Stopband = (double)((pi * 3) / 4);   //[red]

	IIR_Filter.Stopband_attenuation = 30;        //[dB]

	int N;

	IIR_Filter.Cotoff = 2 * tan((IIR_Filter.Cotoff) / 2);            //[red/sec]

	IIR_Filter.Stopband = 2 * tan((IIR_Filter.Stopband) / 2);   //[red/sec]

	N = Buttord(IIR_Filter.Cotoff,
		IIR_Filter.Stopband,
		IIR_Filter.Stopband_attenuation);

	printf("N:  %d  \n", N);

	printf("--------------------------------------------------------\n");

	double as[N + 1], bs[N + 1];

	Butter(N,
		IIR_Filter.Cotoff,
		as,
		bs);

	double az[N + 1], bz[N + 1];

	Bilinear(N,
		as, bs,
		az, bz);

	printf("Finish \n");

	return (int)0;
}
