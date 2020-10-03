/**
 * A classe mesa simula uma típica mesa de um jogo de poker. 
 * Sua funcao eh receber as cartas que o jogador possui e verificar 
 * se existe nelas alguma combinacao.
 * 
 * @author Alberto Campos Neves - 10819033
 * @author Gabriel Van Loon - 10391607
 */

import java.util.Arrays;

public class Mesa {
	private int maxCartas;
	
	public Mesa() {
		maxCartas = 5;
	}
	
	/**
	 * Retorna o mult da combinacao realizada pelo usuario.
	 * @param c
	 * @return
	 */
	public int aposta(Carta[] c) {
		int   mult = 0;
		//vetor com os numeros das cartas
		int[] n    = new int[c.length];
		for (int i = 0; i < n.length; i++) {
			n[i] = c[i].getNumero();
		}
		
		Arrays.sort(n);
		
		mult = checkStraightFlush (c, n);
		
		if (checkSequenciaNum(n) > mult) {
			mult = checkSequenciaNum(n);
		}
		
		return mult;
	}
	
	/**
	 * Checa se o usuario tem uma das seguintes combinacoes:
	 * Royal Straight Flush
	 * Straight Flush
	 * Flush
	 * Straight
	 * @param c
	 * @param n
	 * @return
	 */
	public int checkStraightFlush (Carta[] c, int[] n) {
		boolean flush    = true; //Naipes iguais
		boolean straight = true; //Sequencia crescente de numeros
		
		
		for (int i = 1; i < c.length; i++) {
			if (c[i-1].getNaipe() != c[i].getNaipe()) {
				flush = false;
			}
		}
		
		
		for (int i = 1; i < n.length; i++) {
			if (n[i-1] != (n[i]-1)) {
				straight = false;
			}
		}
		
		if (straight && flush) {
			//Royal Straight Flush
			if (n[0] == 10) {
				return 200;
			}
			//Straight Flush
			return 100;
		
		} else {
			//Flush
			if (flush) {
				return 10;
			}
			//Straight
			else if (straight) {
				return 5;
			}
			//Nenhuma combinacao
			return 0;
		}
	}
	
	/**
	 * Checa se o usuario tem uma das seguintes sequencias:
	 * Quadra
	 * Full Hand
	 * Trinca
	 * Dois pares 
	 * @param n
	 * @return
	 */
	public int checkSequenciaNum (int[]n) {
		boolean par  = false;
		boolean trinca = false;
		
		int[] iguais = new int[maxCartas];
		int numero = n[0];
		int j = 0; //posicao do array de numeros iguais
		iguais[j]++;
		
		for (int i = 1; i < maxCartas; i++) {
			if (n[i] == numero) {
				iguais[j]++;
			}
			else {
				numero = n[i];
				j++;
				iguais[j]++;
			}
		}
		for (int i = 0; i < maxCartas; i++) {
			//Quadra
			if (iguais[i] == 4) {
				return 50;
			} 
			else if (iguais[i] == 3) {
				//Full Hand
				if (par) {
					return 20;
				}
				trinca = true;
			}
			else if (iguais[i] == 2) {
				//Dois pares
				if (par) {
					return 1;
				}
				//Full Hand
				else if (trinca) {
					return 20;
				}
				par = true;
			}
		}
		if (trinca) {
			return 2;
		}
		return 0;
	}
	
	/**
	 * Retorna o nome da combinacao feita pelo jogador.
	 * @param mult
	 * @return
	 */
	public String strCombinacao(int mult) {
		switch (mult) {
			case 1: return ("Dois Pares");
			case 2: return ("Trinca");
			case 5: return ("Straight");
			case 10: return ("Flush");
			case 20: return ("Full Hand");
			case 50: return ("Quadra");
			case 100: return ("Straight Flush");
			case 200: return ("Royal Straight Flush");
		}
		return " ";
	}
	
}
