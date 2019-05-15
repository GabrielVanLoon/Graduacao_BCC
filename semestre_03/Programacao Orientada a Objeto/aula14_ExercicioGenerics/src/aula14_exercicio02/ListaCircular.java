package aula14_exercicio02;

/**
 * Classe que implementa uma lista circular estática de elementos genéricos.
 * @author gabriel van loon
 *
 * @param <T>
 */
public class ListaCircular<T> {
	
	private static int capacidadeMaxima = 10;
	
	private T[] lista;
	private int qtdElementos;
	private int ini;
	private int fim;
	
	/**
	 * Estância de um novo objeto do tipo ListaCircular
	 */
	@SuppressWarnings("unchecked")
	public ListaCircular() {
		this.lista = (T[]) new Object[ListaCircular.capacidadeMaxima];
		this.qtdElementos = 0;
		this.ini  = 0;
		this.fim  = 0;
	}
	
	/**
	 * Insere um novo elemento no inicio da Lista
	 * @param e
	 * @return true se inserido, false caso lista esteja cheia.
	 */
	boolean inserirInicio(T e) {
		if(this.qtdElementos == ListaCircular.capacidadeMaxima) {
			return false;
		
		} else if(this.qtdElementos == 0) {
			this.fim = 0;
			this.ini = 0;
			
			this.lista[0] = e;
			this.qtdElementos += 1;
		} else {
			int novoIni = (ini-1 >= 0) ? (ini-1) : ListaCircular.capacidadeMaxima-1;
			this.lista[novoIni] = e;
			this.qtdElementos += 1;
			this.ini = novoIni;
		}
		return true;
	}
	
	/**
	 * Insere um novo elemento no final da Lista
	 * @param e
	 * @return true se inserido, falso caso lista esteja cheia.
	 */
	boolean inserirFim(T e) {
		if(this.qtdElementos == ListaCircular.capacidadeMaxima) {
			return false;
		
		} else if(this.qtdElementos == 0) {
			this.fim = 0;
			this.ini = 0;
			this.lista[0] = e;
			this.qtdElementos += 1;
		
		} else {
			int novoFim = (fim+1 < ListaCircular.capacidadeMaxima) ? (fim+1) : 0;
			this.fim = novoFim;
			this.lista[novoFim] = e;
			this.qtdElementos += 1;
		}
		return true;
	}
	
	/**
	 * Remove e retorna o primeiro elemento da lista. Em caso de erro
	 * devolve um ponteiro apontando para null;
	 * @return 
	 */
	T removerPrimeiroElemento() {
		T elem = null;
		if(this.qtdElementos == 0) {
			return elem;
		
		} else if(this.qtdElementos == 1) {
			elem = this.lista[this.ini];
			this.lista[this.ini] = null;
			this.qtdElementos -= 1;
		} else {
			elem = this.lista[this.ini];
			this.lista[this.ini] = null;
			int novoIni = (ini+1 < ListaCircular.capacidadeMaxima) ? ini+1 : 0;
			this.ini = novoIni;
			this.qtdElementos -= 1;
		}
		return elem;
	}
	
	/**
	 * Remove e retorna o ultimo elemento da lista. Em caso de erro
	 * devolve um ponteiro apontando para null;
	 * @return 
	 */
	T removerUltimoElemento() {
		T elem = null;
		if(this.qtdElementos == 0) {
			return elem;
		
		} else if(this.qtdElementos == 1) {
			elem = this.lista[this.ini];
			this.lista[this.ini] = null;
			this.qtdElementos -= 1;
		
		} else {
			elem = this.lista[this.fim];
			this.lista[this.fim] = null;
			int novoFim = (fim-1 >= 0) ? fim-1 : ListaCircular.capacidadeMaxima-1;
			this.fim = novoFim;
			this.qtdElementos -= 1;
		}
		return elem;
	}
	
	/**
	 * Função que exibe a indexação de cada elemento na lista.
	 *
	public void exibirLista() {
		System.out.println("Inicio: " + this.ini);
		System.out.println("Fim: " + this.fim);
		for(int i = 0; i < ListaCircular.capacidadeMaxima; i++) {
			if(this.lista[i] == null)
				System.out.println("[" + i + "] -> NULO");
			else
				System.out.println("[" + i + "] -> " + this.lista[i]);
		}
	} */
	
	/**
	 * Retorna a capacidade máxima da lista.
	 * @return
	 */
	public static int capacidade() {
		return ListaCircular.capacidadeMaxima;
	}
	
}
