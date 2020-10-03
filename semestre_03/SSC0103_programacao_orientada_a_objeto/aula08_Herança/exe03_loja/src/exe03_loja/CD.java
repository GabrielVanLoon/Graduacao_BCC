package exe03_loja;

public class CD extends Produto {
	private String artista;
	private String genero;
	
	/**
	 * Construtor padrão da classe CD
	 * @param nome
	 * @param preco
	 * @param quantidade
	 * @param codigoBarras
	 * @param genero
	 * @param autor
	 */
	public CD(String nome, double preco, int quantidade,  boolean[] codigoBarras,
			  String genero, String autor) {
		super(nome, preco, quantidade, codigoBarras);
		this.genero = genero;
		this.artista  = autor;
	}
	
	@Override
	public String toString() {
		String str = "\n\tCATEGORIA: CD's"; 
		
		str += super.toString();
		str += "\n\tARTISTA: " + this.artista;
		str += "\n\tGENERO: " + this.genero;
		
		
		
		return str;
	}
	
	public String getArtista() {
		return artista;
	}

	public void setArtista(String autor) {
		this.artista = autor;
	}

	public String getGenero() {
		return genero;
	}

	public void setGenero(String genero) {
		this.genero = genero;
	}
	
}
