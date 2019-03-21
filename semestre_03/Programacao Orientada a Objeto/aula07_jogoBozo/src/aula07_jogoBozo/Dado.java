package aula07_jogoBozo;

public class Dado {
	
	private Random r;
	private int    lado;
	
	public Dado() {
		this.r    = new Random();
		this.lado = 1;
	}
	
	public Dado(int l, Random r) {
		this.r    = r;
		this.lado = l;
	}
	
	public int getLado() {
		return this.lado;
	}
	
	public int rolar() {
		this.lado = this.r.getIntRand(1,7);
		return this.lado;
	}
	
	@Override
	public String toString() {
		return ("" + this.getLado());
	}
	
}
