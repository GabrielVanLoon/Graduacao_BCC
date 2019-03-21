import java.util.Calendar;

public class Random {
	
	private long p = 2147483648L;
	private long m = 843314861L;
	private long a = 453816693L;
	
	private long xi = 1023L; // Semente do Random
	
	public Random(){
		xi = Calendar.getInstance().getTimeInMillis();
	}
	
	public Random(int k){
		xi = k;
	}
	
	/* public double getRand()
	 * - Gera um numero aleatorio x, tal que [0 <= x < 1]
	 */
	public double getRand(){
		xi = (a + (m * xi)) % p;
		return  Math.abs((xi /((double) p)));
	}
	
	/* public  getIntRand(int max)
	 * - Gera um numero aleatorio x, tal que [0 <= x <= (max-1)]
	 */
	public int getIntRand(int max){
		return ((int) (max * getRand()));
	}
	
	/* public  getIntRand(int max)
	 * - Gera um numero aleatorio x, tal que [0 <= x <= (maxInt)]
	 */
	public int getIntRand(){
		return this.getIntRand(Integer.MAX_VALUE);
	}
	
	/* public  getIntRand(int max)
	 * - Gera um numero aleatorio x, tal que [min <= x <= (max-1)]
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
