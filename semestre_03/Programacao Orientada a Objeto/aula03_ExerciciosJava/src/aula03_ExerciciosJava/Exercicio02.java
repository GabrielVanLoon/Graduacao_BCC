/**
 * Aluno: Gabriel Van Loon nº 103.917.07
 */
package aula03_ExerciciosJava;

import java.io.IOException;

public class Exercicio02 {

	public static void main(String[] args) throws IOException {	
		System.out.print("Entre com um número inteiro: ");
		int n = EntradaTeclado.leInt();
		
		for(int i = n; i > 0; i--) {
			for(int j = 0; j < i; j++) {
				System.out.print("*");
			} 
			System.out.print("\n");
		}
	}

}
