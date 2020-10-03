package aula05_ExercicioElevador;

/**
 * A classe implementa as funções básicas de um elevador, dando a possibilidade
 * de inserir ou remover pessoas e também de movimentar o mesmo entre os andares.
 * 
 * @author Gabriel Van Loon
 *
 */
public class Elevador {
	private int andarMax = 0;
	private int andarAtual = 0;
	private int capacidadeMax = 0;
	private int capacidadeAtual = 0;
	
	public Elevador(int capacidadeMax, int andarMax) {
		this.andarMax = andarMax;
		this.capacidadeMax = capacidadeMax;
	}
	
	/**
	 * Entra uma pessoa no elevador. Caso já esteja lotado, imprime uma
	 * mensagem de aviso.
	 */
	public void entra() {
		if(this.capacidadeAtual+1 > this.capacidadeMax) {
			System.out.println("Não cabe mais pessoas no elevador!");
		} else {
			this.capacidadeAtual += 1;
		}
	}
	
	/**
	 * Sai uma pessoa do elevador. Caso já esteja vazio, imprime uma
	 * mensagem de aviso.
	 */
	public void sai() {
		if(this.capacidadeAtual == 0) {
			System.out.println("Não há mais ningúem para sair.");
		} else {
			this.capacidadeAtual -= 1;
		}
	}
	
	/**
	 * O elevador sobe um andar. Caso ele já esteja no último antes,
	 * imprime uma mensagem de aviso.
	 */
	public void sobe() {
		if(this.andarAtual == this.andarMax) {
			System.out.println("O elevador já esta no último andar.");
		} else {
			this.andarAtual += 1;
		}
	}
	
	/**
	 * O elevaor desce um andar. Caso ele já esteja no térreo, imprime
	 * uma mensagem de aviso.
	 */
	public void desce() {
		if(this.andarAtual == 0) {
			System.out.println("O elevador já esta no térreo.");
		} else {
			this.andarAtual -= 1;
		}
	}
	
	public int getAndarMax() {
		return andarMax;
	}

	public void setAndarMax(int andarMax) {
		this.andarMax = andarMax;
	}

	public int getAndarAtual() {
		return andarAtual;
	}

	public void setAndarAtual(int andarAtual) {
		this.andarAtual = andarAtual;
	}

	public int getCapacidadeMax() {
		return capacidadeMax;
	}

	public void setCapacidadeMax(int capacidadeMax) {
		this.capacidadeMax = capacidadeMax;
	}

	public int getCapacidadeAtual() {
		return capacidadeAtual;
	}

	public void setCapacidadeAtual(int capacidadeAtual) {
		this.capacidadeAtual = capacidadeAtual;
	}
	
}
