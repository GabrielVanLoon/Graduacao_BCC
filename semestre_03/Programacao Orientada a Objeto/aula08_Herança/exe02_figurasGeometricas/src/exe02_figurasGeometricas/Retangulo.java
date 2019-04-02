package exe02_figurasGeometricas;

/**
 * Classe que implementa as caracterísicas de um Retângulo
 * @author gabriel
 *
 */
public class Retangulo extends FiguraGeometrica {
	private double base;
	private double altura;
	
	public Retangulo() {
		// Construtor vazio
	}
	
	public Retangulo(double base, double altura, String corRGB, boolean isFill) {
		super(corRGB,isFill);
		this.base   = base;
		this.altura = altura;
	}
	
	@Override
	public double area() {
		return (base * altura);
	}
	
	@Override
	public double perimetro() {
		return (2.0 * base) + (2.0 * altura);
	}

	public double getBase() {
		return base;
	}

	public void setBase(double base) {
		this.base = base;
	}

	public double getAltura() {
		return altura;
	}

	public void setAltura(double altura) {
		this.altura = altura;
	}

	
}
