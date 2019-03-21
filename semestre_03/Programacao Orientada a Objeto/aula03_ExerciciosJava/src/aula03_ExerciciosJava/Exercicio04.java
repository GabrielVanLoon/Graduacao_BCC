/**
 * Aluno: Gabriel Van Loon nº 103.917.07
 */
package aula03_ExerciciosJava;

import java.io.IOException;

public class Exercicio04 {

	public static void main(String[] args) throws IOException {
		System.out.print("Entre com um número inteiro: ");
		int		n 		     = EntradaTeclado.leInt();
		int 	menorDivisor = 0;
		boolean	ehPrimo      = true;
		
		for(int i = 2; i < n/2; i++) {
			if(n % i == 0) {
				ehPrimo 	 = false;
				menorDivisor = i;
				break;
			}
		}
		
		if(ehPrimo) {
			System.out.printf("O número é um primo.\n");
		} else {
			System.out.printf("O número não é um primo e seu menor divisor é %d.\n", menorDivisor);
		}
	}

}
