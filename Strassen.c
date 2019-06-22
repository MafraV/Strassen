#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int maior(a, b)
{
  if(a>b) return a;
  return b;
}

void fazer_matricula(char matricula[])
{
  matricula[0] = '1';
  matricula[1] = '6';
  matricula[2] = '2';
  matricula[3] = '1';
  matricula[4] = '0';
  matricula[5] = '8';
  matricula[6] = '5';
  matricula[7] = '3';
}

int** am(int m, int n)
{
  int **v;
  v = (int **) calloc(m, sizeof(int *));
  int i;
  for(i=0; i<n; i++) v[i] = (int *) calloc(n, sizeof(int));

  return v; 
}

int find_potencia(int n1, int m1)
{
  int i;
  for(i=0; i<10; i++)
  {
    int potencia = pow(2, i);
    if(n1<=potencia && m1<=potencia) return potencia;
  }
  return 0;
}

int** addm(int n, int **a, int **b)
{
  int **c, i, j;
  c = am(n, n);
  for(i=0; i<n; i++)
  {
    for(j=0; j<n; j++)
    {
      c[i][j] = a[i][j] + b[i][j];
    }
  }

  return c;
}

int** subm(int n, int **a, int **b)
{
  int **c, i, j;
  c = am(n, n);
  for(i=0; i<n; i++)
  {
    for(j=0; j<n; j++)
    {
      c[i][j] = a[i][j] - b[i][j];
    }
  } 
  return c;
}

int** strassen(int n, int **a, int **b)
{
  if(n==2)
  {
    int a11, a12, a21, a22, b11, b12, b21, b22;
    a11 = a[0][0];
    a12 = a[0][1];
    a21 = a[1][0];
    a22 = a[1][1];
    b11 = b[0][0];
    b12 = b[0][1];
    b21 = b[1][0];
    b22 = b[1][1];

    int s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
    int p1, p2, p3, p4, p5, p6, p7;
    int **c = am(n, n);
    
    s1 = b12-b22;
    s2 = a11+a12;
    s3 = a21+a22;
    s4 = b21-b11;
    s5 = a11+a22;
    s6 = b11+b22;
    s7 = a12-a22;
    s8 = b21+b22;
    s9 = a11-a21;
    s10 = b11+b12;

    p1 = a11*s1;
    p2 = s2*b22;
    p3 = s3*b11;
    p4 = a22*s4;
    p5 = s5*s6;
    p6 = s7*s8;
    p7 = s9*s10;

    c[0][0] = p5+p4-p2+p6;
    c[0][1] = p1+p2;
    c[1][0] = p3+p4;
    c[1][1] = p5+p1-p3-p7;

    return c;
  }

  int **a11, **a12, **a21, **a22, **b11, **b12, **b21, **b22;
  a11 = am(n/2, n/2);
  a12 = am(n/2, n/2);
  a21 = am(n/2, n/2);
  a22 = am(n/2, n/2);
  b11 = am(n/2, n/2);
  b12 = am(n/2, n/2);
  b21 = am(n/2, n/2);
  b22 = am(n/2, n/2);

  int i, j;

  for(i=0; i<n/2; i++) for(j=0; j<n/2; j++) a11[i][j] = a[i][j];
  for(i=0; i<n/2; i++) for(j=n/2; j<n; j++) a12[i][j-(n/2)] = a[i][j];
  for(i=n/2; i<n; i++) for(j=0; j<n/2; j++) a21[i-(n/2)][j] = a[i][j];
  for(i=n/2; i<n; i++) for(j=n/2; j<n; j++) a22[i-(n/2)][j-(n/2)] = a[i][j];
  for(i=0; i<n/2; i++) for(j=0; j<n/2; j++) b11[i][j] = b[i][j];
  for(i=0; i<n/2; i++) for(j=n/2; j<n; j++) b12[i][j-(n/2)] = b[i][j];
  for(i=n/2; i<n; i++) for(j=0; j<n/2; j++) b21[i-(n/2)][j] = b[i][j];
  for(i=n/2; i<n; i++) for(j=n/2; j<n; j++) b22[i-(n/2)][j-(n/2)] = b[i][j];
  
  int **s1, **s2, **s3, **s4, **s5, **s6, **s7, **s8, **s9, **s10;
  int **p1, **p2, **p3, **p4, **p5, **p6, **p7;
  int **c11, **c12, **c21, **c22, **c;

  c = am(n, n);

  s1 = subm(n/2, b12, b22);
  s2 = addm(n/2, a11, a12);
  s3 = addm(n/2, a21, a22);
  s4 = subm(n/2, b21, b11);
  s5 = addm(n/2, a11, a22);
  s6 = addm(n/2, b11, b22);
  s7 = subm(n/2, a12, a22);
  s8 = addm(n/2, b21, b22);
  s9 = subm(n/2, a11, a21);
  s10 = addm(n/2, b11, b12);

  p1 = strassen(n/2, a11, s1);
  p2 = strassen(n/2, s2, b22);
  p3 = strassen(n/2, s3, b11);
  p4 = strassen(n/2, a22, s4);
  p5 = strassen(n/2, s5, s6);
  p6 = strassen(n/2, s7, s8);
  p7 = strassen(n/2, s9, s10);

  c11 = addm(n/2, p5, p4);
  c11 = subm(n/2, c11, p2);
  c11 = addm(n/2, c11, p6);

  c12 = addm(n/2, p1, p2);

  c21 = addm(n/2, p3, p4);

  c22 = addm(n/2, p5, p1);
  c22 = subm(n/2, c22, p3);
  c22 = subm(n/2, c22, p7);

  for(i=0; i<n/2; i++) for(j=0; j<n/2; j++) c[i][j] = c11[i][j];
  for(i=0; i<n/2; i++) for(j=n/2; j<n; j++) c[i][j] = c12[i][j-(n/2)];
  for(i=n/2; i<n; i++) for(j=0; j<n/2; j++) c[i][j] = c21[i-(n/2)][j];
  for(i=n/2; i<n; i++) for(j=n/2; j<n; j++) c[i][j] = c22[i-(n/2)][j-(n/2)];

  return c;
}

int main() 
{
  int n1, m1, n2, m2;
  scanf("%d%d%d%d", &n1, &m1, &n2, &m2);
  int a[n1][m1], b[n2][m2], item, i, j;

  for(i=0; i<n1; i++)
  {
    for(j=0; j<m1; j++)
    {
      scanf("%d", &item);
      a[i][j] = item;
    }
  }

  for(i=0; i<n2; i++)
  {
    for(j=0; j<m2; j++)
    {
      scanf("%d", &item);
      b[i][j] = item;
    }
  }
  
  int potencia1 = find_potencia(n1, m1);
  int potencia2 = find_potencia(n2, m2);
  int potencia = maior(potencia1, potencia2);
  int **a2 = am(potencia, potencia), **b2 = am(potencia, potencia);

  for(i=0; i<n1; i++) for(j=0; j<m1; j++) a2[i][j] = a[i][j];
  for(i=0; i<n2; i++) for(j=0; j<m2; j++) b2[i][j] = b[i][j];

  int **resultado = am(potencia, potencia);
  resultado = strassen(potencia, a2, b2);

  char matricula[8];
  fazer_matricula(matricula);
  
  for(i=0; i<8; i++) printf("%c", matricula[i]);
  printf("\n");

  printf("%d %d\n", n1, m2);

  for(i=0; i<n1; i++)
  {
    for(j=0; j<m2; j++) printf("%d ", resultado[i][j]);
    printf("\n");
  }

  return 0;
}