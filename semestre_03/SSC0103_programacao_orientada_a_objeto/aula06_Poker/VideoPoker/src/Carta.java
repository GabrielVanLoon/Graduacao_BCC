/**
 * Essa classe foi criada para simular uma carta de baralho.
 * 
 * @author Alberto Campos Neves - 10819033
 * @author Gabriel Van Loon - 10391607
 */

public class Carta {
	private int numero;
	private int naipe;
	
	public Carta(int num, int naipe) {
		this.numero = num;
		this.naipe  = naipe;
	}

	/**
	 * retorna o naipe c da carta.
	 * @return
	 */
	public char getNaipeChar() {
		char c = ' ';
		switch(this.naipe) {
			case 0: c = 'c';
				break;
			case 1: c = 'e';
				break;
			case 2: c = 'o';
				break;
			case 3: c = 'p';
				break;
		}
		return c;
	}
	
	public int getNumero() {
		return numero;
	}

	public void setNumero(int numero) {
		this.numero = numero;
	}
	
	public int getNaipe() {
		return naipe;
	}

	public void setNaipe(int naipe) {
		this.naipe = naipe;
	}
	
	@Override
	public String toString() {
		String str = "n." + this.numero;
		switch(this.naipe) {
			case 0: str += " Copas";
				break;
			case 1: str += " Espadas";
				break;
			case 2: str += " Ouros";
				break;
			case 3: str += " Paus";
				break;
		}
		return str;
	}
}

