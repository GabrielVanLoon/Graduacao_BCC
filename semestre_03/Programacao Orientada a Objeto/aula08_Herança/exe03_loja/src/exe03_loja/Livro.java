package exe03_loja;

public class Livro extends Produto {
	private String genero;
	private String autor;
	
	/**
	 * Construtor padrão da classe Livro
	 * @param nome
	 * @param preco
	 * @param quantidade
	 * @param codigoBarras
	 * @param genero
	 * @param autor
	 */
	public Livro(String nome, double preco, int quantidade,  boolean[] codigoBarras,
			  String genero, String autor) {
		super(nome, preco, quantidade, codigoBarras);
		this.genero  = genero;
		this.autor   = autor;
	}
	
	public String toString() {
		String str = "\n\tCATEGORIA: Livros"; 
		
		str += super.toString();
		str += "\n\tAUTOR: " + this.autor;
		str += "\n\tGENERO: " + this.genero;
		return str;
	}
	
	public String getGenero() {
		return genero;
	}

	public void setGenero(String genero) {
		this.genero = genero;
	}

	public String getAutor() {
		return autor;
	}

	public void setAutor(String autor) {
		this.autor = autor;
	}
}
