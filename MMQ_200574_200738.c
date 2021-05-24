// ------------------------- Cabeçalho --------------------------- //
/*Projeto Método dos Multiplos Quadrados - Métodos Númericos

Integrantes:
Felipe Eler de Oliveira Machado 200738
Felipe Victorino Sarubo 200574

Turma: CP004TIM2*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ------------------------- Estruturas --------------------------- //

typedef struct Vet
{
	float x;
  float y;
} Vet;

typedef struct MMQ
{
	float y;
  float u0;
  float u1;
  float u2;
} MMQ;

typedef struct Equ
{
  float du0; //dependente de u0
  float du1;
  float du2;
  float dy;
} Equ;

// ------------------------- Protótipos de Funções ---------------- //

void alocaVet(Vet **p, int tam);
void alocaMMQ(MMQ **p, int tam);
void alocaEqu(Equ **p);

// ------------------------- Main --------------------------------- //

int main()
{
  MMQ *pMMQ = NULL;
  Vet *pVet = NULL;
  Equ *pEqu = NULL;
  int i = 0, k = 0, tfunc = 0, kmax, n;
  float pivot, M21, M31, M32, a0, a1, a2;
  char dnv = 's';
  
  do{
  // ----- Passo 1. Construir os vetores ----- //
  printf("\n// ----- Passo 1. Construir os vetores ----- //");
  //Receber os pontos:
    //Receber o numero de pontos (n)
    printf("\nDigite a quantidade de pontos na tabela: ");
    scanf("%i",&n);
    fflush(stdin);

    alocaMMQ(&pMMQ, n);
    alocaVet(&pVet, n);
    alocaEqu(&pEqu);
    //Loop (For i=n):
    for (i = 0; i < n; i++)
    {
      //Receber os pontos no formato [x y]
      printf("Digite o %io ponto no formato [x y]: ", i+1);
      scanf("%f %f",&((pVet+i)->x), &((pVet+i)->y));
      fflush(stdin);
    }
  //Receber o tipo de função:
    //Receber tfunc 0 (Reta), 1 (Parábola)
    do
    {
      printf("Escolha o tipo de funcao [0 (Reta), 1 (Parabola)]: ");
      scanf("%i",&tfunc);
      fflush(stdin);
    } while (tfunc > 1 || tfunc < 0);

  //Exibindo tabela
  printf("\nx\ty");
  for (i = 0; i < n; i++)
  {
    printf("\n%.3f\t %.3f", (pVet+i)->x, (pVet+i)->y);
  }



  // ----- Passo 2. Montar o sistema escalar ----- //
  printf("\n\n// ----- Passo 2. Montar o sistema escalar ----- //");
    //Loop (for i=n)
    for (i = 0; i < n; i++)
    {
      //MMQ[i] = [yi  xi^0  xi^1  xi^2]
      (pMMQ+i)->y  = (pVet+i)->y;
      (pMMQ+i)->u0 = pow((pVet+i)->x, 0);
      (pMMQ+i)->u1 = pow((pVet+i)->x, 1);
      (pMMQ+i)->u2 = pow((pVet+i)->x, 2);
    }

  //Exibindo tabela
  if (tfunc == 0)
  {
    printf("\ny\tu0\tu1");
    for (i = 0; i < n; i++)
    {
      printf("\n%.3f\t %.3f\t %.3f", (pMMQ+i)->y, (pMMQ+i)->u0, (pMMQ+i)->u1);
    }
  }else{
    printf("\ny\tu0\tu1\tu2");
    for (i = 0; i < n; i++)
    {
      printf("\n%.3f\t %.3f\t %.3f\t %.3f", (pMMQ+i)->y, (pMMQ+i)->u0, (pMMQ+i)->u1, (pMMQ+i)->u2);
    }
  }



  // ----- Passo 3. Reescrever o sistema de equações ----- //
  printf("\n\n// ----- Passo 3. Reescrever o sistema de equacoes ----- //");
    //Se (tfunc == 0)
      //kmax = 2
    //Se (tfunc == 1)
      //kmax = 3
    kmax = (tfunc == 0) ? 2 : 3;

    /*
    Iniciar a struct Equ com zeros
      Loop (for k=kmax)
        Equ[k].du0 = 0
        Equ[k].du1 = 0
        Equ[k].du2 = 0
        Equ[k].dy  = 0
    */
    for (k = 0; k < kmax; k++)
    {
      (pEqu+k)->du0 = 0;
      (pEqu+k)->du1 = 0;
      (pEqu+k)->du2 = 0;
      (pEqu+k)->dy  = 0;
    }

    //Loop (for i=n)
      /*
      Se (tfunc == 0)
        Equ[0].du0 += MMQ[i].u0 * MMQ[i].u0
        Equ[0].du1 += MMQ[i].u0 * MMQ[i].u1
        Equ[0].dy  += MMQ[i].u0 * MMQ[i].y

        Equ[1].du0 += MMQ[i].u1 * MMQ[i].u0
        Equ[1].du1 += MMQ[i].u1 * MMQ[i].u1
        Equ[1].dy  += MMQ[i].u1 * MMQ[i].y
        
      Se (tfunc == 1)
        Equ[0].du0 += MMQ[i].u0 * MMQ[i].u0
        Equ[0].du1 += MMQ[i].u0 * MMQ[i].u1
        Equ[0].du2 += MMQ[i].u0 * MMQ[i].u2
        Equ[0].dy  += MMQ[i].u0 * MMQ[i].y

        Equ[1].du0 += MMQ[i].u1 * MMQ[i].u0
        Equ[1].du1 += MMQ[i].u1 * MMQ[i].u1
        Equ[1].du2 += MMQ[i].u1 * MMQ[i].u2
        Equ[1].dy  += MMQ[i].u1 * MMQ[i].y

        Equ[2].du0 += MMQ[i].u2 * MMQ[i].u0
        Equ[2].du1 += MMQ[i].u2 * MMQ[i].u1
        Equ[2].du2 += MMQ[i].u2 * MMQ[i].u2
        Equ[2].dy  += MMQ[i].u2 * MMQ[i].y
      */
    for (i = 0; i < n; i++)
    {
      (pEqu+0)->du0 += (pMMQ+i)->u0 * (pMMQ+i)->u0;
      (pEqu+0)->du1 += (pMMQ+i)->u0 * (pMMQ+i)->u1;
      (pEqu+0)->dy  += (pMMQ+i)->u0 * (pMMQ+i)->y;

      (pEqu+1)->du0 += (pMMQ+i)->u1 * (pMMQ+i)->u0;
      (pEqu+1)->du1 += (pMMQ+i)->u1 * (pMMQ+i)->u1;
      (pEqu+1)->dy  += (pMMQ+i)->u1 * (pMMQ+i)->y;

      if (tfunc == 1)
      {
        (pEqu+0)->du2 += (pMMQ+i)->u0 * (pMMQ+i)->u2;
        (pEqu+1)->du2 += (pMMQ+i)->u1 * (pMMQ+i)->u2;

        (pEqu+2)->du0 += (pMMQ+i)->u2 * (pMMQ+i)->u0;
        (pEqu+2)->du1 += (pMMQ+i)->u2 * (pMMQ+i)->u1;
        (pEqu+2)->du2 += (pMMQ+i)->u2 * (pMMQ+i)->u2;
        (pEqu+2)->dy  += (pMMQ+i)->u2 * (pMMQ+i)->y;
      }
    }
    if(tfunc == 0){
      printf("\ndu0\tdu1\tdy");
      for (i = 0; i < 2; i++)
      {
        printf("\n%.3f\t %.3f\t %.3f", (pEqu+i)->du0, (pEqu+i)->du1, (pEqu+i)->dy);
      }
    }else{
      printf("\ndu0\tdu1\tdu2\tdy");
      for (i = 0; i < 3; i++)
      {
        printf("\n%.3f\t %.3f\t %.3f\t %.3f", (pEqu+i)->du0, (pEqu+i)->du1, (pEqu+i)->du2, (pEqu+i)->dy);
      }
    }



    // ----- Passo 4. Eliminação de Gauss ----- //
    printf("\n\n// ----- Passo 4. Eliminacao de Gauss ----- //");
    //pivot = Equ[0].du0
    pivot = (pEqu+0)->du0;

    //M21 = Equ[1].du0 / pivot
    M21 = (pEqu+1)->du0 / pivot;

    //M31 = Equ[2].du0 / pivot
    M31 = (pEqu+2)->du0 / pivot;

    /*
    Equ[1].du0 = Equ[1].du0 - (Equ[0].du0 * M21)
    Equ[1].du1 = Equ[1].du1 - (Equ[0].du1 * M21)
    Equ[1].du2 = Equ[1].du2 - (Equ[0].du2 * M21)
    Equ[1].dy  = Equ[1].dy  - (Equ[0].dy  * M21)

    Equ[2].du0 = Equ[2].du0 - (Equ[0].du0 * M31)
    Equ[2].du1 = Equ[2].du1 - (Equ[0].du1 * M31)
    Equ[2].du2 = Equ[2].du2 - (Equ[0].du2 * M31)
    Equ[2].dy  = Equ[2].dy  - (Equ[0].dy  * M31)
    */

    (pEqu+1)->du0 = (pEqu+1)->du0 - ((pEqu+0)->du0 * M21);
    (pEqu+1)->du1 = (pEqu+1)->du1 - ((pEqu+0)->du1 * M21);
    (pEqu+1)->dy  = (pEqu+1)->dy  - ((pEqu+0)->dy  * M21);
    if(tfunc == 1){
      (pEqu+1)->du2 = (pEqu+1)->du2 - ((pEqu+0)->du2 * M21);

      (pEqu+2)->du0 = (pEqu+2)->du0 - ((pEqu+0)->du0 * M31);
      (pEqu+2)->du1 = (pEqu+2)->du1 - ((pEqu+0)->du1 * M31);
      (pEqu+2)->du2 = (pEqu+2)->du2 - ((pEqu+0)->du2 * M31);
      (pEqu+2)->dy  = (pEqu+2)->dy  - ((pEqu+0)->dy  * M31);
    }

    //Exibindo tabela
    printf("\npivot: %.3f", pivot);
    printf("\nM21: %.3f", M21);
    if(tfunc == 0){
      printf("\ndu0\tdu1\tdy");
      for (i = 0; i < 2; i++)
      {
        printf("\n%.3f\t %.3f\t %.3f", (pEqu+i)->du0, (pEqu+i)->du1, (pEqu+i)->dy);
      }
    }else{
      printf("\nM31: %.3f", M31);
      printf("\ndu0\tdu1\tdu2\tdy");
      for (i = 0; i < 3; i++)
      {
        printf("\n%.3f\t %.3f\t %.3f\t %.3f", (pEqu+i)->du0, (pEqu+i)->du1, (pEqu+i)->du2, (pEqu+i)->dy);
      }
    }

    if (tfunc == 1)
    {
      //pivot = Equ[1].du1
      pivot = (pEqu+1)->du1;

      //M32 = Equ[2].du1 / pivot
      M32 = (pEqu+2)->du1 / pivot;

      /*
      Equ[2].du0 = Equ[2].du0 - (Equ[1].du0 * M32)
      Equ[2].du1 = Equ[2].du1 - (Equ[1].du1 * M32)
      Equ[2].du2 = Equ[2].du2 - (Equ[1].du2 * M32)
      Equ[2].dy  = Equ[2].dy  - (Equ[1].dy  * M32)
      */
      (pEqu+2)->du0 = (pEqu+2)->du0 - ((pEqu+1)->du0 * M32);
      (pEqu+2)->du1 = (pEqu+2)->du1 - ((pEqu+1)->du1 * M32);
      (pEqu+2)->du2 = (pEqu+2)->du2 - ((pEqu+1)->du2 * M32);
      (pEqu+2)->dy  = (pEqu+2)->dy  - ((pEqu+1)->dy  * M32);
      
      ///Exibindo tabela
      printf("\n\npivot: %.3f", pivot);
      printf("\nM32: %.3f", M32);
      printf("\ndu0\tdu1\tdu2\tdy");
      for (i = 0; i < 3; i++)
      {
        printf("\n%.3f\t %.3f\t %.3f\t %.3f", (pEqu+i)->du0, (pEqu+i)->du1, (pEqu+i)->du2, (pEqu+i)->dy);
      }
    }


    // ----- Passo 5. Substituir os valores ----- //
    printf("\n\n// ----- Passo 5. Substituir os valores ----- //");
    //a2 = Equ[2].dy / Equ[2].du2
    //a1 = (Equ[1].dy - (Equ[1].du2 * a2)) / Equ[1].du1
    //a0 = (Equ[0].dy - (Equ[0].du2 * a2) - (Equ[0].du1 * a1)) / Equ[0].du0

    if (tfunc == 0)
    {
      a1 = (pEqu+1)->dy / (pEqu+1)->du1;
      a0 = ((pEqu+0)->dy - ((pEqu+0)->du1 * a1)) / (pEqu+0)->du0;
    }else{
      a2 = (pEqu+2)->dy / (pEqu+2)->du2;
      a1 = ((pEqu+1)->dy - ((pEqu+1)->du2 * a2)) / (pEqu+1)->du1;
      a0 = ((pEqu+0)->dy - ((pEqu+0)->du2 * a2) - ((pEqu+0)->du1 * a1)) / (pEqu+0)->du0;
    }
    if(tfunc == 0){
      printf("\na0\ta1");
      printf("\n%.3f\t%.3f", a0, a1);
    }else{
      printf("\na0\ta1\ta2");
      printf("\n%.3f\t%.3f\t%.3f", a0, a1, a2);
    }



    //  ----- Passo 6. Construir a função ----- //
    printf("\n\n//  ----- Passo 6. Construir a funcao ----- //");
    //"p(x) = "+a2+"x² + "+a1+"x + "=a0

    //printf("p(x) = %.3fx^2 + %.3fx + %.3f", a2, a1, a0);
    if(tfunc == 0){
      printf("\np(x) = %.3fx ", a1);
    }else{
      printf("\np(x) = %.3fx^2 ", a2);
      if (a1 < 0) printf("%.3fx ", a1); else printf("+%.3fx ", a1);
    }
    if (a0 < 0) printf("%.3f", a0); else printf("+%.3f", a0);



    do
    {
      printf("\n\nDeseja executar novamente? [s/n]: ");
      scanf("%c", &dnv);
    } while (dnv != 's' && dnv != 'S' && dnv != 'n' && dnv != 'N');
    system("CLS");
  }while (dnv == 's' || dnv == 'S');

  printf("\n\n");
  return 0;
}

