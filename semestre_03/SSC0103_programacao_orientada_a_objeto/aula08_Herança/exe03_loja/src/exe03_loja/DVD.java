package exe03_loja;

public class DVD extends Produto {
	private String genero;
	private String diretor;
	
	/**
	 * Construtor padrão da classe DVD
	 * @param nome
	 * @param preco
	 * @param quantidade
	 * @param codigoBarras
	 * @param genero
	 * @param diretor
	 */
	public DVD(String nome, double preco, int quantidade,  boolean[] codigoBarras,
			  String genero, String diretor) {
		super(nome, preco, quantidade, codigoBarras);
		this.genero  = genero;
		this.diretor = diretor;
	}
	
	@Override
	public String toString() {
		String str = "\n\tCATEGORIA: DVD's"; 
		
		str += super.toString();
		str += "\n\tDIRETOR: " + this.diretor;
		str += "\n\tGENERO: " + this.genero;
		return str;
	}
	
	public String getDiretor() {
		return diretor;
	}

	public void setDiretor(String diretor) {
		this.diretor = diretor;
	}

	public String getGenero() {
		return genero;
	}

	public void setGenero(String genero) {
		this.genero = genero;
	}
	
}
