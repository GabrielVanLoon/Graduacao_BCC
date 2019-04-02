/**
 * Essa classe foi criada para simular um baralho.
 * 
 * @author Alberto Campos Neves - 10819033
 * @author Gabriel Van Loon - 10391607
 */

import java.util.ArrayList;

public class Baralho {
	private Random r;
	private ArrayList<Carta> monte;
	private ArrayList<Carta> descarte;
	
	public Baralho() {
		this.r         = new Random();
		this.monte     = new ArrayList<Carta>();
		this.descarte  = new ArrayList<Carta>();
		
		for (int i = 0; i < 4; i++) { //Naipe
			for (int j = 2; j < 15; j++) { //Numero
				Carta c = new Carta(j, i);
				monte.add(c);
			}
		}
	}
	
	/**
	 * Retira uma carta c do monte e a retorna para o usuario.
	 * @return c
	 */
	public Carta draw() {
		int pos = r.getIntRand(monte.size(), 0);
		Carta c = monte.get(pos);
		monte.remove(pos);
		return c;
	}
	
	/**
	 * Adiciona a carta c ao monte de descarte.
	 * @param c
	 */
	public void descartar(Carta c) {
		this.descarte.add(c);
	}
	
	/**
	 * Retorna ao usuario se o monte esta vazio.
	 * @return
	 */
	public boolean monteVazio() {
		return this.monte.isEmpty();
	}
	
	/**
	 * Reinsere as carta descartadas ao monte.
	 */
	public void reset() {
		while(!descarte.isEmpty()) {
			Carta c = descarte.get(0);
			descarte.remove(0);
			monte.add(c);
		}
	}
}
