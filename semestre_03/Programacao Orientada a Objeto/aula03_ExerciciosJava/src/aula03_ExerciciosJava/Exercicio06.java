/**
 * Aluno: Gabriel Van Loon nº 103.917.07
 */
package aula03_ExerciciosJava;

import java.io.IOException;

public class Exercicio06 {

	public static void main(String[] args) throws IOException {
		double  min = 0, max = 0, temp = 0;
		boolean firstN = true;
		
		System.out.print("Entre com um valor (0 para sair): ");
		temp = EntradaTeclado.leDouble();
		while(temp != 0) {
			
			if(firstN) {
				min = max = temp;
				firstN = false;
			}
			
			if(temp < min) {
				min = temp;
			}
			
			if(temp > max) {
				max = temp;
			}
			
			System.out.print("Entre com um valor (0 para sair): ");
			temp = EntradaTeclado.leDouble();
		}
		
		System.out.print("\n");
		System.out.printf("O maior numero enviado foi: %.3f.\n", max);
		System.out.printf("O menor numero enviado foi: %.3f.\n", min);
	}

}
