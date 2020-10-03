package exe02_figurasGeometricas;

/**
 * Classe que define os atributos e métodos padrões de uma figura geométrica.
 * @author Gabriel Van Loon
 */
public class FiguraGeometrica {
	private String	color;
	private boolean filled;
	
	public FiguraGeometrica() {
		// Construtor vazio
	}
	
	public FiguraGeometrica(String corRGB, boolean isFill) {
		this.color  = corRGB;
		this.filled = isFill;
	}
	
	public double area() {
		return 0;
	}
	
	public double perimetro() {
		return 0;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}

	public boolean isFilled() {
		return filled;
	}

	public void setFilled(boolean filled) {
		this.filled = filled;
	}
	
}
