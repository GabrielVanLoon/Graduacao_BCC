/**
 * Essa classe foi criada para simular o jogador em uma mesa de poker.
 * 
 * @author Alberto Campos Neves - 10819033
 * @author Gabriel Van Loon - 10391607
 */

import java.util.Arrays;

public class Jogador {
	private int     creditos;
	private int     maxCartas;
	private Carta[] cartas;
	
	public Jogador() {
		maxCartas = 5;
		creditos = 200;
		cartas = new Carta[maxCartas];
	}
	/**
	 * Recebe os creditos ganhados na aposta.
	 * @param p
	 */
	public void receberCreditos (int p) {
		this.creditos += p;
	}
	
	/**
	 * Aposta qtd creditos.
	 * @param qtd
	 * @return
	 */
	public int apostarCreditos (int qtd) {
		if(qtd < 0) {
			return -1;
		}
		int qtdApostada = (qtd > this.creditos) ? this.creditos : qtd;
		this.creditos   -= qtdApostada;
		return qtdApostada;
	}
	
	/**
	 * Retorna um conjunto de 5 cartas ao usuario.
	 * @param b
	 */
	public void comprarMao(Baralho b) {
		for (int i = 0; i < maxCartas; i++) {
			cartas[i] = b.draw();
		}
	}
	
	/**
	 * Descarta as cartas escolhidas pelo usuario
	 * @param b
	 */
	public void descartarMao(Baralho b) {
		for (int i = maxCartas-1; i >= 0 ; i--) {
			 b.descartar(cartas[i]);
			 cartas[i] = null;
		}
	}
	
	/**
	 * Recebe a posicao pos da carta que o usuario deseja trocar.
	 * @param b
	 * @param pos
	 */
	public void trocarCarta(Baralho b, int pos) {
		Carta c = cartas[pos];
		b.descartar(c);
		cartas[pos] = b.draw();
	}
	
	/**
	 * Recebe  as posicoes das cartas que o usuario deseja trocar.
	 * @param b
	 * @param pos
	 */
	public void trocarCarta(Baralho b, boolean[] pos) {
		//Troca a(s) carta(s) que o jogador deseja descartar
		for (int i = 0; i < maxCartas; i++) {
			if (pos[i]) {
				trocarCarta (b, i);
			}
		}
	}
	
	/**
	 * Recebe as posicao das cartas que o usuario deseja trocar.
	 * @param b
	 * @param s
	 */
	public void trocarCarta(Baralho b, String s) {
		 boolean[] pos = new boolean[maxCartas];
		 String[] inteiros = s.split(" ");
		 Arrays.fill(pos, false);
		 
		 for (int i = 0; i < inteiros.length; i++) {
			 try {
				 int p = Integer.parseInt(inteiros[i]);
				 if (p <= maxCartas && p > 0) {
					 pos[p-1] = true;
				 }
			 } catch (Exception e) {
				 
			 }
		 }
		 
		 trocarCarta(b, pos);
	}
	
	/**
	 * Mostra ao usuario as cartas que estao em sua mao.
	 */
	public void mostrarMao() {
		
		String strLinha = "+----------+";
	
		String[] strLinha1 = new String[15];
		strLinha1[2]  = "|2         |";
		strLinha1[3]  = "|3         |";
		strLinha1[4]  = "|4         |";
		strLinha1[5]  = "|5         |";
		strLinha1[6]  = "|6         |";
		strLinha1[7]  = "|7         |";
		strLinha1[8]  = "|8         |";
		strLinha1[9]  = "|9         |";
		strLinha1[10] = "|10        |";
		strLinha1[11] = "|11        |";
		strLinha1[12] = "|12        |";
		strLinha1[13] = "|13        |";
		strLinha1[14]  = "|A         |";
		
		String[] strLinha3 = new String[15];
		strLinha3[2]  = "|  2   de  |";
		strLinha3[3]  = "|  3   de  |";
		strLinha3[4]  = "|  4   de  |";
		strLinha3[5]  = "|  5   de  |";
		strLinha3[6]  = "|  6   de  |";
		strLinha3[7]  = "|  7   de  |";
		strLinha3[8]  = "|  8   de  |";
		strLinha3[9]  = "|  9   de  |";
		strLinha3[10] = "|  10  de  |";
		strLinha3[11] = "|  Valete  |";
		strLinha3[12] = "|  Dama    |";
		strLinha3[13] = "|  Rei de  |";
		strLinha3[14] = "|  Ás  de  |";
		
		String[] strLinha4 = new String[4];
		strLinha4[0]  = "|  Copas   |";
		strLinha4[1]  = "|  Espadas |";
		strLinha4[2]  = "|  Ouros   |";
		strLinha4[3]  = "|  Paus    |";
	
		String[] strLinha6 = new String[15];
		strLinha6[2]  = "|         2|";
		strLinha6[3]  = "|         3|";
		strLinha6[4]  = "|         4|";
		strLinha6[5]  = "|         5|";
		strLinha6[6]  = "|         6|";
		strLinha6[7]  = "|         7|";
		strLinha6[8]  = "|         8|";
		strLinha6[9]  = "|         9|";
		strLinha6[10] = "|        10|";
		strLinha6[11] = "|        11|";
		strLinha6[12] = "|        12|";
		strLinha6[13] = "|        13|";
		strLinha6[14]  = "|         A|";
		
		String[] strPrint = new String[8];
		
		for(int i = 0; i < 8; i++) {
			strPrint[i] = "";
		}
		
		for(int i = 0; i < cartas.length ; i++) {
			Carta c = cartas[i];
			
			strPrint[0] += ("\t" +  strLinha);
			strPrint[1] += ("\t" +  strLinha1[c.getNumero()]);
			strPrint[2] += ("\t" + "|"+ c.getNaipeChar() +"         |");
			strPrint[3] += ("\t" +  strLinha3[c.getNumero()]);
			strPrint[4] += ("\t" +  strLinha4[c.getNaipe()]);
			strPrint[5] += ("\t" + "|         "+ c.getNaipeChar() +"|");
			strPrint[6] += ("\t" + strLinha6[c.getNumero()]);
			strPrint[7] += ("\t" + strLinha);
		}
		
		for(int i = 0; i < 8; i++) {
			System.out.println(strPrint[i]);
		}
		
	}
	
	public int getCreditos() {
		return creditos;
	}

	public void setCreditos(int creditos) {
		this.creditos = creditos;
	}
	
	public Carta[] getCartas() {
		return this.cartas;
	}
	
}
