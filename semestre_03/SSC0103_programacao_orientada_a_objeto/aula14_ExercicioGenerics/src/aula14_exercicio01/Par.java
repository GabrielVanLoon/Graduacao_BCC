package aula14_exercicio01;

/**
 * Implementa uma Classe que representa um par de dados.
 * @author gabriel van loon
 *
 * @param <K> classe do 1º dado
 * @param <V> classe do 2º dado
 */
public class Par<K,V> {
		
	private K chave;
	private V valor;
	
	/**
	 * Construtor padrão do tipo Par()
	 * @param chave
	 * @param valor
	 */
	public Par(K chave, V valor) {
		this.chave = chave;
		this.valor = valor;
	}
	
	public K getChave() {
		return chave;
	}

	public void setChave(K chave) {
		this.chave = chave;
	}

	public V getValor() {
		return valor;
	}

	public void setValor(V valor) {
		this.valor = valor;
	}
	
	@Override
	public String toString() {
		return "[" + this.chave + "]" + " ->" + this.valor;
	}
	
}
