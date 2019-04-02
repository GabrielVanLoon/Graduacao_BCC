package exe02_figurasGeometricas;

/**
 * Classe que implementa as caracterísicas de um Círculo.
 * @author gabriel
 *
 */
public class Circulo extends FiguraGeometrica {
	private double raio;
	
	public Circulo() {
		// Construtor vazio
	}
	
	public Circulo(double raio, String corRGB, boolean isFill) {
		super(corRGB,isFill);
		this.raio = raio;
	}
	
	@Override
	public double area() {
		return (Math.PI * raio * raio);
	}
	
	@Override
	public double perimetro() {
		return (2.0 * Math.PI * raio);
	}

	public double getRaio() {
		return raio;
	}

	public void setRaio(double raio) {
		this.raio = raio;
	}
	
} 
