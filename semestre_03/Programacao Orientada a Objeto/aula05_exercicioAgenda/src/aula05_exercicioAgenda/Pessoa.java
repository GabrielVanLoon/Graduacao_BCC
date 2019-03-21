package aula05_exercicioAgenda;

/**
 * A classe abstrai dados básicos de uma pessoa comum. Tem como objetivo
 * facilitar a manipulação desses dados em outras aplicações.
 * 
 * @author Gabriel Van Loon
 *
 */
public class Pessoa {
	private String 	nome;
	private int 	idade;
	private double	altura;
	
	public Pessoa() {}
	
	public Pessoa(String nome, int idade, double altura) {
		this.nome = nome;
		this.idade = idade;
		this.altura = altura;
	}
	
	/**
	 * Imprime na tela os dados do objeto.
	 */
	public void imprimirDados() {
		System.out.printf("Nome: %s, %d anos e %.2fm de altura.\n", this.nome, this.idade, this.altura);
		// System.out.println("Nome: " + this.nome + ", " + this.idade + " anos e " + this.altura + "m de altura.");
	}
	
	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public int getIdade() {
		return idade;
	}

	public void setIdade(int idade) {
		this.idade = idade;
	}

	public double getAltura() {
		return altura;
	}

	public void setAltura(double altura) {
		this.altura = altura;
	}
	
	
}
