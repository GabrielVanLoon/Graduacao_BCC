/**
 * Representa uma conta bancária genérica.
 * @author delamaro
 *
 */
public abstract class ContaBancaria {
	
	private static int proxNumConta = 1300071;
	
	private String  nomeCliente;
	private int     numConta;
	private double  saldo;
	
	/**
	 * Construtor. Cria uma conta com saldo 0
	 * @param n Nome do titular da conta
	 * @param num Numero atribuído à conta
	 */
	public ContaBancaria(String n) {
		nomeCliente = n;
		saldo       = 0.0;
		numConta    = ContaBancaria.proxNumConta;
		ContaBancaria.proxNumConta += 3;
	} 
	
	/**
	 * Realiza um saque da conta. Caso não haja saldo executa um throw
	 * @param qto
	 * @throws IllegalArgumentException
	 */
	public void saca(double qto) throws IllegalArgumentException {
		if ( saldo < qto) 
			throw new IllegalArgumentException("Saldo insuficiente para esse saque");
		saldo -= qto;
	}
	
	/**
	 * Realiza um depósito na conta.
	 * @param qto
	 */
	public void deposita(double qto) {
		saldo += qto;
	}
	
	/**
	 * Função utilizada por Contas que possuem taxa de 
	 * rendimento em cima do saldo atual.
	 */
	public abstract void atualiza(double taxa);
	
	/**
	 * Obtem o nome do titular da conta.
	 * @return Nome do titular da conta.
	 */
	public String getNomeCliente() {
		return nomeCliente;
	}

	public void setNomeCliente(String nomeCliente) {
		this.nomeCliente = nomeCliente;
	}

	public int getNumConta() {
		return numConta;
	}

	public void setNumConta(int numConta) {
		this.numConta = numConta;
	}

	public double getSaldo() {
		return saldo;
	}
	
	protected void setSaldo(double s){
		this.saldo = s;
	}
	
}
