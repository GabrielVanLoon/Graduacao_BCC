/**
 * Representa uma conta poupança gold com taxa de rend. de 1.5
 * @author 10391607
 *
 */
public class PoupancaOuro extends ContaPoupanca {
	
	private static double rendimento = 1.5;
	
	public PoupancaOuro(String nome, int diaVencimento) {
		super(nome, diaVencimento);
	}

	
	@Override
	public void atualiza(double taxa) {
		double s = getSaldo();
		setSaldo(s * (taxa + PoupancaOuro.rendimento));
	}
	
	/**
	 * getter para visualizar a taxa dessa conta
	 * @return
	 */
	public static double getRendimento() {
		return rendimento;
	}

}
