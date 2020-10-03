/**
 * Aluno: Gabriel Van Loon nº 103.917.07
 */
package aula03_ExerciciosJava;

import java.io.IOException;

public class Exercicios {
	
	/* Exercicio 01 */
	public static void main(String[] args) throws IOException {
		double x, chute, raizX, diff;
		
		System.out.print("Entre com o valor de x:" );
		x 		= EntradaTeclado.leDouble();
		System.out.print("Entre com o chute do valor da raiz de X:" );
		chute	= EntradaTeclado.leDouble();
		
		// Raiz real
		raizX 	= Math.sqrt(x); 
		
		diff = chute - raizX;
		if(diff < 0) {
			diff = - diff;
		}
		
		// Loop para aumentar a precisao
		while(diff > 0.00000001) {
			chute = chute + (x/chute);
			chute = chute/2;
			
			diff = chute - raizX;
			if(diff < 0) {
				diff = - diff;
			}
		}
		
		System.out.printf("Valor aproximado da raiz de x: %f \n", chute );
	}

}
