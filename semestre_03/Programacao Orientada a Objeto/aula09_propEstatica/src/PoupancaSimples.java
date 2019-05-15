/**
 * Representa uma conta poupança simples com taxa de rend. de 1.0
 * @author 10391607
 *
 */
public class PoupancaSimples extends ContaPoupanca {
	
	private static double rendimento = 1.0;
	
	public PoupancaSimples(String nome, int diaVencimento) {
		super(nome, diaVencimento);
	}
	
	@Override
	public void atualiza(double taxa) {
		double s = getSaldo();
		setSaldo(s * (taxa + PoupancaSimples.rendimento));
	}
	
	/**
	 * getter para visualizar a taxa dessa conta
	 * @return
	 */
	public static double getRendimento() {
		return rendimento;
	}

}

