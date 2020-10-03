import java.util.Calendar;

public class Random {
	
	private long p = 2147483648L;
	private long m = 843314861;
	private long a = 453816693;
		
	private long xi = 1023; // essa eh a semente
	
	public double getRand() {
		
		xi = (a + m * xi) % p;
		
		double d = xi; // promove para double;
		return d/p;
	}
	public int getIntRand(int max) {
		double valor = getRand() * max;
		return (int) valor;
		
	}
	public int getIntRand (int max, int min) {
		if (max <= min) {
			throw new
				IllegalArgumentException("Parametros invalidos");
		}
		return min + getIntRand (max-min);
	}
	public int getIntRand () {
		return getIntRand(Integer.MAX_VALUE);
	}
	
	public void setSemente(int semente) {
		xi = semente;
	}
	
	public Random(){
		xi = Calendar.getInstance().getTimeInMillis();
	}
	
	public Random(int k){
		xi = k;
	}
	
	@Override
    public String toString()
    {
     return xi + "";
    }

	

}
