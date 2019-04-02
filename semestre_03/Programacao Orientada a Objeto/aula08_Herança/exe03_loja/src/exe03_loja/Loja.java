package exe03_loja;

import java.util.ArrayList;

public class Loja {
	private ArrayList<Produto> 	estoque;
	private int				 	totalEstoque;
	private double				caixa;
	
	/**
	 * Construtor padrão da classe Loja
	 */
	public Loja() {
		this.estoque = new ArrayList<Produto>();
		this.caixa   = 0.0;
		this.totalEstoque = 0;
	}
	
	/**
	 * Dado o nome de um produto retorna sua posição no estoque ou -1 
	 * caso não seja encontrado.
	 * @param nome
	 * @return
	 */
	public int indexOf(String nome) {
		nome = nome.trim();
		for(int i = 0; i < estoque.size(); i++) {
			if(estoque.get(i).getNome().equals(nome))
				return i;
		}
		return -1;
	}
	
	/**
	 * Dado o codigo de barras de um produto retorna sua posição no estoque 
	 * ou -1 caso não seja encontrado.
	 * @param nome
	 * @return
	 */
	public int indexOf(boolean[] codigoBarras) {
		for(int i = 0; i < estoque.size(); i++) {
			if(estoque.get(i).equalsBarcode(codigoBarras))
				return i;
		}
		return -1;
	}
	
	/**
	 * Adiciona um novo produto no estoque. Não faz verificações de conflito
	 * de código de barra.
	 * @param p
	 */
	public void adicionarProduto(Produto p) {
		if(p == null) throw new IllegalArgumentException("Parâmetros inválidos!");
		this.estoque.add(p);
		this.totalEstoque += p.getQuantidade();
	}
	
	/**
	 * Busca um produto no estoque pelo seu nome e o retorna.
	 * @param nome
	 * @return
	 */
	public Produto buscarProduto(String nome) {
		int index = this.indexOf(nome);
		return (index >= 0) ? estoque.get(index) : null;
	}
	
	/**
	 * Busca um produto no estoque pelo seu codigo de barras e o retorna.
	 * @param nome
	 * @return
	 */
	public Produto buscarProduto(boolean[] codigoBarras) {
		int index = this.indexOf(codigoBarras);
		return (index >= 0) ? estoque.get(index) : null;
	}
	
	/**
	 * Realiza a venda de um produto no estoque, identificado pelo seu
	 * código de barras. Caso o produto não existe ou não haja estoque
	 * suficiente do mesmo retorna uma mensagem de erro.
	 * @param codigoBarras
	 * @param quantidade
	 */
	public void venderProduto(boolean[] codigoBarras, int quantidade) {
		Produto p = this.buscarProduto(codigoBarras);
		
		if(p == null) {
			System.out.println("O produto não consta no nosso estoque!");
			return;
		
		} else if(p.getQuantidade() < quantidade) {
			System.out.println("Não há estoque suficiente do produto!");
			return;
		}
		
		// Atualizando o caixa e a quantidade do produto
		p.setQuantidade(p.getQuantidade() - quantidade);
		this.caixa += quantidade * p.getPreco();
		this.totalEstoque -= quantidade;
	}
	
	/**
	 * Recebe um código de barras amigável do usuário, converte para seu
	 * array análogo e chama a função venderProduto(boolean[], int).
	 * @param barcode
	 * @param quantidade
	 */
	public void venderProduto(String barcode, int quantidade) {
		boolean[] codigoBarras = Produto.boolCodigoBarra(barcode);
		venderProduto(codigoBarras, quantidade);
	}
	
	/**
	 * Mostra a situação atual da loja, sendo possível escolher entre exibir ou não
	 * os produtos atuais do estoque.
	 * @param mostrarProdutos
	 */
	public void mostrarEstoque(boolean mostrarProdutos) {
		System.out.println("\tQTD. TOTAL DE PRODUTOS: " + estoque.size() + " produtos.");
		System.out.println("\tQTD. ATUAL DE ESTOQUE:  " + this.totalEstoque + " peças.");
		System.out.println("\tCAIXA ATUAL DA EMPRESA: R$" +  String.format("%.2f", this.caixa)   + ".");
		
		if(mostrarProdutos) {
			System.out.println();
			System.out.print("\tPRODUTOS:");
			for(Produto p : this.estoque) 
				System.out.println(p);
		}
		
	}
	
	/**
	 * Mostra a situação atual da loja mas não mostra o estoque.
	 * @param mostrarProdutos
	 */
	public void mostrarEstoque() {
		mostrarEstoque(false);
	}
	
}
