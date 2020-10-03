package exe03_loja;

import java.io.IOException;

public class Main {
	
	public static void main(String[] args) throws IOException {
		Loja l = new Loja();
		
		/**
		 * Cadastrando os produtos na loja
		 */
		CD[] cds = new CD[4];
		cds[0] = new CD("Cantigas de Bar", 23.99, 12, Produto.gerarCodigoBarra(), "Sertanejo", "Maraiara e Maiaraisa");
		cds[1] = new CD("Sing All Night Long", 90.99, 33, Produto.gerarCodigoBarra(), "Pop/Rock", "DJ TechTonik");
		cds[2] = new CD("Poemas da Meia Noite", 27.99, 4, Produto.gerarCodigoBarra(), "Rap", "Mc Marcon");
		cds[3] = new CD("Single Warsongs", 55.95, 23, Produto.gerarCodigoBarra(), "Rock Acústico", "Arkhangels");
		
		DVD[] dvds = new DVD[4];
		dvds[0] = new DVD("Velozes e Furiosos 13", 19.99, 2, Produto.gerarCodigoBarra(), "Ação/Aventura", "Hajid J. Connor");
		dvds[1] = new DVD("Forever Dreams", 5.79, 1, Produto.gerarCodigoBarra(), "Mistério", "Phillip J. J. Kristens");
		dvds[2] = new DVD("Projeto Y", 29.99, 60, Produto.gerarCodigoBarra(), "Comédia", "Felipe H. Guerra");
		dvds[3] = new DVD("Purple Code - Missão Nebrasca", 19.99, 5, Produto.gerarCodigoBarra(), "Ação/Aventura", "Christian O. Reilly");
		
		Livro[] livros = new Livro[4];
		livros[0] = new Livro("Under the Sea", 39.99, 18, Produto.gerarCodigoBarra(), "Romance/Mistério", "Alice Campos");
		livros[1] = new Livro("Antologia Poética de Pinheiros vol. II", 89.99, 4, Produto.gerarCodigoBarra(), "Poesia", "Diva V. L. Dourado");
		livros[2] = new Livro("Black Glove", 35.50, 2, Produto.gerarCodigoBarra(), "Ação/Aventura", "Rick V. Jefferson");
		livros[3] = new Livro("A Guilda dos Licantrôpos", 12.99, 11, Produto.gerarCodigoBarra(), "Ficção e Fantasia", "Gabriel Van loon");
		
		for(int i = 0; i < 4; i++) {
			l.adicionarProduto(cds[i]);
			l.adicionarProduto(dvds[i]);
			l.adicionarProduto(livros[i]);
		}
		
		/**
		 * Exibe o estoque inicial e também a listagem dos produtos disponíveis para compra
		 */
		l.mostrarEstoque(true);
		
		
		/**
		 * Loop em que o usuário pode entrar com quais produtos deseja comprar.
		 * Também mostra, conforme as compras, o andamento do caixa da loja.
		 */
		String barcode    = "  ";
		int    quantidade = 0;
		
		while(barcode.charAt(0) != 'x') {
			try {
				System.out.println("\n\tEntre com o código de barras e a quantidade. Digite 'x' caso queira sair "
									+ "ou 'e' para mostrar novamente a listagem de produtos");
				
				System.out.print("\tCódigo de barras: ");
				barcode = EntradaTeclado.leString();
				
				if(barcode.trim().charAt(0) == 'x')
					break;
				
				if(barcode.trim().charAt(0) == 'e') {
					System.out.println();
					l.mostrarEstoque(true);
					continue;
				}
					
				
				System.out.print("\tQuantidade: ");
				quantidade = EntradaTeclado.leInt();
				
				Produto p = l.buscarProduto(Produto.boolCodigoBarra(barcode));
				
				if(p != null && p.getQuantidade() >= quantidade) {
					
					System.out.println("\n\tVENDIDO " + quantidade + " UNIDADE. DE " + p.getNome() + " POR R$" + 
										String.format("%.2f", p.getPreco() * quantidade));
					
					l.venderProduto(barcode, quantidade);
					
					System.out.print("\n\tESTOQUE ATUALIZADO... ");
					l.mostrarEstoque(false);
					
				} else {
					System.out.println("\n\tPRODUTO NÃO ENCONTRADO OU ESTOQUE INSUFICIENTE");
				}
			} catch(Exception e) {
				// try catch mudinho
			}
		}
		
		System.exit(0);
	}
}
