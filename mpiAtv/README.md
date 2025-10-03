# Exercício MPI: Soma de Quadrados com Validação

## Feito Por:
- Marco Antonio de Camargo - 10418309
- Natan Moreira Passos - 10417916
- Nicolas Henriques de Almeida - 10418357 <br> <br>
Sala 06G - Mackenzie

## Objetivo
implementar um programa em **C com MPI** que calcula a soma dos quadrados dos números de 1 a 40 de forma paralela. Ao final, o programa deverá comparar o resultado obtido com o resultado sequencial esperado, validando a execução paralela..<br>

---
## Funcionamento
1. Ambiente MPI é inicializado
2. Numeros de 1 a 40 são colocados em um vetor de tamanho 40
3. Vetor é dividido em partes iguais e cada parte é enviada para um processo diferente
4. Cada processo calcula a soma, um a um, dos quadrados dos valores no vetor
5. Somas são somadas
7. Processo raiz compara a soma das somas ao resultado obtido utilizando a formula 
8. Processo raiz diz se ambas são ou não iguais 
```math
\sum_{i=1}^{N} i^2 = \frac{N(N+1)(2N+1)}{6}
```
8. Processo raiz imprime o resultado
---
## Compilação e execução
### Compilar o código
- **Usando makefile:** 
```bash 
make calc
```
- Isso criará o executável `soma_quadrados`.

- **Usando mpicc manualmente:**
``` bash
mpicc -o soma_quadrados soma_quadrados.c
```
- Isso criará o executável `soma_quadrados`.

### Execução
``` bash
mpirun -np <Numero de Processos> ./soma_quadrados
```
---