// ------------------------- Funções ------------------------------ //

void alocaMMQ(MMQ **p, int m)
{
  if ((*p = (MMQ *)realloc(*p, m * sizeof(MMQ))) == NULL)
  {
    printf("\nErro na alocacao. O programa sera encerrado!");
    exit(1);
  }
}

void alocaVet(Vet **p, int m)
{
  if ((*p = (Vet *)realloc(*p, m * sizeof(Vet))) == NULL)
  {
    printf("\nErro na alocacao. O programa sera encerrado!");
    exit(1);
  }
}

void alocaEqu(Equ **p)
{
  if ((*p = (Equ *)realloc(*p, 3 * sizeof(Equ))) == NULL)
  {
    printf("\nErro na alocacao. O programa sera encerrado!");
    exit(1);
  }
}

// ------------------------- To Do List --------------------------- //
/*
Processamento:
  "Passo 1. Construir os vetores"
  Receber os pontos:
    Receber o numero de pontos (n)
    Loop (For i=n):
      Receber os pontos no formato [x y]
  Receber o tipo de função:
    Receber tfunc 0 (Reta), 1 (Parábola)
  
  "Passo 2. Montar o sistema escalar"
    Loop (for i=n)
      MMQ[i] = [yi  xi^0  xi^1  xi^2]

  "Passo 3. Reescrever o sistema de equações"
    Se (tfunc == 0)
      kmax = 2
    Se (tfunc == 1)
      kmax = 3

    Iniciar a struct Equ com zeros
      Loop (for k=kmax)
        Equ[k].du0 = 0
        Equ[k].du1 = 0
        Equ[k].du2 = 0
        Equ[k].dy  = 0

    Loop (for i=n)
      Se (tfunc == 0)
        Equ[0].du0 += MMQ[i].u0 * MMQ[i].u0
        Equ[0].du1 += MMQ[i].u0 * MMQ[i].u1
        Equ[0].dy  += MMQ[i].u0 * MMQ[i].y

        Equ[1].du0 += MMQ[i].u1 * MMQ[i].u0
        Equ[1].du1 += MMQ[i].u1 * MMQ[i].u1
        Equ[1].dy  += MMQ[i].u1 * MMQ[i].y

      Se (tfunc == 1)
        Equ[0].du0 += MMQ[i].u0 * MMQ[i].u0
        Equ[0].du1 += MMQ[i].u0 * MMQ[i].u1
        Equ[0].du2 += MMQ[i].u0 * MMQ[i].u2
        Equ[0].dy  += MMQ[i].u0 * MMQ[i].y

        Equ[1].du0 += MMQ[i].u1 * MMQ[i].u0
        Equ[1].du1 += MMQ[i].u1 * MMQ[i].u1
        Equ[1].du2 += MMQ[i].u1 * MMQ[i].u2
        Equ[1].dy  += MMQ[i].u1 * MMQ[i].y

        Equ[2].du0 += MMQ[i].u2 * MMQ[i].u0
        Equ[2].du1 += MMQ[i].u2 * MMQ[i].u1
        Equ[2].du2 += MMQ[i].u2 * MMQ[i].u2
        Equ[2].dy  += MMQ[i].u2 * MMQ[i].y

  "Passo 4. Eliminação de Gauss"
    pivot = Equ[0].du0
    M21 = Equ[1].du0 / pivot
    M31 = Equ[2].du0 / pivot

    Equ[1].du0 = Equ[1].du0 - (Equ[0].du0 * M21)
    Equ[1].du1 = Equ[1].du1 - (Equ[0].du1 * M21)
    Equ[1].du2 = Equ[1].du2 - (Equ[0].du2 * M21)
    Equ[1].dy  = Equ[1].dy  - (Equ[0].dy  * M21)

    Equ[2].du0 = Equ[2].du0 - (Equ[0].du0 * M31)
    Equ[2].du1 = Equ[2].du1 - (Equ[0].du1 * M31)
    Equ[2].du2 = Equ[2].du2 - (Equ[0].du2 * M31)
    Equ[2].dy  = Equ[2].dy  - (Equ[0].dy  * M31)

    pivot = Equ[1].du1
    M32 = Equ[2].du1 / pivot

    Equ[2].du0 = Equ[2].du0 - (Equ[1].du0 * M32)
    Equ[2].du1 = Equ[2].du1 - (Equ[1].du1 * M32)
    Equ[2].du2 = Equ[2].du2 - (Equ[1].du2 * M32)
    Equ[2].dy  = Equ[2].dy  - (Equ[1].dy  * M32)

  "Passo 5. Substituir os valores"
    a2 = Equ[2].dy / Equ[2].du2
    a1 = (Equ[1].dy - (Equ[1].du2 * a2)) / Equ[1].du1
    a0 = (Equ[0].dy - (Equ[0].du2 * a2) - (Equ[0].du1 * a1)) / Equ[0].du0

  "Passo 6. Construir a função"
    "p(x) = "+a2+"x² + "+a1+"x + "=a0
*/