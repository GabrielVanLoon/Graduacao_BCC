package exe03_loja;
import java.util.Random;

public class Produto {
	private static int tamCodigoBarras = 10;
	
	private String    nome;
	private double    preco;
	private int       quantidade;
	private boolean[] codigoBarras;
	
	/**
	 * Função auxiliar que gera uma sequencia de true ou falses que representa
	 * um código de barras de um produto.
	 * @return
	 */
	public static boolean[] gerarCodigoBarra() {
		boolean[] cb = new boolean[tamCodigoBarras];
		Random    r  = new Random();
		
		for(int i = 0; i < tamCodigoBarras; i++) 
			cb[i] = r.nextBoolean();
		return cb;
	}
	
	/**
	 * Transforma o vetor booleano em uma string apresentável para o usuário.
	 * @param barcode
	 * @return
	 */
	public static String strCodigoBarra(boolean[] barcode) {
		String str = "";
		for(int i = 0; i < barcode.length; i++) 
			str += (barcode[i]) ? "▮" : "▯";
		return str;
	}
	
	/**
	 * Transforma a string amigável do código de barras em seu vetor correspondente.
	 * @param barcode
	 * @return
	 */
	public static boolean[] boolCodigoBarra(String barcode) {
		barcode = barcode.trim();
		boolean[] codigoBarra = new boolean[barcode.length()];
		for(int i = 0; i < barcode.length(); i++) 
			codigoBarra[i] = (barcode.charAt(i) == '1' || barcode.charAt(i) == '▮') ? true : false;
		return codigoBarra;
	}
	
	/**
	 * Construtor padrão de um Produto
	 * @param nome
	 * @param preco
	 * @param quantidade
	 * @param codigoBarras
	 */
	public Produto(String nome, double preco, int quantidade, boolean[] codigoBarras) {
		this.nome       = nome;
		this.preco      = preco;
		this.quantidade = quantidade;
		this.codigoBarras = codigoBarras;
	}
	
	/**
	 * Retorna true se o código de barras do produto for igual ao do param.
	 * @param barcode
	 * @return
	 */
	public boolean equalsBarcode(boolean[] barcode) {
		if(barcode.length != Produto.tamCodigoBarras) return false;
		for(int i = 0; i < Produto.tamCodigoBarras; i++) {
			if(this.codigoBarras[i] != barcode[i])
				return false;
		}
		return true;
	}
	
	@Override
	public String toString() {
		String str = "";
		
		str += "\n\tNOME: "  + this.nome;
		str += "\n\tPREÇO: R$" + String.format("%.2f", this.preco);
		str += "\n\tQUANTIDADE: " + this.quantidade;
		str += "\n\tCODIGO DE BARRAS: " + Produto.strCodigoBarra(this.getCodigoBarras());
		
		return str;
	}
	
	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public double getPreco() {
		return preco;
	}

	public void setPreco(double preco) {
		this.preco = preco;
	}

	public int getQuantidade() {
		return quantidade;
	}

	public void setQuantidade(int quantidade) {
		this.quantidade = quantidade;
	}

	public boolean[] getCodigoBarras() {
		return codigoBarras;
	}

	public void setCodigoBarras(boolean[] codigoBarras) {
		this.codigoBarras = codigoBarras;
	}
	
}