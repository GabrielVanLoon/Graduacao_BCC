/**
 * Aluno: Gabriel Van Loon nº 103.917.07
 */
package aula03_ExerciciosJava;

import java.io.IOException;

public class Exercicio05 {

	public static void main(String[] args) throws IOException {
		
		System.out.print("Entre com um numero inteiro: ");
		int n = EntradaTeclado.leInt();
		
		if(n == 2) {
			System.out.print("Não ha numeros primos menores do que o numero 2.\n");
		} else {
			
			boolean[] numeros = new boolean[n];
			
			// Setando todos os numeros
			// true - ehPrimo | false - naoEhPrimo
			for(int i = 0; i < n; i++) {
				numeros[i] = true;
			}
			
			// Marcando os não primos
			for(int i = 2; i < n; i++) {
				if(numeros[i] == false) continue;
				for(int j = i+i; j < n; j = j+i) {
					numeros[j] = false;
				}
			}
			
			// Buscando o menor primo abaixo de N
			for(int i = n-1; i > 1; i--) {
				if(numeros[i] == true) {
					System.out.printf("Primeiro numero primo menor: %d.", i);
					break;
				}
			}
		}
	}

}
