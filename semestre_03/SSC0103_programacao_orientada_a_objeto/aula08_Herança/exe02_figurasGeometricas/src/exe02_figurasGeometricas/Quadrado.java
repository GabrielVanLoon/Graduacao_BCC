package exe02_figurasGeometricas;

/**
 * Classe que implementa as caracterísicas de um Quadrado
 * @author gabriel
 *
 */
public class Quadrado extends FiguraGeometrica {
	private double lado;
	
	public Quadrado() {
		// Construtor vazio
	}
	
	public Quadrado(double lado, String corRGB, boolean isFill) {
		super(corRGB,isFill);
		this.lado = lado;
	}
	
	@Override
	public double area() {
		return (lado * lado);
	}
	
	@Override
	public double perimetro() {
		return (4.0 * lado);
	}

	public double getLado() {
		return lado;
	}

	public void setLado(double lado) {
		this.lado = lado;
	}
	
}
