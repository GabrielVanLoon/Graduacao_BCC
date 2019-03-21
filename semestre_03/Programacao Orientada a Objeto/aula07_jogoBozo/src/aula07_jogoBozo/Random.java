package aula07_jogoBozo;

import java.util.Calendar;

public class Random {
	
	private long p = 2147483648L;
	private long m = 843314861;
	private long a = 453816693;
	
	private long xi = 1023; // Semente do Random
	
	public Random(){
		xi = Calendar.getInstance().getTimeInMillis();
	}
	
	public Random(int k){
		xi = k;
	}
	
	/* public double getRand()
	 * - Gera um numero aleatorio, x, entre [0, 0.9999)
	 */
	public double getRand(){
		xi = (a + (m * xi)) % p;
		double d = xi;
		return (d / p);
	}
	
	/* public  getIntRand(int max)
	 * - Gera um numero aleatorio, x, entre [0, max-1]
	 */
	public int getIntRand(int max){
		return ((int) (max * getRand()));
	}
	
	/* public  getIntRand(int max)
	 * - Gera um numero aleatorio, x, entre [0, Integer.MAX_VALUE - 1]
	 */
	public int getIntRand(){
		return this.getIntRand(Integer.MAX_VALUE);
	}
	
	/* public  getIntRand(int max)
	 * - Gera um numero aleatorio, x, entre [min, max-1]
	 */
	public int getIntRand(int min, int max){
		if(max <= min) throw new IllegalArgumentException("Parâmetros inválidos!");
		return (int) (this.getIntRand(max-min) + min);
	}
	
	public void setSemente(int k){
		this.xi = k;
	}
	
	@Override
	public String toString() {
		return (xi + "");
	}
	
}
